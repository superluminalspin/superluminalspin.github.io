package com.cs360.projecttwo_v02;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import androidx.annotation.Nullable;

import java.util.ArrayList;
import java.util.List;

/*
**      Helper function that manages database operations.
*       Inserts, Deletes, and Searches the database for Customers.
*       Uses full-text search for search queries on a virtual table
*       that is created the same time as the regular table and is
*       updated simultaneously.
 */
public class DatabaseHelper extends SQLiteOpenHelper {

    public static final String CUSTOMER_TABLE = "CUSTOMER_TABLE";
    public static final String CUSTOMER_FTS_TABLE = "CUSTOMER_FTS_TABLE";
    public static final String COLUMN_CUSTOMER_NAME = "CUSTOMER_NAME";
    public static final String COLUMN_CUSTOMER_AGE = "CUSTOMER_AGE";
    public static final String COLUMN_ACTIVE_CUSTOMER = "ACTIVE_CUSTOMER";
    public static final String COLUMN_ID = "ID";
    public static final String TAG = "DatabaseHelper";

    public DatabaseHelper(@Nullable Context context) {
        super(context, "customer.db", null, 1);
    }

    // Called first time DB is accessed to create new DB
    @Override
    public void onCreate(SQLiteDatabase db) {
        // Create standard table
        String createTableStatement =
                        "CREATE TABLE "
                        + CUSTOMER_TABLE + " ("
                        + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                        + COLUMN_CUSTOMER_NAME + " TEXT, "
                        + COLUMN_CUSTOMER_AGE + " INT, "
                        + COLUMN_ACTIVE_CUSTOMER + " BOOL)";

        db.execSQL(createTableStatement);

        // Create virtual table for searching
        String createFTSStatement =
                        "CREATE VIRTUAL TABLE "
                        + CUSTOMER_FTS_TABLE + " USING fts4("
                        + COLUMN_CUSTOMER_NAME + ", "
                        + COLUMN_CUSTOMER_AGE + ", "
                        + COLUMN_ACTIVE_CUSTOMER + ")";

        db.execSQL(createFTSStatement);

        // Auto-sync trigger for INSERT operations
        String insertTrigger =
                        "CREATE TRIGGER customer_fts_insert " +
                        "AFTER INSERT ON "
                        + CUSTOMER_TABLE + " " +
                        "BEGIN " +
                        "INSERT INTO "
                        + CUSTOMER_FTS_TABLE + "(rowid, "
                        + COLUMN_CUSTOMER_NAME + ", "
                        + COLUMN_CUSTOMER_AGE + ", "
                        + COLUMN_ACTIVE_CUSTOMER + ") " +
                        "VALUES (NEW."
                        + COLUMN_ID + ", NEW."
                        + COLUMN_CUSTOMER_NAME + ", " +
                        "CAST(NEW."
                        + COLUMN_CUSTOMER_AGE + " AS TEXT), " +
                        "CASE WHEN NEW."
                        + COLUMN_ACTIVE_CUSTOMER + " = 1 THEN 'active' ELSE 'inactive' END);" + "END";

        db.execSQL(insertTrigger);

        // Auto-sync trigger for delete
        String deleteTrigger =
                        "CREATE TRIGGER customer_fts_delete " +
                        "AFTER DELETE ON "
                        + CUSTOMER_TABLE + " " +
                        "BEGIN " +
                        "DELETE FROM "
                        + CUSTOMER_FTS_TABLE + " WHERE rowid = OLD."
                        + COLUMN_ID + "; " + "END";

        db.execSQL(deleteTrigger);
    }

    // called if the db version num changes.
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }


/*
**      METHOD TO ADD ONE CUSTOMER TO THE DATABASE
**      (returns boolean value based on success of insertion action)
*/
    public boolean addOne(CustomerModel customerModel) {

        try (SQLiteDatabase db = this.getWritableDatabase()) {
            ContentValues cv = new ContentValues();
            cv.put(COLUMN_CUSTOMER_NAME, customerModel.getName());
            cv.put(COLUMN_CUSTOMER_AGE, customerModel.getAge());
            cv.put(COLUMN_ACTIVE_CUSTOMER, customerModel.isActive());

            // insert = PRIMARY KEY AUTOINCREMENT
            long insert = db.insert(CUSTOMER_TABLE, null, cv);

            if (insert != -1) {
                Log.d(TAG, "Customer added successfully with ID: " + insert);
                return true;
            } else {
                Log.w(TAG, "Failed to insert customer: " + customerModel.getName());
                return false;
            }

        } catch (Exception e) {
            Log.e(TAG, "Error adding customer: " + customerModel.getName(), e);
            return false;
        }
    }

    // Method to remove one customer from the db based on id
    public boolean deleteOne(CustomerModel customerModel) {
        // find customerModel in the db if it found delete it and return true
        // if it is not found return false
        SQLiteDatabase db = this.getWritableDatabase();

        int rowsDeleted = db.delete(
                CUSTOMER_TABLE, COLUMN_ID + " = ?",
                new String[]{String.valueOf(customerModel.getId())});

        db.close();

        return rowsDeleted > 0;
    }

    // Method to retrieve all table contents and return as a list of CustomerModel objects
    public List<CustomerModel> getEveryone() {

        List<CustomerModel> returnList = new ArrayList<>();
        SQLiteDatabase db = null;
        Cursor cursor = null;

        try {
            // get data from db
            String queryString = "SELECT * FROM " + CUSTOMER_TABLE;

            db = this.getReadableDatabase();

            // get cursor from DB, selection args null
            cursor = db.rawQuery(queryString, null);

            if (cursor.moveToFirst()) {
                // loop through the cursor and create new customer obj and put into return list
                do {
                    int customerID = cursor.getInt(0);
                    String customerName = cursor.getString(1);
                    int customerAge = cursor.getInt(2);
                    // use ternary operator to return boolean 1 = false else true
                    boolean customerActive = (cursor.getInt(3) == 1);

                    CustomerModel newCustomer = new CustomerModel(customerID, customerName, customerAge, customerActive);

                    returnList.add(newCustomer);

                } while (cursor.moveToNext());
                Log.d(TAG, "Retrieved " + returnList.size() + " customers from database");
            } else {
                Log.d(TAG, "No customers found in database");
            }

        } catch (Exception e) {
            Log.e(TAG, "Error retrieving customers from database", e);
        } finally {
            if (cursor != null) {
                cursor.close();
            }
            if (db != null) {
                db.close();
            }
        }

        return returnList;
    }

    // Search function that makes use of full-text search on a virtual table
    // returns an empty list if the search is unsuccessful, or returns a
    // populated list to be displayed via the CustomerAdapter with search
    // results.
    public List<CustomerModel> searchCustomers(String searchQuery) {

        if (searchQuery == null || searchQuery.trim().isEmpty()) {
            Log.w(TAG, "Search query is null or empty");
            return new ArrayList<>();
        }

        SQLiteDatabase db = null;
        Cursor cursor = null;
        List<CustomerModel> customers = new ArrayList<>();

        try {
            db = this.getReadableDatabase();

            String query = "SELECT c.* FROM " + CUSTOMER_TABLE + " c " +
                    "JOIN " + CUSTOMER_FTS_TABLE + " fts ON c." + COLUMN_ID + " = fts.rowid " +
                    "WHERE " + CUSTOMER_FTS_TABLE + " MATCH ? ";

            cursor = db.rawQuery(query, new String[]{searchQuery});

            if (cursor.moveToFirst()) {
                do {
                    CustomerModel customer = new CustomerModel();
                    customer.setId((cursor.getInt(0)));
                    customer.setName(cursor.getString(1));
                    customer.setAge(cursor.getInt(2));
                    customer.setActive(cursor.getInt(3) == 1);
                    customers.add(customer);
                } while (cursor.moveToNext());
                Log.d(TAG, "Search for '" + searchQuery + "' returned " + customers.size() + " results");
            } else {
                Log.d(TAG, "Search for '" + searchQuery + "' returned no results");
            }

        } catch (Exception e) {
            Log.e(TAG, "Error searching customers with query: " + searchQuery, e);
        } finally {
            if (cursor != null) {
                cursor.close();
            }
            if (db != null) {
                db.close();
            }
        }
        return customers;
    }
}

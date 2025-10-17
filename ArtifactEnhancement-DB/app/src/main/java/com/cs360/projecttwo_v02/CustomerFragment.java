package com.cs360.projecttwo_v02;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import com.google.android.material.textfield.TextInputEditText;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.SwitchCompat;
import androidx.fragment.app.Fragment;
import androidx.appcompat.app.AlertDialog;

import java.util.Objects;

/**
 *      Fragment that manages the Add/Remove functionality for Customers.
 *      Automatically updates a listview when objects are added or removed
 *      from the database.
 */
public class CustomerFragment extends Fragment {

    // references to buttons and other controls on the layout
    Button btn_add;
    TextInputEditText et_name, et_age;
    SwitchCompat sw_activeCustomer;
    ListView lv_customerList;

    ArrayAdapter<CustomerModel> customerArrayAdapter;
    DatabaseHelper databaseHelper;


    @Override
    public void onDestroy() {
        super.onDestroy();
        if (databaseHelper != null) {
            databaseHelper.close(); // Close database connection
        }
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_customer, container, false);

        // Initialize views
        initializeViews(view);

        // Initialize database helper if one does not exist
        if (getContext() != null) {
            databaseHelper = new DatabaseHelper(getContext());
            showCustomersOnListView(databaseHelper);
        }

        // Set up button listeners
        setupClickListeners();
        return view;
    }

    private void setupClickListeners() {

        // Add button click listener
        btn_add.setOnClickListener(v -> {
            // return from click if inputs are invalid
            if (!validateInputs()) {
                return;
            }

            try {
                // Customer has default ID of -1, ID set by SQL schema
                CustomerModel customerModel = new CustomerModel(
                        -1,
                        Objects.requireNonNull(et_name.getText()).toString().trim(),
                        Integer.parseInt(Objects.requireNonNull(et_age.getText()).toString().trim()),
                        sw_activeCustomer.isChecked());

                boolean success = databaseHelper.addOne(customerModel);

                // If insertion is successful, output message, clear fields and update list view
                // otherwise, output warning message.
                if (success) {
                    Toast.makeText(
                            getContext(),
                            "Customer added successfully!",
                            Toast.LENGTH_SHORT).show();

                    clearInputFields();

                    showCustomersOnListView(databaseHelper);
                } else {
                    Toast.makeText(
                            getContext(),
                            "Failed to add customer",
                            Toast.LENGTH_SHORT).show();
                }
            } catch (NumberFormatException e) {
                Toast.makeText(
                        getContext(),
                        "Please enter a valid age",
                        Toast.LENGTH_SHORT).show();
            } catch (Exception e) {
                Toast.makeText(
                        getContext(),
                        "Error: " + e.getMessage(),
                        Toast.LENGTH_SHORT).show();
            }
        });


        // Click listener for listview to remove items from db
        lv_customerList.setOnItemClickListener((parent, view, position, id) -> {
            CustomerModel clickedCustomer = (CustomerModel) parent.getItemAtPosition(position);

            // Confirmation dialog for deleting customers from the database
            new AlertDialog.Builder(requireContext())
                    .setTitle("Delete Customer")
                    .setMessage("Are you sure you want to delete " + clickedCustomer.getName() + "?")
                    .setPositiveButton("Delete", (dialog, which) -> {
                        boolean success = databaseHelper.deleteOne(clickedCustomer);
                        if (success) {
                            showCustomersOnListView(databaseHelper);
                            Toast.makeText(
                                    getContext(),
                                    "Deleted " + clickedCustomer.getName(),
                                    Toast.LENGTH_SHORT).show();
                        } else {
                            Toast.makeText(
                                    getContext(),
                                    "Failed to delete customer",
                                    Toast.LENGTH_SHORT).show();
                        }
                    })
                    .setNegativeButton("Cancel", null)
                    .show();
        });
    }

    private void initializeViews(View view) {
        btn_add = view.findViewById(R.id.btn_add);
        et_age = view.findViewById(R.id.et_age);
        et_name = view.findViewById(R.id.et_name);
        sw_activeCustomer = view.findViewById(R.id.sw_activeCustomer);
        lv_customerList = view.findViewById(R.id.lv_customerList);
    }

    // Use customer adapter to display an organized list
    private void showCustomersOnListView(DatabaseHelper databaseHelper) {
        customerArrayAdapter = new CustomerAdapter(requireContext(), databaseHelper.getEveryone());
        lv_customerList.setAdapter(customerArrayAdapter);
    }

    // Function to validate user input, returns true if inputs are valid
    // returns false if fields are empty or aren't in a logical range
    private boolean validateInputs() {
        String name = et_name.getText() != null ? et_name.getText().toString().trim() : "";
        String age = et_age.getText() != null ? et_age.getText().toString().trim() : "";

        if (name.isEmpty()) {
            et_name.setError("Name is required");
            return false;
        }

        if (age.isEmpty()) {
            et_age.setError("Age is required");
            return false;
        }

        try {
            int ageInt = Integer.parseInt(age);
            if (ageInt < 0 || ageInt > 150) {
                et_age.setError("Please enter a valid age (0-150)");
                return false;
            }
        } catch (NumberFormatException e) {
            et_age.setError("Please enter a valid number");
            return false;
        }

        return true;
    }

    // Function that clears all edit text boxes and resets isChecked
    private void clearInputFields() {
        et_name.setText("");
        et_age.setText("");
        sw_activeCustomer.setChecked(false);
    }
}

package com.cs360.projecttwo_v02;

import android.os.Bundle;
import androidx.fragment.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import com.google.android.material.textfield.TextInputEditText;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.util.Log;

/**
 *      Fragment that manages the SEARCH functionality
 *      Allows searching of the Customers database for any field
 */
public class SearchFragment extends Fragment {

    Button btn_search, btn_clear;
    TextInputEditText et_search;
    ListView lv_searchlist;
    ArrayAdapter<CustomerModel> searchArrayAdapter;
    DatabaseHelper databaseHelper;

    public static final String TAG = "SearchFragment";

    public SearchFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (databaseHelper != null) {
            databaseHelper.close(); // Close database connection
        }
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
            View view = inflater.inflate(R.layout.fragment_search, container, false);
            btn_search = view.findViewById(R.id.btn_search);
            btn_clear = view.findViewById(R.id.btn_clear);
            et_search = view.findViewById(R.id.et_search);
            lv_searchlist = view.findViewById(R.id.lv_searchlist);

            databaseHelper = new DatabaseHelper(getContext());

            setupClickListeners();

            return view;
    }

    private void setupClickListeners() {
        btn_search.setOnClickListener(v -> {
            // Get query from edit text box and ensure it isn't null
            // if it is null, set to an empty string
            try {
                String query = et_search.getText() != null ?
                        et_search.getText().toString() : "";

                // Pass query to DB and populate a list and set the adapter
                searchArrayAdapter = new CustomerAdapter(requireContext(), databaseHelper.searchCustomers(query));
                lv_searchlist.setAdapter(searchArrayAdapter);
            } catch (Exception e) {
                Log.e(TAG, "Error during search", e);
            }
        });

        btn_clear.setOnClickListener(v -> {
            // Clear search bar
            et_search.setText("");

            // Clear any populated listview by setting the adapter to null
            lv_searchlist.setAdapter(null);
        });
    }
}
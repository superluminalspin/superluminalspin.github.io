package com.cs360.projecttwo_v02;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import androidx.annotation.NonNull;

import java.util.List;


/*
*       Adapter class that handles the displaying of data.
*       This class is used to bridge data in a list format with the
*       ListView.
 */
public class CustomerAdapter extends ArrayAdapter<CustomerModel> {

    public CustomerAdapter(Context context, List<CustomerModel> customers) {
        super(context, 0, customers);
    }

    @NonNull
    @Override
    // Fills individual TextView objects with data to be displayed in the layout
    public View getView(int position, View convertView, @NonNull ViewGroup parent) {
        CustomerModel customer = getItem(position);

        if (convertView == null) {
            convertView = LayoutInflater.from(getContext())
                    .inflate(R.layout.customer_list_item, parent, false);
        }

        TextView nameText = convertView.findViewById(R.id.customer_name);
        TextView ageText = convertView.findViewById(R.id.customer_age);
        TextView statusText = convertView.findViewById(R.id.customer_status);

        assert customer != null;
        nameText.setText(customer.getName());
        ageText.setText(String.valueOf(customer.getAge()));
        statusText.setText(customer.isActive() ? "Active" : "Inactive"); // Use your actual getter

        return convertView;
    }
}

// FreeCodeCamp.com exercise designed by Shad Sluiter
// https://www.youtube.com/watch?v=312RhjfetP8&t=3522s

package com.cs360.projecttwo_v02;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.fragment.NavHostFragment;
import androidx.navigation.ui.NavigationUI;
import com.google.android.material.bottomnavigation.BottomNavigationView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Get NavHostFragment first, then get NavController from it
        NavHostFragment navHostFragment = (NavHostFragment) getSupportFragmentManager()
                .findFragmentById(R.id.nav_host_fragment);

        if (navHostFragment != null) {
            NavController navController = navHostFragment.getNavController();

            // Get the BottomNavigationView
            BottomNavigationView bottomNav = findViewById(R.id.nav_view);

            // Connect BottomNavigationView with NavController
            NavigationUI.setupWithNavController(bottomNav, navController);
        }
    }
}

package com.myfirstapp.firebase_java_test;

import static androidx.core.content.ContentProviderCompat.requireContext;

import static java.security.AccessController.getContext;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.myfirstapp.firebase_java_test.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    ActivityMainBinding binding;
    String CelestialBody;
    FirebaseDatabase db;
    DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        String[] celestial = getResources().getStringArray(R.array.celestial);
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>(this, R.layout.dropdown_item,celestial);
        binding.autoCompleteTextView.setAdapter(arrayAdapter);



        binding.button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                CelestialBody = binding.autoCompleteTextView.getText().toString();

                if(!CelestialBody.isEmpty()){
                    Celestial celestial = new Celestial(CelestialBody);
                    db = FirebaseDatabase.getInstance();
                    reference = db.getReference("Planet");
                    reference.setValue(CelestialBody).addOnCompleteListener(new OnCompleteListener<Void>() {
                        @Override
                        public void onComplete(@NonNull Task<Void> task) {

                            binding.autoCompleteTextView.setText("");
                            Toast.makeText(MainActivity.this, "Succesfully updated", Toast.LENGTH_SHORT).show();

                        }
                    });
                }

            }
        });
    }
}
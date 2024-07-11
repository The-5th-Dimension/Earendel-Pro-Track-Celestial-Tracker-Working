package com.myfirstapp.firebase_java_test;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.google.android.material.textfield.TextInputLayout;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class Login extends AppCompatActivity {

    FirebaseDatabase db;
    DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Button buttonSwitchPage = findViewById(R.id.login_main);
        TextInputLayout usernameTextInputLayout = findViewById(R.id.textInputLayout);
        TextInputLayout passwordTextInputLayout = findViewById(R.id.password);

        Button registerButton = findViewById(R.id.register);
        TextInputLayout usernameRegisterTextInputLayout = findViewById(R.id.username_register);
        TextInputLayout passwordRegisterTextInputLayout = findViewById(R.id.password_register);

        buttonSwitchPage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Login functionality
                String username = usernameTextInputLayout.getEditText().getText().toString();
                String password = passwordTextInputLayout.getEditText().getText().toString();

                db = FirebaseDatabase.getInstance();
                reference = db.getReference("Users");

                reference.child(username).addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                        if (dataSnapshot.exists() && password.equals(dataSnapshot.getValue(String.class))) {
                            Toast.makeText(Login.this, "Successfully Logged in", Toast.LENGTH_SHORT).show();

                            // Pass the username to MainActivity
                            Intent intent = new Intent(Login.this, MainActivity.class);
                            intent.putExtra("USERNAME", username);
                            startActivity(intent);
                        } else {
                            Toast.makeText(Login.this, "Login failed", Toast.LENGTH_SHORT).show();
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError databaseError) {
                        Toast.makeText(Login.this, "Database error", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });

        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Registration functionality
                String newUsername = usernameRegisterTextInputLayout.getEditText().getText().toString();
                String newPassword = passwordRegisterTextInputLayout.getEditText().getText().toString();

                db = FirebaseDatabase.getInstance();
                reference = db.getReference("Users");

                // Check if the username already exists
                reference.child(newUsername).addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                        if (dataSnapshot.exists()) {
                            Toast.makeText(Login.this, "Username already exists, choose another one.", Toast.LENGTH_SHORT).show();
                        } else {
                            // If username doesn't exist, create a new user
                            reference.child(newUsername).setValue(newPassword);
                            Toast.makeText(Login.this, "Account created successfully", Toast.LENGTH_SHORT).show();
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError databaseError) {
                        Toast.makeText(Login.this, "Database error", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
    }
}

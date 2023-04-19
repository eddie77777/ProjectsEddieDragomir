package com.example.gymcoach;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.*;

public class RegisterActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        TextView redirectButton = findViewById(R.id.redirect_login);
        Button registerButton = findViewById(R.id.button_register);
        EditText usernameInput = findViewById(R.id.input_username);
        EditText passwordInput = findViewById(R.id.input_password);
        EditText confirmInput = findViewById(R.id.input_confirmPassword);

        redirectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(RegisterActivity.this,LoginActivity.class));
            }
        });

        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(usernameInput.length() == 0) {
                    usernameInput.setError("Enter a name");
                }
                else if(passwordInput.length() == 0) {
                    passwordInput.setError("Enter a password");
                }
                else if (!passwordInput.getText().toString().equals(confirmInput.getText().toString())) {
                    confirmInput.setError("Confirmati parola");
                }
                else {
                    startActivity(new Intent(RegisterActivity.this, LoginActivity.class));
                    Toast.makeText(RegisterActivity.this, "Successfully registered", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
package com.example.gymcoach;

import static android.provider.ContactsContract.CommonDataKinds.Website.URL;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.*;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class LoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        TextView redirectButton = findViewById(R.id.redirect_register);
        Button loginButton = findViewById(R.id.button_login);
        EditText usernameInput = findViewById(R.id.input_username);
        EditText passwordInput = findViewById(R.id.input_password);

        redirectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(LoginActivity.this, RegisterActivity.class));
            }
        });

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(usernameInput.length() == 0) {
                    usernameInput.setError("Enter a name");
                }
                else if(passwordInput.length() == 0) {
                    passwordInput.setError("Enter a password");
                }
                else {
                    Retrofit retrofit = new Retrofit.Builder()
                            .baseUrl("http://192.168.100.25:8080/")
                            .addConverterFactory(GsonConverterFactory.create())
                            .build();

                    MyAPICall myAPICall = retrofit.create(MyAPICall.class);

                    Call<List<DataModel>> call = myAPICall.getData();
                    call.enqueue(new Callback<List<DataModel>>() {
                        @Override
                        public void onResponse(Call<List<DataModel>> call, Response<List<DataModel>> response) {
                            //200 refers to OK
                            if(response.code() != 200) {
                                Toast.makeText(LoginActivity.this, "Nu e ok", Toast.LENGTH_SHORT).show();
                                return;
                            }
                            Toast.makeText(LoginActivity.this, response.body().get(0).getUsername(), Toast.LENGTH_SHORT).show();
                        }

                        @Override
                        public void onFailure(Call<List<DataModel>> call, Throwable t) {
                            Toast.makeText(LoginActivity.this, "Fail"+ t.toString(), Toast.LENGTH_SHORT).show();
                        }
                    });
                    startActivity(new Intent(LoginActivity.this, MainActivity.class));
                    //Toast.makeText(LoginActivity.this, "Successfully logged in", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
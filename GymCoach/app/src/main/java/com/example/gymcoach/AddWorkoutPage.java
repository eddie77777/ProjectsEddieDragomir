package com.example.gymcoach;

import android.content.Intent;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputLayout;

import java.util.ArrayList;

public class AddWorkoutPage extends AppCompatActivity {

    ListView listView;
    ArrayList<String> exercises = new ArrayList<>();
    ArrayAdapter myAdapter;
    Integer indexVal;
    String item;

    String[] muscleCategories = {"Da", "Nu", "Poate", "Janes"};
    AutoCompleteTextView autoCompleteTextView;
    ArrayAdapter<String> adapterCategories;


    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.edit_workout);

        EditText editName = findViewById(R.id.edit_name);
        TextInputLayout editCategory = findViewById(R.id.show_category);

        String name = "Not set";
        String category = "Not set";

        Bundle extras = getIntent().getExtras();
        if(extras != null) {
            name = extras.getString("workout_name");
            category = extras.getString("muscle_category");
        }
        editName.setHint(name);
        editCategory.setHint(category);


        Button backBtn = findViewById(R.id.back_btn);
        backBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Intent intent = new Intent(AddWorkoutPage.this, WorkoutsActivity.class);
                intent.putExtra("workout_name", editName.getText());
              //  intent.putExtra("muscle_category", editCategory.getText());
                startActivity(intent);
            }
        });

        Button doneBtn = findViewById(R.id.done_btn);
        doneBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(AddWorkoutPage.this, WorkoutsActivity.class);
                startActivity(intent);
            }
        });

        listView = (ListView) findViewById(R.id.exercises_list);

        //Aici iau exercitii din baza de date
        exercises.add("ex1");
        myAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,exercises);

        listView.setAdapter(myAdapter);



        autoCompleteTextView = findViewById(R.id.auto_complete_text);
        adapterCategories = new ArrayAdapter<String>(this,R.layout.list_item,muscleCategories);
        autoCompleteTextView.setAdapter(adapterCategories);

        autoCompleteTextView.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                String item = parent.getItemAtPosition(position).toString();
                //Aici va trebui sa adaug in baza de date workout nou
                Toast.makeText(getApplicationContext(), "New category: "+item, Toast.LENGTH_SHORT).show();
            }
        });
    }
}

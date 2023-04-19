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

public class EditWorkoutPage extends AppCompatActivity {

    ListView listView;
    ArrayList<String> exercises = new ArrayList<>();
    ArrayAdapter myAdapter;

    EditText exerciseName;
    Button addBtn, editBtn, deleteBtn;

    //String[] muscleCategories = getResources().getStringArray(R.array.muscle_categories);
    //Aici iau grupele de muschi din baza de date
    String[] muscleCategories;
    AutoCompleteTextView autoCompleteTextView;
    ArrayAdapter<String> adapterCategories;

    String nume_copil = "";
    String categorie_copil = "";

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.edit_workout);

        EditText editName = findViewById(R.id.edit_name);
        TextInputLayout editCategory = findViewById(R.id.show_category);

        String name = "Not set";
        String category = "Not set";
        muscleCategories = getResources().getStringArray(R.array.muscle_categories);

       Bundle extras = getIntent().getExtras();
        if(extras != null) {
            name = extras.getString("workout_name");
            category = extras.getString("muscle_category");
            exercises = extras.getStringArrayList("exercises");
        }

        editName.setHint(name);
        editCategory.setHint(category);

        Button backBtn = findViewById(R.id.back_btn);
        backBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Intent intent = new Intent(EditWorkoutPage.this, WorkoutPage.class);
                if(!editName.getText().toString().equals("")) {
                    nume_copil = editName.getText().toString();
                }
                else
                    nume_copil = editName.getHint().toString();
                intent.putExtra("workout_name", nume_copil);
                intent.putExtra("muscle_category", categorie_copil);
                intent.putExtra("exercises", exercises);
                startActivity(intent);
            }
        });


        listView = (ListView) findViewById(R.id.exercises_list);
        //Aici iau exercitii din baza de date
        myAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_single_choice,exercises);
        listView.setAdapter(myAdapter);

        //set selected item
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                exerciseName.setText(exercises.get(i));
            }
        });

        //Dropdown-ul
        autoCompleteTextView = findViewById(R.id.auto_complete_text);
        adapterCategories = new ArrayAdapter<String>(this,R.layout.list_item,muscleCategories);
        autoCompleteTextView.setAdapter(adapterCategories);

        autoCompleteTextView.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                String item = parent.getItemAtPosition(position).toString();
                categorie_copil=item;
                Toast.makeText(getApplicationContext(), "New category: "+item, Toast.LENGTH_SHORT).show();
            }
        });
        Button doneBtn = findViewById(R.id.done_btn);
        doneBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(EditWorkoutPage.this, WorkoutsActivity.class);
                startActivity(intent);
            }
        });


        exerciseName = findViewById(R.id.editExerciseName);
        addBtn = findViewById(R.id.addExercise_btn);
        editBtn = findViewById(R.id.editExercise_btn);
        deleteBtn = findViewById(R.id.deleteExercise_btn);

        addBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                add();
            }
        });

        editBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                update();
            }
        });

        deleteBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                delete();
            }
        });
    }

    //add
    private void add() {
        String exercise_name = exerciseName.getText().toString();
        if(!exercise_name.isEmpty() && exerciseName.length()>0) {
            //add
            myAdapter.add(exercise_name);

            //refresh
            myAdapter.notifyDataSetChanged();
            exerciseName.setText("");
            Toast.makeText(getApplicationContext(), exercise_name + " added", Toast.LENGTH_SHORT).show();
        }
        else
            Toast.makeText(getApplicationContext(), "Nothing to add", Toast.LENGTH_SHORT).show();
    }

    //update
    private void update() {
        String exercise_name = exerciseName.getText().toString();
        //get position of selected item
        int pos = listView.getCheckedItemPosition();

        if(!exercise_name.isEmpty() && exerciseName.length()>0) {

            //remove item
            myAdapter.remove(exercises.get(pos));

            //insert
            myAdapter.insert(exercise_name,pos);

            //refresh
             myAdapter.notifyDataSetChanged();

            Toast.makeText(getApplicationContext(), exercise_name+" updated", Toast.LENGTH_SHORT).show();
        }
        else
            Toast.makeText(getApplicationContext(), "Nothing to update", Toast.LENGTH_SHORT).show();
    }

    private void delete() {
        //get position of selected item
        int pos = listView.getCheckedItemPosition();

        if (pos > -1) {
            //remove
            myAdapter.remove(exercises.get(pos));

            //refresh
            myAdapter.notifyDataSetChanged();
            exerciseName.setText("");
            Toast.makeText(getApplicationContext(), " updated", Toast.LENGTH_SHORT).show();
        } else
            Toast.makeText(getApplicationContext(), "Nothing to delete", Toast.LENGTH_SHORT).show();
    }
}

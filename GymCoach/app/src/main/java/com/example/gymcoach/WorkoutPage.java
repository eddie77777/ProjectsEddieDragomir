package com.example.gymcoach;

import android.content.Intent;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;

public class WorkoutPage extends AppCompatActivity {

    ListView listView;
    ArrayList<String> exercises = new ArrayList<>();
    ArrayAdapter myAdapter;
    Integer indexVal;
    String item;

    ArrayList<String> getExercises()
    {
        return exercises;
    }

    void setExercises(ArrayList<String> exercises)
    {
        this.exercises = exercises;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.page_workout);

        WorkoutRecyclerViewAdapter.RecyclerViewClickListener listener;

        TextView tvName = findViewById(R.id.workout_name);

        String name = "Not set";
        String category = "Not set";
        ArrayList<String> ex;

        Bundle extras = getIntent().getExtras();
        if(extras != null) {
            name = extras.getString("workout_name");
            category = extras.getString("muscle_category");
            exercises = extras.getStringArrayList("exercises");
        }
        tvName.setText(name);

        TextView tvCategory = findViewById(R.id.show_category);
        tvCategory.setText(category);

        final String workout_name = name;
        final String workout_category = category;

        Button backBtn = findViewById(R.id.back_btn);
        backBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(WorkoutPage.this, WorkoutsActivity.class);
                startActivity(intent);
            }
        });


      listView = (ListView) findViewById(R.id.exercises_list);

      //Aici iau exercitii din baza de date
      myAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,exercises);

      listView.setAdapter(myAdapter);

      Button editButton = findViewById(R.id.edit_button);
      editButton.setOnClickListener(new View.OnClickListener() {
          @Override
          public void onClick(View view) {
              Intent intent = new Intent(WorkoutPage.this, EditWorkoutPage.class);
              intent.putExtra("workout_name", workout_name);
              intent.putExtra("muscle_category", workout_category);
              intent.putExtra("exercises", exercises);
              startActivity(intent);
          }
      });
    }
}

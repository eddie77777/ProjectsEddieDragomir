package com.example.gymcoach;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;


public class WorkoutsActivity extends AppCompatActivity {

    ArrayList<String> exercises = new ArrayList<>();
    ArrayList<WorkoutModel> workoutModels = new ArrayList<>();
    /*int[] workoutImage = {R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image,
            R.drawable.workout_image
    };*/
    int workoutImage = R.drawable.workout_image;

    private WorkoutRecyclerViewAdapter.RecyclerViewClickListener listener;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_workouts);
        RecyclerView recyclerView = findViewById(R.id.workoutsList);
      /*  try {
            setUpWorkoutModels2();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }*/
        try {
            setUpWorkoutModels2();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        setOnClickListener();
        /*try {
            TimeUnit.SECONDS.sleep(5);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }*/
        WorkoutRecyclerViewAdapter adapter = new WorkoutRecyclerViewAdapter(this, workoutModels, listener);
        recyclerView.setAdapter(adapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        Button backBtn = findViewById(R.id.back_btn);
        backBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(WorkoutsActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });

        Button addBtn = findViewById(R.id.add_btn);
        addBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(WorkoutsActivity.this, AddWorkoutPage.class);
                startActivity(intent);
            }
        });
    }

    private void setOnClickListener() {
        listener = new WorkoutRecyclerViewAdapter.RecyclerViewClickListener() {
            @Override
            public void onClick(View v, int position) {
                Intent intent = new Intent(getApplicationContext(), WorkoutPage.class);
                intent.putExtra("workout_name", workoutModels.get(position).getWorkoutName());
                intent.putExtra("muscle_category", workoutModels.get(position).getMuscleCategory());
                intent.putExtra("exercises", exercises);
                startActivity(intent);
            }
        };
    }

    private void setUpWorkoutModels() {
        String[] workoutNames = getResources().getStringArray(R.array.workout_names);
        String[] muscleCategories = getResources().getStringArray(R.array.muscle_categories);
        for(int i = 0; i < workoutNames.length; i++) {
            //in workoutModels vor fi luate workout-urile din baza de date cu un select
            workoutModels.add(new WorkoutModel(workoutNames[i], muscleCategories[i],workoutImage));
        }
    }

    private void setUpWorkoutModels2() throws InterruptedException {
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("http://192.168.100.25:8080/")
                .addConverterFactory(GsonConverterFactory.create())
                .build();

        MyAPICall myAPICall = retrofit.create(MyAPICall.class);

        Call<List<WorkoutDataModel>> call = myAPICall.getWorkout();
       // TimeUnit.SECONDS.sleep(5);
        call.enqueue(new Callback<List<WorkoutDataModel>>() {
            @Override
            public void onResponse(Call<List<WorkoutDataModel>> call, Response<List<WorkoutDataModel>> response) {
                //200 refers to OK
                if(response.code() != 200) {
                    Toast.makeText(WorkoutsActivity.this, "Not OK", Toast.LENGTH_SHORT).show();
                    return;
                }
                String[] muscleCategories = getResources().getStringArray(R.array.muscle_categories);
                for(int i=0; i<response.body().size(); i++)
                    workoutModels.add(new WorkoutModel(response.body().get(i).getName(), muscleCategories[i], workoutImage));
                Toast.makeText(WorkoutsActivity.this, response.body().get(0).getName(), Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onFailure(Call<List<WorkoutDataModel>> call, Throwable t) {
                Toast.makeText(WorkoutsActivity.this, "Fail"+ t.toString(), Toast.LENGTH_SHORT).show();
            }
        });
    }
}
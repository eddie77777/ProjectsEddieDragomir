package com.example.gymcoach;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.GET;

public interface MyAPICall {
    @GET("users")
    Call<List<DataModel>> getData();
    @GET("users/52/workouts")
    Call<List<WorkoutDataModel>> getWorkout();
}

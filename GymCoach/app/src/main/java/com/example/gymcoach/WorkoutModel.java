package com.example.gymcoach;

public class WorkoutModel {
     String workoutName;
     String muscleCategory;
     int image;

     public WorkoutModel(String workoutName, String muscleCategory,int image) {
          this.workoutName = workoutName;
          this.muscleCategory = muscleCategory;
          this.image = image;
     }

     public String getWorkoutName() {
          return workoutName;
     }

     public String getMuscleCategory() {
          return muscleCategory;
     }

     public int getImage() {
          return image;
     }
}

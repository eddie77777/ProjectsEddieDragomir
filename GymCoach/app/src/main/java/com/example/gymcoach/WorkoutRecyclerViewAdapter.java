package com.example.gymcoach;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class WorkoutRecyclerViewAdapter extends RecyclerView.Adapter<WorkoutRecyclerViewAdapter.MyViewHolder> {

    Context context;
    ArrayList<WorkoutModel> workoutModels;
    static RecyclerViewClickListener listener;

    public WorkoutRecyclerViewAdapter(Context context, ArrayList<WorkoutModel> workoutModels, RecyclerViewClickListener listener) {
        this.context = context;
        this.workoutModels = workoutModels;
        this.listener = listener;
    }
    @NonNull
    @Override
    public WorkoutRecyclerViewAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        //This is where you inflate the layout (Giving a look to our rows)
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.recyclerview_row, parent, false);
        return new WorkoutRecyclerViewAdapter.MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull WorkoutRecyclerViewAdapter.MyViewHolder holder, int position) {
        //assigning values to the views we created in the recyclerview_row layout file
        //based on the position of the recycler view
        holder.tvName.setText(workoutModels.get(position).getWorkoutName());
        //development idea: here we can change image in order to fit each of muscle category
        holder.iv.setImageResource(workoutModels.get(position).getImage());
        holder.tvCategory.setText(workoutModels.get(position).getMuscleCategory());
    }

    @Override
    public int getItemCount() {
        //the recycler view just wants to know the number of items you want displayed on the phone screen
        return workoutModels.size();
    }

    public interface RecyclerViewClickListener {
        void onClick(View v, int position);
    }

    public static class MyViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        //grabbing the views from our recyclerview_row layout file
        //like in the onCreate method

        ConstraintLayout clRow;
        ImageView iv;
        TextView tvName, tvCategory;

        public MyViewHolder(@NonNull View itemView) {
            super(itemView);

            itemView.setOnClickListener(this);
            iv = itemView.findViewById(R.id.workout_image);
            tvName = itemView.findViewById(R.id.workout_name);
            tvCategory = itemView.findViewById(R.id.workout_category);
            clRow = itemView.findViewById((R.id.clRow));
        }

        @Override
        public void onClick(View view) {
            listener.onClick(view, getAdapterPosition());
        }
    }
}

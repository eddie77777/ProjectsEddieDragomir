package com.example.gymcoach;

import com.google.gson.annotations.SerializedName;

public class DataModel {
    private int userId;
    private boolean active;
    private String password;
    private String username;

    public int getUserId() {
        return userId;
    }

    public boolean isActive() {
        return active;
    }

    public String getPassword() {
        return password;
    }

    public String getUsername() {
        return username;
    }
}

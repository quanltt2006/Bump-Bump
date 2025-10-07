package com.arkanoid.game.model;

public class PowerUp {
    private String type;
    private int durationSeconds;

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }
    public int getDurationSeconds() { return durationSeconds; }
    public void setDurationSeconds(int durationSeconds) { this.durationSeconds = durationSeconds; }
}

package com.arkanoid.game.model;

public class GameState {
    private int score;
    private int lives;
    private int level;

    public int getScore() { return score; }
    public void setScore(int score) { this.score = score; }
    public int getLives() { return lives; }
    public void setLives(int lives) { this.lives = lives; }
    public int getLevel() { return level; }
    public void setLevel(int level) { this.level = level; }
}

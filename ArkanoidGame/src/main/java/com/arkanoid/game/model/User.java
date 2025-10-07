package com.arkanoid.game.model;

public class User {
    private long id;
    private String username;
    private String passwordHash;
    private String email;
    private int coins;
    private int gems;
    private String equippedPaddleId;
    private int highScore;

    public long getId() { return id; }
    public void setId(long id) { this.id = id; }

    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }

    public String getPasswordHash() { return passwordHash; }
    public void setPasswordHash(String passwordHash) { this.passwordHash = passwordHash; }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }

    public int getCoins() { return coins; }
    public void setCoins(int coins) { this.coins = coins; }

    public int getGems() { return gems; }
    public void setGems(int gems) { this.gems = gems; }

    public String getEquippedPaddleId() { return equippedPaddleId; }
    public void setEquippedPaddleId(String equippedPaddleId) { this.equippedPaddleId = equippedPaddleId; }

    public int getHighScore() { return highScore; }
    public void setHighScore(int highScore) { this.highScore = highScore; }
}

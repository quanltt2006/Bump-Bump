package com.arkanoid.game.model;

public class Paddle {
    private String id;
    private String name;
    private double width;
    private double height;
    private int level;
    private int priceCoins;
    private int priceGems;

    public String getId() { return id; }
    public void setId(String id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public double getWidth() { return width; }
    public void setWidth(double width) { this.width = width; }
    public double getHeight() { return height; }
    public void setHeight(double height) { this.height = height; }
    public int getLevel() { return level; }
    public void setLevel(int level) { this.level = level; }
    public int getPriceCoins() { return priceCoins; }
    public void setPriceCoins(int priceCoins) { this.priceCoins = priceCoins; }
    public int getPriceGems() { return priceGems; }
    public void setPriceGems(int priceGems) { this.priceGems = priceGems; }
}

package com.arkanoid.game.model;

public class Item {
    private String id;
    private String name;
    private int priceCoins;
    private int priceGems;

    public String getId() { return id; }
    public void setId(String id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public int getPriceCoins() { return priceCoins; }
    public void setPriceCoins(int priceCoins) { this.priceCoins = priceCoins; }
    public int getPriceGems() { return priceGems; }
    public void setPriceGems(int priceGems) { this.priceGems = priceGems; }
}

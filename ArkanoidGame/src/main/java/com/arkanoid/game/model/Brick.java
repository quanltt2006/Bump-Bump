package com.arkanoid.game.model;

public class Brick {
    private int row;
    private int col;
    private String type;
    private int hitsRequired;

    public int getRow() { return row; }
    public void setRow(int row) { this.row = row; }
    public int getCol() { return col; }
    public void setCol(int col) { this.col = col; }
    public String getType() { return type; }
    public void setType(String type) { this.type = type; }
    public int getHitsRequired() { return hitsRequired; }
    public void setHitsRequired(int hitsRequired) { this.hitsRequired = hitsRequired; }
}

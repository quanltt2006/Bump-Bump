package com.example.arkanoid.entities;

import javafx.geometry.Rectangle2D;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Paddle {
    private final Rectangle view;
    private final double width;
    private final double height;

    public Paddle(double x, double y, double width, double height) {
        this.view = new Rectangle(width, height);
        this.view.setFill(Color.CORNFLOWERBLUE);
        this.view.setArcWidth(10);
        this.view.setArcHeight(10);
        this.view.setTranslateX(x);
        this.view.setTranslateY(y);
        this.width = width;
        this.height = height;
    }

    public Rectangle getView() { return view; }

    public void setX(double x) { view.setTranslateX(x); }
    public void setY(double y) { view.setTranslateY(y); }

    public double getX() { return view.getTranslateX(); }
    public double getY() { return view.getTranslateY(); }

    public Rectangle2D getBounds() {
        return new Rectangle2D(getX() - width/2, getY() - height/2, width, height);
    }
}

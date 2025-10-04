package com.example.arkanoid.entities;

import javafx.geometry.Rectangle2D;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Brick {
    private final Rectangle view;
    private boolean destroyed = false;
    private final int hitPoints;

    public Brick(double x, double y, double width, double height, int hitPoints, Color color) {
        this.view = new Rectangle(width, height, color);
        this.view.setTranslateX(x);
        this.view.setTranslateY(y);
        this.view.setArcWidth(6);
        this.view.setArcHeight(6);
        this.hitPoints = hitPoints;
    }

    public Rectangle getView() { return view; }

    public boolean isDestroyed() { return destroyed; }

    public void hit() {
        if (destroyed) return;
        if (hitPoints <= 1) {
            destroyed = true;
            view.setVisible(false);
        }
        // For scaffold simplicity, ignore multi-HP color changes
    }

    public Rectangle2D getBounds() {
        return new Rectangle2D(view.getTranslateX() - view.getWidth()/2,
                               view.getTranslateY() - view.getHeight()/2,
                               view.getWidth(), view.getHeight());
    }
}

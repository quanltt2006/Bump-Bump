package com.example.arkanoid.entities;

import javafx.geometry.Rectangle2D;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class Ball {
    private final Circle view;
    private double velocityX;
    private double velocityY;

    public Ball(double x, double y, double radius) {
        this.view = new Circle(radius, Color.WHITE);
        this.view.setTranslateX(x);
        this.view.setTranslateY(y);
        this.velocityX = 220.0;
        this.velocityY = -220.0;
    }

    public Circle getView() { return view; }

    public double getX() { return view.getTranslateX(); }
    public double getY() { return view.getTranslateY(); }

    public void setPosition(double x, double y) {
        view.setTranslateX(x);
        view.setTranslateY(y);
    }

    public void setVelocity(double vx, double vy) {
        this.velocityX = vx;
        this.velocityY = vy;
    }

    public double getVelocityX() { return velocityX; }
    public double getVelocityY() { return velocityY; }

    public void update(double dt) {
        view.setTranslateX(view.getTranslateX() + velocityX * dt);
        view.setTranslateY(view.getTranslateY() + velocityY * dt);
    }

    public Rectangle2D getBounds() {
        double r = view.getRadius();
        return new Rectangle2D(getX() - r, getY() - r, r * 2, r * 2);
    }
}

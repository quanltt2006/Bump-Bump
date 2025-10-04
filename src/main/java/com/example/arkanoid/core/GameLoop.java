package com.example.arkanoid.core;

import javafx.animation.AnimationTimer;

public class GameLoop extends AnimationTimer {

    private final ScreenManager screenManager;
    private long previousTimeNs = -1L;

    public GameLoop(ScreenManager screenManager) {
        this.screenManager = screenManager;
    }

    @Override
    public void handle(long now) {
        if (previousTimeNs < 0) {
            previousTimeNs = now;
            return;
        }
        long deltaNs = now - previousTimeNs;
        previousTimeNs = now;
        double deltaSeconds = deltaNs / 1_000_000_000.0;
        screenManager.update(deltaSeconds);
    }
}

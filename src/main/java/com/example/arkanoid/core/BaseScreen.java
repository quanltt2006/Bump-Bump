package com.example.arkanoid.core;

import javafx.scene.Group;

public abstract class BaseScreen {

    protected final GameContext gameContext;
    protected final Group rootGroup;

    protected BaseScreen(GameContext gameContext) {
        this.gameContext = gameContext;
        this.rootGroup = new Group();
        init();
    }

    protected abstract void init();

    public void onEnter() {}

    public void onExit() {}

    public void update(double deltaSeconds) {}

    public Group getRoot() {
        return rootGroup;
    }
}

package com.example.arkanoid.core;

import com.example.arkanoid.screens.*;
import javafx.scene.layout.StackPane;

public class ScreenManager {

    private final GameContext gameContext;
    private final StackPane root;

    private BaseScreen currentScreen;

    public ScreenManager(GameContext gameContext, StackPane root) {
        this.gameContext = gameContext;
        this.root = root;
    }

    public void showMenu() {
        setScreen(new MenuScreen(gameContext));
    }

    public void showGameplay(int levelIndex) {
        setScreen(new GameplayScreen(gameContext, levelIndex));
    }

    public void showLevelSelect() {
        setScreen(new LevelSelectScreen(gameContext));
    }

    public void showSettings() {
        setScreen(new SettingsScreen(gameContext));
    }

    public void showPause() {
        setScreen(new PauseScreen(gameContext));
    }

    public void showGameOver(boolean victory, int score) {
        setScreen(new GameOverScreen(gameContext, victory, score));
    }

    private void setScreen(BaseScreen newScreen) {
        if (currentScreen != null) {
            currentScreen.onExit();
        }
        currentScreen = newScreen;
        root.getChildren().setAll(currentScreen.getRoot());
        currentScreen.onEnter();
    }

    public void update(double deltaSeconds) {
        if (currentScreen != null) {
            currentScreen.update(deltaSeconds);
        }
    }
}

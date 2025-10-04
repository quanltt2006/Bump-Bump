package com.example.arkanoid.core;

import com.example.arkanoid.assets.AssetManager;
import com.example.arkanoid.audio.AudioManager;
import com.example.arkanoid.input.InputManager;
import com.example.arkanoid.levels.LevelManager;
import com.example.arkanoid.services.SaveService;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class GameContext {

    private final Stage stage;
    private final Scene scene;
    private final StackPane root;

    private final InputManager inputManager;
    private final AssetManager assetManager;
    private final AudioManager audioManager;

    private final LevelManager levelManager;
    private final SaveService saveService;

    private ScreenManager screenManager;

    public GameContext(Stage stage,
                       Scene scene,
                       StackPane root,
                       InputManager inputManager,
                       AssetManager assetManager,
                       AudioManager audioManager) {
        this.stage = stage;
        this.scene = scene;
        this.root = root;
        this.inputManager = inputManager;
        this.assetManager = assetManager;
        this.audioManager = audioManager;
        this.levelManager = new LevelManager();
        this.saveService = new SaveService();
    }

    public Stage getStage() { return stage; }
    public Scene getScene() { return scene; }
    public StackPane getRoot() { return root; }

    public InputManager getInputManager() { return inputManager; }
    public AssetManager getAssetManager() { return assetManager; }
    public AudioManager getAudioManager() { return audioManager; }

    public LevelManager getLevelManager() { return levelManager; }
    public SaveService getSaveService() { return saveService; }

    public ScreenManager getScreenManager() { return screenManager; }
    public void setScreenManager(ScreenManager screenManager) { this.screenManager = screenManager; }
}

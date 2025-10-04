package com.example.arkanoid;

import com.example.arkanoid.core.GameContext;
import com.example.arkanoid.core.GameLoop;
import com.example.arkanoid.core.ScreenManager;
import com.example.arkanoid.input.InputManager;
import com.example.arkanoid.assets.AssetManager;
import com.example.arkanoid.audio.AudioManager;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.net.URL;

public class ArkanoidApp extends Application {

    public static final int WINDOW_WIDTH = 960;
    public static final int WINDOW_HEIGHT = 540;

    @Override
    public void start(Stage primaryStage) {
        StackPane root = new StackPane();
        Scene scene = new Scene(root, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Load CSS if available
        URL cssUrl = getClass().getResource("/styles/app.css");
        if (cssUrl != null) {
            scene.getStylesheets().add(cssUrl.toExternalForm());
        }

        primaryStage.setTitle("Arkanoid");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);

        // Instantiate managers and context
        InputManager inputManager = new InputManager();
        AssetManager assetManager = new AssetManager();
        AudioManager audioManager = new AudioManager();

        GameContext context = new GameContext(primaryStage, scene, root, inputManager, assetManager, audioManager);
        ScreenManager screenManager = new ScreenManager(context, root);
        context.setScreenManager(screenManager);

        // Attach input
        inputManager.attach(scene);

        // Start at menu screen
        screenManager.showMenu();

        // Start game loop
        GameLoop loop = new GameLoop(screenManager);
        loop.start();

        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

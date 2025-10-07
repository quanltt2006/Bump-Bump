package com.arkanoid.game;

import javafx.application.Application;
import javafx.stage.Stage;
import com.arkanoid.game.view.ViewManager;

public class MainApp extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        ViewManager.getInstance().setPrimaryStage(primaryStage);
        ViewManager.getInstance().showLoginScreen();
        primaryStage.setTitle("Arkanoid: Shattered Realms");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

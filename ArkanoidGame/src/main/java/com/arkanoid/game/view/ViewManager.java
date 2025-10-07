package com.arkanoid.game.view;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

public class ViewManager {
    private static final ViewManager INSTANCE = new ViewManager();

    private Stage primaryStage;

    private ViewManager() {}

    public static ViewManager getInstance() {
        return INSTANCE;
    }

    public void setPrimaryStage(Stage primaryStage) {
        this.primaryStage = primaryStage;
    }

    private Parent load(String fxmlName) {
        try {
            return FXMLLoader.load(Objects.requireNonNull(
                    getClass().getResource("/com/arkanoid/game/fxml/" + fxmlName)
            ));
        } catch (IOException e) {
            throw new RuntimeException("Failed to load FXML: " + fxmlName, e);
        }
    }

    private void show(String fxmlName) {
        Parent root = load(fxmlName);
        Scene scene = primaryStage.getScene();
        if (scene == null) {
            scene = new Scene(root);
            scene.getStylesheets().add(Objects.requireNonNull(
                    getClass().getResource("/com/arkanoid/game/css/style.css")
            ).toExternalForm());
            primaryStage.setScene(scene);
        } else {
            scene.setRoot(root);
        }
    }

    public void showLoginScreen() { show("Login.fxml"); }
    public void showRegisterScreen() { show("Register.fxml"); }
    public void showMainMenu() { show("MainMenu.fxml"); }
    public void showGameScreen() { show("GameScreen.fxml"); }
    public void showShop() { show("Shop.fxml"); }
    public void showPaddleSelection() { show("PaddleSelection.fxml"); }
    public void showLeaderboard() { show("Leaderboard.fxml"); }
    public void showSettings() { show("Settings.fxml"); }
}

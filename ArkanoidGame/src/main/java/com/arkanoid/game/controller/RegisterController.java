package com.arkanoid.game.controller;

import com.arkanoid.game.view.ViewManager;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;

public class RegisterController {
    @FXML private TextField usernameField;
    @FXML private TextField emailField;
    @FXML private PasswordField passwordField;

    @FXML
    private void onSubmit(ActionEvent event) {
        // TODO: register via DatabaseManager
        ViewManager.getInstance().showLoginScreen();
    }

    @FXML
    private void onBack(ActionEvent event) {
        ViewManager.getInstance().showLoginScreen();
    }
}

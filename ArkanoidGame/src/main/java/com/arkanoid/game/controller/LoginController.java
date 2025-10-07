package com.arkanoid.game.controller;

import com.arkanoid.game.view.ViewManager;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;

public class LoginController {
    @FXML private TextField usernameField;
    @FXML private PasswordField passwordField;
    @FXML private Button loginButton;
    @FXML private Button registerButton;
    @FXML private Button guestButton;

    @FXML
    private void onLogin(ActionEvent event) {
        // TODO: authenticate via DatabaseManager
        ViewManager.getInstance().showMainMenu();
    }

    @FXML
    private void onRegister(ActionEvent event) {
        ViewManager.getInstance().showRegisterScreen();
    }

    @FXML
    private void onGuest(ActionEvent event) {
        ViewManager.getInstance().showMainMenu();
    }
}

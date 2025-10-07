package com.arkanoid.game.controller;

import com.arkanoid.game.view.ViewManager;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class MainMenuController {

    @FXML private void onPlay(ActionEvent e) { ViewManager.getInstance().showGameScreen(); }
    @FXML private void onShop(ActionEvent e) { ViewManager.getInstance().showShop(); }
    @FXML private void onPaddle(ActionEvent e) { ViewManager.getInstance().showPaddleSelection(); }
    @FXML private void onLeaderboard(ActionEvent e) { ViewManager.getInstance().showLeaderboard(); }
    @FXML private void onSettings(ActionEvent e) { ViewManager.getInstance().showSettings(); }
    @FXML private void onLogout(ActionEvent e) { ViewManager.getInstance().showLoginScreen(); }
}

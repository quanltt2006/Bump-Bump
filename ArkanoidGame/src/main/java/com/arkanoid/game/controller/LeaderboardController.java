package com.arkanoid.game.controller;

import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

public class LeaderboardController {
    @FXML private TableView<?> leaderboardTable;
    @FXML private TableColumn<?, ?> rankColumn;
    @FXML private TableColumn<?, ?> usernameColumn;
    @FXML private TableColumn<?, ?> scoreColumn;
}

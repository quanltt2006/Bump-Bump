package com.arkanoid.game.controller;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Slider;

public class SettingsController {
    @FXML private Slider musicSlider;
    @FXML private Slider effectsSlider;
    @FXML private ComboBox<String> qualityCombo;
    @FXML private ComboBox<String> languageCombo;
    @FXML private CheckBox fullscreenCheck;
    @FXML private Button saveButton;
}

package com.example.arkanoid.screens;

import com.example.arkanoid.core.BaseScreen;
import com.example.arkanoid.core.GameContext;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.VBox;

public class SettingsScreen extends BaseScreen {

    public SettingsScreen(GameContext gameContext) {
        super(gameContext);
    }

    @Override
    protected void init() {
        Label title = new Label("Settings");
        title.getStyleClass().add("title-text");

        double savedVolume = gameContext.getSaveService().getSfxVolume();
        gameContext.getAudioManager().setSfxVolume(savedVolume);
        Slider sfxSlider = new Slider(0, 1, savedVolume);
        sfxSlider.valueProperty().addListener((obs, o, n) -> {
            gameContext.getAudioManager().setSfxVolume(n.doubleValue());
            gameContext.getSaveService().setSfxVolume(n.doubleValue());
        });

        Button back = new Button("Back");
        back.setOnAction(e -> gameContext.getScreenManager().showMenu());

        VBox box = new VBox(12, title, new Label("SFX Volume"), sfxSlider, back);
        box.setAlignment(Pos.CENTER);
        rootGroup.getChildren().add(box);
    }
}

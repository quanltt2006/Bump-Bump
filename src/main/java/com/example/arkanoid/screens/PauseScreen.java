package com.example.arkanoid.screens;

import com.example.arkanoid.core.BaseScreen;
import com.example.arkanoid.core.GameContext;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class PauseScreen extends BaseScreen {

    public PauseScreen(GameContext gameContext) {
        super(gameContext);
    }

    @Override
    protected void init() {
        Text title = new Text("Paused");
        title.getStyleClass().add("title-text");

        Button resume = new Button("Resume");
        resume.setOnAction(e -> gameContext.getScreenManager().showGameplay(1)); // naive resume: go to level 1

        Button settings = new Button("Settings");
        settings.setOnAction(e -> gameContext.getScreenManager().showSettings());

        Button quit = new Button("Quit to Menu");
        quit.setOnAction(e -> gameContext.getScreenManager().showMenu());

        VBox box = new VBox(12, title, resume, settings, quit);
        box.setAlignment(Pos.CENTER);
        rootGroup.getChildren().add(box);
    }
}

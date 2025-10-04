package com.example.arkanoid.screens;

import com.example.arkanoid.core.BaseScreen;
import com.example.arkanoid.core.GameContext;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class MenuScreen extends BaseScreen {

    public MenuScreen(GameContext gameContext) {
        super(gameContext);
    }

    @Override
    protected void init() {
        Text title = new Text("ARKANOID");
        title.getStyleClass().add("title-text");
        int best = gameContext.getSaveService().getHighScore();
        Text bestText = new Text("Best: " + best);

        Button play = new Button("Play");
        play.getStyleClass().add("primary");
        play.setOnAction(e -> gameContext.getScreenManager().showLevelSelect());

        Button settings = new Button("Settings");
        settings.setOnAction(e -> gameContext.getScreenManager().showSettings());

        Button exit = new Button("Exit");
        exit.setOnAction(e -> gameContext.getStage().close());

        VBox box = new VBox(12, title, bestText, play, settings, exit);
        box.setAlignment(Pos.CENTER);
        rootGroup.getChildren().add(box);
    }
}

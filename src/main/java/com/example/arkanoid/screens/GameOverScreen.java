package com.example.arkanoid.screens;

import com.example.arkanoid.core.BaseScreen;
import com.example.arkanoid.core.GameContext;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class GameOverScreen extends BaseScreen {

    private final boolean victory;
    private final int score;

    public GameOverScreen(GameContext gameContext, boolean victory, int score) {
        super(gameContext);
        this.victory = victory;
        this.score = score;
    }

    @Override
    protected void init() {
        Text title = new Text(victory ? "You Win!" : "Game Over");
        title.getStyleClass().add("title-text");

        int previousHigh = gameContext.getSaveService().getHighScore();
        if (score > previousHigh) {
            gameContext.getSaveService().setHighScore(score);
        }
        Text scoreText = new Text("Score: " + score + "  (Best: " + Math.max(previousHigh, score) + ")");

        Button retry = new Button("Retry");
        retry.setOnAction(e -> gameContext.getScreenManager().showLevelSelect());

        Button menu = new Button("Main Menu");
        menu.setOnAction(e -> gameContext.getScreenManager().showMenu());

        VBox box = new VBox(12, title, scoreText, retry, menu);
        box.setAlignment(Pos.CENTER);
        rootGroup.getChildren().add(box);
    }
}

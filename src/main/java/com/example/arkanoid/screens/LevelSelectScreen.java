package com.example.arkanoid.screens;

import com.example.arkanoid.core.BaseScreen;
import com.example.arkanoid.core.GameContext;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class LevelSelectScreen extends BaseScreen {

    public LevelSelectScreen(GameContext gameContext) {
        super(gameContext);
    }

    @Override
    protected void init() {
        Text title = new Text("Select Level");
        title.getStyleClass().add("title-text");

        FlowPane grid = new FlowPane();
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(10));
        grid.setAlignment(Pos.CENTER);

        int maxLevels = 10;
        for (int i = 1; i <= maxLevels; i++) {
            int levelIndex = i;
            Button levelBtn = new Button("Level " + i);
            levelBtn.setOnAction(e -> gameContext.getScreenManager().showGameplay(levelIndex));
            grid.getChildren().add(levelBtn);
        }

        Button back = new Button("Back");
        back.setOnAction(e -> gameContext.getScreenManager().showMenu());

        VBox box = new VBox(16, title, grid, back);
        box.setAlignment(Pos.CENTER);
        rootGroup.getChildren().add(box);
    }
}

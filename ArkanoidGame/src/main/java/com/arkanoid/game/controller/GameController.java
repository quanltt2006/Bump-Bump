package com.arkanoid.game.controller;

import javafx.animation.AnimationTimer;
import com.arkanoid.game.view.ViewManager;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;

public class GameController {
    @FXML private Canvas gameCanvas;
    @FXML private Label scoreLabel;
    @FXML private Label livesLabel;
    @FXML private Label levelLabel;
    @FXML private Button pauseButton;
    @FXML private Button exitButton;

    private AnimationTimer gameLoop;
    private double paddleX = 350;
    private double paddleY = 560;
    private double paddleWidth = 100;
    private double paddleHeight = 20;

    private double ballX = 390;
    private double ballY = 300;
    private double ballVX = 3;
    private double ballVY = 3;
    private double ballRadius = 8;

    @FXML
    private void initialize() {
        GraphicsContext g = gameCanvas.getGraphicsContext2D();
        gameCanvas.addEventHandler(MouseEvent.MOUSE_MOVED, e -> {
            paddleX = Math.max(0, Math.min(e.getX() - paddleWidth / 2,
                    gameCanvas.getWidth() - paddleWidth));
        });

        gameLoop = new AnimationTimer() {
            @Override
            public void handle(long now) {
                update();
                render(g);
            }
        };
        gameLoop.start();
    }

    private void update() {
        ballX += ballVX;
        ballY += ballVY;

        // wall collisions
        if (ballX - ballRadius < 0 || ballX + ballRadius > gameCanvas.getWidth()) {
            ballVX *= -1;
        }
        if (ballY - ballRadius < 0) {
            ballVY *= -1;
        }
        // paddle collision simple AABB
        if (ballY + ballRadius >= paddleY && ballY + ballRadius <= paddleY + paddleHeight &&
                ballX >= paddleX && ballX <= paddleX + paddleWidth && ballVY > 0) {
            ballVY *= -1;
        }
        // bottom out
        if (ballY - ballRadius > gameCanvas.getHeight()) {
            ballX = gameCanvas.getWidth() / 2;
            ballY = gameCanvas.getHeight() / 2;
            ballVY = -Math.abs(ballVY);
        }
    }

    private void render(GraphicsContext g) {
        g.setFill(Color.BLACK);
        g.fillRect(0, 0, gameCanvas.getWidth(), gameCanvas.getHeight());

        g.setFill(Color.WHITE);
        g.fillRect(paddleX, paddleY, paddleWidth, paddleHeight);

        g.setFill(Color.RED);
        g.fillOval(ballX - ballRadius, ballY - ballRadius, ballRadius * 2, ballRadius * 2);
    }

    @FXML
    private void onPause() {
        if (gameLoop == null) return;
        gameLoop.stop();
    }

    @FXML
    private void onExit() {
        if (gameLoop != null) gameLoop.stop();
        ViewManager.getInstance().showMainMenu();
    }
}

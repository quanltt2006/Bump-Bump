package com.example.arkanoid.screens;

import com.example.arkanoid.core.BaseScreen;
import com.example.arkanoid.core.GameContext;
import com.example.arkanoid.entities.Ball;
import com.example.arkanoid.entities.Brick;
import com.example.arkanoid.entities.Paddle;
import com.example.arkanoid.levels.LevelManager;
import javafx.geometry.Rectangle2D;
import javafx.scene.Group;
import javafx.scene.input.KeyCode;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class GameplayScreen extends BaseScreen {

    private final int levelIndex;
    private Paddle paddle;
    private Ball ball;
    private final List<Brick> bricks = new ArrayList<>();
    private int score = 0;
    private Text scoreText;
    private boolean paused = false;

    private static final double WORLD_WIDTH = 960;
    private static final double WORLD_HEIGHT = 540;

    public GameplayScreen(GameContext gameContext, int levelIndex) {
        super(gameContext);
        this.levelIndex = levelIndex;
    }

    @Override
    protected void init() {
        Group world = new Group();
        rootGroup.getChildren().add(world);

        paddle = new Paddle(WORLD_WIDTH / 2, WORLD_HEIGHT - 40, 120, 16);
        ball = new Ball(WORLD_WIDTH / 2, WORLD_HEIGHT - 60, 8);

        world.getChildren().addAll(paddle.getView(), ball.getView());

        LevelManager levelManager = gameContext.getLevelManager();
        for (LevelManager.BrickSpec spec : levelManager.loadLevel(levelIndex)) {
            Brick b = new Brick(spec.x, spec.y, spec.w, spec.h, spec.hp, spec.color);
            bricks.add(b);
            world.getChildren().add(b.getView());
        }

        scoreText = new Text(16, 24, "Score: 0");
        scoreText.setFill(Color.WHITE);
        rootGroup.getChildren().add(scoreText);
    }

    @Override
    public void update(double dt) {
        if (gameContext.getInputManager().isKeyDown(KeyCode.ESCAPE) && !paused) {
            paused = true;
            gameContext.getScreenManager().showPause();
            return;
        }
        handleInput(dt);
        ball.update(dt);
        constrainBall();
        handleCollisions();
        checkWinLose();
        scoreText.setText("Score: " + score);
    }

    private void handleInput(double dt) {
        double speed = 380.0;
        double x = paddle.getX();
        if (gameContext.getInputManager().isKeyDown(KeyCode.LEFT) || gameContext.getInputManager().isKeyDown(KeyCode.A)) {
            x -= speed * dt;
        }
        if (gameContext.getInputManager().isKeyDown(KeyCode.RIGHT) || gameContext.getInputManager().isKeyDown(KeyCode.D)) {
            x += speed * dt;
        }
        x = Math.max(60, Math.min(WORLD_WIDTH - 60, x));
        paddle.setX(x);
    }

    private void constrainBall() {
        double x = ball.getX();
        double y = ball.getY();
        double vx = ball.getVelocityX();
        double vy = ball.getVelocityY();

        if (x < 8) { x = 8; vx = Math.abs(vx); }
        if (x > WORLD_WIDTH - 8) { x = WORLD_WIDTH - 8; vx = -Math.abs(vx); }
        if (y < 8) { y = 8; vy = Math.abs(vy); }

        ball.setPosition(x, y);
        ball.setVelocity(vx, vy);
    }

    private boolean intersects(Rectangle2D a, Rectangle2D b) {
        return a.intersects(b);
    }

    private void handleCollisions() {
        // Paddle collision
        if (intersects(ball.getBounds(), paddle.getBounds())) {
            ball.setVelocity(ball.getVelocityX(), -Math.abs(ball.getVelocityY()));
        }

        // Brick collisions
        Iterator<Brick> it = bricks.iterator();
        while (it.hasNext()) {
            Brick brick = it.next();
            if (!brick.isDestroyed() && intersects(ball.getBounds(), brick.getBounds())) {
                brick.hit();
                score += 10;
                ball.setVelocity(ball.getVelocityX(), -ball.getVelocityY());
                gameContext.getAudioManager().playSfx(gameContext.getAssetManager(), "/sounds/hit.wav");
                if (brick.isDestroyed()) {
                    // keep for now; you can remove node on cleanup
                }
            }
        }
    }

    private void checkWinLose() {
        if (ball.getY() > WORLD_HEIGHT + 50) {
            gameContext.getScreenManager().showGameOver(false, score);
        }
        boolean allDestroyed = bricks.stream().allMatch(Brick::isDestroyed);
        if (allDestroyed) {
            gameContext.getScreenManager().showGameOver(true, score);
        }
    }
}

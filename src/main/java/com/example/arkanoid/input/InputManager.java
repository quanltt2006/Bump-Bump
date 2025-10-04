package com.example.arkanoid.input;

import javafx.scene.Scene;
import javafx.scene.input.KeyCode;

import java.util.HashSet;
import java.util.Set;

public class InputManager {

    private final Set<KeyCode> pressedKeys = new HashSet<>();

    public void attach(Scene scene) {
        scene.setOnKeyPressed(e -> pressedKeys.add(e.getCode()));
        scene.setOnKeyReleased(e -> pressedKeys.remove(e.getCode()));
        // Ensure scene is focusable
        scene.getRoot().setFocusTraversable(true);
        scene.getRoot().requestFocus();
    }

    public boolean isKeyDown(KeyCode keyCode) {
        return pressedKeys.contains(keyCode);
    }
}

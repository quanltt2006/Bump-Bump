package com.example.arkanoid.levels;

import javafx.scene.paint.Color;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class LevelManager {

    public static class BrickSpec {
        public final double x;
        public final double y;
        public final double w;
        public final double h;
        public final int hp;
        public final Color color;
        public BrickSpec(double x, double y, double w, double h, int hp, Color color) {
            this.x = x; this.y = y; this.w = w; this.h = h; this.hp = hp; this.color = color;
        }
    }

    public List<BrickSpec> loadLevel(int index) {
        String path = "/levels/level_" + index + ".txt";
        InputStream stream = getClass().getResourceAsStream(path);
        if (stream == null) {
            return createDefaultLevel();
        }
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(stream, StandardCharsets.UTF_8))) {
            List<BrickSpec> specs = new ArrayList<>();
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) continue;
                String[] parts = line.split(",");
                double x = Double.parseDouble(parts[0]);
                double y = Double.parseDouble(parts[1]);
                double w = Double.parseDouble(parts[2]);
                double h = Double.parseDouble(parts[3]);
                int hp = Integer.parseInt(parts[4]);
                Color color = Color.web(parts.length > 5 ? parts[5] : "#FF6B6B");
                specs.add(new BrickSpec(x, y, w, h, hp, color));
            }
            return specs;
        } catch (IOException ex) {
            return createDefaultLevel();
        }
    }

    private List<BrickSpec> createDefaultLevel() {
        List<BrickSpec> specs = new ArrayList<>();
        double startX = 120;
        double startY = 100;
        double w = 70;
        double h = 24;
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 10; col++) {
                double x = startX + col * (w + 6);
                double y = startY + row * (h + 6);
                specs.add(new BrickSpec(x, y, w, h, 1, Color.hsb((row * 50 + col * 10) % 360, 0.6, 0.95)));
            }
        }
        return specs;
    }
}

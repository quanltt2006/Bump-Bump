package com.example.arkanoid.assets;

import javafx.scene.image.Image;
import javafx.scene.media.AudioClip;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class AssetManager {

    private final Map<String, Image> imageCache = new HashMap<>();
    private final Map<String, AudioClip> audioCache = new HashMap<>();

    public Image getImage(String path) {
        if (imageCache.containsKey(path)) return imageCache.get(path);
        URL url = getClass().getResource(path);
        if (url == null) throw new IllegalArgumentException("Image not found: " + path);
        Image img = new Image(url.toExternalForm());
        imageCache.put(path, img);
        return img;
    }

    public AudioClip getAudio(String path) {
        if (audioCache.containsKey(path)) return audioCache.get(path);
        URL url = getClass().getResource(path);
        if (url == null) throw new IllegalArgumentException("Audio not found: " + path);
        AudioClip clip = new AudioClip(url.toExternalForm());
        audioCache.put(path, clip);
        return clip;
    }
}

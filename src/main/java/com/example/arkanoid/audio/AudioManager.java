package com.example.arkanoid.audio;

import com.example.arkanoid.assets.AssetManager;

public class AudioManager {

    private double sfxVolume = 0.6;

    public void playSfx(AssetManager assets, String path) {
        try {
            var clip = assets.getAudio(path);
            clip.setVolume(sfxVolume);
            clip.play();
        } catch (Exception ignored) {
            // ignore missing audio in scaffold
        }
    }

    public double getSfxVolume() { return sfxVolume; }
    public void setSfxVolume(double sfxVolume) { this.sfxVolume = sfxVolume; }
}

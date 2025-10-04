package com.example.arkanoid.services;

import java.util.prefs.BackingStoreException;
import java.util.prefs.Preferences;

public class SaveService {

    private static final String KEY_HIGH_SCORE = "highScore";
    private static final String KEY_SFX_VOLUME = "sfxVolume";

    private final Preferences prefs = Preferences.userNodeForPackage(SaveService.class);

    public int getHighScore() {
        return prefs.getInt(KEY_HIGH_SCORE, 0);
    }

    public void setHighScore(int score) {
        if (score <= getHighScore()) return;
        prefs.putInt(KEY_HIGH_SCORE, score);
        flushQuietly();
    }

    public double getSfxVolume() {
        return prefs.getDouble(KEY_SFX_VOLUME, 0.6);
    }

    public void setSfxVolume(double volume) {
        prefs.putDouble(KEY_SFX_VOLUME, Math.max(0.0, Math.min(1.0, volume)));
        flushQuietly();
    }

    private void flushQuietly() {
        try { prefs.flush(); } catch (BackingStoreException ignored) {}
    }
}

package com.arkanoid.game.model;

import com.arkanoid.game.util.Constants;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseManager {
    private static final DatabaseManager INSTANCE = new DatabaseManager();

    private DatabaseManager() {
        initSchema();
    }

    public static DatabaseManager getInstance() {
        return INSTANCE;
    }

    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection(Constants.DB_URL);
    }

    private void initSchema() {
        try (Connection conn = getConnection(); Statement st = conn.createStatement()) {
            st.executeUpdate("CREATE TABLE IF NOT EXISTS users (\n" +
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,\n" +
                    "username TEXT UNIQUE NOT NULL,\n" +
                    "password_hash TEXT,\n" +
                    "email TEXT,\n" +
                    "coins INTEGER DEFAULT 0,\n" +
                    "gems INTEGER DEFAULT 0,\n" +
                    "equipped_paddle_id TEXT,\n" +
                    "high_score INTEGER DEFAULT 0\n" +
                    ")");

            st.executeUpdate("CREATE TABLE IF NOT EXISTS leaderboard (\n" +
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,\n" +
                    "username TEXT NOT NULL,\n" +
                    "score INTEGER NOT NULL\n" +
                    ")");
        } catch (SQLException e) {
            throw new RuntimeException("Failed to init database schema", e);
        }
    }

    public void createUser(User user) {
        String sql = "INSERT INTO users(username, password_hash, email, coins, gems, equipped_paddle_id, high_score) VALUES(?,?,?,?,?,?,?)";
        try (Connection conn = getConnection(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, user.getUsername());
            ps.setString(2, user.getPasswordHash());
            ps.setString(3, user.getEmail());
            ps.setInt(4, user.getCoins());
            ps.setInt(5, user.getGems());
            ps.setString(6, user.getEquippedPaddleId());
            ps.setInt(7, user.getHighScore());
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Failed to create user", e);
        }
    }

    public User getUser(String username) {
        String sql = "SELECT * FROM users WHERE username=?";
        try (Connection conn = getConnection(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                User u = new User();
                u.setId(rs.getLong("id"));
                u.setUsername(rs.getString("username"));
                u.setPasswordHash(rs.getString("password_hash"));
                u.setEmail(rs.getString("email"));
                u.setCoins(rs.getInt("coins"));
                u.setGems(rs.getInt("gems"));
                u.setEquippedPaddleId(rs.getString("equipped_paddle_id"));
                u.setHighScore(rs.getInt("high_score"));
                return u;
            }
            return null;
        } catch (SQLException e) {
            throw new RuntimeException("Failed to get user", e);
        }
    }

    public void updateUser(User user) {
        String sql = "UPDATE users SET password_hash=?, email=?, coins=?, gems=?, equipped_paddle_id=?, high_score=? WHERE username=?";
        try (Connection conn = getConnection(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, user.getPasswordHash());
            ps.setString(2, user.getEmail());
            ps.setInt(3, user.getCoins());
            ps.setInt(4, user.getGems());
            ps.setString(5, user.getEquippedPaddleId());
            ps.setInt(6, user.getHighScore());
            ps.setString(7, user.getUsername());
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Failed to update user", e);
        }
    }

    public void saveHighScore(String username, int score) {
        String sql = "INSERT INTO leaderboard(username, score) VALUES(?,?)";
        try (Connection conn = getConnection(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, username);
            ps.setInt(2, score);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Failed to save high score", e);
        }
    }

    public List<String> getLeaderboard(int limit) {
        String sql = "SELECT username || ':' || score AS entry FROM leaderboard ORDER BY score DESC LIMIT ?";
        try (Connection conn = getConnection(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, limit);
            ResultSet rs = ps.executeQuery();
            List<String> list = new ArrayList<>();
            while (rs.next()) {
                list.add(rs.getString("entry"));
            }
            return list;
        } catch (SQLException e) {
            throw new RuntimeException("Failed to get leaderboard", e);
        }
    }
}

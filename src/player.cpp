#include "Player.h"
#include <iostream>

// Constructor
Player::Player(SDL_Renderer* renderer) {
    this->renderer = renderer;

    // Tải hình ảnh nhân vật
    SDL_Surface* surface = IMG_Load("player.png");
    if (!surface) {
        std::cerr << "Failed to load player image: " << IMG_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Khởi tạo vị trí và kích thước
    x = 100;
    y = 200;
    width = 50;
    height = 50;
}

// Destructor
Player::~Player() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
void Player::Update() {
 // Cập nhật chuyển động dọc (nhảy)
    velocityY += gravity;
    y += velocityY;

    // Cập nhật chuyển động ngang
    if (movingRight) {
        x += velocityX;
    } else {
        x -= velocityX;
    }

    // Khi chim chạm biên, đổi hướng
    if (x >= rightBoundary) {
        movingRight = false; // Quay lại trái
    }
    if (x <= leftBoundary) {
        movingRight = true; // Quay lại phải
    }

    // Giới hạn rơi
    if (y >= 500) {
        y = 500;
        velocityY = 0;
    }

}
// Cập nhật trạng thái nhân vật
void Player::Jump() {
velocityY = -jump_force;
}

// Vẽ nhân vật lên màn hình
void Player::Render() {
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}


// Đặt vị trí nhân vật
void Player::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

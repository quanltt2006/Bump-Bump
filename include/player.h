#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Player {
public:
 Player(SDL_Renderer* renderer);
    ~Player();
    void Update(); // Cập nhật trạng thái nhân vật
    void Render(); // Vẽ nhân vật lên màn hình
    void SetPosition(int x, int y); // Đặt vị trí nhân vật
    void Jump(); //

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int x, y; // Vị trí nhân vật
    int width, height; // Kích thước nhân vật
    float jumpForce; // Lực nhảy

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 1400;
float velocityY = 0;     // Vận tốc rơi (trục y)
const float gravity = 0.5;
const float jump_force = 8;

float velocityX = 2;  // Tốc độ ngang của chim
bool movingRight = true; // Chim đang bay về bên phải

const float leftBoundary = 50;  // Biên trái
const float rightBoundary = 350; // Biên phải

};

#endif

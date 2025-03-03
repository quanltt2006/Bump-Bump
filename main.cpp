#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
using namespace std;

const int mh_rong = 500;
const int mh_cao = 1000;
const int vit_SIZE = 40;
const int GRAVITY = 1;
const int JUMP_STRENGTH = -15;
const int vit_SPEED = 5;
const int cnv_rong = 50;
const int cnv_GAP = 500;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;
SDL_Texture* cnvTexture = nullptr;

struct cnv {
    int x, y, width, height;
};

vector<cnv> cnvs;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "ERROR" << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "ERROR" << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        cout << "ERROR" << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("BUMP BUMP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mh_rong, mh_cao, SDL_WINDOW_SHOWN);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    return true;
}

bool loadanh() {
    SDL_Surface* surface = IMG_Load("duck.jpg");


    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("cnv.png");


    cnvTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    return true;
}

void close() {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(cnvTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void taocnvs() {
    cnvs.clear();

    const int MIN_GAP = 200;
    const int MAX_HEIGHT = mh_cao / 3;


    int topHeight = rand() % (MAX_HEIGHT - MIN_GAP) + MIN_GAP;
    cnv leftTop = {0, 0, cnv_rong, topHeight};
    cnv rightTop = {mh_rong - cnv_rong, 0, cnv_rong, topHeight};

    int bottomHeight = rand() % (MAX_HEIGHT - MIN_GAP) + MIN_GAP;
    int bottomY = mh_cao - bottomHeight;
    cnv leftBottom = {0, bottomY, cnv_rong, bottomHeight};
    cnv rightBottom = {mh_rong - cnv_rong, bottomY, cnv_rong, bottomHeight};

    cnvs.push_back(leftTop);
    cnvs.push_back(rightTop);
    cnvs.push_back(leftBottom);
    cnvs.push_back(rightBottom);

    if (rand() % 2 == 0) {
        int midY = topHeight + MIN_GAP + rand() % (mh_cao - topHeight - bottomHeight - 2 * MIN_GAP);
        int midHeight = 150 ;

        cnv rightMid = {mh_rong - cnv_rong, midY, cnv_rong, midHeight};

        cnvs.push_back(rightMid);
    }

else {int midY = topHeight + MIN_GAP + rand() % (mh_cao - topHeight - bottomHeight - 2 * MIN_GAP);
        int midHeight = 150;
            cnv leftMid = {0, midY, cnv_rong, midHeight};
        cnvs.push_back(leftMid);


}


}


bool check_vacham(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

int main(int argc, char* argv[]) {
    if (!init() || !loadanh()) {
        return -1;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk* amthanh = Mix_LoadWAV("click.wav");
    Mix_Chunk* amthanh1 = Mix_LoadWAV("beep.wav");

    TTF_Font* ourfont = TTF_OpenFont("hihi.ttf", 32);
    if (!ourfont) {
        cout << "Error" << TTF_GetError() << std::endl;
        return -1;
    }

    int vitX = mh_rong / 2;
    int vitY = mh_cao / 2;
    int vitVelY = 0;
    int vitVelX = vit_SPEED;

    bool quit = false;
    SDL_Event e;

    bool flipped = false;

    taocnvs();

   Uint32 lastPassedTime = 0;
int score = 0;
bool gameOver = false;
int gameOverRectY = mh_cao;
while (!quit) {
    Uint32 currentTime = SDL_GetTicks();

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE) {
                if (gameOver) {
                    gameOver = false;
                    gameOverRectY = mh_cao;
                    vitX = mh_rong / 2;
                    vitY = mh_cao / 2;
                    vitVelY = 0;
                    score = 0;
                    taocnvs();
                } else {
                    vitVelY = JUMP_STRENGTH;
                    Mix_PlayChannel(-1, amthanh, 0);
                }
            }
        }
    }

    if (!gameOver) {
        vitVelY += GRAVITY;
        vitY += vitVelY;
        vitX += vitVelX;

        if (vitX < 0 || vitX + vit_SIZE > mh_rong) {
            vitVelX = -vitVelX;
            flipped = !flipped;
            score++;
            Mix_PlayChannel(-1, amthanh1, 0);
            lastPassedTime = SDL_GetTicks();
        }

        if (lastPassedTime > 0 && SDL_GetTicks() - lastPassedTime >= 500) {
            taocnvs();
            lastPassedTime = 0;
        }

        if (vitY < 0) {
            vitY = 0;
            vitVelY = 0;
        } else if (vitY + vit_SIZE > mh_cao) {
            vitY = mh_cao - vit_SIZE;
            vitVelY = 0;
        }

        SDL_Rect vitRect = {vitX, vitY, vit_SIZE, vit_SIZE};
        for (auto& cnv : cnvs) {
            SDL_Rect cnvRect = {cnv.x, cnv.y, cnv.width, cnv.height};
            if (check_vacham(vitRect, cnvRect)) {
                gameOver = true;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect vitRect = {vitX, vitY, vit_SIZE, vit_SIZE};
    SDL_RenderCopyEx(renderer, texture, NULL, &vitRect, 0, NULL, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    for (auto& cnv : cnvs) {
        SDL_Rect cnvRect = {cnv.x, cnv.y, cnv.width, cnv.height};
        SDL_RenderCopy(renderer, cnvTexture, NULL, &cnvRect);
    }

    string scoreText = "Score: " + to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(ourfont, scoreText.c_str(), {255, 255, 255});
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {170, 20, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    if (gameOver) {
        if (gameOverRectY > mh_cao / 2 - 50) {
            gameOverRectY -= 15;
        }

        SDL_Rect gameOverRect = {mh_rong / 2 - 100, gameOverRectY, 200, 100};
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                SDL_RenderFillRect(renderer, &gameOverRect);

        SDL_Surface* gameOverSurface = TTF_RenderText_Solid(ourfont, "Game Over", {0, 0, 0});
        SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
        SDL_Rect gameOverTextRect = {mh_rong / 2 - 100, gameOverRectY + 20, gameOverSurface->w, gameOverSurface->h};
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverTextRect);

        SDL_Surface* replaySurface = TTF_RenderText_Solid(ourfont, "Press SPACE to replay", {0, 0,0});
        SDL_Texture* replayTexture = SDL_CreateTextureFromSurface(renderer, replaySurface);
        SDL_Rect replayTextRect = {mh_rong / 2 - 200 , gameOverRectY + 60, replaySurface->w, replaySurface->h};
        SDL_RenderCopy(renderer, replayTexture, NULL, &replayTextRect);

        SDL_FreeSurface(gameOverSurface);
        SDL_DestroyTexture(gameOverTexture);
        SDL_FreeSurface(replaySurface);
        SDL_DestroyTexture(replayTexture);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
}


    TTF_CloseFont(ourfont);
    Mix_FreeChunk(amthanh);
    Mix_FreeChunk(amthanh1);
    Mix_CloseAudio();
    close();
cout << score;
    return 0;
}

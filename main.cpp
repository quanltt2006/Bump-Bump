#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 1000;
const int PLAYER_SIZE = 40;
const int GRAVITY = 1;
const int JUMP_FORCE = -15;
const int PLAYER_SPEED = 5;
const int OBSTACLE_WIDTH = 50;
const int OBSTACLE_GAP = 500;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* playerTexture = nullptr;
SDL_Texture* obstacleTexture = nullptr;
SDL_Texture* skullTexture = nullptr;
SDL_Texture* pauseButtonTexture = nullptr;
SDL_Texture* backButtonTexture = nullptr;

struct Obstacle {
    int x, y, width, height;
};

struct Skull {
    int x, y, width, height;
};

vector<Obstacle> obstacles;
vector<Skull> skulls;


int loadHighScore() {
    int highScore = 0;
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}

void saveHighScore(int highScore) {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL_image initialization failed: " << IMG_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("Bump Bump",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return true;
}

bool loadResources(string playerImagePath) {
    SDL_Surface* tempSurface = IMG_Load(playerImagePath.c_str());
    playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("cnv.png");
    obstacleTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("skull.png");
    skullTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("pause.png");
    pauseButtonTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("back.png");
    backButtonTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return true;
}

void cleanup() {
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(obstacleTexture);
    SDL_DestroyTexture(skullTexture);
    SDL_DestroyTexture(pauseButtonTexture);
    SDL_DestroyTexture(backButtonTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void createSkulls() {
    skulls.clear();
    skulls.push_back({0, 100, 40, 40});
    skulls.push_back({0, 800, 40, 40});
}

void createObstacles(bool isHardMode, bool isFlipped) {
    obstacles.clear();
    if (!isHardMode) {

        const int MIN_GAP = 100 ;
        const int MIN_HEIGHT_EDGE = 250;
        const int MAX_HEIGHT_EDGE = 300;
        const int MIN_HEIGHT_MID = 100;
        const int MAX_HEIGHT_MID = 200;

        int topHeight = MIN_HEIGHT_EDGE + rand() % (MAX_HEIGHT_EDGE - MIN_HEIGHT_EDGE + 1);

        int bottomHeight = MIN_HEIGHT_EDGE + rand() % (MAX_HEIGHT_EDGE - MIN_HEIGHT_EDGE + 1);
        int bottomY = SCREEN_HEIGHT - bottomHeight;
        int midHeight = MIN_HEIGHT_MID + rand() % (MAX_HEIGHT_MID - MIN_HEIGHT_MID + 1);
        int midY = topHeight + MIN_GAP + rand() % (SCREEN_HEIGHT - topHeight - bottomHeight - MIN_GAP - midHeight);
        if (!isFlipped) {
            Obstacle rightTop = {SCREEN_WIDTH - OBSTACLE_WIDTH, 0, OBSTACLE_WIDTH, topHeight};
            Obstacle rightBottom = {SCREEN_WIDTH - OBSTACLE_WIDTH, bottomY, OBSTACLE_WIDTH, bottomHeight};
            obstacles.push_back(rightBottom);

            obstacles.push_back(rightTop);
            if (rand() % 2 == 0) {
                Obstacle rightMid = {SCREEN_WIDTH - OBSTACLE_WIDTH, midY, OBSTACLE_WIDTH, midHeight};
                obstacles.push_back(rightMid);
    }
    } else {
            Obstacle leftBottom = {0, bottomY, OBSTACLE_WIDTH, bottomHeight};
            Obstacle leftTop = {0, 0, OBSTACLE_WIDTH, topHeight};

            obstacles.push_back(leftBottom);
            obstacles.push_back(leftTop);
            if (rand() % 2 == 0) {
                Obstacle leftMid = {0, midY, OBSTACLE_WIDTH, midHeight};
                obstacles.push_back(leftMid);
                }
            }
        }
    else {

            const int MIN_GAP = 200;
            const int MAX_HEIGHT = SCREEN_HEIGHT / 3;

            int topHeight = rand() % (MAX_HEIGHT - MIN_GAP) + MIN_GAP;
            Obstacle left = {0, 0, OBSTACLE_WIDTH, topHeight};
            Obstacle right = {SCREEN_WIDTH - OBSTACLE_WIDTH, 0, OBSTACLE_WIDTH, topHeight};

            obstacles.push_back(left);
            obstacles.push_back(right);

    }
}




void showMainMenu(bool& startGame, bool& isHardMode) {
    SDL_Event e;
    bool inMenu = true;
    bool soundOn = true;
    SDL_Surface* menusurface = IMG_Load("menu.jpg");
    SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer, menusurface);

    Mix_Chunk* menuSound = Mix_LoadWAV("amthanh.mp3");
    if (menuSound && soundOn) {
        Mix_PlayChannel(-1, menuSound, 0);
    }

    SDL_Surface* speakerOnSurface = IMG_Load("on.png");
    SDL_Surface* speakerOffSurface = IMG_Load("off.png");
    SDL_Texture* speakerOnTexture = SDL_CreateTextureFromSurface(renderer, speakerOnSurface);
    SDL_Texture* speakerOffTexture = SDL_CreateTextureFromSurface(renderer, speakerOffSurface);
    SDL_FreeSurface(speakerOnSurface);
    SDL_FreeSurface(speakerOffSurface);

    const int speakerSize = 40;
    const int speakerX = SCREEN_WIDTH - speakerSize - 20;
    const int speakerY = 20;

    while (inMenu) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int easyButtonWidth = 100;
        int easyButtonHeight = 50;
        int easyButtonX = SCREEN_WIDTH / 2 - easyButtonWidth / 2;
        int easyButtonY = SCREEN_HEIGHT / 2 - easyButtonHeight / 2 - 60;

        int hardButtonWidth = 100;
        int hardButtonHeight = 50;
        int hardButtonX = SCREEN_WIDTH / 2 - hardButtonWidth / 2;
        int hardButtonY = SCREEN_HEIGHT / 2 - hardButtonHeight / 2 + 60;

        if (x >= easyButtonX && x <= easyButtonX + easyButtonWidth &&
            y >= easyButtonY && y <= easyButtonY + easyButtonHeight) {
            easyButtonWidth = 120;
            easyButtonHeight = 60;
            easyButtonX = SCREEN_WIDTH / 2 - easyButtonWidth / 2;
            easyButtonY = SCREEN_HEIGHT / 2 - easyButtonHeight / 2 - 60;
        }

        if (x >= hardButtonX && x <= hardButtonX + hardButtonWidth &&
            y >= hardButtonY && y <= hardButtonY + hardButtonHeight) {
            hardButtonWidth = 120;
            hardButtonHeight = 60;
            hardButtonX = SCREEN_WIDTH / 2 - hardButtonWidth / 2;
            hardButtonY = SCREEN_HEIGHT / 2 - hardButtonHeight / 2 + 60;
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                inMenu = false;
                startGame = false;
                cleanup();
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (x >= speakerX && x <= speakerX + speakerSize &&
                    y >= speakerY && y <= speakerY + speakerSize) {
                    soundOn = !soundOn;
                    if (soundOn) {
                        Mix_Resume(-1);
                        if (menuSound && !Mix_Playing(-1)) {
                            Mix_PlayChannel(-1, menuSound, 0);
                        }
                    } else {
                        Mix_Pause(-1);
                    }
                }
                else if (x >= easyButtonX && x <= easyButtonX + easyButtonWidth &&
                    y >= easyButtonY && y <= easyButtonY + easyButtonHeight) {
                    inMenu = false;
                    startGame = true;
                    isHardMode = false;
                }
                else if (x >= hardButtonX && x <= hardButtonX + hardButtonWidth &&
                    y >= hardButtonY && y <= hardButtonY + hardButtonHeight) {
                    inMenu = false;
                    startGame = true;
                    isHardMode = true;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

        SDL_Rect easyButton = {easyButtonX, easyButtonY, easyButtonWidth, easyButtonHeight};
        SDL_Surface* easySurface = IMG_Load("easy.png");
        SDL_Texture* easyTexture = SDL_CreateTextureFromSurface(renderer, easySurface);
        SDL_RenderCopy(renderer, easyTexture, NULL, &easyButton);
        SDL_FreeSurface(easySurface);
        SDL_DestroyTexture(easyTexture);

        SDL_Rect hardButton = {hardButtonX, hardButtonY, hardButtonWidth, hardButtonHeight};
        SDL_Surface* hardSurface = IMG_Load("hard.png");
        SDL_Texture* hardTexture = SDL_CreateTextureFromSurface(renderer, hardSurface);
        SDL_RenderCopy(renderer, hardTexture, NULL, &hardButton);
        SDL_FreeSurface(hardSurface);
        SDL_DestroyTexture(hardTexture);

        SDL_Rect speakerButton = {speakerX, speakerY, speakerSize, speakerSize};
        if (soundOn) {
            SDL_RenderCopy(renderer, speakerOnTexture, NULL, &speakerButton);
        } else {
            SDL_RenderCopy(renderer, speakerOffTexture, NULL, &speakerButton);
        }

        SDL_RenderPresent(renderer);
    }

    if (menuSound) Mix_FreeChunk(menuSound);
    SDL_DestroyTexture(speakerOnTexture);
    SDL_DestroyTexture(speakerOffTexture);
    SDL_DestroyTexture(menuTexture);
    SDL_FreeSurface(menusurface);

}


string showPlayerSelection(bool& startgame) {
    SDL_Event e;
    bool selectscreen = true;
    string selected = "";
    SDL_Surface* selectsurface = IMG_Load("menu2.png");
    SDL_Texture* selecttexture = SDL_CreateTextureFromSurface(renderer, selectsurface);
    SDL_FreeSurface(selectsurface);

    vector<Obstacle> v;
    vector<SDL_Texture*> nvtextures(6);
    for (int i = 0; i < 6; i++) {
        v.push_back({100 * (i % 3 + 1), 50 + 150 * (i / 3 +3 ) , 40, 40 });
        string s = "duck" + to_string(i) + ".png";
        SDL_Surface* nvsurface = IMG_Load(s.c_str());
        nvtextures[i] = SDL_CreateTextureFromSurface(renderer, nvsurface);
        SDL_FreeSurface(nvsurface);
    }

    while (selectscreen) {
        int m, n;
        SDL_GetMouseState(&m, &n);

        for (int i = 0; i < 6; i++) {
            v[i].width = 60;
            v[i].height = 60;

        }

        for (int i = 0; i < 6; i++) {
            if (m >= v[i].x && m <= v[i].x + v[i].width && n >= v[i].y && n <= v[i].y + v[i].height) {

                v[i].width = 80;
                v[i].height = 80;





            }
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                selectscreen = false;
                startgame = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < 6; i++) {
                    if (m >= v[i].x && m <= v[i].x + v[i].width && n >= v[i].y && n <= v[i].y + v[i].height) {
                        selectscreen = false;
                        startgame = true;
                        selected = "duck" + to_string(i) + ".png";
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, selecttexture, NULL, NULL);

        for (int i = 0; i < 6; i++) {
            SDL_Rect nv = {v[i].x, v[i].y, v[i].width, v[i].height};
            SDL_RenderCopy(renderer, nvtextures[i], NULL, &nv);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(selecttexture);
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(nvtextures[i]);
    }
    return selected;

}


bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

void showGameOver(int& gameOverRectY, TTF_Font* ourfont) {
    SDL_Rect gameOverRect = {SCREEN_WIDTH / 2 - 100, gameOverRectY, 200, 100};
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &gameOverRect);

        SDL_Surface* gameOverSurface = TTF_RenderText_Solid(ourfont, "Game Over", {255, 255, 255});
        SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
        SDL_Rect gameOverTextRect = {SCREEN_WIDTH / 2 - 50, gameOverRectY + 20, gameOverSurface->w, gameOverSurface->h};
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverTextRect);

        SDL_Surface* replaySurface = TTF_RenderText_Solid(ourfont, "Press SPACE to replay", {255, 255,255});
        SDL_Texture* replayTexture = SDL_CreateTextureFromSurface(renderer, replaySurface);
        SDL_Rect replayTextRect = {SCREEN_WIDTH / 2 - 100 , gameOverRectY + 60, replaySurface->w, replaySurface->h};
        SDL_RenderCopy(renderer, replayTexture, NULL, &replayTextRect);
                if (gameOverRectY > SCREEN_HEIGHT / 2 - 50) {
            gameOverRectY -= 20;
        }

        SDL_DestroyTexture(gameOverTexture);
        SDL_DestroyTexture(replayTexture);

}
void updateGameLogic(
    int& playerX, int& playerY,
    int& playerVelX, int& playerVelY,
    bool& isFlipped,
    int& score,
    int& highScore,
    bool& isGameOver,
    bool& hasGameStarted,
    bool isHardMode,
    Uint32& lastObstacleTime,
    int& obstacleSpeed,
    int& skullSpeed,
    Mix_Chunk* scoreSound,
    Mix_Chunk* gameOverSound
) {
    playerVelY += GRAVITY;
    playerY += playerVelY;
    playerX += playerVelX;

    if (playerX < 0 || playerX + PLAYER_SIZE > SCREEN_WIDTH) {
        playerVelX = -playerVelX;
        isFlipped = !isFlipped;
        score++;
        Mix_PlayChannel(-1, scoreSound, 0);
        lastObstacleTime = SDL_GetTicks();
    }

    if (lastObstacleTime > 0 && SDL_GetTicks() - lastObstacleTime >= 500) {
        lastObstacleTime = 0;
        if (!isHardMode) {
            createObstacles(isHardMode, isFlipped);
        }
    }

    if (playerY < 0) {
        playerY = 0;
        playerVelY = 0;
    } else if (playerY + PLAYER_SIZE > SCREEN_HEIGHT) {
        playerY = SCREEN_HEIGHT - PLAYER_SIZE;
        playerVelY = 0;
    }

    if (isHardMode && !obstacles.empty() && !skulls.empty()) {
        obstacles[0].y += obstacleSpeed;
        obstacles[1].y += obstacleSpeed;

        if (obstacles[0].y < 0 || obstacles[0].y + obstacles[0].height > SCREEN_HEIGHT) {
            obstacleSpeed = -obstacleSpeed;
        }

        for (auto& skull : skulls) {
            skull.x += skullSpeed;
            if (skull.x <= 0 || skull.x + skull.width >= SCREEN_WIDTH) {
                skullSpeed = -skullSpeed;
            }
        }
    }

    SDL_Rect playerRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};

    for (const auto& obstacle : obstacles) {
        SDL_Rect obstacleRect = {obstacle.x, obstacle.y, obstacle.width, obstacle.height};
        if (checkCollision(playerRect, obstacleRect)) {
            isGameOver = true;
            Mix_PlayChannel(-1, gameOverSound, 0);
            hasGameStarted = false;
            if (score > highScore) {
                highScore = score;
                saveHighScore(highScore);
            }
            return;;
        }
    }

    if (isHardMode) {
        for (const auto& skull : skulls) {
            SDL_Rect skullRect = {skull.x, skull.y, skull.width, skull.height};
            if (checkCollision(playerRect, skullRect)) {
                isGameOver = true;
                Mix_PlayChannel(-1, gameOverSound, 0);
                hasGameStarted = false;
                 if (score > highScore) {
                highScore = score;
                saveHighScore(highScore);
            }
            return;
            }
        }
    }
}
void renderText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const string& text,
    int x, int y,
    SDL_Color color
) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void handlePauseButton(
    SDL_Renderer* renderer,
    SDL_Texture* pauseTexture,        e
    TTF_Font* font,
    SDL_Rect& pauseRect,
    bool& isPaused,
    int mouseX, int mouseY,
    bool hasGameStarted,
    bool isGameOver,
    bool clicked
) {
    if (!isGameOver && hasGameStarted) {
        bool isHovered = (mouseX >= pauseRect.x &&
                         mouseX <= pauseRect.x + pauseRect.w &&
                         mouseY >= pauseRect.y &&
                         mouseY <= pauseRect.y + pauseRect.h);

        if (clicked && isHovered) {
            isPaused = !isPaused;
            isPaused ? Mix_Pause(-1) : Mix_Resume(-1);
        }

        SDL_Rect renderRect = isHovered ?
            SDL_Rect{pauseRect.x - 5, pauseRect.y - 5,
                    pauseRect.w + 10, pauseRect.h + 10} :
            pauseRect;
        SDL_RenderCopy(renderer, pauseTexture, nullptr, &renderRect);

        if (isPaused) {
            SDL_Color white = {255, 255, 255};
            renderText(renderer, font, "PAUSED",
                      SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 10, white);
        }
    }
}
void handleBackButton(
    SDL_Renderer* renderer,
    SDL_Texture* backTexture,
    SDL_Rect& backRect,
    bool& isHardMode,
    bool& isGameOver,
    bool& hasGameStarted,
    int& playerX, int& playerY,
    int& playerVelY,
    int& score,
    int& gameOverRectY,
    int mouseX, int mouseY,
    bool clicked,
    bool isFlipped,
    Mix_Chunk* clickSound
) {
    if (isGameOver) {
        bool isHovered = (mouseX >= backRect.x &&
                         mouseX <= backRect.x + backRect.w &&
                         mouseY >= backRect.y &&
                         mouseY <= backRect.y + backRect.h);

        if (clicked && isHovered) {
            isHardMode = !isHardMode;
            Mix_PlayChannel(-1, clickSound, 0);
            playerX = SCREEN_WIDTH / 2;
            playerY = SCREEN_HEIGHT / 2;
            playerVelY = 0;
            score = 0;
            createObstacles(isHardMode, isFlipped);
            isHardMode ? createSkulls() : skulls.clear();
            hasGameStarted = false;
            isGameOver = false;
            gameOverRectY = SCREEN_HEIGHT;
        }

        SDL_Rect renderRect = isHovered ?
            SDL_Rect{backRect.x - 5, backRect.y - 5,
                    backRect.w + 10, backRect.h + 10} :
            backRect;
        SDL_RenderCopy(renderer, backTexture, nullptr, &renderRect);
    }
}
void resetGame(bool& isGameOver, int& gameOverRectY, int& playerX, int& playerY,
               int& playerVelY, int& score, bool isHardMode, bool isFlipped) {
    isGameOver = false;
    gameOverRectY = SCREEN_HEIGHT;
    playerX = SCREEN_WIDTH / 2;
    playerY = SCREEN_HEIGHT / 2;
    playerVelY = 0;
    score = 0;
    createObstacles(isHardMode, isFlipped);
    if (isHardMode) createSkulls();
}
int main(int argc, char* argv[]) {
    if (!initializeSDL()) {
        return -1;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk* jumpSound = Mix_LoadWAV("click.wav");
    Mix_Chunk* scoreSound = Mix_LoadWAV("beep.wav");
    Mix_Chunk* gameOverSound = Mix_LoadWAV("bye.mp3");

    TTF_Font* font = TTF_OpenFont("hihi.ttf", 10);
    if (!font) {
        cout << "Font loading failed: " << TTF_GetError() << endl;
        return -1;
    }

    bool isHardMode = false;
    bool startGame = false;
    bool isRunning = true;

    showMainMenu(startGame, isHardMode);
    string selectedPlayer = showPlayerSelection(startGame);
    loadResources(selectedPlayer);

    if (!startGame) {
        cleanup();
        return 0;
    }

    int playerX = SCREEN_WIDTH / 2;
    int playerY = SCREEN_HEIGHT / 2;
    int playerVelY = 0;
    int playerVelX = PLAYER_SPEED;
    bool isFlipped = false;

    int score = 0;
    int highScore = loadHighScore();
    bool isGameOver = false;
    bool isPaused = false;
    bool hasGameStarted = false;
    int gameOverRectY = SCREEN_HEIGHT;
    Uint32 lastObstacleTime = 0;
    int obstacleSpeed = 10;
    int skullSpeed = 3;

    SDL_Rect pauseButtonRect = {SCREEN_WIDTH - 80, 20, 40, 40};
    SDL_Rect backButtonRect = {SCREEN_WIDTH/2 - 20, 400, 40, 40};

    createObstacles(isHardMode, isFlipped);
    if (isHardMode) createSkulls();

    SDL_Event event;
    while (isRunning) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        bool mouseClicked = false;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                if (isGameOver) {
                   resetGame(isGameOver, gameOverRectY, playerX, playerY,
                 playerVelY, score, isHardMode, isFlipped);
                }
                else if (!hasGameStarted) {
                    hasGameStarted = true;
                    playerVelY = JUMP_FORCE;
                    Mix_PlayChannel(-1, jumpSound, 0);
                }
                else if (!isPaused) {
                    playerVelY = JUMP_FORCE;
                    Mix_PlayChannel(-1, jumpSound, 0);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouseClicked = true;
            }
        }

        if (!isPaused && !isGameOver && hasGameStarted) {
            updateGameLogic(playerX, playerY, playerVelX, playerVelY, isFlipped,
                          score, highScore, isGameOver, hasGameStarted, isHardMode,
                          lastObstacleTime, obstacleSpeed, skullSpeed,
                          scoreSound, gameOverSound);
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect playerRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};
        SDL_RenderCopyEx(renderer, playerTexture, nullptr, &playerRect,
                        0, nullptr, isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        for (const auto& obstacle : obstacles) {
            SDL_Rect obstacleRect = {obstacle.x, obstacle.y, obstacle.width, obstacle.height};
            SDL_RenderCopy(renderer, obstacleTexture, nullptr, &obstacleRect);
        }

        if (isHardMode) {
            for (const auto& skull : skulls) {
                SDL_Rect skullRect = {skull.x, skull.y, skull.width, skull.height};
                SDL_RenderCopy(renderer, skullTexture, nullptr, &skullRect);
            }
        }

        handlePauseButton(renderer, pauseButtonTexture, font, pauseButtonRect,
                         isPaused, mouseX, mouseY, hasGameStarted, isGameOver, mouseClicked);
        handleBackButton(renderer, backButtonTexture, backButtonRect, isHardMode,
                        isGameOver, hasGameStarted, playerX, playerY, playerVelY,
                        score, gameOverRectY, mouseX, mouseY, mouseClicked, isFlipped, jumpSound);

        SDL_Color white = {255, 255, 255};
        renderText(renderer, font, "Score: " + to_string(score), 50, 20, white);
        renderText(renderer, font, "High Score: " + to_string(highScore), 200, 20, white);

        if (isGameOver) {
            showGameOver(gameOverRectY, font);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup();
    TTF_CloseFont(font);
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(scoreSound);
    Mix_FreeChunk(gameOverSound);
    Mix_CloseAudio();

    return 0;
}

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <fstream>
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
SDL_Texture* skullTexture = nullptr;
SDL_Texture* pauseButtonTexture = nullptr;

struct cnv {
    int x, y, width, height;
};
struct Skull {
    int x, y, width, height;
};

vector<cnv> cnvs;
vector<Skull> skulls;
int loadhighscore() {
int highscore = 0 ;
ifstream file ("highscore.txt");
if(file.is_open()) {
    file >> highscore;
    file.close();
}
return highscore;



}
void savehighscore(int highscore) {
ofstream file ("highscore.txt");
if (file.is_open()) { file << highscore ;
file.close();
}
}
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

bool loadanh(string s ) {
    SDL_Surface* surface = IMG_Load(s.c_str());


    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("cnv.png");


    cnvTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
            SDL_Surface* surface1 = IMG_Load("skull.png");

    skullTexture = SDL_CreateTextureFromSurface(renderer, surface1);
        SDL_FreeSurface(surface1);
    SDL_Surface* surface2 = IMG_Load("pause.png");
pauseButtonTexture = SDL_CreateTextureFromSurface(renderer, surface2);
        SDL_FreeSurface(surface2);

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

void taoskulls() {
skulls.clear();
    Skull skull1 = {0, 100 , 40 , 40 };
    Skull skull2 = {0, 800 , 40 , 40 };
    skulls.push_back(skull1);
    skulls.push_back(skull2);




}

void taocnvs( bool kt ) {
    if (!kt) {

    cnvs.clear();

const int MIN_GAP = 100 ;
const int MAX_HEIGHT = mh_cao / 3;
const int MIN_HEIGHT_EDGE = 250;
const int MAX_HEIGHT_EDGE = 300;
const int MIN_HEIGHT_MID = 100;
const int MAX_HEIGHT_MID = 200;

int topHeight = MIN_HEIGHT_EDGE + rand() % (MAX_HEIGHT_EDGE - MIN_HEIGHT_EDGE + 1);
cnv leftTop = {0, 0, cnv_rong, topHeight};
cnv rightTop = {mh_rong - cnv_rong, 0, cnv_rong, topHeight};

int bottomHeight = MIN_HEIGHT_EDGE + rand() % (MAX_HEIGHT_EDGE - MIN_HEIGHT_EDGE + 1);
int bottomY = mh_cao - bottomHeight;
cnv leftBottom = {0, bottomY, cnv_rong, bottomHeight};
cnv rightBottom = {mh_rong - cnv_rong, bottomY, cnv_rong, bottomHeight};

cnvs.push_back(leftTop);
cnvs.push_back(rightTop);
cnvs.push_back(leftBottom);
cnvs.push_back(rightBottom);

int midHeight = MIN_HEIGHT_MID + rand() % (MAX_HEIGHT_MID - MIN_HEIGHT_MID + 1);
int midY = topHeight + MIN_GAP + rand() % (mh_cao - topHeight - bottomHeight - MIN_GAP - midHeight);

if (rand() % 2 == 0) {
    cnv rightMid = {mh_rong - cnv_rong, midY, cnv_rong, midHeight};
    cnvs.push_back(rightMid);
} else {
    cnv leftMid = {0, midY, cnv_rong, midHeight};
    cnvs.push_back(leftMid);
}
    }
else {    cnvs.clear();

            const int MIN_GAP = 200;
    const int MAX_HEIGHT = mh_cao / 3;

    int topHeight = rand() % (MAX_HEIGHT - MIN_GAP) + MIN_GAP;
    cnv left = {0, 0, cnv_rong, topHeight};
    cnv right = {mh_rong - cnv_rong, 0, cnv_rong, topHeight};

    cnvs.push_back(left);
    cnvs.push_back(right);

}
}
void drawmenu(bool& startGame, bool& isHardMode) {
    SDL_Event e;
    bool inMenu = true;
    bool soundOn = true;
    SDL_Surface* menusurface = IMG_Load("menu.jpg");
    SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer, menusurface);

    Mix_Chunk* menuSound = Mix_LoadWAV("amthanh.mp3");
    if (menuSound && soundOn) {
        Mix_PlayChannel(-1, menuSound, 0);
    }

    SDL_Surface* speakerOnSurface = IMG_Load("loa.png");
    SDL_Surface* speakerOffSurface = IMG_Load("loa.png"); 
    SDL_Texture* speakerOnTexture = SDL_CreateTextureFromSurface(renderer, speakerOnSurface);
    SDL_Texture* speakerOffTexture = SDL_CreateTextureFromSurface(renderer, speakerOffSurface);
    SDL_FreeSurface(speakerOnSurface);
    SDL_FreeSurface(speakerOffSurface);

    const int speakerSize = 40;
    const int speakerX = mh_rong - speakerSize - 20;
    const int speakerY = 20;

    while (inMenu) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int easyButtonWidth = 100;
        int easyButtonHeight = 50;
        int easyButtonX = mh_rong / 2 - easyButtonWidth / 2;
        int easyButtonY = mh_cao / 2 - easyButtonHeight / 2 - 60;

        int hardButtonWidth = 100;
        int hardButtonHeight = 50;
        int hardButtonX = mh_rong / 2 - hardButtonWidth / 2;
        int hardButtonY = mh_cao / 2 - hardButtonHeight / 2 + 60;

        if (x >= easyButtonX && x <= easyButtonX + easyButtonWidth &&
            y >= easyButtonY && y <= easyButtonY + easyButtonHeight) {
            easyButtonWidth = 120;
            easyButtonHeight = 60;
            easyButtonX = mh_rong / 2 - easyButtonWidth / 2;
            easyButtonY = mh_cao / 2 - easyButtonHeight / 2 - 60;
        }

        if (x >= hardButtonX && x <= hardButtonX + hardButtonWidth &&
            y >= hardButtonY && y <= hardButtonY + hardButtonHeight) {
            hardButtonWidth = 120;
            hardButtonHeight = 60;
            hardButtonX = mh_rong / 2 - hardButtonWidth / 2;
            hardButtonY = mh_cao / 2 - hardButtonHeight / 2 + 60;
        }

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                inMenu = false;
                startGame = false;
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


bool check_vacham(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}
string selectnv(bool &startgame) {

    SDL_Event e;
    bool selectscreen = true;
    string selected = "";
    SDL_Surface* selectsurface = IMG_Load("menu2.png");
    SDL_Texture* selecttexture = SDL_CreateTextureFromSurface(renderer, selectsurface);
    SDL_FreeSurface(selectsurface);

    vector<cnv> v;
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
int main(int argc, char* argv[]) {
    if (!init()) {
        return -1;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk* amthanh = Mix_LoadWAV("click.wav");
    Mix_Chunk* amthanh1 = Mix_LoadWAV("beep.wav");
    Mix_Chunk* amthanh2 = Mix_LoadWAV("bye.mp3");

    TTF_Font* ourfont = TTF_OpenFont("hihi.ttf", 20);
    if (!ourfont) {
        cout << "Error" << TTF_GetError() << std::endl;
        return -1;
    }
    bool hardmode = false ;
    bool startGame = false;
    bool selectscreen = false ;
    drawmenu(selectscreen,hardmode);
    string selected = selectnv(startGame);
    loadanh(selected);
    if (!startGame) {
        close();
        return 0;
    }

    int vitX = mh_rong / 2;
    int vitY = mh_cao / 2;
    int vitVelY = 0;
    int vitVelX = vit_SPEED;

    bool quit = false;
    SDL_Event e;

    bool flipped = false;

    taocnvs(hardmode);

    Uint32 lastPassedTime = 0;
    int score = 0;
    bool gameOver = false;
    int gameOverRectY = mh_cao;
    bool gameStarted = false;
    int cnvtocdo = 10;
    int cnvtocdo1 = 2;
    int highscore = loadhighscore();
bool isPaused = false;

while (!quit) {
    Uint32 currentTime = SDL_GetTicks();
    SDL_Rect pauseButtonRect = {mh_rong - 80, 20, 60, 60};

int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isPauseHovered = (mouseX >= pauseButtonRect.x && mouseX <= pauseButtonRect.x + pauseButtonRect.w &&
                          mouseY >= pauseButtonRect.y && mouseY <= pauseButtonRect.y + pauseButtonRect.h);
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN && !gameOver && gameStarted) {
            if (isPauseHovered) {
                isPaused = !isPaused;
                if (isPaused) {
                    Mix_Pause(-1);
                } else {
                    Mix_Resume(-1);
                }
            }
        }
        else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE) {
                if (gameOver) {
                    gameOver = false;
                    gameOverRectY = mh_cao;
                    vitX = mh_rong / 2;
                    vitY = mh_cao / 2;
                    vitVelY = 0;
                    score = 0;
                    taocnvs(hardmode);
                    if (hardmode) {taoskulls();}
                    gameStarted = false ;


                } else if (!gameStarted) {
                    gameStarted = true;
                    vitVelY = JUMP_STRENGTH;
                    Mix_PlayChannel(-1, amthanh, 0);
                }
            else {vitVelY = JUMP_STRENGTH;
                    Mix_PlayChannel(-1, amthanh, 0);

            }
            }
        }
    }

    if (!isPaused && !gameOver && gameStarted) {
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
            lastPassedTime = 0;
            if (!hardmode) {
                taocnvs(hardmode);
            }
        }

        if (vitY < 0) {
            vitY = 0;
            vitVelY = 0;
        } else if (vitY + vit_SIZE > mh_cao) {
            vitY = mh_cao - vit_SIZE;
            vitVelY = 0;
        }
        if(hardmode) {
                    cnvs[0].y += cnvtocdo;
                                        cnvs[1].y += cnvtocdo;

                    if (cnvs[0].y < 0 || cnvs[0].y + cnvs[0].height > mh_cao) {
                        cnvtocdo = -cnvtocdo;
                    }


                for (auto& skull : skulls) {
                    skull.x += cnvtocdo1;
                    if (skull.x <= 0 || skull.x + skull.width >= mh_rong) {
                        cnvtocdo1 = -cnvtocdo1;
                    }
                }




        }
        SDL_Rect vitRect = {vitX, vitY, vit_SIZE, vit_SIZE};
        for (auto& cnv : cnvs) {
            SDL_Rect cnvRect = {cnv.x, cnv.y, cnv.width, cnv.height};
            if (check_vacham(vitRect, cnvRect)) {
                gameOver = true;
            }
        }
    if(hardmode) {
        for (auto &skull : skulls) {
                            SDL_Rect skullRect = {skull.x, skull.y, skull.width, skull.height};
                            if(check_vacham(skullRect,vitRect)) {
                                gameOver = true;
                            }

        }


    }
    }
        if (gameOver) {
            gameStarted = false;



        if (score > highscore) {
            highscore = score;
            savehighscore(score);
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
    if (hardmode) {
        for (auto& skull : skulls) {
            SDL_Rect skullRect = {skull.x, skull.y, skull.width, skull.height};
            SDL_RenderCopy(renderer, skullTexture, NULL, &skullRect);
            SDL_RenderDrawRect(renderer, &skullRect);
        }
}
    if (!gameOver && gameStarted && pauseButtonTexture != nullptr) {

        if (isPauseHovered) {
        SDL_Rect hoverRect = {
            pauseButtonRect.x - 5,
            pauseButtonRect.y - 5,
            pauseButtonRect.w + 10,
            pauseButtonRect.h + 10
        };
        SDL_RenderCopy(renderer, pauseButtonTexture, NULL, &hoverRect);
    } else {
        SDL_RenderCopy(renderer, pauseButtonTexture, NULL, &pauseButtonRect);
    }

    if (isPaused) {
        SDL_Surface* pausedSurface = TTF_RenderText_Solid(ourfont, "PAUSED", {255, 255, 255});
        SDL_Texture* pausedTexture = SDL_CreateTextureFromSurface(renderer, pausedSurface);
        SDL_Rect pausedRect = {mh_rong/2 - pausedSurface->w/2, mh_cao/2 - pausedSurface->h/2,
                              pausedSurface->w, pausedSurface->h};
        SDL_RenderCopy(renderer, pausedTexture, NULL, &pausedRect);
        SDL_FreeSurface(pausedSurface);
        SDL_DestroyTexture(pausedTexture);
    }
}

    string scoreText = "Score: " + to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(ourfont, scoreText.c_str(), {255, 255, 255});
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {50, 20, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
    string highscoreText = "MAX: " + to_string(highscore);
    SDL_Surface* highscoreSurface = TTF_RenderText_Solid(ourfont, highscoreText.c_str(), {255, 255, 255});
    SDL_Texture* highscoreTexture = SDL_CreateTextureFromSurface(renderer, highscoreSurface);
    SDL_Rect highscoreRect = {200, 20 , highscoreSurface->w, highscoreSurface->h};
    SDL_RenderCopy(renderer, highscoreTexture, NULL, &highscoreRect);
    SDL_FreeSurface(highscoreSurface);
    SDL_DestroyTexture(highscoreTexture);
    if (gameOver) {
        Mix_PlayChannel(-1, amthanh2, 0);

        if (gameOverRectY > mh_cao / 2 - 50) {
            gameOverRectY -= 15;
        }

        SDL_Rect gameOverRect = {mh_rong / 2 - 100, gameOverRectY, 200, 100};
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                SDL_RenderFillRect(renderer, &gameOverRect);

        SDL_Surface* gameOverSurface = TTF_RenderText_Solid(ourfont, "Game Over", {255, 255, 255});
        SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
        SDL_Rect gameOverTextRect = {mh_rong / 2 - 50, gameOverRectY + 20, gameOverSurface->w, gameOverSurface->h};
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverTextRect);

        SDL_Surface* replaySurface = TTF_RenderText_Solid(ourfont, "Press SPACE to replay", {255, 255,255});
        SDL_Texture* replayTexture = SDL_CreateTextureFromSurface(renderer, replaySurface);
        SDL_Rect replayTextRect = {mh_rong / 2 - 100 , gameOverRectY + 60, replaySurface->w, replaySurface->h};
        SDL_RenderCopy(renderer, replayTexture, NULL, &replayTextRect);


    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
}


    TTF_CloseFont(ourfont);
    Mix_FreeChunk(amthanh);
    Mix_FreeChunk(amthanh1);
    Mix_FreeChunk(amthanh2);

    Mix_CloseAudio();
return 0;
}

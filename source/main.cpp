#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

const string WINDOW_TITLE = "GAME V";
const int WINDOW_WIDTH = 1000;
const int WINDOw_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;

bool isRunning = true, flip = false;
string state = "normal";

string backgroundList[] = {
    "resource/background/background_1.png",
};

string explosionList[] = {
    "resource/explosion/Explosion_1.png",
    "resource/explosion/Explosion_2.png",
    "resource/explosion/Explosion_3.png",
    "resource/explosion/Explosion_4.png",
    "resource/explosion/Explosion_5.png",
    "resource/explosion/Explosion_6.png",
    "resource/explosion/Explosion_7.png",
    "resource/explosion/Explosion_8.png",
    "resource/explosion/Explosion_9.png",
    "resource/explosion/Explosion_10.png",
};

string characterRunList[] = {
    "resource/character/run/run_1.png",
    "resource/character/run/run_2.png",
};

string characterJumpList[] = {
    "resource/character/jump/jump_1.png",
    "resource/character/jump/jump_2.png",
    "resource/character/jump/jump_3.png",
    "resource/character/jump/jump_4.png",
};

string characterFlyList[] = {
    "resource/character/fly/fly_1.png",
    "resource/character/fly/fly_2.png",
};

string characterDownList[] = {
    "resource/character/down/down_1.png",
};

class LiveTexture {
public:
    LiveTexture() {};
    ~LiveTexture() {
        SDL_DestroyTexture(texture);
    };

    bool loadFromFile(std::string path) {
        texture = IMG_LoadTexture(renderer, path.c_str());
        return texture != nullptr;
    }

    void render(int x, int y, int w, int h, string path) {
        SDL_Rect renderQuad = {x, y, w, h};
        loadFromFile(path.c_str());
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    }

    SDL_Texture* texture;
};

class spriteSheet {
public:
    spriteSheet(int size = 0, string* spriteList = nullptr) {
        this->frameSize = size;
        this->spriteList = spriteList;
        spriteTexture = new LiveTexture;
        currentFrame = 0;
    }
    ~spriteSheet() {
        spriteTexture->~LiveTexture();
    };

    void render(int x, int y, int w, int h) {
        spriteTexture->render(x, y, w, h, spriteList[currentFrame]);
        ++ currentFrame;
        if (currentFrame == frameSize) {
            currentFrame = 0;
            state = "normal";
        }
    }

    LiveTexture* spriteTexture;
    string* spriteList;

    int frameSize;
    int currentFrame;

}* background;

class Character {
public:
    Character(int x = 0, int y = 0, int w = 0, int h = 0) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    };
    ~Character() {
        spriteTexture->~spriteSheet();
    };

    spriteSheet* spriteTexture;
    int x;
    int y;
    int w;
    int h;

}* character;

class CharacterState {
public:
    CharacterState() {};
    ~CharacterState() {
        explosion->~spriteSheet();
        run->~spriteSheet();
        jump->~spriteSheet();
        fly->~spriteSheet();
        down->~spriteSheet();
    };

    spriteSheet* explosion;
    spriteSheet* run;
    spriteSheet* jump;
    spriteSheet* fly;
    spriteSheet* down;
}* characterState;

void logSDLError() {
    printf("error!... %s\n", SDL_GetError());
    exit(0);
}

void init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) logSDLError();
    window = SDL_CreateWindow(
        WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOw_HEIGHT, SDL_WINDOW_SHOWN
    );
    if (window == nullptr) logSDLError();

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) logSDLError();

    character = new Character(100, WINDOw_HEIGHT - 100, 100, 100);

    characterState = new CharacterState;

    const int BACKGROUND_FRAME_SIZE = 1;
    background = new spriteSheet(BACKGROUND_FRAME_SIZE, backgroundList);

    const int CHARACTER_EXPLOSION_FRAME_SIZE = 10;
    characterState->explosion = new spriteSheet(CHARACTER_EXPLOSION_FRAME_SIZE, explosionList);

    const int CHARACTER_RUN_FRAME_SIZE = 2;
    characterState->run = new spriteSheet(CHARACTER_RUN_FRAME_SIZE, characterRunList);

    const int CHARACTER_JUMP_FRAME_SIZE = 4;
    characterState->jump = new spriteSheet(CHARACTER_JUMP_FRAME_SIZE, characterJumpList);    

    const int CHARACTER_FLY_FRAME_SIZE = 2;
    characterState->fly = new spriteSheet(CHARACTER_FLY_FRAME_SIZE, characterFlyList);

    const int CHARACTER_DOWN_FRAME_SIZE = 1;
    characterState->down = new spriteSheet(CHARACTER_DOWN_FRAME_SIZE, characterDownList);

    character->spriteTexture = characterState->run;
}

void close() {
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyTexture(texture);
    texture = nullptr;

    background->~spriteSheet();
    character->~Character();
    characterState->~CharacterState();

    IMG_Quit();
    SDL_Quit();
}

void handleEvent() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;

                    case SDLK_SPACE:
                        if (character->y == WINDOw_HEIGHT - character->h)
                            state = "jump";
                        else 
                            state = "fly";
                        break;
                    
                    case SDLK_q:
                        state = "explosion";
                }

                break;
        }
    }
}

void update() {
    if (state == "normal") {
        if (character->y == WINDOw_HEIGHT - character->h)
            character->spriteTexture = characterState->run;
        else {
            character->spriteTexture = characterState->down;
            if (character->y < WINDOw_HEIGHT - character->h)
                character->y += 5;
        }
    }
    
    if (state == "jump") {
        character->spriteTexture = characterState->jump;
        if (character->y)
            character->y -= 5;
    }

    if (state == "fly") {
        character->spriteTexture = characterState->fly;
        if (character->y)
            character->y -= 5;
    }

    if (state == "explosion") 
        character->spriteTexture = characterState->explosion;
}

void render() {
    SDL_RenderClear(renderer);

    background->render(0, 0, WINDOW_WIDTH, WINDOw_HEIGHT);
    character->spriteTexture->render(character->x, character->y, character->w, character->h);

    SDL_RenderPresent(renderer);
}

int main() {
    const int FPS = 15;
    const int frameDelay = 1200 / FPS;

    Uint32 frameStart;
    int frameTime;

    init();

    while (isRunning == true) {
        frameStart = SDL_GetTicks();

        handleEvent();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    close();
}
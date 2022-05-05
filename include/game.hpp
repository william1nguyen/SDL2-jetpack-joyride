#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

class Game {
public:
    const string WINDOW_TITLE = "GAME V";
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 400;

    static SDL_Renderer* renderer;
    
    void init();
    void handle_event();
    bool is_running();
    void update();
    void render();
    void close();

private:
    bool game_over = false;
    SDL_Window* window;
};
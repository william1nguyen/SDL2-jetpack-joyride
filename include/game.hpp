#include "library.hpp"
#include <time.h>

struct Game {
    const string WINDOW_TITLE = "GAME V";
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 400;

    SDL_Window* window;

    static SDL_Renderer* renderer;
    static int velocity;
    static int timer;

    static int highscore;
    static int total_coin;
    static int coin_earn_this_game;
    static int score_this_game;

    bool game_over = false;
    bool pause = false;

    static int Rand(int a, int b);

    void init();
    void handle_event();
    bool is_running();
    void update();
    void render();
    void close();
};

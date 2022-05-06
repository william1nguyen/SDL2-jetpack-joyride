#include "library.hpp"

class Game {
public:
    const string WINDOW_TITLE = "GAME V";
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 400;

    static SDL_Renderer* renderer;
    static int velocity;
    
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
#include "library.hpp"

struct Coin {
    SDL_Texture* texture;
    int current_frame = 0;
    int x;
    int y;
    int w;
    int h;
    
    bool coin_exist = true;
    int coin_earn_this_game = 0;

    int frame_size = 0;

    Coin();
    ~Coin();

    void update();
    void render();
};
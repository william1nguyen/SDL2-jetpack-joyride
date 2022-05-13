#include "library.hpp"

struct Background {
    // seperate screen to 2 side : left - right

    SDL_Rect render_quad;

    SDL_Texture* texture;
    
    int current_frame;
    int frame_size;

    Background();
    ~Background();

    void update();
    void render();
};
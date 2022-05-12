#include "library.hpp"

struct Background {
    // seperate screen to 2 side : left - right

    SDL_Rect render_quad_left;
    SDL_Rect render_quad_right;
    SDL_Rect dest_rect_left;
    SDL_Rect dest_rect_right;

    SDL_Texture* texture_left = NULL;
    SDL_Texture* texture_right = NULL;
    
    int current_frame = 0;
    int frame_size = 0;

    Background();
    ~Background();

    void update();
    void render();
};
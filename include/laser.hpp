#include "library.hpp"

struct Laser {
    SDL_Texture* texture;
    SDL_Rect render_quad;
    int current_frame = 0;
    int x;
    int y;
    int w;
    int h;

    int frame_size = 0;
    string state = "warning";
    string pre_state = "warning";

    Laser();
    ~Laser();

    void update();
    void render();
};

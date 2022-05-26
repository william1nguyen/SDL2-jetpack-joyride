#include "library.hpp"

struct Zapper {
    string* path;

    SDL_Texture* texture;
    SDL_Rect render_quad;
    int current_frame = 0;
    int x;
    int y;
    int w;
    int h;
    int id;

    int frame_size = 0;

    Zapper(int id = 0);
    ~Zapper();

    void update();
    void render();
};

#include "library.hpp"

struct Character {
    string* path;
    SDL_Rect render_quad;

    int frame_size = 0;
    string state = "normal";

    SDL_Texture* texture;
    int current_frame = 0;
    int x;
    int y;
    int w;
    int h;

    Character();
    ~Character();

    void update();
    void render();
    bool on_ground();
    void running();
    void jumping();
    void flying();
    void landing();
};
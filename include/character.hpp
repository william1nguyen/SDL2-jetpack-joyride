#include "game.hpp"

class Character {
public:
    string* path;
    SDL_Rect render_quad;

    int frame_size = 0;
    string state = "running";

    Character();
    ~Character();

    void render();
    bool on_ground();
    void running();
    void jumping();
    void flying();
    void landing();

private:
    SDL_Texture* texture;
    int current_frame = 0;
    int x;
    int y;
    int w;
    int h;
    int velocity;
};
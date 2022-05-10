#include "library.hpp"

class Missles {
public:
    int frame_size = 0;

    Missles();
    ~Missles();

    void update();
    void render();

private:
    SDL_Texture* texture;
    int current_frame = 0;
    int x;
    int y;
    int w;
    int h;
    int id;
};
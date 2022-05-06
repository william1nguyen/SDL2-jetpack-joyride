#include "library.hpp"

class Zapper {
public:
    string* path;
    SDL_Rect render_quad;

    int frame_size = 0;

    Zapper(int id = 0);
    ~Zapper();

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
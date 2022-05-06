#include "library.hpp"

class Background {
public:
    string* path;
    SDL_Rect render_quad;

    int frame_size = 0;

    Background();
    ~Background();

    void render();

private:
    SDL_Texture* texture;
    int current_frame = 0;
};
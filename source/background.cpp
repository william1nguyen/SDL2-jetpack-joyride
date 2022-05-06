#include "../include/background.hpp"
#include "../include/game.hpp"

const int background_frame_size = 3;
string background_path[] = {
    "resource/background/Sector_0.png",
    "resource/background/Sector_1.png",
    "resource/background/Sector_2.png",
};

const int background_width_pixel = 2048;
const int background_height_pixel = 461;

Background::Background() {
    frame_size = background_frame_size;

    render_quad = {
        0, 0, background_width_pixel/4, background_height_pixel
    };

    path = new string[frame_size];
    path = background_path;
};
Background::~Background() {
    SDL_DestroyTexture(texture);
};

void Background::render() {
    texture = IMG_LoadTexture(Game::renderer, path[1].c_str());
    SDL_RenderCopy(Game::renderer, texture, &render_quad, NULL);
    
    ++ current_frame;
    if (current_frame == frame_size) 
        current_frame = 0;
    ++ render_quad.x;
    if (render_quad.x == background_width_pixel)
        render_quad.x = 0;

}
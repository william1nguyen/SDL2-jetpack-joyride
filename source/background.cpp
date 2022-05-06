#include "../include/background.hpp"
#include "../include/game.hpp"

const int background_frame_size = 1;
string background_path[] = {
    "resource/background/Sector_0.png",
    "resource/background/Sector_1.png",
    "resource/background/Sector_2.png",
};

Background::Background() {
    frame_size = background_frame_size;
    path = new string[frame_size];
    path = background_path;
};
Background::~Background() {
    SDL_DestroyTexture(texture);
};

void Background::render() {
    texture = IMG_LoadTexture(Game::renderer, path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, NULL);
    
    ++ current_frame;
    if (current_frame == frame_size) 
        current_frame = 0;
}
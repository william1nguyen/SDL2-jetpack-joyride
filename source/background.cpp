#include "../include/background.hpp"
#include "../include/game.hpp"

const int background_frame_size = 13;
string background_path[] = {
    "resource/background/0.png",
    "resource/background/1.png",
    "resource/background/2.png",
    "resource/background/3.png",
    "resource/background/4.png",
    "resource/background/5.png",
    "resource/background/6.png",
    "resource/background/7.png",
    "resource/background/8.png",
    "resource/background/9.png",
    "resource/background/10.png",
    "resource/background/11.png",
    "resource/background/12.png",
};

const int background_width_pixel = 2048;
const int background_render_width = background_width_pixel / 4;
const int background_height_pixel = 461;

Background::Background() {
    frame_size = background_frame_size;

    render_quad_left = {
        0, 0, background_render_width, background_height_pixel
    };

    dest_rect_left = {
        0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT
    };

    render_quad_right = {
        0, 0, background_render_width, background_height_pixel
    };

    dest_rect_right = {
        Game::WINDOW_WIDTH, 0, 0, Game::WINDOW_HEIGHT 
    };
};
Background::~Background() {
    SDL_DestroyTexture(texture_left);
    texture_left = NULL;
    SDL_DestroyTexture(texture_right);
    texture_right = NULL;
};

void Background::update() {
    
}

void Background::render() { 
    texture_left = IMG_LoadTexture(Game::renderer, background_path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture_left, &render_quad_left, &dest_rect_left);
    
    SDL_DestroyTexture(texture_left);
    texture_left = NULL;

    //texture_right = IMG_LoadTexture(Game::renderer, background_path[(current_frame + 1) % frame_size].c_str());
    //SDL_RenderCopy(Game::renderer, texture_right, &render_quad_right, &dest_rect_right);
    
    //SDL_DestroyTexture(texture_right);
    //texture_right = NULL;

    update();
}
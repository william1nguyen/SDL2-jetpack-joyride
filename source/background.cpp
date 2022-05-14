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

const int background_render_width = Game::WINDOW_WIDTH / 8;

Background::Background() {
    texture = NULL;
    
    frame_size = background_frame_size;
    current_frame = 0;

    render_quad = {
        0, 0, background_render_width, Game::WINDOW_HEIGHT
    };
};
Background::~Background() {
    SDL_DestroyTexture(texture);
    texture = NULL;
};

void Background::update() {
    render_quad.x += Game::velocity / 5;
    if (render_quad.x >= Game::WINDOW_WIDTH / 2) {
        render_quad.x %= Game::WINDOW_WIDTH / 2;
        current_frame = (current_frame + 1) % frame_size;
    }
}

void Background::render() { 
    SDL_Rect render_space = {
        0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT
    }; 

    texture = IMG_LoadTexture(Game::renderer, background_path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, &render_quad, &render_space);

    SDL_DestroyTexture(texture);
    texture = NULL;

    update();
}
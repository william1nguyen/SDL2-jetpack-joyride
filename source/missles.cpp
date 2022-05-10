#include "../include/missles.hpp"
#include "../include/game.hpp"

const int missles_frame_size = 24;
const string missles_path[] = {
    "resource/missles/1m.png",
    "resource/missles/1m1.png",
    "resource/missles/1m.png",
    "resource/missles/1m1.png",
    "resource/missles/1m.png",
    "resource/missles/1m1.png",
    "resource/missles/2m.png",
    "resource/missles/2m2.png",
    "resource/missles/2m.png",
    "resource/missles/2m2.png",
    "resource/missles/2m.png",
    "resource/missles/2m2.png",
    "resource/missles/1.png",
    "resource/missles/2.png",
    "resource/missles/3.png",
    "resource/missles/4.png",
    "resource/missles/5.png",
    "resource/missles/6.png",
    "resource/missles/7.png",
    "resource/missles/8.png",
    "resource/missles/9.png",
    "resource/missles/10.png",
    "resource/missles/11.png",
    "resource/missles/12.png",
};

Missles::Missles() {
    frame_size = missles_frame_size;
    w = 100;
    h = 50;
    x = Game::WINDOW_WIDTH - w;
    y = 0;
}
Missles::~Missles() {
    SDL_DestroyTexture(texture);
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

void Missles::update() {
    if (current_frame <= 12)
        return;
    x -= Game::velocity;
    if (x < -w) {
        x = Game::WINDOW_WIDTH - w;
        current_frame = 0;
    }
}

void Missles::render() {
    SDL_Rect render_quad = {x, y, w, h};
    texture = IMG_LoadTexture(Game::renderer, missles_path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, &render_quad);

    SDL_DestroyTexture(texture);
    texture = NULL;

    ++ current_frame;
    if (current_frame == frame_size)
        current_frame = 13;
}
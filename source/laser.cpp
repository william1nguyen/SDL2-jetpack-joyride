#include "../include/laser.hpp"
#include "../include/game.hpp"

const int laser_frame_warning_size = 30;
const int laser_frame_beam_size = 20;

const int laser_frame_size = 70;
const string laser_path[] = {
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/0.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
    "resource/lazer/1.png",
    "resource/lazer/2.png",
};

Laser::Laser() {
    texture = NULL;
    current_frame = 0;
    frame_size = laser_frame_size;
    x = 0;
    y = 0;
    w = Game::WINDOW_WIDTH;
    h = 50;
    render_quad = {x, y, w, h};
}

Laser::~Laser() {
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Laser::update() {

}

void Laser::render() {
    render_quad = {x, y, w, h};

    texture = IMG_LoadTexture(Game::renderer, laser_path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, &render_quad);

    SDL_DestroyTexture(texture);
    texture = NULL;

    ++ current_frame;
    if (current_frame == frame_size) {
        current_frame = 0;
        y = Game::Rand(0, Game::WINDOW_HEIGHT - h);
    }

    if (current_frame <= laser_frame_warning_size)
        state = "warning";
    else
        state = "beaming";
}

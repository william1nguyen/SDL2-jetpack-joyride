#include "../include/coin.hpp"
#include "../include/game.hpp"

const int coin_frame_size = 12;
const string coin_frame_path[] = {
    "resource/coin/1.1.png",
    "resource/coin/1.png",
    "resource/coin/2.1.png",
    "resource/coin/2.png",
    "resource/coin/3.1.png",
    "resource/coin/3.png",
    "resource/coin/4.1.png",
    "resource/coin/4.png",
    "resource/coin/5.1.png",
    "resource/coin/5.png",
    "resource/coin/6.1.png",
    "resource/coin/6.png",
};

Coin::Coin() {
    texture = NULL;
    frame_size = coin_frame_size;
    current_frame = 0;
    coin_exist = true;
    w = 20;
    h = 20;
    x = Game::WINDOW_WIDTH;
    y = Game::Rand(0, Game::WINDOW_HEIGHT - 200);
}
Coin::~Coin() {
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Coin::update() {
    x -= Game::velocity;
    if (x < -200) {
        x = Game::WINDOW_WIDTH;
        y = Game::Rand(0, Game::WINDOW_HEIGHT - 200);
    }
}

void Coin::render() {
    if (coin_exist == false)
        return;

    SDL_Rect render_quad = {x, y, w, h};

    texture = IMG_LoadTexture(Game::renderer, coin_frame_path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, &render_quad);

    SDL_DestroyTexture(texture);
    texture = NULL;

    ++ current_frame;
    if (current_frame == frame_size) {
        current_frame = 0;
    }
}
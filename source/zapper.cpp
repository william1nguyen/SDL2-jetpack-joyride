#include "../include/zapper.hpp"
#include "../include/game.hpp"

const int zapper_frame_size = 4;
string zapper_diagonal_path[] = {
    "resource/zappers/diagonal/d1.png",
    "resource/zappers/diagonal/d2.png",
    "resource/zappers/diagonal/d3.png",
    "resource/zappers/diagonal/d4.png",
};

string zapper_horizontal_path[] = {
    "resource/zappers/horizontal/h1.png",
    "resource/zappers/horizontal/h2.png",
    "resource/zappers/horizontal/h3.png",
    "resource/zappers/horizontal/h4.png",
};

string zapper_vertical_path[] = {
    "resource/zappers/vertical/v1.png",
    "resource/zappers/vertical/v2.png",
    "resource/zappers/vertical/v3.png",
    "resource/zappers/vertical/v4.png",
};

string zapper_type[] = {"", "diagonal", "horizontal", "vertical"};
string* zapper_path[] = {NULL, zapper_diagonal_path, zapper_horizontal_path, zapper_vertical_path};
pair <int, int> zapper_w_h[] = {
    {0, 0}, {150, 150}, {180, 60}, {60, 180}
};

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int Rand(int a, int b) {
    return uniform_int_distribution <int> (a, b) (rng);
}

Zapper::Zapper(int id) {
    frame_size = zapper_frame_size;
    this->id = id;
    path = zapper_path[id];
    w = zapper_w_h[id].first;
    h = zapper_w_h[id].second;
    x = Game::WINDOW_WIDTH - w + id * w;
    y = Rand(0, Game::WINDOW_HEIGHT - 2 * h);
}
Zapper::~Zapper() {
    SDL_DestroyTexture(texture);
}

void Zapper::update() {
    x = x - Game::velocity;
    if (x < -w) {
        id = Rand(1, 3);
        path = zapper_path[id];
        w = zapper_w_h[id].first;
        h = zapper_w_h[id].second;

        x = Game::WINDOW_WIDTH - w + id*w;
        y = Rand(0, Game::WINDOW_HEIGHT - h);
    }
}   

void Zapper::render() {
    render_quad = {x, y, w, h};
    texture = IMG_LoadTexture(Game::renderer, path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, &render_quad);
    
    ++ current_frame;
    if (current_frame == frame_size) 
        current_frame = 0;
}
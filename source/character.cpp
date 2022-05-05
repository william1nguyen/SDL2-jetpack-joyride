#include "../include/character.hpp"

const int character_running_frame_size = 4;
string character_running_path[] = {
    "resource/character/running/running_1.png",
    "resource/character/running/running_1.png",
    "resource/character/running/running_2.png",
    "resource/character/running/running_2.png",
};

const int character_jumping_frame_size = 4;
string character_jumping_path[] = {
    "resource/character/jumping/jumping_1.png",
    "resource/character/jumping/jumping_2.png",
    "resource/character/jumping/jumping_3.png",
    "resource/character/jumping/jumping_4.png",
};

const int character_flying_frame_size = 2;
string character_flying_path[] = {
    "resource/character/flying/flying_1.png",
    "resource/character/flying/flying_2.png",
};

const int character_landing_frame_size = 1;
string character_landing_path[] = {
    "resource/character/landing/landing_1.png",
};

const int ground = Game::WINDOW_HEIGHT;

Character::Character() {
    path = new string[frame_size];
    w = 50;
    h = 50;
    x = Game::WINDOW_WIDTH / 3;
    y = ground - h;
    velocity = 5;
};
Character::~Character() {
    delete path;
    path = NULL;

    SDL_DestroyTexture(texture);
    texture = NULL;
};

void Character::render() {
    render_quad = {x, y, w, h};
    texture = IMG_LoadTexture(Game::renderer, path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, &render_quad);
    
    ++ current_frame;
    if (current_frame == frame_size) {
        current_frame = 0;
        if (on_ground())
            state = "running";
        else 
            state = "landing";
    }
}

bool Character::on_ground() { return y == ground - h; }

void Character::running() {
    if (state != "running") return;
    frame_size = character_running_frame_size;
    path = character_running_path;
    current_frame = 0;
    state = "normal";
}

void Character::jumping(){
    if (state != "jumping") return;
    y = (y - velocity) ? y - velocity : y;
    frame_size = character_jumping_frame_size;
    path = character_jumping_path;
    current_frame = 0;
    state = "normal";
}

void Character::flying() {
    if (state != "flying") return;
    y = (y - velocity) ? y - velocity : y;
    frame_size = character_flying_frame_size;
    path = character_flying_path;
    current_frame = 0;
    state = "normal";
}

void Character::landing() {
    if (state != "landing") return;
    y = (!on_ground()) ? y + velocity : y;
    frame_size = character_landing_frame_size;
    path = character_landing_path;
    current_frame = 0;
    state = "normal";
}
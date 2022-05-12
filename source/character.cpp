#include "../include/character.hpp"
#include "../include/game.hpp"

const int character_running_frame_size = 2;
string character_running_path[] = {
    "resource/character/running/running_1.png",
    //"resource/character/running/running_1.png",
    //"resource/character/running/running_2.png",
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

const int ground = Game::WINDOW_HEIGHT - 20;

Character::Character() {
    path = new string[frame_size];
    w = 70;
    h = 70;
    x = Game::WINDOW_WIDTH / 3;
    y = ground - h;
};
Character::~Character() {
    SDL_DestroyTexture(texture);
};

void Character::update() {
    if (state == "jumping") {
        jumping();
    }  else if (state == "flying") {
        flying();
    } else {
        if (on_ground()) 
            running();
        else  
            landing();
    }
}

void Character::render() {
    render_quad = {x, y, w, h};
    if(texture != nullptr) 
        texture = nullptr;
        
    texture = IMG_LoadTexture(Game::renderer, path[current_frame].c_str());
    SDL_RenderCopy(Game::renderer, texture, NULL, &render_quad);
    
    ++ current_frame;
    if (current_frame == frame_size) {
        current_frame = 0;
        state = "normal";
    }
}

bool Character::on_ground() { return y == ground - h; }

void Character::running() {
    frame_size = character_running_frame_size;
    if (path != character_running_path) {
        path = character_running_path;
        current_frame = 0;
    }
}

void Character::jumping(){
    y = max(y - Game::velocity, 0);
    frame_size = character_jumping_frame_size;
    if (path != character_jumping_path) {
        path = character_jumping_path;
        current_frame = 0;
    }
}

void Character::flying() {
    y = max(y - Game::velocity, 0);
    frame_size = character_flying_frame_size;
    if (path != character_flying_path) {
        path = character_flying_path;
        current_frame = 0;
    }
}

void Character::landing() {
    y = (!on_ground()) ? y + Game::velocity / 2 : y;
    frame_size = character_landing_frame_size;
    if (path != character_landing_path) {
        path = character_landing_path;
        current_frame = 0;
    }
}
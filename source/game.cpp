#include "../include/character.hpp"

SDL_Renderer* Game::renderer;
const int Game::WINDOW_HEIGHT;
const int Game::WINDOW_WIDTH;

Character* character;

void Game::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    character = new Character;
}

void Game::close() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}

void Game::handle_event() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                game_over = true;
                break;
            
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        game_over = true;
                        break;
                    case SDLK_SPACE:
                        if (character->on_ground())
                            character->state = "jumping";
                        else 
                            character->state = "flying";
                        break;
                }

                break;
        }
    }
}

bool Game::is_running() { return game_over == false; }

void Game::update() {
    if (character->state == "running")
        character->running();

    if (character->state == "jumping")
        character->jumping();
    
    if (character->state == "flying")
        character->flying();
    
    if (character->state == "landing")
        character->landing();
}

void Game::render() {
    SDL_RenderClear(renderer);
    
    character->render();

    SDL_RenderPresent(renderer);
}
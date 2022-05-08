#include "../include/game.hpp"
#include "../include/character.hpp"
#include "../include/background.hpp"
#include "../include/zapper.hpp"

SDL_Renderer* Game::renderer;
const int Game::WINDOW_HEIGHT;
const int Game::WINDOW_WIDTH;

int Game::velocity;

Background* background;
Character* character;
Zapper* zapper;

void Game::init() {
    srand(time(0));

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    velocity = 8;

    background = new Background;
    character = new Character;
    
    zapper = new Zapper(rand() % 3 + 1);
}

void Game::close() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete background;
    delete character;
    delete zapper;
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
    character->update();
    zapper->update();
}   

void Game::render() {
    SDL_RenderClear(renderer);

    background->render();

    character->render();
    zapper->render();

    SDL_RenderPresent(renderer);
}
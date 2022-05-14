#include "../include/game.hpp"
#include "../include/character.hpp"
#include "../include/background.hpp"
#include "../include/missles.hpp"
#include "../include/zapper.hpp"
#include "../include/laser.hpp"
#include "../include/coin.hpp"

#include <fstream>

SDL_Renderer* Game::renderer;
const int Game::WINDOW_HEIGHT;
const int Game::WINDOW_WIDTH;
const int number_of_coin_on_line = 8;
const int number_of_coin_on_row = 4;

int Game::velocity;
int Game::timer;
int Game::total_coin;
int Game::highscore;

Background* background;
Character* character;
Missles* missles;
Zapper* zapper;
Laser* laser;
Coin* coin_base;
Coin** coin;

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int Game::Rand(int a, int b) {
    return uniform_int_distribution <int> (a, b) (rng);
}

void Game::init() {
    srand(time(0));

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    velocity = 20;
    timer = 0;
    coin_earn_this_game = 0;
    score_this_game = 0;
    
    ifstream inp;
    inp.open("highscore.txt");
    inp >> highscore;
    inp.close();

    inp.open("coin.txt");
    inp >> total_coin;
    inp.close();

    background = new Background;
    character = new Character;
    missles = new Missles();
    zapper = new Zapper(rand() % 3 + 1);
    laser = new Laser();
    coin_base = new Coin();

    coin = new Coin* [number_of_coin_on_row];
    for (int i = 0; i < number_of_coin_on_row; ++i) 
        coin[i] = new Coin[number_of_coin_on_line];

    for (int i = 0; i < number_of_coin_on_row; ++i)
        for (int j = 0; j < number_of_coin_on_line; ++j) {
            coin[i][j].w = 30;
            coin[i][j].h = 30;
            coin[i][j].y = coin_base->y + i * 30;
            coin[i][j].x = coin_base->x + j * 30;
        }
}

void Game::close() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    delete background;
    background = NULL;

    delete character;
    character = NULL;
    
    delete zapper;
    zapper = NULL;
    
    delete missles;
    missles = NULL;

    delete laser;
    laser = NULL;

    delete coin_base;
    coin_base = NULL;

    delete [] coin;
        
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
                    case SDLK_p:
                        pause = true;
                        break;
                    case SDLK_c:
                        pause = false;
                        break;
                }
                break;
        }
    }
}

bool Game::is_running() { 
    if (laser->y < character->y && character->y < laser->y + laser->h - 20 && laser->state == "beaming") {
        Game::game_over = true;
    }

    if (max(character->x, missles->x) < min(character->x + character->w, missles->x + missles->w) - 15)
        if (max(character->y, missles->y) < min(character->y + character->h, missles->y + missles->h) - 15)
            Game::game_over = true;

    if (max(character->x, zapper->x) < min(character->x + character->w, zapper->x + zapper->w) - 30)
        if (max(character->y, zapper->y) < min(character->y + character->h, zapper->y + zapper->h) - 30)
            Game::game_over = true;

    return game_over == false; 
}

void Game::update() {
    if (pause)
        return;
    ++ timer;
    ++ score_this_game;

    highscore = max(highscore, score_this_game);

    character->update();
    missles->update();
    zapper->update();
    coin_base->update();

    for (int i = 0; i < number_of_coin_on_row; ++i)
        for (int j = 0; j < number_of_coin_on_line; ++j) {
            if (coin_base->x == Game::WINDOW_WIDTH)
                coin[i][j].coin_exist = true;

            coin[i][j].y = coin_base->y + i * 30;
            coin[i][j].x = coin_base->x + j * 30;

            if (max(character->x, coin[i][j].x) < min(character->x + character->w, coin[i][j].x + coin[i][j].w))
                if (max(character->y, coin[i][j].y) < min(character->y + character->h, coin[i][j].y + coin[i][j].h)) {
                    ++ coin_earn_this_game;
                    ++ total_coin;
                    coin[i][j].coin_exist = false;
                }
        }
}      

void Game::render() {
    if (pause) 
        return;
    SDL_RenderClear(renderer);

    background->render();
    

    character->render();
    zapper->render();
    missles->render();
    laser->render();
    
    for (int i = 0; i < number_of_coin_on_row; ++i)
        for (int j = 0; j < number_of_coin_on_line; ++j)
            coin[i][j].render();

    SDL_RenderPresent(Game::renderer);
}
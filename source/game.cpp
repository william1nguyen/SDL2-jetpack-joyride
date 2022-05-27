#include "../include/SBDL.hpp"
#include "../include/game.hpp"
#include "../include/sound.hpp"
#include "../include/character.hpp"
#include "../include/background.hpp"
#include "../include/missles.hpp"
#include "../include/zapper.hpp"
#include "../include/laser.hpp"
#include "../include/coin.hpp"
#include "../include/menu.hpp"

#include <fstream>

SDL_Renderer* Game::renderer;
const int Game::WINDOW_HEIGHT;
const int Game::WINDOW_WIDTH;

int Game::velocity;
int Game::timer;
int Game::total_coin;
int Game::highscore;
int Game::score_this_game = 0;
int Game::coin_earn_this_game = 0;
bool temporary_lose = false;

TTF_Font *score_font;

Character* barry;
Missles* missles;
Zapper* zapper;
Laser* laser;

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int Game::Rand(int a, int b) {
    return uniform_int_distribution <int> (a, b) (rng);
}

Music *game_music;
Sound *coin_sound, *missle_warning_sound, *laser_warning_sound;
Sound *laser_fire_sound, *missle_launch_sound;

bool init_music() {
    game_music = SBDL::loadMusic ("music.mp3");

    SBDL::playMusic (game_music, -1);

    coin_sound = SBDL::loadSound ("coin.wav");
    missle_warning_sound = SBDL::loadSound ("missile_warning.wav");
    laser_warning_sound = SBDL::loadSound ("laser_warning.wav");
    missle_launch_sound = SBDL::loadSound ("missile_launch.wav");
    laser_fire_sound = SBDL::loadSound("laser_fire.wav");

    return true;
}

bool play_sound (string s) {
    if (s == "coin") SBDL::playSound(coin_sound, 1);
    if (s == "missles_warning") SBDL::playSound(missle_warning_sound, 1);
    if (s == "missles_launch") SBDL::playSound(missle_launch_sound, 1);
    if (s == "laser_warning") SBDL::playSound(laser_warning_sound, 1);
    if (s == "laser_fire") SBDL::playSound(laser_fire_sound, 1);
    return true;
}

void init_high_score() {
    ifstream inp;
    inp.open("highscore.txt");
    inp >> Game::highscore;
    inp.close();
}

void init_coin() {
    ifstream inp;
    inp.open("coin.txt");
    inp >> Game::total_coin;
    inp.close();
}

void score_add() {
    ++ Game::score_this_game;
    if (Game::score_this_game > Game::highscore) {
        Game::highscore = Game::score_this_game;
        ofstream out;
        out.open ("highscore.txt");
        out << Game::highscore << "\n";
        out.close();
    }
}

void coin_add() {
    ++ Game::coin_earn_this_game;
    ++ Game::total_coin;
    ofstream out;
    out.open ("coin.txt");
    out << Game::total_coin << "\n";
    out.close();
}

void show_score() {
    Texture score_tex = SBDL::createFontTexture (score_font, "score : " + std::to_string(Game::score_this_game), 255, 255, 255);
    SBDL::showTexture (score_tex, 0, 0);
    SBDL::freeTexture (score_tex);
}

void show_high_score() {
    if (temporary_lose) {
        Texture score_tex = SBDL::createFontTexture (score_font, "high score : " + std::to_string(Game::highscore), 255, 255, 255);
        SBDL::showTexture (score_tex, 300, 100);
        SBDL::freeTexture (score_tex);
        return;
    }
}

void show_coin() {
    Texture coin_tex = SBDL::createFontTexture (score_font, "coin : " + std::to_string(Game::coin_earn_this_game), 255, 255, 255);
    SBDL::showTexture (coin_tex, 0, 50);
    SBDL::freeTexture (coin_tex);
}

void show_total_coin() {
    if (temporary_lose) {
        Texture coin_tex = SBDL::createFontTexture (score_font, "total coin : " + std::to_string(Game::total_coin), 255, 255, 255);
        SBDL::showTexture (coin_tex, 300, 150);
        SBDL::freeTexture (coin_tex);
        return;
    }
}

void show_message() {
    if (temporary_lose) {
        Texture msg_tex = SBDL::createFontTexture (score_font, "Press R to restart or Q to quit", 255, 255, 255);
        SBDL::showTexture (msg_tex, 200, 300);
        SBDL::freeTexture (msg_tex);
    }
}

void Game::init() {
    srand(time(0));

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SBDL::Core::renderer = renderer;

    SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // make scaled rendering smoother

    velocity = 10;
    timer = 0;
    coin_earn_this_game = 0;
    score_this_game = 0;

    init_high_score();
    init_coin();

    load_background_texture();

    barry = new Character;
    missles = new Missles();
    zapper = new Zapper(rand() % 3 + 1);
    laser = new Laser();

    load_coin_texture();
    restart_coins();

    TTF_Init();
    score_font = SBDL::loadFont("Jetpackia.ttf", 30);

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ); // init SDL_Mixer
    init_music();
}

void Game::game_restart() {
    game_over = temporary_lose = false;
    velocity = 10;
    timer = 0;
    coin_earn_this_game = 0;
    score_this_game = 0;

    first_x = 0;
    came_x = 0;

    barry = new Character;
    missles = new Missles();
    zapper = new Zapper(rand() % 3 + 1);
    laser = new Laser();

    load_coin_texture();
    restart_coins();

    init_music();
}

void Game::close() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    delete barry;
    barry = NULL;

    delete zapper;
    zapper = NULL;

    delete missles;
    missles = NULL;

    delete laser;
    laser = NULL;

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
                        if (barry->on_ground())
                            barry->state = "jumping";
                        else
                            barry->state = "flying";
                        break;
                    case SDLK_p:
                        pause = true;
                        break;
                    case SDLK_c:
                        pause = false;
                        break;
                    case SDLK_q:
                        game_over = true;
                        break;
                    case SDLK_r:
                        game_restart();
                        break;
                }
                break;
        }
    }

    SBDL::updateEvents();

    // Do SDL_KEYDOWN khong the giu key duoc khi barry jump nen ta dung keyHold()

    if (SBDL::keyHold(SDL_SCANCODE_SPACE)) // hold key
        barry->state = "flying";

    if (SBDL::keyRelease(SDL_SCANCODE_SPACE)) // not hold key anymore
        barry->state = "normal";
}

bool Game::is_running() {
    if (laser->y < barry->y && barry->y < laser->y + laser->h - 20 && laser->state == "beaming") {
        temporary_lose = true;
    }

    if (max(barry->x, missles->x) < min(barry->x + barry->w, missles->x + missles->w) - 15)
        if (max(barry->y, missles->y) < min(barry->y + barry->h, missles->y + missles->h) - 15)
            temporary_lose = true;

    if (max(barry->x, zapper->x) < min(barry->x + barry->w, zapper->x + zapper->w) - 30)
        if (max(barry->y, zapper->y) < min(barry->y + barry->h, zapper->y + zapper->h) - 30)
            temporary_lose = true;

    return game_over == false;
}

void Game::update() {
    if (pause || temporary_lose) {
        SBDL::stopAllSound();
        return;
    }

    score_add();
    ++ timer;

    barry->update();
    missles->update();
    zapper->update();
    move_coin();

    for (int i = 0; i < coins_height; ++i)
        for (int j = 0; j < coins_width; ++j) {
            if (!coins[i][j].show)
                continue;
            SDL_Rect render_quad = {coins[i][j].x, coins[i][j].y, coin_tex[0].width, coin_tex[0].height};

            if (SBDL::hasIntersectionRect(barry->render_quad, render_quad)) {
                coin_add();
                coins[i][j].show = false;
                play_sound ("coin");
            }
        }

    if (timer % 158 == 0)
        missles->state = "warning";
    if (timer % 312 == 0)
        laser->state = "fire";
}

void Game::render() {
    // load menu when lose
    if (pause || temporary_lose) {
        Texture lose_background = SBDL::loadTexture("resource/menu/pauseb.png");
        SBDL::showTexture(lose_background, 0, 0);
    }
    show_high_score();
    show_total_coin();
    show_message();

    SBDL::updateRenderClear();

    if (pause || temporary_lose)
        return;
    SDL_RenderClear(renderer);

    show_background();

    barry->render();
    zapper->render();

    if (missles->state != "normal") {
        missles->render();
    }

    laser->render();
    if (laser->state == "warning") {
        SBDL::stopAllSound();
        play_sound ("laser_warning");
    } else {
        SBDL::stopAllSound();
        play_sound ("laser_fire");
    }

    show_coin_texture();

    show_score();
    show_coin();

    SDL_RenderPresent(Game::renderer);
}

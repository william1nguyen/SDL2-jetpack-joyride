#include "../include/game.hpp"
#include <fstream>

Game* game;

int main() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game;

    game->init();

    while (game->is_running()) {
        frameStart = SDL_GetTicks();

        game->handle_event();
        game->update();
        game->render();
        

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    ofstream out;
    out.open("highscore.txt");
    out << Game::highscore << endl;
    out.close();

    out.open("coin.txt");
    out << Game::total_coin << endl;
    out.close();

    game->close();
}
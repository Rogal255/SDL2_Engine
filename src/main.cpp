#include "SDL.h"
#include "Game.hpp"
#include <iostream>

int main([[maybe_unused]] int arc, [[maybe_unused]] char* argv[]) {
    Game game;
    game.init();
    std::cout << "text\n";
    SDL_Delay(2000);
    SDL_Quit();
    return 0;
}

#pragma once
#include "SDL.h"
#include <memory>

class Game {
public:
    Game() = default;
    ~Game() = default;
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void init();

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_ {nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_ {nullptr, SDL_DestroyRenderer};
};

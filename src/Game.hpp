#pragma once
#include "SDL.h"
#include "Updatable.hpp"
#include "GameObservers.hpp"
#include <memory>
#include <vector>

class Game : public GameObservers {
public:
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    static std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
    static std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;

    void mainLoop();

private:
    void handleEvents();
    void render();

    bool isRunning_ {true};
    SDL_Event event_;

    // TODO: Load those from file
    const bool windowFullScreen_ {false};
    const int resolutionWidth_ {800};
    const int resolutionHeight_ {600};
};

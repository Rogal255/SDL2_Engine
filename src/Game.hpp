#pragma once
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SDL.h"
#include <memory>

class Game {
public:
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void mainLoop(); // Performance critical

    EntityManager entityManager;

private:
    void handleEvents(); // Performance critical
    void update();       // Performance critical
    void render();       // Performance critical

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_ {nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_ {nullptr, SDL_DestroyRenderer};
    bool isRunning_ {true};
    SDL_Event event_;

    // TODO: Load those from file
    const bool windowFullScreen_ {false};
    const int resolutionWidth_ {800};
    const int resolutionHeight_ {600};

    void testECS();
};

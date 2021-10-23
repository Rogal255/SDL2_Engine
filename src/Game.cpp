#include "Game.hpp"
#include "SDL.h"
#include <memory>
#include <stdexcept>
#include <string>

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Game::Game() - SDL_Init - %s\n", SDL_GetError());
        throw std::runtime_error("Game::Game() - SDL_Init has failed");
    }
    if (windowFullScreen_) {
        window_.reset(SDL_CreateWindow("Title",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       resolutionWidth_,
                                       resolutionHeight_,
                                       SDL_WINDOW_FULLSCREEN));
    } else {
        window_.reset(SDL_CreateWindow("Title",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       resolutionWidth_,
                                       resolutionHeight_,
                                       SDL_WINDOW_SHOWN));
    }
    if (!window_) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Game::Game() - SDL_CreateWindow - %s\n", SDL_GetError());
        throw std::runtime_error("Game::Game() - SDL_CreateWindow has failed");
    }
    renderer_.reset(SDL_CreateRenderer(window_.get(), -1, 0));
    if (!renderer_) {
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Game::Game() - SDL_CreateRenderer - %s\n", SDL_GetError());
        throw std::runtime_error("Game::Game() - SDL_CreateRenderer has failed");
    }
    if (SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, SDL_ALPHA_OPAQUE)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Game::Game() - SDL_SetRenderDrawColor - %s\n", SDL_GetError());
        throw std::runtime_error("Game::Game() - SDL_SetRenderDrawColor has failed");
    }
}

Game::~Game() { SDL_Quit(); }

void Game::run() {
    const uint16_t FPS {60};
    const uint16_t maxFrameTime {1000 / FPS};
    uint32_t currentFrameStart {SDL_GetTicks()};
    uint32_t currentFrameTime;

    // Performance critical starts here
    while (isRunning_) {
        handleEvents();
        update();
        render();
        currentFrameTime = SDL_GetTicks() - currentFrameStart;
        if (maxFrameTime > currentFrameTime) {
            SDL_Delay(maxFrameTime - currentFrameTime);
        }
    }
}

// Performance critical
void Game::handleEvents() {
    while (SDL_PollEvent(&event_)) {
        switch (event_.type) {
        case SDL_QUIT:
            isRunning_ = false;
            break;
        case SDL_KEYDOWN:
            // TODO: write (any) input handler
            if (event_.key.keysym.sym == SDLK_ESCAPE) {
                isRunning_ = false;
            }
            break;
        }
    }
}

// Performance critical
void Game::update() { }

// Performance critical
void Game::render() {
    SDL_RenderClear(renderer_.get());
    // TODO: render everything
    SDL_RenderPresent(renderer_.get());
}
#include "Game.hpp"
#include "Scene.hpp"
#include "SDL.h"
#include <iostream>
#include <memory>
#include <stdexcept>

std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> Game::window_ {nullptr, SDL_DestroyWindow};
std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> Game::renderer_ {nullptr, SDL_DestroyRenderer};

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

void Game::mainLoop() {
    const uint16_t FPS {60};
    const uint16_t maxFrameTime {1000 / FPS};
    uint32_t currentFrameStart {0};
    uint32_t currentFrameTime {0};

    while (isRunning_) {
        currentFrameStart = SDL_GetTicks();
        handleEvents();
        update(maxFrameTime);
        render();
        currentFrameTime = SDL_GetTicks() - currentFrameStart;
        if (maxFrameTime > currentFrameTime) {
            SDL_Delay(maxFrameTime - currentFrameTime);
        }
    }
}

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

void Game::render() {
    SDL_RenderClear(renderer_.get());
    // TODO: render everything
    SDL_RenderPresent(renderer_.get());
}

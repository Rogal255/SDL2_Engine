#include "Game.hpp"
#include <memory>
#include <stdexcept>
#include <string>

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error("Game::init. SDL_Init went wrong... " + std::string(SDL_GetError()));
    }
    window_.reset(SDL_CreateWindow("Title", 100, 100, 600, 600, SDL_WINDOW_SHOWN));
    if (!window_) {
        throw std::runtime_error("Game::init. SDL_CreateWindow went wrong... " + std::string(SDL_GetError()));
    }
    renderer_.reset(SDL_CreateRenderer(window_.get(), -1, 0));
    if (!renderer_) {
        throw std::runtime_error("Game::init. SDL_CreateRenderer went wrong... " + std::string(SDL_GetError()));
    }
}

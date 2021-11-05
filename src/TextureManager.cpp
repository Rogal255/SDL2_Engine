#include "TextureManager.hpp"
#include "Game.hpp"
#include "SDL_image.h"
#include <memory>

SDL_Texture* TextureManager::getTexture(const std::string& path) {
    auto it = texturesMap_.find(path);
    if (it == texturesMap_.end()) {
        SDL_Surface* tmpSurface = IMG_Load(path.c_str());
        SDL_Texture* rawTexture = SDL_CreateTextureFromSurface(Game::renderer_.get(), tmpSurface);
        SDL_FreeSurface(tmpSurface);
        texturePtr uniqueTexture {rawTexture, SDL_DestroyTexture};
        texturesMap_.emplace(std::make_pair(path, std::move(uniqueTexture)));
        return rawTexture;
    }
    return it->second.get();
}

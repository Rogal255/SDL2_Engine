#pragma once

#include "SDL.h"
#include <map>
#include <memory>
#include <string>

class TextureManager {
    using texturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

public:
    static SDL_Texture* getTexture(const std::string& path);

private:
    static inline std::map<std::string, texturePtr> texturesMap_;
};

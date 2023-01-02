#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <memory>
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace DGMon {
    class TextureLoader {
        public:
            TextureLoader();
            ~TextureLoader();
            std::shared_ptr<sf::Texture> getTexture(std::string name);
        private:
            std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;

    };
};

#endif
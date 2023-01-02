#include "TextureLoader.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <memory>
#include <unordered_map>

using namespace DGMon;

TextureLoader::TextureLoader() 
{
    // TODO: generalize by listing files
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile("assets/tilesets/outside.png")) {
        std::cerr << "Failed to load outside texture\n";
    }

    textures.insert({"tilesets/Outside", texture});
}

TextureLoader::~TextureLoader()
{
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>>().swap(textures);
}

std::shared_ptr<sf::Texture> TextureLoader::getTexture(std::string name) {
    return textures.at(name);
}

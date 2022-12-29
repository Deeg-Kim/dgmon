#include "LayoutLoader.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "util/Const.hpp"

using namespace DGMon;

LayoutLoader::LayoutLoader() {
    std::unordered_map<std::string, Tile> tiles;
    Json::Reader reader;

    // TODO: Generalize to more texture sources
    std::ifstream outsideFile("data/tiles/outside.json");
    Json::Value tileData;
    reader.parse(outsideFile, tileData);

    for (auto key : tileData.getMemberNames()) {
        auto cur = tileData[key];
        Tile t {OUTSIDE, cur["texX"].asInt(), cur["texY"].asInt(), sf::Color::White};
        tiles.insert({key, t});
    }

    std::unordered_map<std::string, Block> blocks;

    std::ifstream blocksFile("data/blocks/blocks.json");
    Json::Value blockData;
    reader.parse(blocksFile, blockData);
    
    for (auto key : blockData.getMemberNames()) {
        auto cur = blockData[key];
        std::vector<Tile> blockTiles {};
        for (auto tile : cur["tiles"]) {
            blockTiles.push_back(tiles.at(tile.asString()));
        }
        int height = cur["height"].asInt();
        blocks.insert({key, Block (blockTiles, height)});
    }

    // Load textures
    sf::Texture outdoorTexture;
    if (!outdoorTexture.loadFromFile("assets/tilesets/outside.png")) {
        std::cerr << "Failed to load outside texture\n";
    }

    std::ifstream zonesFile("data/zones/zones.json");
    Json::Value zonesData;
    reader.parse(zonesFile, zonesData);

    for (auto key : zonesData.getMemberNames()) {
        auto cur = zonesData[key];
        std::vector<Block> zoneBlocks {};
        for (auto block : cur["blocks"]) {
            zoneBlocks.push_back(blocks.at(block.asString()));
        }
        Zone z(zoneBlocks, outdoorTexture);
        z.load();
        zones.insert({key, z});
    }
}

LayoutLoader::~LayoutLoader() {
    
}

Zone LayoutLoader::getZone(std::string zoneName) {
    return zones.at(zoneName);
}
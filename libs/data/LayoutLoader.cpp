#include "LayoutLoader.hpp"
#include "util/Const.hpp"
#include "util/Direction.hpp"
#include <memory>

using namespace DGMon;

LayoutLoader::LayoutLoader(std::shared_ptr<sf::View> view, std::shared_ptr<TextureLoader> textureLoader)
:view(view)
,textureLoader(textureLoader)
{
    const std::shared_ptr<Tile> TILE_NONE_PTR = std::make_shared<Tile>("tilesets/Outside", 0, 0, sf::Color(0, 0, 0, 0));
    Json::Reader reader;

    // TODO: Generalize to more texture sources
    std::ifstream outsideFile("data/tiles/outside.json");
    Json::Value tileData;
    reader.parse(outsideFile, tileData);

    std::vector<std::string> expectedTileAttributes = {"texX", "texY"};
    std::string textureSource = tileData["texture"].asString();
    for (auto key : tileData["definitions"].getMemberNames()) {
        auto cur = tileData["definitions"][key];

        for (auto attr : expectedTileAttributes) {
            if (!cur.isMember(attr)) {
                throw std::invalid_argument("Missing tile argument for " + key + ": " + attr);
            }
        }

        auto t = std::make_shared<Tile>(textureSource, cur["texX"].asInt(), cur["texY"].asInt(), sf::Color::White);
        tiles.insert({key, t});
    }

    std::ifstream blocksFile("data/blocks/blocks.json");
    Json::Value blockData;
    reader.parse(blocksFile, blockData);
    
    std::vector<std::string> expectedBlockAttributes = {"name", "tiles", "heights"};
    for (auto key : blockData.getMemberNames()) {
        auto cur = blockData[key];

        for (auto attr : expectedBlockAttributes) {
            if (!cur.isMember(attr)) {
                throw std::invalid_argument("Missing block argument for " + key + ": " + attr);
            }
        }

        std::vector<std::shared_ptr<Tile>> blockTiles;
        for (auto tile : cur["tiles"]) {
            if (tile.asString() == "") {
                blockTiles.push_back(TILE_NONE_PTR);
            } else {
                blockTiles.push_back(tiles.at(tile.asString()));
            }
        }

        if (blockTiles.size() != 4) {
            throw std::invalid_argument("Block " + key + " does not have exactly 4 tiles.");
        }

        std::vector<int> heights {};
        for (auto height : cur["heights"]) {
            heights.push_back(height.asInt());
        }

        if (heights.size() != 4) {
            throw std::invalid_argument("Block " + key + " does not have exactly 4 heights.");
        }

        auto name = cur["name"].asString();
        blocks[key] = std::move(std::make_shared<Block>(name, blockTiles, heights));
    }
}

LayoutLoader::~LayoutLoader() {    
}

std::shared_ptr<LayoutLoad> LayoutLoader::loadLayout(std::string zoneName, int offsetX, int offsetY, std::shared_ptr<Trainer> trainer) {
    auto primary = getLayout(zoneName, trainer);
    primary->init(offsetX, offsetY);

    std::vector<std::shared_ptr<Layout>> adjacent {};
    for (auto c : primary->connectionsByDirection) {
        auto dir = c.first;
        auto connections = c.second;

        for (auto connection : connections) {
            auto layout = getLayout(connection->transition.toAttribute, trainer);

            if (dir == DirectionType::UP) {
                layout->init(offsetX, offsetY - layout->heightBlocks * BLOCK_SIZE);
            }

            adjacent.push_back(layout);
        }
    }

    return std::make_shared<LayoutLoad>(primary, adjacent);
}

std::shared_ptr<Layout> LayoutLoader::getLayout(std::string zoneName, std::shared_ptr<Trainer> trainer) {
    std::ifstream layoutsFile("data/layouts/" + zoneName + ".json");
    Json::Value layoutsData;

    Json::Reader reader;
    reader.parse(layoutsFile, layoutsData);

    std::vector<std::string> expectedLayoutAttributes = {"width", "height", "connections", "layers"};
    
    for (auto attr : expectedLayoutAttributes) {
        if (!layoutsData.isMember(attr)) {
            throw std::invalid_argument("Missing layout argument for " + zoneName + ": " + attr);
        }
    }

    int widthBlocks = layoutsData["width"].asInt();
    int heightBlocks = layoutsData["height"].asInt();

    std::vector<std::shared_ptr<ScreenLayer>> backgroundLayers {};
    std::vector<std::shared_ptr<ScreenLayer>> foregroundLayers {};

    // TODO: add more sanity checks on layouts
    for (auto layer : layoutsData["layers"]) {
        std::vector<std::shared_ptr<Block>> layerBlocks;

        for (auto block : layer["blocks"]) {
            layerBlocks.push_back(blocks.at(block.asString()));
        }

        auto screenLayer = std::make_shared<ScreenLayer>(widthBlocks, heightBlocks, layerBlocks, textureLoader->getTexture("tilesets/Outside"));

        if (layer["type"].asString() == "background") {
            backgroundLayers.push_back(screenLayer);
        } else if (layer["type"].asString() == "foreground") {
            foregroundLayers.push_back(screenLayer);
        }
    }

    std::vector<std::shared_ptr<Connection>> connections;
    for (auto connection : layoutsData["connections"]) {
        Direction dir = NONE_DIRECTION;
        std::string dirName = connection["direction"].asString();

        if (dirName == "UP") {
            dir = UP_DIRECTION;
        } else if (dirName == "DOWN") {
            dir = DOWN_DIRECTION;
        } else if (dirName == "LEFT") {
            dir = LEFT_DIRECTION;
        } else if (dirName == "RIGHT") {
            dir = RIGHT_DIRECTION;
        }

        StateTransition transition;
        transition.type = StateTransitionType::CONNECT;
        transition.toAttribute = connection["target"].asString();
        transition.fromAttribute = zoneName;
        transition.destinationType = StateType::LAYOUT;

        connections.push_back(std::make_shared<Connection>(transition, connection["x"].asInt(), connection["y"].asInt(), dir));
    }

    std::shared_ptr<Layout> layout = std::make_shared<Layout>(zoneName, widthBlocks, heightBlocks, trainer, backgroundLayers, foregroundLayers, connections);

    return layout;
}

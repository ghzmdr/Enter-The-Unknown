#ifndef FLOOR_FACTORY
#define FLOOR_FACTORY

#include <string>
#include <memory>

#include "Floor.hpp"
#include "Loaders/FloorLoader.hpp"

#include "Resource/Resources.hpp"
std::unique_ptr<Floor> static FloorLoad(std::unique_ptr<Floor> &fptr, const std::string &filename, TextureManager &textures)
{
    FloorLoader floorData{filename};
    fptr->tileSize = floorData.getTileSize();
    fptr->setTileSheet(textures[floorData.getTileSheetFileName()]);
    fptr->loadTileMap(floorData.getMap());
    fptr->loadCollidables(floorData.getCollidables());
    auto spos = floorData.getSpawnPosition();
    fptr->spawnPosition = sf::Vector2i{spos.x, spos.y};
    fptr->setExit(floorData.getExitPosition());
    fptr->loadEnemies(floorData.getEnemies());
    return std::move(fptr);
}

std::unique_ptr<Floor> static FloorFactory(const std::string &filename, TextureManager &textures)
{ 
    std::unique_ptr<Floor> fptr{new Floor()};
    return std::move(FloorLoad(fptr, filename, textures));
}

#endif
#ifndef RESOURCES_HPP
#define RESOURCES_HPP 

#include "Resource/ResourceManager.hpp"
#include <string>
namespace sf 
{
    class Texture;
    class Font;
}

namespace Textures
{
    ID TitleBackground  = "img/titleBG.png";
    ID Button           = "img/button.png";
    ID Player           = "img/playerCombat.png";
    ID WorldTiles       = "img/levelTiles.png";
}


namespace Fonts
{
    ID Main  = "font/font.ttf";
}

template<typename Resource>
class ResourceManager;

typedef ResourceManager<sf::Texture> TextureManager;
typedef ResourceManager<sf::Font> FontManager;

#endif
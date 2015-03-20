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
    ID TitleBackground  = "res/img/titleBG.png";
    ID Button           = "res/img/button.png";
    ID WorldTiles       = "res/img/levelTiles.png";
}


namespace Fonts
{
    ID Main  = "res/font/font.ttf";
}

template<typename Resource>
class ResourceManager;

typedef ResourceManager<sf::Texture> TextureManager;
typedef ResourceManager<sf::Font> FontManager;

#endif
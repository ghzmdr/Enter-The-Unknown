#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <sstream>
#include <cmath>



template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template<typename DrawableObject>
void centerOrigin(DrawableObject &obj)
{
    sf::FloatRect bounds = obj.getLocalBounds();
    obj.setOrigin(std::floor(bounds.width /2.f), std::floor(bounds.height /2.f));
}


#endif
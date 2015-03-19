#include "GUI/Button.hpp"

namespace GUI
{

Button::Button(const sf::Font &font, const sf::Texture &texture)
: sprite{texture},
isToggle{false},
text{"", font, 25},
normal{0,0,btnWidth, btnHeight},
selected{btnWidth,0,btnWidth, btnHeight},
pressed{btnWidth * 2, 0, btnWidth, btnHeight}
{
    sprite.setTextureRect(normal);
    sf::FloatRect bounds = sprite.getLocalBounds();
    text.setPosition(bounds.width /2.f, bounds.height /2.f);
}

void Button::setAction(Action action){ this->action = action;}
void Button::setText(const std::string &text){ this->text.setString(text); centerOrigin(this->text);}

void Button::setToggle(bool flag)
{isToggle = flag;}

bool Button::isSelectable() const 
{return true;}

void Button::select() 
{Component::select(); sprite.setTextureRect(selected);}

void Button::deselect() 
{Component::deselect(); sprite.setTextureRect(normal);}

void Button::activate() 
{
    Component::activate();

    if (action)
        action();

    if (isToggle)
        sprite.setTextureRect(pressed);
    else deactivate();
}

void Button::deactivate()
{
    Component::deactivate();

    if (isToggle)
        isSelected() ? sprite.setTextureRect(selected) : sprite.setTextureRect(normal);
}

void Button::handleEvent(const sf::Event &event){}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(text, states);
}


}
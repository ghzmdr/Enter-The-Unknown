#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GUI/Component.hpp"
#include "Resource/Resources.hpp"
#include "Resource/ResourceManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Utils/Utility.hpp"

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

constexpr int btnWidth{400}, btnHeight{100};

class Button : public Component
{

public:
    typedef std::shared_ptr<Button> Ptr;
    typedef std::function<void()> Action;

    Button(const sf::Font &font, const sf::Texture &texture);

    void setAction(Action action);
    void setText(const std::string &text);
    void setToggle(bool flag);

    virtual bool isSelectable() const;
    virtual void select();
    virtual void deselect();

    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event &event);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    Action action;

    sf::Sprite sprite;
    sf::Text text;
    bool isToggle;

    sf::IntRect normal, selected, pressed;
};

}   


#endif
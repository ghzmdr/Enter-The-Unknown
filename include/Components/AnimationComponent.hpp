#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <vector>
#include <map>
#include <string>

#include "Components/Component.hpp"
#include "Components/GraphicsComponent.hpp"

class Entity;


/*
*   This class is higly coupled with the graphics component,
*   That is, it's parent should own an instance of GraphicsComponent
*   since without graphics there can be no animation
*/

class AnimationComponent : public Component
{
public:
    AnimationComponent(){};
    std::map<std::string, std::vector<unsigned short>> animations;    
    virtual void update(Entity &parent){};

    unsigned short skipFrames;

private:
    unsigned short framesSkipped;
};


#endif
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Entity;

class Component
{
public:
    Component(){};
    virtual void update(Entity &parent){};    
};

#endif
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Entity;

class Component
{
public:
    virtual void update(Entity &parent){};    
};

#endif
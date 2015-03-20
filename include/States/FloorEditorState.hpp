#ifndef FLOOR_EDITOR_STATE
#define FLOOR_EDITOR_STATE

#include "States/State.hpp"
#include "Editor/FloorEditor.hpp"

class FloorEditorState : public State
{
public:
    FloorEditorState(StateStack &stack, Context context);

    virtual void draw();    
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& e);

private:
    FloorEditor editor;
};

#endif

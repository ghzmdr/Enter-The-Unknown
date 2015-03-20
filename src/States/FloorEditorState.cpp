#include "States/FloorEditorState.hpp"
#include "Debug.h"

FloorEditorState::FloorEditorState(StateStack& stack, Context context):
State(stack, context), 
editor{getContext()}
{
    log_info("INIT FLOOR EDITOR STATE");
}

void FloorEditorState::draw()
{
    editor.draw();
}

bool FloorEditorState::update(sf::Time dt)
{    
    editor.update(dt);
    return true;
}

bool FloorEditorState::handleEvent(const sf::Event& event)
{
    editor.handleEvent(event);
    return true;
}

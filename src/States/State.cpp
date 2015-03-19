#include "States/State.hpp"
#include "States/StateStack.hpp"

void State::requestStackPush(StateID state)     {stack->push(state);}
void State::requestStackPop()                   {stack->pop();}
void State::requestStackClear()                 {stack->clear();}

State::Context State::getContext() const {return context;}

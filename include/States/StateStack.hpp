#ifndef STATESTACK_H
#define STATESTACK_H

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include "States/State.hpp"
#include "States/StateID.hpp"

namespace sf
{
    class Event;
    class RenderWindow;
}

class StateStack
{
    public:
        enum Action { Push, Pop, Clear };

        explicit StateStack(State::Context context):context{context}{};

        template<typename T>
        void registerState(StateID state);

        void update(sf::Time deltaT);
        void draw();
        void handleEvent(const sf::Event& event);

        void push(StateID state);
        void pop();        
        void clear();

        bool isEmpty() const;

    private:
        State::Ptr createState(StateID state);
        void applyPendingChanges();

        struct PendingChange
        {
            explicit PendingChange(Action a, StateID stID = StateID::None): action{a}, stateID{stID}{};
            Action action;
            StateID stateID;
        };

        std::vector<State::Ptr> stack;
        std::vector<PendingChange> pendings;

        State::Context context;
        std::map<StateID, std::function<State::Ptr()>> factories;
};

template<typename T>
void StateStack::registerState(StateID state)
{
    factories[state] = [this] ()
    { return State::Ptr{new T(*this, context)};};
}

#endif // STATESTACK_H

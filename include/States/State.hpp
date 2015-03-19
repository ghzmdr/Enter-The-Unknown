#ifndef STATE_H
#define STATE_H

#include "Debug.h"
#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "Resource/Resources.hpp"
#include "StateID.hpp"

namespace sf {class RenderWindow;}
class StateStack;

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

        struct Context
        {
            Context(sf::RenderWindow &win, TextureManager &textures, FontManager &fonts)
            :window{&win}, textures{&textures}, fonts{&fonts}
            {};
            
            sf::RenderWindow *window;

            TextureManager *textures;
            FontManager *fonts;
        };

        State(StateStack& st, Context cont):stack{&st}, context{cont}{};
        virtual ~State(){};

        virtual void draw() = 0;
        virtual bool update(sf::Time deltaT) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;

    protected:
        void requestStackPush(StateID state);
        void requestStackPop();
        void requestStackClear();

        Context getContext() const;

    private:
        StateStack *stack;
        Context context;
};

#endif // STATE_H

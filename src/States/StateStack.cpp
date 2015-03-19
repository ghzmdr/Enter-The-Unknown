#include "States/StateStack.hpp"

//CREATE AND RETURN A NEW STATE
//BY RETRIEVING IT'S CONSTRUCTOR

//FROM THE LAMBDAS STORED IN factories
//AND CALLING IT
State::Ptr StateStack::createState(StateID stateID)
{
    auto found = factories.find(stateID);
    check(found != factories.end(), "Factory not found");
    return found->second();
}


//A SYSTEM TO DEFER UPDATES
//THE CHANGE TO BE MADE IS PUSHED IN A STACK
//ALONG WITH NEEDED INFO (JUST STATE-ID IN CASE OF PUSH)
//WHEN CALLING applyPendingChanges() THEY GET SOLVED
	void StateStack::applyPendingChanges()
	{
		for(auto change : pendings)
			switch(change.action)
			{
				case Push:
					stack.push_back(createState(change.stateID));
					break;
				case Pop:
					stack.pop_back();
					break;
				case Clear:
					stack.clear();
					break;

				default: sentinel();
			}

		pendings.clear();
	}

//BRIDGE METHODS TO PROPAGATE THE UPDATES
	void StateStack::draw()
	{ 
		for (auto &st : stack)
			st->draw();
	}

	void StateStack::update(sf::Time deltaT)
	{
        for (auto& st : stack)
            if (!st->update(deltaT))
            	break;
		applyPendingChanges();
	}

	void StateStack::handleEvent(const sf::Event& event)
	{
		for (auto& st : stack)
			if (!st->handleEvent(event))
				break;
	}

//STACK MANIPULATION METHODS
	void StateStack::push(StateID stateID){pendings.push_back(PendingChange(Push, stateID));}
	void StateStack::pop(){pendings.push_back(PendingChange(Pop));}
	void StateStack::clear(){pendings.push_back(PendingChange(Clear));}

	bool StateStack::isEmpty() const {return stack.empty();}

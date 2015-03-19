#include "SceneNode/SceneNode.hpp"
#include "Debug.h"

void SceneNode::attach(Ptr child)
{
    child->parent = this;
    childs.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detach(const SceneNode& node)
{
    //SEARCH FOR A NODE
    auto found = std::find_if(childs.begin(), childs.end(), [&](Ptr& p) -> bool {return p.get() == &node;});
    check(found != childs.end(), "Searching for inesistent child");

    Ptr res{std::move(*found)};
    res->parent = nullptr;
    childs.erase(found);    
    return res;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	drawCurrent(target, states);
	drawChilds(target, states);
}

void SceneNode::drawChilds(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& child : childs)
		child->draw(target, states);
}


void SceneNode::updateChilds(sf::Time dt)
{
    for(auto& child : childs)
        child->updateCurrent(dt);
}

#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <algorithm>
#include <vector>
#include <utility>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
        SceneNode():parent{nullptr}{};
        ~SceneNode(){};

        void attach(Ptr child);
        Ptr detach(const SceneNode& node);

        void update(sf::Time dt);

    private:
    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{};
    	virtual void drawChilds(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void updateCurrent(sf::Time dt){};
        void updateChilds(sf::Time dt);

        std::vector<Ptr> childs;
        SceneNode* parent;
};

#endif // SCENENODE_HPP

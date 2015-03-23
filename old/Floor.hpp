#include "Floor.hpp"


void Floor::loadTileMap(MapData map)
{
    tileMap.load(tileSheet, map, tileSize); 
    bounds = {0,0,(int)map[0].size() * tileSize, (int)map.size() * tileSize};
}

void Floor::setTileSheet(sf::Texture &ts)
{tileSheet = ts; tileSheet.setSmooth(false); tileSheet.setRepeated(false);}

void Floor::loadCollidables(MapData map)
{
    int maxRow = tileSheet.getSize().x/tileSize;

    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (map[i][j] >= 0)
            {
                collidables.push_back(obstacleFactory(map[i][j], i,j, maxRow));
                sf::RectangleShape r;
                r.setPosition(j*tileSize - tileSize/2, )
                boundings.push_back(sf::);
            }
             

                sf::RectangleShape shape;
                shape.setPosition(j * tileSize - tileSize/2, i * tileSize -tileSize/2);
                shape.setSize({(float)tileSize, (float)tileSize});
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(sf::Color::Red);
                shape.setOutlineThickness(.5f);
                boundings.push_back(shape);
            }
}

void Floor::update(sf::Time deltaT)
{}

void Floor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(tileMap);

    if (drawBoundings)
        for (auto &g : tileMap.grid)
            if (isInBounds(g.getPosition()))
                target.draw(g);
/*
    for (auto &obj : collidables)
        if (isInBounds(obj.position)
            target.draw(obj);
*/
    if (drawBoundings)
        for(auto &b : boundings)
            if (isInBounds(b.getPosition()))
                target.draw(b);

    //target.draw(exit);
}

const bool Floor::isInBounds(const sf::Vector2f &tilePosition) const
{
    //TILE LEFT X IS > WORLD LEFT X (WORLD CENTER X - HALF WORLD WIDTH)
    bool inLeft = tilePosition.x >= viewBounds.left - (viewBounds.width/2 + drawOffset * tileSize);

    //TILE LEFT X IS < WORLD RIGHT X (WORLD CENTER X + HALF WORLD WIDTH)
    bool inRight = tilePosition.x <= viewBounds.left + (viewBounds.width/2 + drawOffset * tileSize);

    //TILE TOP Y > WORLD TOP Y (WORLD CENTER Y - HALF WORLD HEIGHT)
    bool inTop = tilePosition.y >= viewBounds.top - (viewBounds.height/2 + drawOffset * tileSize);

    //TILE BOTTOM Y < WORLD BOTTOM Y (WORLD CENTER Y + HALF WORLD HEIGHT)
    bool inBottom = tilePosition.y <= viewBounds.top + (viewBounds.height/2 + drawOffset * tileSize);

    return inLeft && inRight && inTop && inBottom;

}

std::unique_ptr<Obstacle> Floor::obstacleFactory(unsigned short id, int j, int i, int maxWidth)
{
       int tileSheetWidth = tileSheet.getSize().x/tileSize;

        sf::Vector2i tilePosition = {(id % tileSheetWidth) * tileSize, (id / tileSheetWidth) * tileSize};        
        std::unique_ptr<Obstacle> tile (new Obstacle(new GraphicsComponent(tileSheet, {tilePosition, {tileSize, tileSize}})));        
        tile->position = {j * tileSize * 1.f , i * tileSize * 1.f};                

        return std::move(tile);
}

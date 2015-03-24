#include <Components/GraphicsComponent.hpp>
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
    map2Layer(map);
}

void Floor::update(sf::Time deltaT)
{}

void Floor::loadEnemies(std::vector<EnemyData> enemiesData)
{
    for (auto &e : enemiesData)
    {
        printf("%s, %f %f\n", e.kind.c_str(), e.position.x, e.position.y);
    }
}

void Floor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(tileMap);

    if (drawBoundings)
        for (auto &g : tileMap.grid)
            if (isInBounds(g.getPosition()))
                target.draw(g);

    for (auto &obj : collidables)
        if (isInBounds(obj.position))            
                target.draw(obj);

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

void Floor::map2Layer(const MapData &source)
{
    for (int i = 0; i < source.size(); i++)
        for (int j = 0; j < source[i].size(); j++)
            if (source[i][j] >= 0)
            {
                int tileID = source[i][j];
                int tileSheetWidth = tileSheet.getSize().x/tileSize;

                sf::Vector2i tilePosition = {(tileID % tileSheetWidth) * tileSize, (tileID / tileSheetWidth) *tileSize};

                sf::Vector2f tposition = {j * tileSize * 1.f , i * tileSize * 1.f};  
                sf::Vector2i tsize = {tileSize, tileSize};
                Obstacle tile{new GraphicsComponent(tileSheet, {tilePosition, {tileSize, tileSize}}), tposition, tsize};
                collidables.push_back(tile);

                sf::RectangleShape shape;
                shape.setPosition(j * tileSize - tileSize/2, i * tileSize -tileSize/2);
                shape.setSize({(float)tileSize, (float)tileSize});
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(sf::Color::Red);
                shape.setOutlineThickness(.5f);
                boundings.push_back(shape);
            }
}
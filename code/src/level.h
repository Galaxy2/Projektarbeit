#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);

class level
{
public:
    void loadFromFile(string pfad);
    bool checkCollision(sf::FloatRect& spielerPosition);
    void loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList);

    list<sf::FloatRect> mauern;
    bool collisionsActivated;
    string name;
};


#endif // __LEVEL_H__

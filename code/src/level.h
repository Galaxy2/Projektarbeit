#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);

class level{
    public:
    list<sf::FloatRect> mauern;
    void loadFromFile(string pfad);
    bool checkCollision(sf::FloatRect& spielerPosition);

};


#endif // __LEVEL_H__

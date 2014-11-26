#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "animation.h"
#include "tuere.h"

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);

class level
{
public:
    void loadFromFile(string pfad, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    bool checkCollision(sf::FloatRect& spielerPosition);
    void loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    int checkTuere(sf::FloatRect& spielerPosition);

    list<sf::FloatRect> mauern;
    vector<animation *> pfeile;
    vector<tuere *> tueren;

    sf::Vector2f spielerPosition;
    bool collisionsActivated;
    string name;
};


#endif // __LEVEL_H__

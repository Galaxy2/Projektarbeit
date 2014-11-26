#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "animation.h"

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);

class level
{
public:
    void loadFromFile(string pfad, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    bool checkCollision(sf::FloatRect& spielerPosition);
    bool checkCollisionSchaetze(sf::FloatRect& spielerPosition);
    void loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList);

    list<sf::FloatRect> mauern;
    list<sf::FloatRect> schaetzePositionen;
    vector<animation *> pfeile;
<<<<<<< HEAD
    vector<animation *> tueren;
=======
    vector<animation *> schaetze;
>>>>>>> schatz

    sf::Vector2f spielerPosition;
    bool collisionsActivated;
    string name;
};


#endif // __LEVEL_H__

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "animation.h"
#include "tuere.h"
#include "pfeil.h"

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);

class level
{
public:
    void loadFromFile(string pfad, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    bool checkCollision(sf::FloatRect& spielerPosition);
    bool checkCollisionSchaetze(sf::FloatRect& spielerPosition);
    bool checkCollisionPfeile(sf::FloatRect& spielerPosition);
    void loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    int checkCollisionTuere(sf::FloatRect& spielerPosition);
    void mauerErstellen(sf::FloatRect pos);

    list<sf::FloatRect> mauern;
    list<sf::FloatRect> schaetzePositionen;
    list<sf::FloatRect> pfeilePositionen;
    vector<pfeil *> pfeile;
    vector<tuere *> tueren;
    vector<animation *> schaetze;

    sf::Vector2f spielerPosition;
    bool collisionsActivated;
    string name;
};


#endif // __LEVEL_H__

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "animation.h"
#include "tuere.h"
#include "pfeil.h"
#include "schatz.h"

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);


class level
{
public:
    void loadFromFile(string pfad, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    bool checkCollision(sf::FloatRect& spielerPosition);
    // bool checkCollisionSchaetze(sf::FloatRect& spielerPosition);
    int checkCollisionPfeile(sf::FloatRect& spielerPosition);
    void loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    int checkCollisionTuere(sf::FloatRect& spielerPosition);
    int checkCollisionSchaetze(sf::FloatRect& spielerPosition);
    int checkTuere(sf::FloatRect& spielerPosition);

    list<sf::FloatRect> mauern;
    list<sf::FloatRect> schaetzePositionen;
    list<sf::FloatRect> pfeilePositionen;
    // list<sf::FloatRect> schaetzePositionen;

    vector<pfeil *> pfeile;
    vector<tuere *> tueren;
    vector<schatz *> schaetze;

    sf::Vector2f spielerPosition;
    string deckeName;
    bool collisionsActivated;
    string name;

    // Destruktor
    ~level(void);
};


extern void setzeMauer(int Id);

#endif // __LEVEL_H__

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "animation.h"
#include "tuere.h"
#include "pfeil.h"
#include "schatz.h"
#include "laser.h"
#include "game.h"

using namespace std;

extern sf::Vector2f koordinaten(int x, int y);

class level
{
public:
    void loadFromFile(void);
    bool checkCollision(sf::FloatRect& spielerPosition);
    // bool checkCollisionSchaetze(sf::FloatRect& spielerPosition);
    int checkCollisionPfeile(sf::FloatRect& spielerPosition);
    void loadToScreen(sf::Texture*& hintergrundTextur, sf::Sprite*& hintergrund, list<sf::Drawable *>& renderList, list<animation *>& animationList);
    level *levelLaden(string n);
    int checkCollisionTuere(sf::FloatRect& spielerPosition);
    int checkCollisionSchaetze(sf::FloatRect& spielerPosition);
    int checkTuere(sf::FloatRect& spielerPosition);
    bool checkCollisionLaser(sf::FloatRect& spielerPosition);

    list<sf::FloatRect> mauern;
    list<sf::FloatRect> schaetzePositionen;
    list<sf::FloatRect> pfeilePositionen;
    list<sf::FloatRect> lasersPositionen;
    // list<sf::FloatRect> schaetzePositionen;

    vector<pfeil *> pfeile;
    vector<tuere *> tueren;
    vector<schatz *> schaetze;
    vector<laser *> lasers;

    sf::Vector2f spielerPosition;
    string deckeName;
    bool collisionsActivated;
    string name;

    sf::Time Zeit;

    // Destruktor
    level(void);
    level(string n);
    ~level(void);
};


extern void setzeMauer(int Id);
extern level *levelLaden(string n);
extern unordered_map<string, level*> levelListe;


#endif // __LEVEL_H__

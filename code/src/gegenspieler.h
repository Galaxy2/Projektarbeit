#ifndef __GEGENSPIELER_H__
#define __GEGENSPIELER_H__

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

using namespace std;

class gegenspieler
{
private:
    vector<sf::Vector2f *> waypoints;
    bool vorwaerts;
    sf::Texture textur;
    int waypointNr;
    float speed;

public:
    gegenspieler(float s);
    ~gegenspieler(void);

    void addWaypoint(sf::Vector2f *v);
    void bewegen(void);
    int schrittAbstand(sf::FloatRect spielerPosition);

    sf::Sprite sprite;
};

#endif // __GEGENSPIELER_H__

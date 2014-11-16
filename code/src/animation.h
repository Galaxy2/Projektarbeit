#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class animation
{
public:
    int anzahlSchritte;
    int schritt;

    string name;
    std::vector<sf::Texture*> texturen;

    float deltaT;
    sf::Clock t;
    sf::Sprite sprite;

    void animationAusfuehren(void);

    animation(string n, int N, float dT, int x, int y);
    ~animation(void);
};


#endif // __ANIMATION_H__

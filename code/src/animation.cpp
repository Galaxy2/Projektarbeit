#include "animation.h"
#include <cstdio>

using namespace std;

animation::animation(string n, int N, float dT, int x, int y)
{
    schritt = 0;
    name = n;
    anzahlSchritte = N;
    deltaT = dT;
    sprite.setPosition(x, y);

    for(int i=0; i<N; i++){
        string dateiName = n + "_" + to_string(i) + ".png";

        sf::Texture *textur = new sf::Texture;
        textur->loadFromFile(dateiName);
        texturen.push_back(textur);
    }
}


animation::~animation(void)
{
    // Speicher für allozierte Texturen wieder freigeben!
    for(auto i : texturen)
    {
        delete i;
    }
}


void animation::animationAusfuehren(void)
{
    if(t.getElapsedTime().asSeconds() < deltaT)
        return;

    t.restart();
    sprite.setTexture(*texturen[schritt]);
    schritt = (schritt+1)%anzahlSchritte;
}

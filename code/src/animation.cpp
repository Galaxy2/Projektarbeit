#include "animation.h"
#include <cstdio>

#ifndef LINUX
#include <sstream>
#endif // LINUX


using namespace std;

animation::animation(string n, int N, bool endlos, float dT, int x, int y)
{
    schritt = 0;
    name = n;
    anzahlSchritte = N;
    this->endlos = endlos;
    deltaT = dT;
    sprite.setPosition(x, y);

    string dateiName;
    for(int i=0; i<N; i++)
    {
        #ifndef LINUX
            stringstream dateiNameStream;
            dateiNameStream << n << "_" << i << ".png";

            dateiName = dateiNameStream.str();
        #else
            dateiName = n + "_" + to_string(i) + ".png";
        #endif // LINUX

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

    if(endlos)
    {
        schritt = (schritt+1)%anzahlSchritte;
    }
    else
    {
        if(schritt < anzahlSchritte-1)
        {
            ++schritt;
        }
    }
}


void animation::neustart(void)
{
    schritt = 0;
    t.restart();
    sprite.setTexture(*texturen[schritt]);
}

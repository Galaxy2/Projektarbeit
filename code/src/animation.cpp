#include "animation.h"
#include <cstdio>

#ifndef LINUX
    #include <sstream>
#endif // LINUX


using namespace std;

animation::animation(string n, int N, float dT, int x, int y)
{
    schritt = 0;
    name = n;
    anzahlSchritte = N;
    deltaT = dT;
    sprite.setPosition(x, y);

    string dateiName;
    for(int i=0; i<N; i++){
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
    schritt = (schritt+1)%anzahlSchritte;
}

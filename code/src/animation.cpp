#include "animation.h"

#include <cstdio>
#include <cstdlib>

#ifndef LINUX
#include <sstream>
#endif // LINUX


using namespace std;


void defaultCB(int x)
{
    return;
}


animation::animation(string n, int N, bool endlos, bool start, bool vorwaerts, float dT, int x, int y, int moeglichkeiten)
{
    name = n;
    anzahlSchritte = N;
    this->endlos = endlos;
    deltaT = dT;
    sprite.setPosition(x, y);
    aktiv = start;
    richtung = vorwaerts;
    Id = 0;

    moeglichkeit = rand() % moeglichkeiten;

    if(vorwaerts)
    {
        schritt = 0;
    }
    else
    {
        schritt = anzahlSchritte-1;
    }

    string dateiName;
    for(int i=0; i<N; i++)
    {
#ifndef LINUX
        stringstream dateiNameStream;
        dateiNameStream << n << "_" << moeglichkeit << "_" << i << ".png";

        dateiName = dateiNameStream.str();
#else
        dateiName = n + "_" + to_string(moeglichkeit) + "_" + to_string(i) + ".png";
#endif // LINUX

        sf::Texture *textur = new sf::Texture;
        textur->loadFromFile(dateiName);
        texturen.push_back(textur);
    }


    // Das erste Bild laden, auch wenn die Animation nicht läuft
    if(start)
    {
        sprite.setTexture(*texturen[schritt]);
    }

    // Setze default callback Funktion
    animationEnde = defaultCB;
}


animation::~animation(void)
{
    // Speicher für allozierte Texturen wieder freigeben!
    for(auto i : texturen)
    {
        delete i;
    }
}


void animation::start(void)
{
    aktiv = true;

    if(richtung)
        schritt = 0;
    else
        schritt = anzahlSchritte - 1;

    t.restart();
}


void animation::stop(void)
{
    aktiv = false;
}


void animation::setRichtung(bool vorwaerts)
{
    richtung = vorwaerts;
}


void animation::zeigeSchritt(int k)
{
    sprite.setTexture(*texturen[k]);
}


void animation::animationAusfuehren(void)
{
    if(!aktiv || t.getElapsedTime().asSeconds() < deltaT)
        return;

    t.restart();
    sprite.setTexture(*texturen[schritt]);


    if(endlos)
    {
        if(richtung)
        {
            schritt += 1;

            if(schritt == anzahlSchritte)
                schritt = 0;
        }
        else
        {
            schritt -= 1;

            if(schritt < 0)
                schritt = anzahlSchritte-1;
        }

    }
    else
    {
        if(richtung)
        {
            schritt += 1;

            if(schritt == anzahlSchritte)
                aktiv = false;
        }
        else
        {
            schritt -= 1;

            if(schritt < 0)
                aktiv = false;
        }
    }


    if(!aktiv)
    {
        animationEnde(Id);
    }
}


bool animation::istBeendet(void)
{
    return (t.getElapsedTime().asSeconds() > anzahlSchritte * deltaT);
}


void animation::setOnAnimationEnde(void (*callback)(int))
{
    animationEnde = callback;
}


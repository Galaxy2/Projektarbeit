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
    // Variabeln initialisieren
    name = n;
    anzahlSchritte = N;
    this->endlos = endlos;
    deltaT = dT;
    sprite.setPosition(x, y);
    aktiv = start;
    richtung = vorwaerts;
    Id = 0;

    // Style heraussuchen
    moeglichkeit = rand() % moeglichkeiten;

    // Animation vorwärts oder rückwärts abspielen?
    if(vorwaerts)
    {
        schritt = 0;
    }
    else
    {
        schritt = anzahlSchritte-1;
    }

    // Texturen aus Dateien laden!
    string dateiName;
    for(int i=0; i<N; i++)
    {
#ifndef LINUX // Windows only

        stringstream dateiNameStream;
        dateiNameStream << n << "_" << moeglichkeit << "_" << i << ".png";

        dateiName = dateiNameStream.str();

#else // Linux only

        dateiName = n + "_" + to_string(moeglichkeit) + "_" + to_string(i) + ".png";

#endif // LINUX


        // Textur zum Texturenvektor hinzufügen
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

    // Vorwärts oder Rückwärts abspielen? -> Passendes Bild anzeigen
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
    // Springe zum k. Animationschritt
    sprite.setTexture(*texturen[k]);
}


void animation::animationAusfuehren(void)
{
    // Bild nur ändern, wenn deltaT bereits vorbei
    if(!aktiv || t.getElapsedTime().asSeconds() < deltaT)
        return;

    // t_0 auf 0 setzen
    t.restart();

    // Dem Sprite die richtige Textur zuweisen
    sprite.setTexture(*texturen[schritt]);


    if(endlos)
    {
        if(richtung)
        {
            // Vorwärts!
            schritt += 1;

            // Am Ende -> Zurück zum Start
            if(schritt == anzahlSchritte)
                schritt = 0;
        }
        else
        {
            // Rückwärts
            schritt -= 1;

            // Am Start -> Zurück zum Ende
            if(schritt < 0)
                schritt = anzahlSchritte-1;
        }

    }
    else
    {
        if(richtung)
        {
            // Nur Vorwärts
            schritt += 1;

            // Animation zu Ende? (Nicht mehr aktiv!)
            if(schritt == anzahlSchritte)
                aktiv = false;
        }
        else
        {
            // Nur Rückwärts
            schritt -= 1;

            // Animation am Start? (Nicht mehr aktiv!)
            if(schritt < 0)
                aktiv = false;
        }
    }


    if(!aktiv)
    {
        // Theoretisches Callback (Wird nicht verwendet)
        animationEnde(Id);
    }
}


bool animation::istBeendet(void)
{
    // Vergangene Zeit > Animationsdauer? -> Dann beendet
    return (t.getElapsedTime().asSeconds() > anzahlSchritte * deltaT);
}


void animation::setOnAnimationEnde(void (*callback)(int))
{
    // setter Funktion für Animationscallback
    animationEnde = callback;
}


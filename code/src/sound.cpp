#include <iostream>
#include "main.h"

extern sf::Music musik;

void hintergrundMusik(string name)
{
    // Dateiname zusammensetzen
    string dateiName;

#ifndef LINUX
    // Nur Windows
    stringstream dateiNameStream;

    dateiNameStream << "resources/sound/" << name << ".ogg";
    dateiName = dateiNameStream.str();

#else
    // Nur Linux
    dateiName = "resources/sound/" + name + ".ogg";

#endif // LINUX


    // Versuche Musikdatei zu �ffnen
    if (!musik.openFromFile(dateiName))
    {
        std::cerr << "Fehler beim �ffnen der hintergrundMusik";
    }

    // Musik abspielen!
    musik.play();
}

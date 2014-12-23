#include <iostream>
#include "main.h"

extern sf::Music musik;

void hintergrundMusik(string name)
{

    string dateiName;
    #ifndef LINUX
        stringstream dateiNameStream;

        dateiNameStream << "resources/sound/" << name << ".ogg";
        dateiName = dateiNameStream.str();
    #else
        dateiName = "resources/sound/" + name + ".ogg";
    #endif // LINUX


    if (!musik.openFromFile(dateiName))
    {
        std::cerr << "Fehler beim Öffnen der hintergrundMusik";
    }

    musik.play();
}

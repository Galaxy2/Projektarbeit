#include "console.h"

#include <iostream>

// Möglichst wenige globale Variabeln
namespace console
{
    sf::Text eingabeFeld;
    std::stringstream eingabeText;
    bool activated = false;
}

using namespace console;


void showConsole(void)
{
    // Konsole anzeigen!
    eingabeFeld.setString("> ");
    eingabeText.str("");
    activated = true;
}

void hideConsole(void)
{
    // Konsole verstecken!
    eingabeFeld.setString("");
    activated = false;
}

void updateConsole(char c)
{
    // Wenn "Backspace", dann letztes Zeichen löschen
    if(c == 8)
    {
        std::string text = eingabeText.str();

        // Aber nur, wenn noch Text da ist! (Memory underflow!)
        if(text.length() > 0)
        {
            text.pop_back();

            eingabeText.str("");
            eingabeText << text;
        }
    }
    else
    {
        // Zeichen, das von SFML eingelesen wurde
        eingabeText << c;
    }

    // Neuer Text anzeigen
    eingabeFeld.setString("> " + eingabeText.str());
}

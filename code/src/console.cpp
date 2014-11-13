#include "console.h"

#include <iostream>

namespace console
{
    sf::Text eingabeFeld;
    std::stringstream eingabeText;
    bool activated = false;
}

using namespace console;


void showConsole(void)
{
    eingabeFeld.setString("> ");
    eingabeText.str("");
    activated = true;
}

void hideConsole(void)
{
    eingabeFeld.setString("");
    activated = false;
}

void updateConsole(char c)
{
    // Wenn "Backspace"
    if(c == 8)
    {
        std::string text = eingabeText.str();
        text.pop_back();
        eingabeText.str("");
        eingabeText << text;
    }
    else
    {
        eingabeText << c;
    }

    eingabeFeld.setString("> " + eingabeText.str());
}

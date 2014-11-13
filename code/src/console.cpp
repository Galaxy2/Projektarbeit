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
    eingabeFeld.setColor(sf::Color::Red);
    eingabeFeld.setCharacterSize(20);

    activated = true;
}

void hideConsole(void)
{
    eingabeFeld.setString("");
    activated = false;
}

void updateConsole(char c)
{
    eingabeText << c;
    eingabeFeld.setString("> " + eingabeText.str());
    std::cerr << "> " + eingabeText.str() << std::endl;
}

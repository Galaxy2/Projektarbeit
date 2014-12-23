#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

namespace console
{
extern sf::Text eingabeFeld;
extern std::stringstream eingabeText;
extern bool activated;
}

extern void showConsole(void);
extern void hideConsole(void);
extern void updateConsole(char c);


#endif // __CONSOLE_H__

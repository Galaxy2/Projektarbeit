#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__

#include <string>
#include <SFML/Graphics.hpp>
#include "main.h"


extern sf::Font standardSchriftart;

class benachrichtigung{
    public:
    sf::Text text;

    benachrichtigung(std::string text, int xpos, int ypos, int charSize);
    void updateText(std::string text);
    void test(void);
};

#endif // __NOTIFICATION_H__

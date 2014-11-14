#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <string>
#include "notification.h"


namespace screen
{
extern float factor;
};

extern void hintergrundLaden(std::string levelName, sf::Sprite* s, sf::Texture* h);

#endif // __SCREEN_H__

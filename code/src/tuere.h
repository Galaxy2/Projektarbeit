#ifndef __TUERE_H__
#define __TUERE_H__

#include <SFML/Graphics.hpp>
#include "animation.h"

class tuere
{
public:
    animation *t;
    bool offen;
    float posX, posY;

    tuere(void);
    //~tuere(void);
};


#endif // __TUERE_H__

#ifndef __PFEIL_H__
#define __PFEIL_H__

#include <SFML/Graphics.hpp>
#include "animation.h"

class pfeil
{
public:
    animation *p;
    unsigned int nX, nY;
    unsigned int farbe;
    string nLevel;


    ~pfeil(void);
};

#endif // __PFEIL_H__

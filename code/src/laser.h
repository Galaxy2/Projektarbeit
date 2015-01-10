#ifndef __LASER_H__
#define __LASER_H__

#include <SFML/Graphics.hpp>
#include "animation.h"

class laser
{
    public:
    animation* l;

    laser(void);
    ~laser(void);
};

#endif // __LASER_H__

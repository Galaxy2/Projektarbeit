#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

class level{
    public:
    list<sf::Rect<int> > mauern;
    void loadFromFile(string pfad);

};


#endif // __LEVEL_H__

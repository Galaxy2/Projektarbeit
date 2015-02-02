#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>


class game
{
public:
    //laerm

    int punkte;
    bool gewonnen;
    void punkteHinzufuegen(int p);

    std::string levelName;

    game(void);
    bool checkSieg(void);
};

#endif // __GAME_H__

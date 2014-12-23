#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>


class game
{
    public:
        //laerm

        int punkte;
        void punkteHinzufugen(int p);

        std::string levelName;

        game(void);
};


#endif // __GAME_H__

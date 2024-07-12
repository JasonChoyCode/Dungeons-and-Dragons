// Game.h
#include "Temple.h"
#include "utilities.h"
#include <iostream>
using namespace std;

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    virtual ~Game();
    void play();
private:
    //data members for temple levels
    Temple* m_temple[5];
    int numLevels;
    int goblinRange;
};



#endif // GAME_INCLUDED


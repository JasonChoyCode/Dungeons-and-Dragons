#ifndef Monsters_h
#define Monsters_h

#include "Actors.h"
#include "globals.h"
#include "utilities.h"

class Monsters : public Actor {
public:
    //constructor
    Monsters(string nam, int row, int col, int hitPoints, int armorPoints, int strength, int dexterity, char symbol, Weapons* weap);
    virtual ~Monsters(); // Use default destructor
    //virtual functions for monsters
    virtual void move(char grid[n_rows][n_cols], int row, int col) = 0;
    virtual Objects* dropWeapon(int r, int c) = 0;
};

#endif

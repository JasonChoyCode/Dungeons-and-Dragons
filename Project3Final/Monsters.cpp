#include "Monsters.h"

//Monster constructor
Monsters::Monsters(string nam, int row, int col, int hitPoints, int armorPoints, int strength, int dexterity, char symbol, Weapons* weap)
    : Actor(nam, row, col, hitPoints, armorPoints, strength, dexterity, symbol, weap) {
}

Monsters::~Monsters()
{
}



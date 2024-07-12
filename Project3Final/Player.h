#include "Actors.h"
#include "globals.h"
#include "Inventory.h"
#include <iostream>
using namespace std;


#ifndef Player_h
#define Player_h

class Player : public Actor
{
public:
    //constructors 
    Player(int row, int col); // Constructor declaration
    Player(int row, int col, int maxHP, int health, int armor, int strength, int dex, Weapons* wep, Inventory* invent);
    Player(const Player& other);

    //destructor
    virtual ~Player();

    //move function
    virtual void move(char dir, char grid[n_rows][n_cols]);

    //setter
    void setInventory(Inventory* newInventory);

    //getter function
    int getPrevCol() const;
    int getPrevRow() const;
    int getMaxHP();
    Inventory* getInventory();

    //read scrolls
    string readScroll(char choice);
    string readTele(char choice, pair<int, int> resultLocations);

    //scroll application
    void applyScroll(Scrolls* scroll);
    void incHealth(int i);

    //heal
    void heal();
private:
    //have it later
    int prevRow;
    int prevCol;
    Inventory* invent;
    int maxHitpoints;
};


#endif


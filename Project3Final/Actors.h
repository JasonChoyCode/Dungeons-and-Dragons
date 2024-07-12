#ifndef Actors_h
#define Actors_h
#include "utilities.h"
#include "Objects.h"

class Actor {
public:
    // Constructor
    Actor(string nam, int row, int col, int hitPoints, int armorPoints, int strength, int dexterity, char symbol, Weapons* wep);

    // Destructor
    virtual ~Actor();

    // Accessors
    string getName() const;
    int getRow() const;
    int getCol() const;
    int getHitPoints() const;
    int getArmorPoints() const;
    int getStrength() const;
    int getDexterity() const;
    int getSleepTime() const;
    char getSymbol() const;
    Weapons* getWep() const;

    // Mutators
    void setRow(int row);
    void setCol(int col);
    void setHitPoints(int hitPoints);
    void setArmorPoints(int armorPoints);
    void setStrength(int strength);
    void setDexterity(int dexterity);
    void setSleepTime(int sleepTime);
    void setSymbol(char sm);
    void setWep(Weapons* w);

    //functions for scrolls
    void incArmor(int armor);
    void incStrength(int strength);
    void incDex(int dex);

    //function to heal
    void addHeal();

    // Other methods
    virtual bool attack(Actor* target); //attacking function
    virtual void sleep(); // Function to handle sleeping behavior

private:
    string name;
    int m_row;
    int m_col;
    int m_hitPoints;
    int m_armorPoints;
    int m_strength;
    int m_dexterity;
    int m_sleepTime;
    char m_symbol;
    Weapons* wep;
};

#endif
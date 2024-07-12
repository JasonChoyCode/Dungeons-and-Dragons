#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include "utilities.h"
using namespace std;

//object class
class Objects {
public:
    Objects(string n, int r, int c, char s);
    int getRow() const;
    int getCol() const;
    char getSymbol() const;
    string getName() const;
    virtual ~Objects() = default;
private:
    string name;
    int row;
    int col;
    char symbol;
};

//weapons class
class Weapons : public Objects {
public:
    Weapons(string n, int r, int c, int dex, int dmg, string descrip);
    int getDex() const;
    int getDmg() const;
    string getDescript() const;
private:
    int dexBonus;
    int damage;
    string description;
};

//weapons classes
class Maces : public Weapons {
public:
    Maces(int r, int c);
};

class LongSwords : public Weapons {
public:
    LongSwords(int r, int c);
};

class ShortSwords : public Weapons {
public:
    ShortSwords(int r, int c);
};

class MagicAxes : public Weapons {
public:
    MagicAxes(int r, int c);
};

class Sleepfang : public Weapons {
public:
    Sleepfang(int r, int c);
};

//scrolls class
class Scrolls : public Objects {
public:
    Scrolls(int add, int r, int c, string n, string d);
    int getAtt() const;
    string getDescrip() const;
private:
    int iAttribute;
    string description;
};

//creation of scrolls
class ArmorS : public Scrolls {
public:
    ArmorS(int r, int c);
};

class StrengthS : public Scrolls {
public:
    StrengthS(int r, int c);
};

class HealthS : public Scrolls {
public:
    HealthS(int r, int c);
};

class DexS : public Scrolls {
public:
    DexS(int r, int c);
};

class TeleS : public Scrolls {
public:
    TeleS(int r, int c);
};

//idol class
class Idol : public Objects {
public:
    Idol(int r, int c);
    virtual ~Idol();
};

#endif // OBJECTS_H

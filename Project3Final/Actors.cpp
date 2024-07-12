#include "Actors.h"

// Constructor
Actor::Actor(string nam, int row, int col, int hitPoints, int armorPoints, int strength, int dexterity, char symbol, Weapons* wep)
    : name(nam), m_row(row), m_col(col), m_hitPoints(hitPoints),
    m_armorPoints(armorPoints), m_strength(strength),
    m_dexterity(dexterity), m_sleepTime(0), m_symbol(symbol), wep(wep) {}

// Destructor
Actor::~Actor()
{
    if (getName() != "Player")
    {
        delete wep;
    }
}

// Accessors
string Actor::getName() const {
    return name;
}
int Actor::getRow() const {
    return m_row;
}

int Actor::getCol() const {
    return m_col;
}

int Actor::getHitPoints() const {
    return m_hitPoints;
}

int Actor::getArmorPoints() const {
    return m_armorPoints;
}

int Actor::getStrength() const {
    return m_strength;
}

int Actor::getDexterity() const {
    return m_dexterity;
}

int Actor::getSleepTime() const {
    return m_sleepTime;
}
char Actor::getSymbol() const {
    return m_symbol;
}

Weapons* Actor::getWep() const
{
    return wep;
}

// Mutators
void Actor::setRow(int row) {
    m_row = row;
}

void Actor::setCol(int col) {
    m_col = col;
}

void Actor::setHitPoints(int hitPoints) {
    m_hitPoints = hitPoints;
}

void Actor::setArmorPoints(int armorPoints) {
    m_armorPoints = armorPoints;
}

void Actor::setStrength(int strength) {
    m_strength = strength;
}

void Actor::setDexterity(int dexterity) {
    m_dexterity = dexterity;
}

void Actor::setSleepTime(int sleepTime) {
    m_sleepTime = sleepTime;
}

void Actor::setSymbol(char sm) {
    m_symbol = sm;
}
void Actor::setWep(Weapons* w)
{
    wep = w;
}


//methods for increasing stats (used with scrolls)
void Actor::incArmor(int armor)
{
    if (m_armorPoints + armor > 99)
        m_armorPoints = 99;
    else {
        m_armorPoints += armor;
    }
}
void Actor::incStrength(int strength)
{
    if (m_strength + strength > 99)
        m_strength = 99;
    else {
        m_strength += strength;
    }
}
void Actor::incDex(int dex)
{
    if (m_dexterity + dex > 99)
        m_dexterity = 99;
    else
    {
        m_dexterity += dex;
    }
}

//heal the dragon and the player
void Actor::addHeal()
{
    m_hitPoints++;
}

// Sleep method
void Actor::sleep() {
    if (m_sleepTime > 0) {
        m_sleepTime--;
    }
}

//general attack method for all actors
bool Actor::attack(Actor* target)
{
    int attackerPoints = getWep()->getDex() + getDexterity();
    int defenderPoints = target->getDexterity() + target->getWep()->getDex();

    int attackerRandom = randInt(1, attackerPoints);
    int defenderRandom = randInt(1, defenderPoints);

    //code for attack if the actor is using the fangs of sleep
    if (attackerRandom >= defenderRandom && getWep()->getName() == "magic fangs")
    {
        int damagePoints = randInt(0, getStrength() + getWep()->getDmg() - 1);
        target->setHitPoints(target->getHitPoints() - damagePoints);
        if (trueWithProbability(1 / 5.0))
        {
            int sleepTimeSet = randInt(2, 6);
            if (target->getSleepTime() != 0)
            {
                int store = max(target->getSleepTime(), sleepTimeSet);
                target->setSleepTime(store);
            }
            else {
                target->setSleepTime(sleepTimeSet);
            }
        }
        return true;
    }
    //regular attack if you are not using the fangs of sleep
    if (attackerRandom >= defenderRandom)
    {
        int damagePoints = randInt(0, getStrength() + getWep()->getDmg() - 1);
        target->setHitPoints(target->getHitPoints() - damagePoints);
        return true;
    }
    return false;
}


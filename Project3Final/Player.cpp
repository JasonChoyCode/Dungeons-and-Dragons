#include "Player.h"

//constructor for level 1
Player::Player(int row, int col)
    :Actor("Player", row, col, 20, 2, 2, 2, '@', new ShortSwords(0, 0)), prevRow(-1), prevCol(-1)
{
    invent = new Inventory();
    invent->setFirstItem(getWep());
    maxHitpoints = 20;
}

//constructor for every other level
Player::Player(int row, int col, int maxHP, int health, int armor, int strength, int dex, Weapons* wep, Inventory* inv)
    :Actor("Player", row, col, health, armor, strength, dex, '@', new Weapons(*wep)), prevRow(-1), prevCol(-1), maxHitpoints(maxHP)
{
    invent = new Inventory(*inv);
    invent->removeSingle(getWep());
    invent->setFirstItem(getWep());
}

//destructor
Player::~Player()
{
    delete invent;
}

//copy constructor
Player::Player(const Player& other)
    : Actor(other), prevRow(other.prevRow), prevCol(other.prevCol), maxHitpoints(other.maxHitpoints) {

    invent = new Inventory(*other.invent); // Deep copy the inventory
    Actor::setWep(new Weapons(*other.getWep())); // Deep copy the weapon
}

//accessors
int Player::getPrevRow() const {
    return prevRow;
}

int Player::getPrevCol() const {
    return prevCol;
}

int Player::getMaxHP()
{
    return maxHitpoints;
}

Inventory* Player::getInventory()
{
    return invent;
}

//move onto a place if it is not a wall
void Player::move(char dir, char grid[n_rows][n_cols]) {
    // Implement movement logic based on direction 'dir' and modify grid as necessary
    int r = getRow();
    int c = getCol();
    prevRow = getRow();
    prevCol = getCol();
    //dont forget to account for monsters
    switch (dir) {
    case 'h': // Left
        if (grid[r][c - 1] != '#')
            setCol(c - 1);
        break;
    case 'l': // Right
        if (grid[r][c + 1] != '#')
            setCol(c + 1);
        break;
    case 'k': // Up
        if (grid[r - 1][c] != '#')
            setRow(r - 1);
        break;
    case 'j': // Down
        if (grid[r + 1][c] != '#')
            setRow(r + 1);
        break;
    default:
        break;
    }
}

//setter
void Player::setInventory(Inventory* newInventory) {
    if (invent != newInventory) {
        delete invent; // Safely delete the old inventory if it's not the same as the new one
        invent = newInventory; // Update the pointer to the new inventory
    }
}


//read scroll functions
string Player::readScroll(char choice) {
    invent->displayInventory();

    int valid = choice - 'a';

    //check valid index
    if (valid < 0 || valid >= invent->getNumItems()) {
        return "";
    }

    //check if you can read a scroll or not
    Scrolls* selectedScroll = dynamic_cast<Scrolls*>(invent->getItem(valid));
    if (selectedScroll) {
        applyScroll(selectedScroll);
        string scrollReturn = "You read the scroll called " + selectedScroll->getName() + "\n" + selectedScroll->getDescrip();
        invent->removeItem(selectedScroll);
        return scrollReturn;
    }
    else if (valid < invent->getNumItems()) {
        return "You can't read a " + invent->getItem(valid)->getName();
    }
    return "";
}

//read a teleportation scroll
string Player::readTele(char choice, pair<int, int> resultLocations) {
    invent->displayInventory();

    int valid = choice - 'a';

    //check valid index
    if (valid < 0 || valid >= invent->getNumItems()) {
        return "";
    }

    //move the player to a random location if possible
    Scrolls* selectedScroll = dynamic_cast<Scrolls*>(invent->getItem(valid));
    if (selectedScroll->getName() == "scroll of teleportation") {
        int newRow = resultLocations.first;
        int newCol = resultLocations.second;
        // Update player's position
        setRow(newRow);
        setCol(newCol);

        // Mark the new position on the grid
        string scrollReturn = "You read the scroll called " + selectedScroll->getName() + "\n" + selectedScroll->getDescrip();
        invent->removeItem(selectedScroll);
        return scrollReturn;
    }
    else if (valid < invent->getNumItems())
    {
        return "You can't read a " + invent->getItem(valid)->getName();
    }
    return "";
}

//increase health points function for scroll
void Player::incHealth(int i)
{
    if (maxHitpoints + i > 99)
        maxHitpoints = 99;
    else {
        maxHitpoints += i;
    }
}

//apply the scroll to player's stats
void Player::applyScroll(Scrolls* scroll) {
    if (scroll->getName() == "scroll of enhance armor") {
        incArmor(scroll->getAtt());
    }
    else if (scroll->getName() == "scroll of strength") {
        incStrength(scroll->getAtt());
    }
    else if (scroll->getName() == "scroll of enhance health") {
        incHealth(scroll->getAtt());
    }
    else if (scroll->getName() == "scroll of enhance dexterity") {
        incDex(scroll->getAtt());
    }
    else if (scroll->getName() == "scroll of teleportation")
    {

    }
}

//heal player function
void Player::heal()
{
    if (getHitPoints() + 1 <= maxHitpoints)
        addHeal();
}
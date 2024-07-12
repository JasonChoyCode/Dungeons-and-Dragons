// Game.cpp

#include "Game.h"

// Implement these and other Game member functions you may have added.

//constructor and destructor
Game::Game(int smellDistance)
    :goblinRange(smellDistance), numLevels(1)
{
    m_temple[0] = new Temple(0, goblinRange, 0, 0, 0, 0, 0, nullptr, nullptr);
}

Game::~Game()
{
    for (int i = 0; i < numLevels; i++)
    {
        delete m_temple[i];
    }
}

//play function implementations
void Game::play()
{
    //display
    m_temple[0]->display();
    int l = 0;
    char cmd = ' ';
    bool endGame = false;
    //while the game is not supposed to end
    while (cmd != 'q') {
        // Clear screen 
        clearScreen();

        // Display the current temple level
        m_temple[l]->display();

        // Check if the player is dead
        if (m_temple[l]->getPlayer()->getHitPoints() <= 0) {
            cout << "Press q to exit game." << endl;
            while (getCharacter() != 'q')
            {
            }
            break;
        }
        if (endGame)
        {
            cout << "Press q to exit game." << endl;
            // Get the next command from the player
            while (getCharacter() != 'q')
            {
            }
            break;
        }

        cmd = getCharacter();

        // Handle the command
        switch (cmd) {
            //case for q which u cannot press if you are sleeping
        case 'q':
            if (m_temple[l]->getPlayer()->getSleepTime() > 0 && m_temple[l]->getPlayer()->getHitPoints() <= 0)
            {
                continue;
            }
            else if (m_temple[l]->getPlayer()->getSleepTime() > 0)
            {
                cmd = '6';
                break;
            }
            break;
            //case for the four arrow movements
        case 'h':
        case 'l':
        case 'k':
        case 'j':
            m_temple[l]->setDir(cmd);
            break;
            //case for wielding a weapon
        case 'w': {
            if (m_temple[l]->getPlayer()->getSleepTime() > 0)
                break;
            // Handle weapon switch
            m_temple[l]->setDir(cmd);
            m_temple[l]->getPlayer()->getInventory()->displayInventory();
            char set = getCharacter();
            //change your weapon based on the character that the user presses
            Weapons* currentWep = m_temple[l]->getPlayer()->getWep();
            Weapons* newWep = m_temple[l]->getPlayer()->getInventory()->chooseWep(set, currentWep);
            if (newWep != nullptr && currentWep == newWep)
                continue;
            else if (newWep != nullptr) {
                m_temple[l]->getPlayer()->setWep(newWep);
                m_temple[l]->getOutputs().push_back("You are wielding " + newWep->getName());
            }
            //cannot wield a scroll check
            else if (set - 'a' < m_temple[l]->getPlayer()->getInventory()->getNumItems())
            {
                m_temple[l]->getOutputs().push_back("You can't wield " + m_temple[l]->getPlayer()->getInventory()->getItem(set - 'a')->getName());
            }
            break;
        }
                //case for reading scrolls
        case 'r': {
            if (m_temple[l]->getPlayer()->getSleepTime() > 0)
                break;
            m_temple[l]->setDir(cmd);
            m_temple[l]->getPlayer()->getInventory()->displayInventory();
            char set = getCharacter();
            //check for the character and see if there is a scroll at that position
            int valid = set - 'a';
            //separate code to check for the scroll of teleportation for it to work
            if (valid >= 0 && valid < m_temple[l]->getPlayer()->getInventory()->getNumItems() && m_temple[l]->getPlayer()->getInventory()->getItem(valid)->getName() == "scroll of teleportation") {
                pair<int, int> resultLocation = m_temple[l]->getEmptyLocations();
                int prevRow = m_temple[l]->getPlayer()->getRow();
                int prevCol = m_temple[l]->getPlayer()->getCol();
                string teleportResult = m_temple[l]->getPlayer()->readTele(set, resultLocation);
                m_temple[l]->setCoord(prevRow, prevCol, ' ');
                m_temple[l]->setCoord(resultLocation.first, resultLocation.second, '@');
                m_temple[l]->getOutputs().push_back(teleportResult);
            }
            //regular outputs for all the other different types of scrolls
            else if (valid >= 0 && valid < m_temple[l]->getPlayer()->getInventory()->getNumItems())
            {
                m_temple[l]->getOutputs().push_back(m_temple[l]->getPlayer()->readScroll(set));
            }
            break;
        }
        case '>':
            //case for the stairs and moving levels
            if (m_temple[l]->getPlayer()->getSleepTime() > 0) break;
            m_temple[l]->setDir(cmd);
            //stairs only for levels that are under level 5
            if (l < 4 && m_temple[l]->getPlayer()->getRow() == m_temple[l]->getStair().first &&
                m_temple[l]->getPlayer()->getCol() == m_temple[l]->getStair().second) {
                int i = l;
                l++;
                numLevels++;
                //process of creating a new player if you move levels with the same data that it originally has
                Weapons* currentWeapon = m_temple[i]->getPlayer()->getWep();
                Inventory* currentInventory = m_temple[i]->getPlayer()->getInventory();
                // Set current inventory to null to prevent double deletion
                m_temple[l] = new Temple(l, goblinRange, m_temple[i]->getPlayer()->getMaxHP(), m_temple[i]->getPlayer()->getHitPoints(),
                    m_temple[i]->getPlayer()->getArmorPoints(), m_temple[i]->getPlayer()->getStrength(), m_temple[i]->getPlayer()->getDexterity(),
                    currentWeapon, currentInventory);
            }
            break;
            //case for checking the inventory
        case 'i':
            if (m_temple[l]->getPlayer()->getSleepTime() > 0)
                break;
            m_temple[l]->setDir(cmd);
            m_temple[l]->getPlayer()->getInventory()->displayInventory();
            getCharacter(); // Wait for any character to close the inventory display
            break;
        case 'c':
            //case for cheating
            if (m_temple[l]->getPlayer()->getSleepTime() > 0)
                break;
            m_temple[l]->getPlayer()->setHitPoints(50);
        case 'g':
            //case for picking up an item
            if (m_temple[l]->getPlayer()->getSleepTime() > 0)
                break;
            m_temple[l]->setDir(cmd);
            //can only pick up items if your inventory is not full
            if (m_temple[l]->getPlayer()->getInventory()->getNumItems() <= 25) {
                // Assuming the addItem() method and getItemOnGrid() method exist
                Objects* item = m_temple[l]->getObject(m_temple[l]->getPlayer()->getRow(), m_temple[l]->getPlayer()->getCol());
                if (item != nullptr) {
                    m_temple[l]->getPlayer()->getInventory()->addItem(item);
                    //fix the output statement
                    //check if it is a scroll or weapon
                    Scrolls* temp = dynamic_cast<Scrolls*>(item);
                    if (temp != nullptr)
                    {
                        m_temple[l]->getOutputs().push_back("You pick up a scroll called " + item->getName());
                    }
                    else {
                        m_temple[l]->getOutputs().push_back("You pick up " + item->getName());
                    }
                    // Assuming you have a way to remove the item from the grid
                    m_temple[l]->removeObject(item->getRow(), item->getCol());
                }
            }
            else {
                m_temple[l]->getOutputs().push_back("Your knapsack is full; you can't pick that up.");
            }
            //if it is level 4 then you have the chance to pick up the idol and win the game
            if (l == 4)
            {
                //debug the end game its fucked and just doesn't work
                if (m_temple[l]->getPlayer()->getRow() == m_temple[l]->getIdol().first &&
                    m_temple[l]->getPlayer()->getCol() == m_temple[l]->getIdol().second) {
                    m_temple[l]->getPlayer()->getInventory()->addItem(new Idol(m_temple[l]->getIdol().first, m_temple[l]->getIdol().second));
                    Objects* item = m_temple[l]->getObject(m_temple[l]->getPlayer()->getRow(), m_temple[l]->getPlayer()->getCol());
                    m_temple[l]->getOutputs().push_back("You pick up the golden idol");
                    m_temple[l]->getOutputs().push_back("Congratulations, you won!");
                    endGame = true;
                }
            }
            break;

        default:
            // Continue loop for unrecognized commands
            continue;
        }
    }
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.

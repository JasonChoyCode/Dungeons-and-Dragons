#include "Temple.h"


Temple::Temple(int l, int smellDistance, int maxHP, int health, int armor, int strength, int dex, Weapons* wep, Inventory* inv)
    :level(l), smellD(smellDistance)
{
    //create all the rooms
    int numR = randInt(4, 6);
    for (int i = 0; i < numR; i++)
    {
        generateRoom();
    }

    
    int roomIndex = randInt(0, rooms.size() - 1);
    const Rooms& selectedRoom = rooms[roomIndex];

    // Get the bounds of the selected room
    int roomRow = selectedRoom.getRows();
    int roomCol = selectedRoom.getCols();
    int roomWidth = selectedRoom.getWidth();
    int roomHeight = selectedRoom.getHeight();

    //set grid
    int r, c;

    // Fill the grid with dots
    for (r = 0; r < n_rows; r++)
        for (c = 0; c < n_cols; c++)
            grid[r][c] = '#';


    //Set the rooms to empty grids
    for (const Rooms& room : rooms) {
        int roomRow = room.getRows();
        int roomCol = room.getCols();
        int roomWidth = room.getWidth();
        int roomHeight = room.getHeight();

        for (int i = 0; i < roomHeight; ++i) {
            for (int j = 0; j < roomWidth; ++j) {
                int newRow = roomRow + i;
                int newCol = roomCol + j;
                if (newRow >= 0 && newRow < n_rows && newCol >= 0 && newCol < n_cols) {
                    grid[newRow][newCol] = ' ';
                }
            }
        }
    }
    //add the corridors
    createHallways();

    //spawning of the stair
    if (level < 4)
    {
        vector<pair<int, int>> emptyLocations;
        for (int r = 0; r < n_rows; r++) {
            for (int c = 0; c < n_cols; c++) {
                if (grid[r][c] == ' ') {
                    emptyLocations.push_back({ r, c });
                }
            }
        }

        // Place the '>' symbol at a random empty location
        if (!emptyLocations.empty()) {
            int stairIndex = randInt(0, emptyLocations.size() - 1);
            grid[emptyLocations[stairIndex].first][emptyLocations[stairIndex].second] = '>';
            stair.push_back(emptyLocations[stairIndex]);
        }
    }

    //spawn the idol
    if (level == 4)
    {
        vector<pair<int, int>> emptyLocations;
        for (int r = 0; r < n_rows; r++) {
            for (int c = 0; c < n_cols; c++) {
                if (grid[r][c] == ' ') {
                    emptyLocations.push_back({ r, c });
                }
            }
        }

        // Place the idol symbol at a random empty location
        if (!emptyLocations.empty()) {
            int idolIndex = randInt(0, emptyLocations.size() - 1);
            grid[emptyLocations[idolIndex].first][emptyLocations[idolIndex].second] = '&';
            idol.push_back(emptyLocations[idolIndex]);
        }
    }

    //spawn the player
    int playerRow = randInt(roomRow, roomRow + roomHeight - 1);
    int playerCol = randInt(roomCol, roomCol + roomWidth - 1);

    if (l == 0)
    {
        player = new Player(playerRow, playerCol);
    }
    else
    {
        player = new Player(playerRow, playerCol, maxHP, health, armor, strength, dex, wep, inv);
    }

    //spawn the objects
    spawnItems();

    //spawn the monsters
    numMonsters = randInt(2, 5 * (l + 1) + 1);

    if (l >= 0) {
        // Create a list of all empty locations
        vector<pair<int, int>> emptyLocations;
        for (int r = 0; r < n_rows; r++) {
            for (int c = 0; c < n_cols; c++) {
                if (grid[r][c] == ' ') {
                    emptyLocations.push_back({ r, c });
                }
            }
        }

        // Determine number of Snakewomen
        int numSnake = randInt(2, numMonsters);
        numMonsters -= numSnake;
        for (int i = 0; i < numSnake; i++) {
            if (!emptyLocations.empty()) {
                int index = randInt(0, emptyLocations.size() - 1);
                int row = emptyLocations[index].first;
                int col = emptyLocations[index].second;
                emptyLocations.erase(emptyLocations.begin() + index); // Remove the location
                monsters.push_back(new Snakewomen(row, col));
            }
        }

        // Determine number of Goblins
        int numGoblin = randInt(0, numMonsters);
        numMonsters -= numSnake;
        for (int i = 0; i < numGoblin; i++) {
            if (!emptyLocations.empty()) {
                int index = randInt(0, emptyLocations.size() - 1);
                int row = emptyLocations[index].first;
                int col = emptyLocations[index].second;
                emptyLocations.erase(emptyLocations.begin() + index); // Remove the location
                monsters.push_back(new Goblin(row, col, smellD));
            }
        }

        // Determine number of Bogeymen
        if (l >= 2) {
            int numBogeymen = randInt(0, numMonsters);
            numMonsters -= numSnake;
            for (int i = 0; i < numBogeymen; i++) {
                if (!emptyLocations.empty()) {
                    int index = randInt(0, emptyLocations.size() - 1);
                    int row = emptyLocations[index].first;
                    int col = emptyLocations[index].second;
                    emptyLocations.erase(emptyLocations.begin() + index); // Remove the location
                    monsters.push_back(new Bogeyman(row, col));
                }
            }
        }

        // Determine number of Dragons
        if (l >= 3) {
            int numDragons = randInt(0, numMonsters);
            for (int i = 0; i < numDragons; i++) {
                if (!emptyLocations.empty()) {
                    int index = randInt(0, emptyLocations.size() - 1);
                    int row = emptyLocations[index].first;
                    int col = emptyLocations[index].second;
                    emptyLocations.erase(emptyLocations.begin() + index); // Remove the location
                    monsters.push_back(new Dragon(row, col));
                }
            }
        }
    }
}

//destructor
Temple::~Temple()
{
    delete player;
    for (Monsters* monster : monsters) {
        delete monster;
    }
    for (int i = 0; i < spawnedNew.size(); i++)
    {
        delete spawnedNew[i];
    }
}

//return the object at a given position
Objects* Temple::getObject(int r, int c)
{
    for (int i = 0; i < spawnedNew.size(); i++)
    {
        if (spawnedNew[i]->getRow() == r && spawnedNew[i]->getCol() == c)
        {
            return spawnedNew[i];
        }
    }
    return nullptr; // Return nullptr if no object is found at the given position
}

//remove the object
void Temple::removeObject(int r, int c)
{
    for (int i = 0; i < spawnedNew.size(); ++i)
    {
        if (spawnedNew[i]->getRow() == r && spawnedNew[i]->getCol() == c)
        {
            spawnedNew.erase(spawnedNew.begin() + i); // Remove the object from the vector
            grid[r][c] = ' '; // Clear the position on the grid
            return; // Exit the function once the object is found and removed
        }
    }
}

//spawn the items on the grid
void Temple::spawnItems()
{
    int numItems = randInt(2, 3);

    vector<pair<int, int>> emptyLocations;
    for (int r = 0; r < n_rows; r++) {
        for (int c = 0; c < n_cols; c++) {
            if (grid[r][c] == ' ') {
                emptyLocations.push_back({ r, c });
            }
        }
    }
    //randomly determine a drop at a random empty location
    for (int i = 0; i < numItems && !emptyLocations.empty(); i++)
    {
        int selectDrop = randInt(1, 7);
        int randomIndex = randInt(0, emptyLocations.size() - 1);
        int row = emptyLocations[randomIndex].first;
        int col = emptyLocations[randomIndex].second;

        // Remove the chosen location from emptyLocations to prevent spawning multiple items in the same location
        emptyLocations.erase(emptyLocations.begin() + randomIndex);

        switch (selectDrop)
        {
        case 1:
            // Scroll of improve armor
            spawnedNew.push_back(new ArmorS(row, col));
            grid[row][col] = '?';
            break;
        case 2:
            // Scroll of raise strength
            spawnedNew.push_back(new StrengthS(row, col));
            grid[row][col] = '?';
            break;
        case 3:
            // Scroll of enhance health
            spawnedNew.push_back(new HealthS(row, col));
            grid[row][col] = '?';
            break;
        case 4:
            // Scroll of enhance dexterity
            spawnedNew.push_back(new DexS(row, col));
            grid[row][col] = '?';
            break;
        case 5:
            // Mace
            // Create a new Mace object and place it on the grid
            spawnedNew.push_back(new Maces(row, col));
            grid[row][col] = ')';
            break;
        case 6:
            // Short sword
            // Create a new ShortSword object and place it on the grid
            spawnedNew.push_back(new ShortSwords(row, col));
            grid[row][col] = ')';
            break;
        case 7:
            // Long sword
            // Create a new LongSword object and place it on the grid
            spawnedNew.push_back(new LongSwords(row, col));
            grid[row][col] = ')';
            break;
        default:
            // Code to handle cases other than 1-7
            break;
        }
    }
}


//getter
int Temple::getLevel() const {
    return level;
}

//add a room to the vector
void Temple::addRoom(const Rooms& room) {
    rooms.push_back(room);
}

//set a coordinate to a certain char
void Temple::setCoord(int r, int c, char w)
{
    grid[r][c] = w;
}


void Temple::setGrid()
{
    createHallways();
}

//return the player
Player* Temple::getPlayer() const
{
    return player;
}

//set a direction
void Temple::setDir(char dir)
{
    direct = dir;
}

//check if the rooms are built on top of each other
bool Temple::roomOverlap(const Rooms& newRoom, const Rooms& existingRoom)
{
    int newRow = newRoom.getRows();
    int newCol = newRoom.getCols();
    int newWidth = newRoom.getWidth();
    int newHeight = newRoom.getHeight();

    // Get the positions and dimensions of the existing room
    int existingRow = existingRoom.getRows();
    int existingCol = existingRoom.getCols();
    int existingWidth = existingRoom.getWidth();
    int existingHeight = existingRoom.getHeight();

    // Check for overlap by comparing the boundaries of the rooms
    if (newCol + newWidth < existingCol || existingCol + existingWidth < newCol ||
        newRow + newHeight < existingRow || existingRow + existingHeight < newRow) {
        // No overlap detected
        return false;
    }
    else {
        // Overlap detected
        return true;
    }
}

//create a room
void Temple::generateRoom()
{
    bool roomAdded = false;

    while (!roomAdded) {
        int width = randInt(5, 16);
        int height = randInt(5, 12);
        int row = randInt(1, n_rows - height - 1);
        int col = randInt(1, n_cols - width - 1);

        Rooms newRoom(row, col, width, height);

        // Check if the new room overlaps with any existing room
        roomAdded = true; // Assume the room can be added
        for (const Rooms& existingRoom : rooms) {
            if (roomOverlap(newRoom, existingRoom)) {
                // If overlap is detected, set roomAdded to false and break the loop
                roomAdded = false;
                break;
            }
        }

        if (roomAdded) {
            // If no overlap is detected, add the room to the vector
            addRoom(newRoom);
        }
    }
}


//get the string of outputs
vector<string>& Temple::getOutputs()
{
    return outputs;
}

//when you kill a monster it should not automatically move onto their spot
void Temple::displayActors() {
    if (player != nullptr) {
        int prevRow = player->getRow();
        int prevCol = player->getCol();

        // Move player
        if (player->getSleepTime() == 0)
        {
            if (trueWithProbability(1 / 10.0))
            {
                player->heal();
            }
            player->move(direct, grid);

            bool playerAttacked = false;

            // Check if player moved into a monster's position
            for (Monsters* monster : monsters) {
                if (player->getRow() == monster->getRow() && player->getCol() == monster->getCol()) {
                    // Player attacks the monster
                    playerAttacked = true;
                    int initialSleepTime = monster->getSleepTime();
                    if (player->attack(monster)) {
                        // If the monster dies, remove it from the grid and the monsters vector
                        if (monster->getHitPoints() <= 0) {
                            outputs.push_back(player->getName() + " " + player->getWep()->getDescript() + " " + monster->getName() + " dealing a final blow.");

                            // Check if there is a previous item at the monster position
                            bool checkItem = false;
                            for (int i = 0; i < spawnedNew.size(); i++) {
                                if (spawnedNew[i]->getRow() == monster->getRow() && spawnedNew[i]->getCol() == monster->getCol()) {
                                    checkItem = true;
                                }
                            }

                            // Add the drop if there is no item already there
                            if (!checkItem) {
                                Objects* tempstore = monster->dropWeapon(monster->getRow(), monster->getCol());
                                if (tempstore != nullptr) {
                                    spawnedNew.push_back(tempstore);
                                }
                            }

                            // Clear the monster's position on the grid
                            grid[monster->getRow()][monster->getCol()] = ' ';

                            // Find and remove the monster from the vector
                            for (vector<Monsters*>::iterator it = monsters.begin(); it != monsters.end();) {
                                if (*it == monster) {
                                    it = monsters.erase(it); // Erase the monster and get the next iterator
                                    delete monster;
                                    break; // Since each monster is unique, we can break after finding it
                                }
                                else {
                                    ++it; // Move to the next element
                                }
                            }


                            // Ensure player's position on the grid is correctly updated
                            player->setRow(prevRow);
                            player->setCol(prevCol);
                            grid[player->getRow()][player->getCol()] = player->getSymbol();
                        }
                        else {
                            // Player's move is blocked by the monster
                            if (player->getWep()->getName() == "magic fangs" && monster->getSleepTime() > initialSleepTime) {
                                outputs.push_back(player->getName() + " " + player->getWep()->getDescript() + " " + monster->getName() + " and hits, putting " + monster->getName() + " to sleep.");
                            }
                            else {
                                outputs.push_back(player->getName() + " " + player->getWep()->getDescript() + " " + monster->getName() + " and hits.");
                            }
                            player->setRow(prevRow);
                            player->setCol(prevCol);
                        }
                    }
                    else {
                        outputs.push_back(player->getName() + " " + player->getWep()->getDescript() + " " + monster->getName() + " and misses.");
                        // Player's move is blocked by the monster
                        player->setRow(prevRow);
                        player->setCol(prevCol);
                    }
                    break;
                }
            }

            if (!playerAttacked) {
                // Update grid for player's new position if no attack happened
                grid[prevRow][prevCol] = ' ';
                grid[player->getRow()][player->getCol()] = player->getSymbol();
            }
            else {
                // Ensure previous position is cleared if player attacked
                grid[prevRow][prevCol] = ' ';
                // Ensure player's current position is marked on the grid
                grid[player->getRow()][player->getCol()] = player->getSymbol();
            }
        }
        else {
            player->sleep();
        }


        for (Monsters* monster : monsters) {

            if (monster->getSleepTime() > 0)
            {
                monster->sleep();
                continue;
            }
            int MprevRow = monster->getRow();
            int MprevCol = monster->getCol();
            int playerRow = player->getRow();
            int playerCol = player->getCol();

            // Check if monster is adjacent to the player and attacks
            if ((MprevRow == playerRow && abs(MprevCol - playerCol) == 1) ||
                (MprevCol == playerCol && abs(MprevRow - playerRow) == 1)) {
                int initialSleepTime = player->getSleepTime();
                if (monster->attack(player)) {
                    // If the player dies, print the death message
                    if (player->getHitPoints() <= 0) {
                        outputs.push_back(monster->getName() + " " + monster->getWep()->getDescript() + " " + player->getName() + " delivering a fatal blow.");

                        break;
                    }
                    else if (monster->getWep()->getName() == "magic fangs" && player->getSleepTime() > initialSleepTime)
                    {
                        outputs.push_back(monster->getName() + " " + monster->getWep()->getDescript() + " " + player->getName() + " and hits, putting " + player->getName() + " to sleep.");
                    }
                    else {
                        outputs.push_back(monster->getName() + " " + monster->getWep()->getDescript() + " " + player->getName() + " and hits.");
                    }
                }
                else {
                    outputs.push_back(monster->getName() + " " + monster->getWep()->getDescript() + " " + player->getName() + " and misses.");
                }
            }

            // Move the monster
            if (monster->getSleepTime() == 0)
            {
                if (monster->getName() == "Dragon")
                {
                    if (trueWithProbability(1 / 10.0))
                    {
                        monster->addHeal();
                    }
                }
                monster->move(grid, player->getRow(), player->getCol());
            }

            // Update grid for monster's new position
            grid[MprevRow][MprevCol] = ' ';
            grid[monster->getRow()][monster->getCol()] = monster->getSymbol();
        }
    }
    displayConstants();
}


void Temple::displayConstants() {
    // Ensure there is at least one stair defined
    if (!stair.empty()) {
        int stairRow = stair[0].first;
        int stairCol = stair[0].second;

        // Check the current character at the stair's position
        char currentChar = grid[stairRow][stairCol];

        // If it is not a player or a monster, set it to '>'
        if (currentChar != '@' && currentChar != 'S' && currentChar != 'G' && currentChar != 'B' && currentChar != 'D') {
            grid[stairRow][stairCol] = '>';
        }
    }
    if (!idol.empty()) {
        int idolRow = idol[0].first;
        int idolCol = idol[0].second;

        // Check the current character at the idol's position
        char currentChar = grid[idolRow][idolCol];

        // If it is not a player or a monster, set it to '&'
        if (currentChar != '@' && currentChar != 'S' && currentChar != 'G' && currentChar != 'B' && currentChar != 'D') {
            grid[idolRow][idolCol] = '&';
        }
    }
    if (!spawnedNew.empty()) {
        for (size_t i = 0; i < spawnedNew.size(); ++i) {
            int obRow = spawnedNew[i]->getRow();
            int obCol = spawnedNew[i]->getCol();

            // Check the current character at the objects position
            char currentChar = grid[obRow][obCol];

            // If it is not a player or a monster, set it to 'object'
            if (currentChar != '@' && currentChar != 'S' && currentChar != 'G' && currentChar != 'B' && currentChar != 'D') {
                grid[obRow][obCol] = spawnedNew[i]->getSymbol();
            }
        }
    }

}

//find an empty location on the grid
pair<int, int> Temple::getEmptyLocations() const {
    vector<pair<int, int>> emptyLocations;

    for (int r = 0; r < n_rows; ++r) {
        for (int c = 0; c < n_cols; ++c) {
            if (grid[r][c] == ' ') {
                emptyLocations.push_back(make_pair(r, c));
            }
        }
    }

    int randIndex = randInt(0, emptyLocations.size() - 1);

    return emptyLocations[randIndex];
}

// Get center of a room
void Temple::getRoomCenter(const Rooms& room, int& centerRow, int& centerCol) const {
    centerRow = room.getRows() + room.getHeight() / 2;
    centerCol = room.getCols() + room.getWidth() / 2;
}

pair<int, int> Temple::getStair() const
{
    return stair[0];
}

pair<int, int> Temple::getIdol() const
{
    return idol[0];
}

void createHallway(int startRow, int startCol, int endRow, int endCol, char grid[n_rows][n_cols]) {
    // Create horizontal hallway
    int minCol, maxCol;
    int minRow, maxRow;
    if (startCol < endCol) {
        minCol = startCol;
        maxCol = endCol;
    }
    else {
        minCol = endCol;
        maxCol = startCol;
    }
    for (int col = minCol; col <= maxCol; ++col) {
        grid[startRow][col] = ' ';
    }

    // Create vertical hallway
    if (startRow < endRow) {
        minRow = startRow;
        maxRow = endRow;
    }
    else {
        minRow = endRow;
        maxRow = startRow;
    }
    for (int row = minRow; row <= maxRow; ++row) {
        grid[row][endCol] = ' ';
    }
}

void Temple::createHallways() {
    vector<int> connectedRooms;    // List of connected rooms
    vector<int> unconnectedRooms;  // List of unconnected rooms

    for (size_t i = 0; i < rooms.size(); ++i) {
        unconnectedRooms.push_back(i);
    }

    // Start by connecting the first room
    connectedRooms.push_back(0);
    unconnectedRooms.erase(unconnectedRooms.begin());

    while (!unconnectedRooms.empty()) {
        int nearestRoomIndex = -1;
        int nearestConnectedRoom = -1;
        double minDistance = -1; // Initialize to an invalid value

        for (int connectedRoom : connectedRooms) {
            int centerRow1, centerCol1;
            getRoomCenter(rooms[connectedRoom], centerRow1, centerCol1);

            for (size_t i = 0; i < unconnectedRooms.size(); ++i) {
                int unconnectedRoom = unconnectedRooms[i];
                int centerRow2, centerCol2;
                getRoomCenter(rooms[unconnectedRoom], centerRow2, centerCol2);

                // Calculate the distance between the centers
                double distance = sqrt((centerRow2 - centerRow1) * (centerRow2 - centerRow1) +
                    (centerCol2 - centerCol1) * (centerCol2 - centerCol1));

                // Update the nearest room if the distance is smaller
                if (minDistance == -1 || distance < minDistance) {
                    minDistance = distance;
                    nearestRoomIndex = unconnectedRoom;
                    nearestConnectedRoom = connectedRoom;
                }
            }
        }

        // Connect the nearest unconnected room to the nearest connected room
        if (nearestRoomIndex != -1 && nearestConnectedRoom != -1) {
            int centerRow1, centerCol1, centerRow2, centerCol2;
            getRoomCenter(rooms[nearestConnectedRoom], centerRow1, centerCol1);
            getRoomCenter(rooms[nearestRoomIndex], centerRow2, centerCol2);
            createHallway(centerRow1, centerCol1, centerRow2, centerCol2, grid);

            // Move the room from unconnected to connected
            connectedRooms.push_back(nearestRoomIndex);
            // Erase the room from the vector of unconnected rooms
            for (size_t i = 0; i < unconnectedRooms.size(); ++i) {
                if (unconnectedRooms[i] == nearestRoomIndex) {
                    unconnectedRooms.erase(unconnectedRooms.begin() + i);
                    break;
                }
            }
        }
    }
}


//display function
void Temple::display()
{

    // Update grid with player position
    clearScreen();
    displayActors();
    displayConstants();

    // Draw the grid
    for (int r = 0; r < n_rows; r++)
    {
        for (int c = 0; c < n_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message for player info
    if (player != nullptr)
    {
        cout << "Level: " << getLevel()
            << ", Hit Points: " << player->getHitPoints()
            << ", Armor: " << player->getArmorPoints()
            << ", Strength: " << player->getStrength()
            << ", Dexterity: " << player->getDexterity()
            << endl;
    }

    cout << endl;
    //output statements
    while (!outputs.empty()) {
        if (outputs.front() == "")
            outputs.erase(outputs.begin());
        else {
            cout << outputs.front() << endl; // Print the first element
            outputs.erase(outputs.begin());  // Erase the first element
        }
    }

}
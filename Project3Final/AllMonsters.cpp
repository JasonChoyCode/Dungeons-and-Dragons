#include "AllMonsters.h"


//snakewomen

//constructor and destructor
Snakewomen::Snakewomen(int row, int col)
    : Monsters("Snakewomen", row, col, randInt(3, 6), 3, 2, 3, 'S', new Sleepfang(0, 0))
{
}

Snakewomen::~Snakewomen()
{
}

//Move the snakewomen when the distance is within 3 
void Snakewomen::move(char grid[n_rows][n_cols], int playerRow, int playerCol)
{
    int currentRow = getRow();
    int currentCol = getCol();

    // Calculate the distances to the player
    int deltaRow = currentRow - playerRow;
    int deltaCol = currentCol - playerCol;

    // Check if the player is within 3 steps horizontally or vertically
    if (abs(deltaRow) + abs(deltaCol) > 3) {
        return;
    }
    // Determine the direction to move

    if (deltaCol > 0 && (grid[getRow()][getCol() - 1] == ' ' || grid[getRow()][getCol() - 1] == '?' || grid[getRow()][getCol() - 1] == '>' || grid[getRow()][getCol() - 1] == ')' || grid[getRow()][getCol() - 1] == '&')) {
        // Move left
        int newCol = getCol() - 1;
        setCol(newCol);
    }
    else if (deltaCol < 0 && (grid[getRow()][getCol() + 1] == ' ' || grid[getRow()][getCol() + 1] == '?' || grid[getRow()][getCol() + 1] == '>' || grid[getRow()][getCol() + 1] == ')' || grid[getRow()][getCol() + 1] == '&')) {
        // Move right
        int newCol = getCol() + 1;
        setCol(newCol);
    }
    else if (deltaRow > 0 && (grid[getRow() - 1][getCol()] == ' ' || grid[getRow() - 1][getCol()] == '?' || grid[getRow() - 1][getCol()] == '>' || grid[getRow() - 1][getCol()] == ')' || grid[getRow() - 1][getCol()] == '&')) {
        // Move up
        int newRow = getRow() - 1;
        setRow(newRow);
    }
    else if (deltaRow < 0 && (grid[getRow() + 1][getCol()] == ' ' || grid[getRow() + 1][getCol()] == '?' || grid[getRow() + 1][getCol()] == '>' || grid[getRow() + 1][getCol()] == ')' || grid[getRow() + 1][getCol()] == '&')) {
        // Move down
        int newRow = getRow() + 1;
        setRow(newRow);
    }
}

//drop a sleepfang with a probability
Objects* Snakewomen::dropWeapon(int r, int c)
{
    if (trueWithProbability(1 / 3.0))
    {
        return new Sleepfang(r, c);
    }
    return nullptr;
}

//Bogeyman
Bogeyman::Bogeyman(int row, int col)
    : Monsters("Bogeyman", row, col, randInt(3, 6), 3, 2, 3, 'B', new ShortSwords(0, 0))
{
}

//move function the same as Snakewomen but with a distance of 5
void Bogeyman::move(char grid[n_rows][n_cols], int playerRow, int playerCol)
{
    int currentRow = getRow();
    int currentCol = getCol();

    // Calculate the distances to the player
    int deltaRow = currentRow - playerRow;
    int deltaCol = currentCol - playerCol;

    // Check if the player is within 3 steps horizontally or vertically
    if (abs(deltaRow) + abs(deltaCol) > 5) {
        return;
    }
    // Determine the direction to move

    if (deltaCol > 0 && (grid[getRow()][getCol() - 1] == ' ' || grid[getRow()][getCol() - 1] == '?' || grid[getRow()][getCol() - 1] == '>' || grid[getRow()][getCol() - 1] == ')' || grid[getRow()][getCol() - 1] == '&')) {
        // Move left
        int newCol = getCol() - 1;
        setCol(newCol);
    }
    else if (deltaCol < 0 && (grid[getRow()][getCol() + 1] == ' ' || grid[getRow()][getCol() + 1] == '?' || grid[getRow()][getCol() + 1] == '>' || grid[getRow()][getCol() + 1] == ')' || grid[getRow()][getCol() + 1] == '&')) {
        // Move right
        int newCol = getCol() + 1;
        setCol(newCol);
    }
    else if (deltaRow > 0 && (grid[getRow() - 1][getCol()] == ' ' || grid[getRow() - 1][getCol()] == '?' || grid[getRow() - 1][getCol()] == '>' || grid[getRow() - 1][getCol()] == ')' || grid[getRow() - 1][getCol()] == '&')) {
        // Move up
        int newRow = getRow() - 1;
        setRow(newRow);
    }
    else if (deltaRow < 0 && (grid[getRow() + 1][getCol()] == ' ' || grid[getRow() + 1][getCol()] == '?' || grid[getRow() + 1][getCol()] == '>' || grid[getRow() + 1][getCol()] == ')' || grid[getRow() + 1][getCol()] == '&')) {
        // Move down
        int newRow = getRow() + 1;
        setRow(newRow);
    }
}

//chance of dropping a magic axe
Objects* Bogeyman::dropWeapon(int r, int c)
{
    if (trueWithProbability(1 / 10.0))
    {
        return new MagicAxes(r, c);
    }
    return nullptr;
}

Bogeyman::~Bogeyman()
{
}

//Dragon

Dragon::Dragon(int row, int col)
    : Monsters("Dragon", row, col, randInt(20, 25), 4, 4, 4, 'D', new LongSwords(0, 0))
{
    maxHitpoints = getHitPoints();
}

//chance to heal dragon
void Dragon::heal()
{
    if (getHitPoints() + 1 <= maxHitpoints)
        addHeal();
}

//dragon does not move
void Dragon::move(char grid[n_rows][n_cols], int row, int col)
{
}

//100% chance to drop a scroll of some type
Objects* Dragon::dropWeapon(int r, int c)
{
    //adapt it to 5 when you make the teleportation scroll
    int chance = randInt(1, 5);
    switch (chance) {
    case 1:
        return new HealthS(r, c);
        break;
    case 2:
        return new ArmorS(r, c);
        break;
    case 3:
        return new StrengthS(r, c);
        break;
    case 4:
        return new DexS(r, c);
        break;
    case 5:
        return new TeleS(r, c);
        break;
    default:
        // This acts like 'continue' in a loop context, moving to the next iteration
        return nullptr;
        break;
    }
}

Dragon::~Dragon()
{
}


//Goblin constructor
Goblin::Goblin(int row, int col, int smellDistance)
//implement weapon and change the row and column
    : Monsters("Goblin", row, col, randInt(15, 20), 1, 3, 1, 'G', new ShortSwords(0, 0))
{
    smellD = smellDistance;
}

//actual function to move the goblin
void Goblin::move(char grid[n_rows][n_cols], int playerRow, int playerCol)
{
    //get the direction of the most optimal movement
    char direct = pathExists(grid, playerRow, playerCol);

    // Move the goblin based on what the optimal move is
    int currentRow = getRow();
    int currentCol = getCol();

    // Determine the direction to move
    if (direct == 'z') {
        // No valid direction found
        return;
    }

    if (direct == 'l' && currentCol > 0 && (grid[currentRow][currentCol - 1] == ' ' || grid[currentRow][currentCol - 1] == '?' || grid[currentRow][currentCol - 1] == '>' || grid[currentRow][currentCol - 1] == ')' || grid[currentRow][currentCol - 1] == '&')) {
        // Move left
        setCol(currentCol - 1);
    }
    else if (direct == 'r' && currentCol < n_cols - 1 && (grid[currentRow][currentCol + 1] == ' ' || grid[currentRow][currentCol + 1] == '?' || grid[currentRow][currentCol + 1] == '>' || grid[currentRow][currentCol + 1] == ')' || grid[currentRow][currentCol + 1] == '&')) {
        // Move right
        setCol(currentCol + 1);
    }
    else if (direct == 'u' && currentRow > 0 && (grid[currentRow - 1][currentCol] == ' ' || grid[currentRow - 1][currentCol] == '?' || grid[currentRow - 1][currentCol] == '>' || grid[currentRow - 1][currentCol] == ')' || grid[currentRow - 1][currentCol] == '&')) {
        // Move up
        setRow(currentRow - 1);
    }
    else if (direct == 'd' && currentRow < n_rows - 1 && (grid[currentRow + 1][currentCol] == ' ' || grid[currentRow + 1][currentCol] == '?' || grid[currentRow + 1][currentCol] == '>' || grid[currentRow + 1][currentCol] == ')' || grid[currentRow + 1][currentCol] == '&')) {
        // Move down
        setRow(currentRow + 1);
    }
}

//See if there even is a path within the smell distance to the player
char Goblin::pathExists(char grid[n_rows][n_cols], int playerRow, int playerCol) {
    int right = pathExistsHelper(grid, playerRow, playerCol, getRow(), getCol() + 1, 1);
    int left = pathExistsHelper(grid, playerRow, playerCol, getRow(), getCol() - 1, 1);
    int up = pathExistsHelper(grid, playerRow, playerCol, getRow() - 1, getCol(), 1);
    int down = pathExistsHelper(grid, playerRow, playerCol, getRow() + 1, getCol(), 1);

    int minSteps = min({ right, left, up, down });
    if (minSteps > smellD) {
        return 'z'; // No valid path found
    }

    if (minSteps == right) return 'r';
    if (minSteps == left) return 'l';
    if (minSteps == up) return 'u';
    return 'd'; // minSteps == down
}

//check the validity of the move
int Goblin::pathExistsHelper(char grid[n_rows][n_cols], int playerRow, int playerCol, int goblinRow, int goblinCol, int moves) {
    if (!isValid(grid, playerRow, playerCol, goblinRow, goblinCol, moves)) {
        return smellD + 1;
    }
    //return the number of moves it takes for the goblin to reach the player
    if (playerRow == goblinRow && playerCol == goblinCol) {
        return moves;
    }

    // Temporarily mark this cell as visited
    char temp = grid[goblinRow][goblinCol];
    grid[goblinRow][goblinCol] = 'v';

    // Explore all four directions
    int right = pathExistsHelper(grid, playerRow, playerCol, goblinRow, goblinCol + 1, moves + 1);
    int left = pathExistsHelper(grid, playerRow, playerCol, goblinRow, goblinCol - 1, moves + 1);
    int up = pathExistsHelper(grid, playerRow, playerCol, goblinRow - 1, goblinCol, moves + 1);
    int down = pathExistsHelper(grid, playerRow, playerCol, goblinRow + 1, goblinCol, moves + 1);

    // Restore the original grid cell value
    grid[goblinRow][goblinCol] = temp;

    // Return the minimum steps required
    return min(min(right, left), min(up, down));
}

//check if you should even run through the recursion
bool Goblin::isValid(char grid[n_rows][n_cols], int playerRow, int playerCol, int goblinRow, int goblinCol, int moves)
{
    if (moves > smellD)
        return false;
    if (grid[goblinRow][goblinCol] != ' ' && grid[goblinRow][goblinCol] != '@')
        return false;
    else
        return true;
}

//function to drop the goblin's weapon possibilities
Objects* Goblin::dropWeapon(int r, int c)
{
    if (trueWithProbability(1 / 3.0))
    {
        int chance = randInt(1, 2);
        switch (chance) {
        case 1:
            return new MagicAxes(r, c);
            break;
        case 2:
            return new Sleepfang(r, c);
            break;
        default:
            return nullptr;
            break;
        }
    }
    return nullptr;
}

Goblin::~Goblin()
{
}

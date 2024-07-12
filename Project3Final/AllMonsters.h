#ifndef AllMonsters_h
#define AllMonsters_h

#include "Monsters.h"
#include "Objects.h"
#include "utilities.h"
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>

//file for all the monsters

//Snakewomen
class Snakewomen : public Monsters
{
public:
	Snakewomen(int row, int col);
	virtual void move(char grid[n_rows][n_cols], int row, int col);
	virtual Objects* dropWeapon(int r, int c);
	virtual ~Snakewomen();
};

//Bogeyman
class Bogeyman : public Monsters
{
public:
	Bogeyman(int row, int col);
	virtual void move(char grid[n_rows][n_cols], int row, int col);
	virtual Objects* dropWeapon(int r, int c);
	virtual ~Bogeyman();
};

//Dragon
class Dragon : public Monsters
{
public:
	Dragon(int row, int col);
	virtual void move(char grid[n_rows][n_cols], int row, int col);
	virtual Objects* dropWeapon(int r, int c);
	void heal();
	virtual ~Dragon();
private:
	int maxHitpoints;
};

//Goblin
class Goblin : public Monsters
{
public:
	Goblin(int row, int col, int smellDistance);
	virtual ~Goblin();
	virtual void move(char grid[n_rows][n_cols], int row, int col);
	char pathExists(char grid[n_rows][n_cols], int playerRow, int playerCol);
	virtual Objects* dropWeapon(int r, int c);
private:
	int smellD;
	//2 helper functions
	bool isValid(char grid[n_rows][n_cols], int playerRow, int playerCol, int goblinRow, int goblinCol, int moves);
	int pathExistsHelper(char grid[n_rows][n_cols], int playerRow, int playerCol, int goblinRow, int goblinCol, int moves);
};
#endif 
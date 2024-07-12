#ifndef Temple_H
#define Temple_H

#include "utilities.h"
#include "Player.h"
#include "Monsters.h"
#include <iostream>
#include "globals.h"
#include "AllMonsters.h"
#include <vector>
#include "Objects.h"
#include <cmath>
using namespace std;


class Temple
{
public:
	//constructor and destructor
	Temple(int l, int smellDistance, int maxHP, int health, int armor, int strength, int dex, Weapons* wep, Inventory* inv);
	virtual ~Temple();

	//displays
	void display();
	void displayActors();
	void displayConstants();

	//getter
	int getLevel() const;
	Player* getPlayer() const;
	void getRoomCenter(const Rooms& room, int& centerRow, int& centerCol) const;
	pair<int, int> getEmptyLocations() const;
	pair<int, int> getStair() const;
	pair<int, int> getIdol() const;
	Objects* getObject(int r, int c);
	vector<string>& getOutputs();

	//setter methods
	void setCoord(int r, int c, char w);
	void setDir(char dir);

	//room related functions
	void addRoom(const Rooms& room);
	void generateRoom();
	bool roomOverlap(const Rooms& room1, const Rooms& room2);
	void createHallways();

	//miscellaneous helpers
	void setGrid();
	void spawnItems();
	void removeObject(int r, int c);
private:
	int level;
	int smellD;
	vector<Rooms> rooms;
	Player* player;
	vector<Monsters*> monsters;
	char grid[n_rows][n_cols];
	char direct;
	int numMonsters;
	vector<pair<int, int>> stair;
	vector<pair<int, int>> idol;
	//print statements
	vector<string> outputs;
	//new spawned objects
	vector<Objects*> spawnedNew;
};

//create a vector of attacks


#endif 

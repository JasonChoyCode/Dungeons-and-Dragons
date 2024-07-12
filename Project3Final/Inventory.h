#include "utilities.h"
#include "Objects.h"
#include <vector>
#include <iostream>
using namespace std;

class Inventory
{
public:
	//constructors
	Inventory();
	Inventory(const Inventory& other);

	//destructor
	virtual ~Inventory();

	//getter and setter
	Objects* getItem(int index) const;
	void setFirstItem(Weapons* w);
	int getNumItems() const;

	//add and remove
	bool addItem(Objects* temp);
	void removeItem(Objects* item);
	void removeSingle(Objects* item);
	//display
	void displayInventory();

	//choose an object
	Weapons* chooseWep(char choice, Weapons* currWep);
	Scrolls* chooseScroll(char choice);

private:
	vector<Objects*> items;
	void copyItems(const Inventory& other);
	int numItems;
};
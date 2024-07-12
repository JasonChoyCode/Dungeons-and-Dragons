#include "Inventory.h"

//constructor
Inventory::Inventory()
	:numItems(0)
{
}

//copy constructor
Inventory::Inventory(const Inventory& other) {
	copyItems(other);
}

//assist the copy constructor
void Inventory::copyItems(const Inventory& other) {
	for (Objects* item : other.items) {
		items.push_back(new Objects(*item)); // Deep copy each item
	}
}

//add the starting weapon to the inventory based off the start
void Inventory::setFirstItem(Weapons* w)
{
	Weapons* firstItem = w;
	addItem(firstItem);
}

//destructor
Inventory::~Inventory()
{
	for (int i = 0; i < items.size(); i++)
	{
		delete items[i];
	}
}

//function to add a new item to the inventory
bool Inventory::addItem(Objects* temp)
{
	if (numItems > 25)
		return false;
	else
	{
		items.push_back(temp);
		numItems++;
	}
	return true;
}

//function to display inventory
void Inventory::displayInventory()
{
	clearScreen();
	cout << "Inventory: " << endl;
	for (int i = 0; i < items.size(); i++)
	{
		Scrolls* temp = dynamic_cast<Scrolls*>(items[i]);
		if (temp != nullptr)
		{
			cout << " " << char('a' + i) << ". " << "A scroll called " << items[i]->getName() << endl;
		}
		else
		{
			cout << " " << char('a' + i) << ". " << items[i]->getName() << endl;
		}
	}
}

//accessor method
int Inventory::getNumItems() const
{
	return numItems;
}

//function to get the select a weapon for the player
Weapons* Inventory::chooseWep(char choice, Weapons* currWep)
{
	displayInventory();

	int valid = choice - 'a';

	if (valid < 0 || valid > items.size() - 1)
		return currWep;

	Weapons* selectedWeapon = dynamic_cast<Weapons*>(items[valid]);
	if (selectedWeapon) {
		return selectedWeapon;
	}
	else {
		return currWep;
	}
}

//function to select a scroll for the player
Scrolls* Inventory::chooseScroll(char choice) {
	displayInventory();

	int valid = choice - 'a';

	if (valid < 0 || valid >= items.size())
		return nullptr;

	Scrolls* selectedScroll = dynamic_cast<Scrolls*>(items[valid]);
	if (selectedScroll) {
		return selectedScroll;
	}
	else {
		return nullptr;
	}
}

//code that is used to remove scrolls after they are used
void Inventory::removeItem(Objects* item) {
	for (int i = 0; i < items.size(); ++i) {
		if (items[i] == item) {
			numItems--;
			delete items[i];
			items.erase(items.begin() + i);
			break;
		}
	}
}

//code to remove a singular duplicate item when the new player is created
void Inventory::removeSingle(Objects* item)
{
	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->getName() == item->getName()) {
			numItems--;
			delete items[i];
			items.erase(items.begin() + i);
			break;
		}
	}
}

//code to retrieve an item at a certain index
Objects* Inventory::getItem(int index) const {
	if (index >= 0 && index < items.size()) {
		return items[index];
	}
	return nullptr;
}



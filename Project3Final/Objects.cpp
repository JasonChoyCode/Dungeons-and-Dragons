#include "Objects.h"

//General Object constructor
Objects::Objects(string n, int r, int c, char s)
	: name(n), row(r), col(c), symbol(s)
{
}

//accessors for objects
string Objects::getName() const
{
	return name;
}

int Objects::getRow() const
{
	return row;
}
int Objects::getCol() const
{
	return col;
}

char Objects::getSymbol() const
{
	return symbol;
}

//creation of weapons
Weapons::Weapons(string n, int r, int c, int dex, int dmg, string descrip)
	: Objects(n, r, c, ')'), dexBonus(dex), damage(dmg), description(descrip)
{
}

//weapons accessors
int Weapons::getDex() const
{
	return dexBonus;
}

int Weapons::getDmg() const
{
	return damage;
}

string Weapons::getDescript() const
{
	return description;
}

//creation of all weapons
Maces::Maces(int r, int c)
	:Weapons("mace", r, c, 0, 2, "swings mace at")
{
}

LongSwords::LongSwords(int r, int c)
	: Weapons("long sword", r, c, 2, 4, "swings long sword at")
{
}


ShortSwords::ShortSwords(int r, int c)
	: Weapons("short sword", r, c, 0, 2, "slashes short sword at")
{
}

MagicAxes::MagicAxes(int r, int c)
	: Weapons("magic axe", r, c, 5, 5, "chops magic axe at")
{
}

Sleepfang::Sleepfang(int r, int c)
	: Weapons("magic fangs", r, c, 3, 2, "strikes magic fangs at")
{
}

//scroll constructor
Scrolls::Scrolls(int add, int r, int c, string n, string d)
	: Objects(n, r, c, '?'), iAttribute(add), description(d)
{
}

//accessor for scrolls
int Scrolls::getAtt() const
{
	return iAttribute;
}

string Scrolls::getDescrip() const
{
	return description;
}

//creation of scrolls
ArmorS::ArmorS(int r, int c)
	: Scrolls(randInt(1, 3), r, c, "scroll of enhance armor", "Your armor glows blue")
{
}
StrengthS::StrengthS(int r, int c)
	: Scrolls(randInt(1, 3), r, c, "scroll of strength", "Your muscles bulge.")
{
}

HealthS::HealthS(int r, int c)
	: Scrolls(randInt(3, 8), r, c, "scroll of enhance health", "You feel your heart beating stronger.")
{

}

DexS::DexS(int r, int c)
	:Scrolls(1, r, c, "scroll of enhance dexterity", "You feel like less of a klutz.")
{
}

TeleS::TeleS(int r, int c)
	:Scrolls(0, r, c, "scroll of teleportation", "You feel your body wrenched in space and time.")
{
}

//creation of idol
Idol::Idol(int r, int c)
	:Objects("golden idol", r, c, '&')
{
}

Idol::~Idol()
{
}



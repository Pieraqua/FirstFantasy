#include "Weapon.h"

Weapon::Weapon()
{
	this->str = 0;
	this->dex = 0;
	this->armor = 0;
	this->damage_dice = 4;
	this->name = "Fists";
}

Weapon::Weapon(int str, int dex, int armor, int damage_dice, string name)
{
	this->str = str;
	this->dex = dex;
	this->armor = armor;
	this->damage_dice = damage_dice;
	this->name = name;
}

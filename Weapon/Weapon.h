#pragma once
#include <string>
using namespace std;

class Weapon
{
public:
	int get_damage_dice() { return this->damage_dice; }
	int get_str() { return this->str; }
	int get_dex() { return this->dex; }
	int get_armor() { return this->armor; }

	Weapon();
	Weapon(int str, int dex, int armor, int damage_dice, string name);
protected:
	// Dano causado por ataque
	int str;
	// Modificador para acertar
	int dex;
	// Modificador para desviar de ataques
	int armor;
	// ditado pela arma
	int damage_dice;

	string name;

};


#pragma once
#include "Weapon/Weapon.h"

class Character
{
public:
	static const int level_table[];

	static int tests_character();

	// Ataca o personagem. Retorna o dano causado.
	int hit(int attack_roll, int damage_roll);
	// Cura o personagem. Retorna o dano causado.
	int heal(int heal_amount);
	// Revive o personagem com 1 de vida.
	bool ressurect();
	// Aumenta o nivel do personagem
	void level_up();
	// Faz o personagem atacar.
	int attack(Character* target);
	
	int get_damage_dice() { return this->weapon.get_damage_dice(); }
	int get_max_hp() { return this->max_hp; }
	int get_current_hp() { return this->current_hp; }
	int get_str() { return this->str + this->weapon.get_str(); }
	int get_con() { return this->con; }
	int get_dex() { return this->dex + this->weapon.get_dex(); }
	int get_armor() { return this->armor + this->weapon.get_armor(); }
	int get_alive() { return this->alive; }
	int get_level() { return this->level; }
	int get_current_xp() { return this->current_xp; }
	int get_xp_val() { return this->xp_val; }
	string get_name() { return this->name; }

	void set_weapon(Weapon weapon) { this->weapon = weapon; }
	void set_name(string name) { this->name = name; }

	Character();
	Character(int level, int str, int con, int dex, int armor, int xp_val);
	Character(int level, int str, int con, int dex, int armor, int xp_val, Weapon weapon);
private:

protected:
	// Vida maxima
	int max_hp;
	// Vida atual
	int current_hp;
	// Dano causado por ataque
	int str;
	// Modificador de vida máxima
	int con;
	// Modificador para acertar
	int dex;
	// Modificador para desviar de ataques
	int armor;
	// Estado atual do personagem
	bool alive;
	// Level atual do personagem
	int level;
	// XP atual do personagem
	int current_xp;
	// Valor de XP ao derrotar o personagem
	int xp_val;
	// nome
	string name;

	// ditado pela arma
	Weapon weapon;

	// Mata o personagem, sem o desconstruir da memória.
	void die();
};


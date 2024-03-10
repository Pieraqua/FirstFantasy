#pragma once
#include "Character/Character.h"

#include <vector>
#include <string>
using namespace std;

class Combat
{
	vector<Character*> allies;
	vector<Character*> enemies;

	int combat_in_progress;
	bool handle_action(vector<string>, Character*);

public:
	Combat(vector<Character*> allies, vector<Character*> enemies);
	int take_turn();

	// Retorna 0 se combate ainda não acabou, 1 se os aliados ganharam e 2 se os inimigos ganharam.
	int combat_finished() { return combat_in_progress; }


	void print_participants();
};


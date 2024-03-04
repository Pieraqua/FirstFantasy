#pragma once
#include "Character/Character.h"

#include <vector>
#include <string>
using namespace std;

class Combat
{
	vector<Character*> allies;
	vector<Character*> enemies;

	bool combat_in_progress;
	bool handle_action(vector<string>, Character*);

public:
	Combat(vector<Character*> allies, vector<Character*> enemies);
	bool take_turn();
	bool combat_finished() { return !combat_in_progress; }

	void print_participants();
};


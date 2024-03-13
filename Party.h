#pragma once
#include <vector>
using namespace std;

#include"Character/Character.h"
class Party
{
private:
	vector<Character> party_members;
public:
	void add_character(Character);
	void remove_character(Character*);
	vector<Character*> get_members();

	static int test();
};


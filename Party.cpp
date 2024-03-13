#include "Party.h"

#include "FrostWolfEngine/SystemOutput.h"

void Party::add_character(Character car)
{
	party_members.push_back(car);
}

void Party::remove_character(Character* car)
{
	for (vector<Character>::iterator it = party_members.begin(); it < party_members.end(); it++)
	{
		if (&(*it) == car)
			party_members.erase(it);
	}
}

vector<Character*> Party::get_members()
{
	vector<Character*> vec;

	for (vector<Character>::iterator it = party_members.begin(); it < party_members.end(); it++)
	{
		vec.push_back(&(*it));
	}

	return vec;
}

int Party::test()
{
	Party test_party;

	Character testcars[10];

	vector<Character*> members;

	int fail = 1;

	for (int i = 0; i < 10; i++)
	{
		testcars[i] = Character::random_character();

		// Adicionar os personagens e testar se eles existem na party
		test_party.add_character(testcars[i]);
		members = test_party.get_members();
		fail = 1;
		for (vector<Character*>::iterator it = members.begin(); it < members.end(); it++)
		{
			if (*(*it) == testcars[i])
			{
				fail = 0;
				break;
			}
		}

		if (fail) {
			SystemOutput::getInstance()->printToConsole("Party test fail - add", SystemOutput::outputLevel::ERROR);
			return 1;
		}

	}

	// Remover os personagens e verificar que eles não estão mais na party
	for (int i = 0; i < 10; i++)
	{
		// Remover os personagens e testar se eles existem na party
		test_party.remove_character(*(members.begin()));
		members = test_party.get_members();
		fail = 0;
		for (vector<Character*>::iterator it = members.begin(); it < members.end(); it++)
		{
			if (*(*it) == testcars[i])
			{
				SystemOutput::getInstance()->printToConsole("Party test fail - remove", SystemOutput::outputLevel::ERROR);
				fail = 1;
				break;
			}
		}

		if (fail) return 1;

	}

	if (test_party.get_members().size()) {
		SystemOutput::getInstance()->printToConsole("Party test fail - party not empty", SystemOutput::outputLevel::ERROR);
		return 1;
	}
	// sucesso
	return 0;
}

#include "Combat.h"
#include "SystemOutput.h"
#include "SystemInput.h"
#include "Utils.h"

bool Combat::handle_action(vector<string> user_action, Character* actor)
{
    if (user_action.size() < 2) return false;

    if (Utils::to_lower(user_action.at(0)) == "attack")
    {
        for (vector<Character*>::iterator it = this->enemies.begin(); it < this->enemies.end(); it++)
        {
            if (Utils::to_lower(user_action.at(1)) == (*it)->get_name())
            {
                actor->attack((*it));
                return true;
            }
        }
    }
    return false;
}

Combat::Combat(vector<Character*> allies, vector<Character*> enemies)
{
    this->allies = allies;
    this->enemies = enemies;
}

bool Combat::take_turn()
{
    SystemOutput* output = SystemOutput::getInstance();
    SystemInput* input = SystemInput::getInstance();
    vector<string> user_action;
    vector<Character*>::iterator it;
    for (it = this->allies.begin(); it < this->allies.end(); it++)
    {
        output->printToConsole("What will " + (*it)->get_name() + " do?\n\x1b[?12h\x1b[1mAttack\x1b[0m", SystemOutput::outputLevel::INFO);
        
        while (!handle_action(input->getUserInput(), (*it)))
        {
            output->printToConsole("Invalid command.\nWhat will " + (*it)->get_name() + " do?\n\x1b[?12h\x1b[1mAttack\x1b[0m", SystemOutput::outputLevel::INFO);
        }

    }

    for (it = this->enemies.begin(); it < this->enemies.end(); it++)
    {
        if ((*it)->get_alive())
            return false;
    }
    return true;
}

void Combat::print_participants()
{
    string message = "Allies: \n";
    vector<Character*>::iterator ptr;
    
    
    for (ptr = allies.begin(); ptr < allies.end(); ptr++)
        message += (*ptr)->get_name() + "\n";

    message += "Enemies:\n";
    for (ptr = enemies.begin(); ptr < enemies.end(); ptr++)
        message += (*ptr)->get_name() + "\n";

    SystemOutput::getInstance()->printToConsole(message, SystemOutput::outputLevel::INFO);
}

#include "Combat.h"
#include "FrostWolfEngine/SystemOutput.h"
#include "FrostWolfEngine/SystemInput.h"
#include "FrostWolfEngine/Utils.h"

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

int Combat::take_turn()
{
    SystemOutput* output = SystemOutput::getInstance();
    SystemInput* input = SystemInput::getInstance();
    vector<string> user_action;
    vector<Character*>::iterator it;

    // Retorna 2 se os inimigos ganharam
    int end_combat_allies = 2;
    // Retorna 1 se os aliados ganharam
    int end_combat_enemies = 1;

    for (it = this->allies.begin(); it < this->allies.end(); it++)
    {
        if ((*it)->get_alive()) {
            output->printToConsole("What will " + (*it)->get_name() + " do?\n\x1b[?12h\x1b[1mAttack\x1b[0m", SystemOutput::outputLevel::INFO);

            while (!handle_action(input->getUserInput(), (*it)))
            {
                output->printToConsole("Invalid command.\nWhat will " + (*it)->get_name() + " do?\n\x1b[?12h\x1b[1mAttack\x1b[0m", SystemOutput::outputLevel::INFO);
            }

            end_combat_allies = 0;
        }

    }

    for (it = this->enemies.begin(); it < this->enemies.end(); it++)
    {
        if ((*it)->get_alive())
        {
            if (!end_combat_allies) {
                (*it)->attack(this->allies.at(Utils::rolldx(this->allies.size())));
                output->printToConsole("Press enter to continue.", SystemOutput::outputLevel::INFO);
                input->getUserInput();
            }
            end_combat_enemies = 0;
        }
    }
    

    // Retorna 3 se ambos tiverem sido derrotados (empate)
    this->combat_in_progress = (end_combat_allies | end_combat_enemies);

    switch (this->combat_in_progress) 
    {
    case 1:
        output->printToConsole("The enemies have been defeated!", SystemOutput::outputLevel::INFO);
        break;
    case 2:
        output->printToConsole("The allies have been defeated!", SystemOutput::outputLevel::INFO);
        break;
    case 3:
        output->printToConsole("Both parties have been defeated!", SystemOutput::outputLevel::INFO);
        break;
    default:
        break;
    }

    return this->combat_in_progress;
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

#include "Character.h"
#include <assert.h>
#include "Utils.h"
#include "SystemOutput.h"

#define LEVEL_MAX 7
const int Character::level_table[] = { 0, 300, 900, 2400, 4800, 9600, 19000, 999999 };

int Character::hit(int attack_roll, int damage_roll)
{
    int damage = damage_roll;

    if (!this->alive) {
        return 0;
    }
    if (attack_roll < this->armor)
    {
        damage = 0;
    }

    this->current_hp -= damage;
    if (this->current_hp <= 0)
    {
        this->die();
        //SystemOutput::getInstance()->printToConsole(this->name + " is killed!", SystemOutput::outputLevel::INFO);
    }

    return damage;
}

int Character::tests_character()
{
    Character char_1 = Character();
    Character char_2 = Character(1, 2, 3, 4, 5, 200);

    assert(char_1.get_current_hp() == char_1.get_max_hp());
    assert(char_1.get_current_hp() == char_1.get_con() * char_1.get_level() + 10);

    assert(char_2.get_current_hp() == char_2.get_max_hp());
    assert(char_2.get_current_hp() == char_2.get_con() * char_2.get_level() + 10);

    char_2.hit(char_2.get_armor() + 1, 2);

    assert(char_2.get_current_hp() == char_2.get_max_hp() - 2);

    int dmg = char_2.attack(&char_1);

    assert(char_1.get_current_hp() == char_1.get_max_hp() - dmg);

    char_1.hit(char_1.get_armor() + 1, char_1.get_current_hp());

    assert(!char_1.get_alive());

    return 0;
}

int Character::heal(int heal_amount)
{
    int healing = 0;
    if (this->alive)
        healing = heal_amount + current_hp > max_hp ? max_hp - current_hp : heal_amount;
    return healing;
}

bool Character::ressurect()
{
    if (this->alive)
        return false;

    this->alive = true;
    this->current_hp = 1;
    return true;
}

void Character::level_up()
{
    this->level += 1;
    this->max_hp = con*level;
}

int Character::attack(Character* target)
{
    int attack = Utils::rolldx(20) + this->get_dex();
    int damage = Utils::rolldx(this->get_damage_dice()) + this->get_str();
    SystemOutput::getInstance()->printToConsole(this->name + " attacked " + target->name + ", rolled a " + to_string(attack) + " to hit for " + to_string(damage) + " damage.", SystemOutput::outputLevel::INFO);
    int damage_dealt = target->hit(attack, damage);

    if(damage_dealt > 0 && target->get_alive())
        SystemOutput::getInstance()->printToConsole("Dealt " + to_string(damage_dealt) + " damage.", SystemOutput::outputLevel::INFO);
    else if(damage_dealt > 0 && !target->get_alive())
        SystemOutput::getInstance()->printToConsole("Dealt " + to_string(damage_dealt) + " damage. " + target->get_name() + " was killed!", SystemOutput::outputLevel::INFO);
    else if(damage_dealt == 0 && target->get_alive())
        SystemOutput::getInstance()->printToConsole("Dealt no damage.", SystemOutput::outputLevel::INFO);
    else if (damage_dealt == 0 && !target->get_alive())
        SystemOutput::getInstance()->printToConsole("Target is already dead!", SystemOutput::outputLevel::INFO);


    return damage_dealt;
}

Character::Character()
{
    this->alive = true;
    this->level = 0;
    this->str = 1;
    this->con = 1;
    this->dex = 1;
    this->armor = 1;

    this->max_hp = 10 + level*con;
    this->current_hp = max_hp;

    this->current_xp = Character::level_table[level > LEVEL_MAX ? LEVEL_MAX : level];
    this->xp_val = 100;

    this->weapon = Weapon();
    this->name = "bob";
}

Character::Character(int level, int str, int con, int dex, int armor, int xp_val) : Character()
{
    this->alive = true;
    this->level = level;
    this->str = str;
    this->con = con;
    this->dex = dex;
    this->armor = armor;

    this->max_hp = 10 + level * con;
    this->current_hp = max_hp;

    this->current_xp = Character::level_table[level > LEVEL_MAX ? LEVEL_MAX : level];
    this->xp_val = xp_val;

    this->weapon = Weapon();
}


Character::Character(int level, int str, int con, int dex, int armor, int xp_val, Weapon weapon) : Character(level, str, con, dex, armor, xp_val)
{
    this->weapon = weapon;
}

void Character::die()
{
    this->alive = false;
    this->current_hp = 0;
}

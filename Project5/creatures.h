#ifndef __CREATURES_H__
#define __CREATURES_H__

// find here the manin data structure for the game
// feel free to expand it to suit your improvements

enum classes {warrior, wizard, druid, priest, paladin};

struct warrior_stats{
	int hp = 350;
	int attack_min = 15;
	int attack_max = 60;
	int armor = 16;
};

struct wizard_stats {
	int hp = 280;
	int attack_min = 20;
	int attack_max = 80;
	int armor = 14;
};

struct druid_stats {
	int hp = 320;
	int attack_min = 10;
	int attack_max = 65;
	int armor = 14;
};

struct priest_stats {
	int hp = 280;
	int attack_min = 12;
	int attack_max = 55;
	int armor = 14;
};

struct paladin_stats {
	int hp = 350;
	int attack_min = 10;
	int attack_max = 40;
	int armor = 16;
};

struct combat_data
{
	int hp;
	int attack_min;
	int attack_max;
	int armor;
	int max_hp;
	int level1_hp;
};

struct hero_data
{
	char *name;
	struct combat_data combat;
	classes your_class;
	int level;
	int coins;
	int xp;

};

struct monster_data
{
	struct combat_data combat;
	int coins;
	int xp;
	int dead;
};

void initzialize_goblin(monster_data *goblin, int hero_attack, int hero_level);
void hit_hero(hero_data *hero, monster_data *goblin);
void my_strcpy(char *dest, char *source);
void increase_lvl(hero_data *hero);
void use_special_ability(hero_data *hero, monster_data *goblins, int target_goblin, int goblins_coming);

#endif // __CREATURES_H__
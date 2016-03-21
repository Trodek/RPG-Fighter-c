#include"creatures.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Use this file to add all utility functions, like calculating combat results

void initzialize_goblin(monster_data *goblin, int hero_attack, int hero_level){
	
	int goblin_hp;
	while ((goblin_hp = rand() % (200*hero_level)) < 70);
	goblin->combat.hp = goblin_hp; 
	goblin->combat.attack_max = 15*hero_level*3/2;
	goblin->combat.attack_min = 5*hero_level*3/2;
	goblin->combat.armor = rand() % ((hero_attack / 3) * 2);
	goblin->coins = rand() % 50;
	goblin->xp = 35;
	goblin->dead = 0;
}

void hit_hero(hero_data *hero, monster_data *goblin){
	int goblin_hit;
	while ((goblin_hit = rand() % goblin->combat.attack_max) < goblin->combat.attack_min);
	goblin_hit -= hero->combat.armor;
	if (goblin_hit>0) hero->combat.hp -= goblin_hit;
}

void increase_lvl(hero_data *hero){
	if (hero->xp >= 150 * hero->level){
		hero->xp -= 150 * hero->level;
		hero->level++;
		printf("\nCongratulations %s! you reach level %d.", hero->name, hero->level);
		hero->combat.max_hp = hero->combat.level1_hp*hero->level;
		hero->combat.hp = hero->combat.max_hp;
		switch (hero->your_class){
		case warrior: hero->combat.attack_max *= 1.8f;
			hero->combat.attack_min *= 1.8f;
			hero->combat.armor *= 1.6f;
			break;
		case wizard: hero->combat.attack_max *= 2;
			hero->combat.attack_min *= 2;
			hero->combat.armor *= 1.3f;
			break;
		case druid: hero->combat.attack_max *= 1.6f;
			hero->combat.attack_min *= 1.6f;
			hero->combat.armor *= 1.5f;
			break;
		case priest: hero->combat.attack_max *= 2.5f;
			hero->combat.attack_min *= 1.2f;
			hero->combat.armor *= 1.3f;
			break;
		case paladin: hero->combat.attack_max *= 1.3f;
			hero->combat.attack_min *= 1.3f;
			break;
		};
		printf("\nYour new stats are: HP: %d, minimum attack: %d, maximum attack: %d, armor: %d.", hero->combat.hp, hero->combat.attack_min, hero->combat.attack_max, hero->combat.armor);
	}

}

void use_special_ability(hero_data *hero, monster_data *goblins, int target_goblin, int goblins_coming){
	switch (hero->your_class){
	case warrior: for (int goblin_num = 0; goblin_num < goblins_coming; goblin_num++) {
			(goblins + goblin_num)->combat.hp -= hero->combat.attack_max;
		}
		printf("\nYou hit all goblins for your maximum damage (%d).", hero->combat.attack_max);
		break;
	case wizard: (goblins + target_goblin)->combat.hp = 0;
		printf("\nYour fireball hits goblin %d.", target_goblin + 1);
		break;
	case druid: int hero_hit;
		while ((hero_hit = (rand() % hero->combat.attack_max)) < hero->combat.attack_min);
		(goblins + target_goblin)->combat.hp -= hero_hit;
		hero->combat.hp += hero_hit;
		if (hero->combat.hp>hero->combat.max_hp) hero->combat.hp = hero->combat.max_hp;
		printf("\nYou hit goblin %d for %d and heal you the same amount.", target_goblin + 1, hero_hit);
		break;
	case priest: hero->combat.hp += 60*hero->level;
		if (hero->combat.hp>hero->combat.max_hp) hero->combat.hp = hero->combat.max_hp;
		printf("\nYou heal yourself for %d.", 60 * hero->level);
		break;
	case paladin: hero->combat.armor += 3;
		hero->combat.hp += 25*hero->level;
		printf("\nYou increase your armor for 3 and your HP for %d.",25*hero->level);
		break;
	}


}

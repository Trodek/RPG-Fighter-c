#include <stdio.h>
#include "creatures.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initialize(hero_data *hero, int MAX_NAME_LENGHT){
	hero->name = (char *)malloc(20);
	printf("\nWhats your name adventure? ");
	scanf_s("%s", hero->name, MAX_NAME_LENGHT);
	printf("What type of hero are you? Are you a Warrior (0)? or maybe a Wizzard (1)?\nLooking more carefully you look more like a Druid (2).\nNO, wait, you are a Priest (3)\nBut you also got Paladin (4) things...");
	printf("\nChoose your class, I'm bad analyzing people: ");
	int num;
	scanf_s("%d", &num);
	switch (num){
		case 0: {hero->your_class = warrior;
				warrior_stats warr;
				hero->combat.hp = warr.hp;
				hero->combat.max_hp = warr.hp;
				hero->combat.level1_hp = warr.hp;
				hero->combat.attack_max = warr.attack_max;
				hero->combat.attack_min = warr.attack_min;
				hero->combat.armor = warr.armor;
				break; }
		case 1: {hero->your_class = wizard;
				wizard_stats wiz;
				hero->combat.hp = wiz.hp;
				hero->combat.level1_hp = wiz.hp;
				hero->combat.max_hp = wiz.hp;
				hero->combat.attack_max = wiz.attack_max;
				hero->combat.attack_min = wiz.attack_min;
				hero->combat.armor = wiz.armor;
				break; }
		case 2: {hero->your_class = druid;
				druid_stats drui;
				hero->combat.hp = drui.hp;
				hero->combat.level1_hp = drui.hp;
				hero->combat.max_hp = drui.hp;
				hero->combat.attack_max = drui.attack_max;
				hero->combat.attack_min = drui.attack_min;
				hero->combat.armor = drui.armor;
				break; }
		case 3: {hero->your_class = priest;
				priest_stats pri;
				hero->combat.hp = pri.hp;
				hero->combat.level1_hp = pri.hp;
				hero->combat.max_hp = pri.hp;
				hero->combat.attack_max = pri.attack_max;
				hero->combat.attack_min = pri.attack_min;
				hero->combat.armor = pri.armor;
				break; }
		case 4: {hero->your_class = paladin;
				paladin_stats pal;
				hero->combat.hp = pal.hp;
				hero->combat.level1_hp = pal.hp;
				hero->combat.max_hp = pal.hp;
				hero->combat.attack_max = pal.attack_max;
				hero->combat.attack_min = pal.attack_min;
				hero->combat.armor = pal.armor;
				break; }
	};
	hero->level = 1;
	hero->coins = 0;
	hero->xp = 0;
	printf("\nSo, your stats are: HP: %d, minimum attack: %d, maximum attack: %d, armor: %d.", hero->combat.hp,hero->combat.attack_min, hero->combat.attack_max, hero->combat.armor);
	printf("\nLet's see how many goblins you can kill.");

}

void fights_loop(hero_data *hero){

	srand(time(NULL));
	int goblins_coming;
	int target_goblin;
	int fight_end;
	int fight;
	int goblins_killed = 0;
	for (fight = 1; hero->combat.hp > 0;fight++){
		printf("\n\nAre you ready for your %d fight? Your enemys are coming...", fight);
		while((goblins_coming = rand() % 6)<1);
		monster_data *goblins = (monster_data *)malloc(goblins_coming*sizeof(monster_data));
		for (int goblin_num = 0; goblin_num < goblins_coming; goblin_num++)
			initzialize_goblin((goblins + goblin_num),hero->combat.attack_max, hero->level);
		printf("\n%s this time you are facing %d goblin", hero->name,goblins_coming);
		if (goblins_coming>1) printf("s");
		fight_end = 0;
		int goblins_kill_this_fight = 0;
		int xp_befor_fight = hero->xp;
		int coins_befor_fight = hero->coins;
		int cd = 0;
		while (!fight_end){
			getchar();
			target_goblin = rand() % goblins_coming;
			while ((goblins + target_goblin)->combat.hp<0){
				target_goblin = rand() % goblins_coming;
			}
			if (!cd && (rand()%101<50)){
				use_special_ability(hero,goblins,target_goblin, goblins_coming);
				cd = 1;
			}
			else{
				int hero_hit;
				while ((hero_hit = (rand() % hero->combat.attack_max)) < hero->combat.attack_min);
				(goblins + target_goblin)->combat.hp -= hero_hit;
				printf("\nNice job %s, you hit goblin %d for %d damage.", hero->name, target_goblin + 1, hero_hit);
			}
			printf("Your current HP is %d.", hero->combat.hp);
			for (int goblin_num = 0; goblin_num < goblins_coming; goblin_num++){
				if ((goblins + goblin_num)->combat.hp <= 0&& !(goblins+goblin_num)->dead) printf("\nYou kill goblin %d.", goblin_num + 1);
			}
			for (int goblin_num = 0; goblin_num < goblins_coming; goblin_num++){
				if ((goblins + goblin_num)->combat.hp <= 0 && !(goblins + goblin_num)->dead){
					goblins_killed++;
					goblins_kill_this_fight++;
					(goblins + goblin_num)->dead = 1;
					hero->xp += (goblins + goblin_num)->xp;
					hero->coins += (goblins + goblin_num)->coins;
				}
			}
			for (int goblin_num = 0;goblin_num<goblins_coming;goblin_num++){
				int prehit_hero_hp = hero->combat.hp;
				if ((goblins + goblin_num)->combat.hp>0) {
					hit_hero(hero, goblins + goblin_num);
					printf("\nThe goblin %d hits %s for %d damage.", goblin_num + 1, hero->name, prehit_hero_hp - hero->combat.hp);
				}
			}
			if (hero->combat.hp <= 0) fight_end = 1;
			if (goblins_kill_this_fight == goblins_coming){
				fight_end = 1;
				printf("\n\nNice job %s you defeat all the goblins this time.", hero->name);
				printf("\nThis fight you win %d XP and %d coins. Your current HP is %d.", hero->xp - xp_befor_fight, hero->coins - coins_befor_fight, hero->combat.hp);
			}
			
		}
		free(goblins);
		increase_lvl(hero);
		cd = 1;
	}
	printf("\n\nThe hero %s will be remembered for facing %d fights and defeating %d goblins.\n\n\t\t\tREAST IN PEACE %s", hero->name, fight-1, goblins_killed, hero->name);
}
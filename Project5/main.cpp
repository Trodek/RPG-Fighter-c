#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "creatures.h"
#include "other_functions.h"

int MAX_NAME_LENGHT = 20;



int main()
{
	// Use this file to add the main flow of code. 
	// Keep it clean using creatures.cpp to create utility functions
	// Remember to free all allocated memory with malloc
	hero_data *hero;
	hero = (hero_data *) malloc(sizeof(hero_data));
	initialize(hero, MAX_NAME_LENGHT);
	fights_loop(hero);
	free(hero->name);
	free(hero);
	getchar();
	getchar();
	return 0;
}
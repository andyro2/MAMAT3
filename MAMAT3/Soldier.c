#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Soldier.h"


#define MAX_ID_LENGTH 4
#define MAX_POS_LENGTH 6

struct Soldier_ {
	char pos[MAX_POS_LENGTH];
	char ID[MAX_ID_LENGTH];
};

soldier* Soldier_Create(char* ID, char* pos)
{
	soldier* s;
	if (ID == NULL || pos == NULL)
		return NULL;
	s = (soldier*)malloc(sizeof(soldier));
	if (s == NULL) {
		free(s);
		return NULL;
	}
	strcpy(s->ID, ID);
	strcpy(s->pos, pos);
	return s;
}

void Soldier_Delete(soldier* sol)
{
	if (sol == NULL)
		return;
	free(sol);
	return;
}

soldier* Soldier_Duplicate(soldier* exist_soldier)
{
	if (exist_soldier == NULL)
		return NULL;

	soldier* new_soldier = Soldier_Create(exist_soldier->pos, exist_soldier->ID);
	if (new_soldier == NULL)
		return NULL;

	return new_soldier;
}

void Soldier_Print(soldier* sol) {
	if (sol == NULL) {
		return;
	}
	printf("%s , %s\n", sol->ID, sol->pos);
	return;
}
#include "Soldier.h"
#include "defs.h"


struct Soldier_ {
	char pos[MAX_POS_LENGTH];
	char ID[MAX_ID_LENGTH];
};

soldier* Soldier_Create(char* ID, char* pos)
{
	soldier* s;
	if (!Soldier_Valid_ID_Pos(ID, pos))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	s = (soldier*)malloc(sizeof(soldier));
	if (s == NULL) {
		free(s);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(s->ID, ID);
	strcpy(s->pos, pos);
	return s;
}

void Soldier_Delete(soldier* sol)
{
	if (sol == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	free(sol);
	return;
}

soldier* Soldier_Duplicate(soldier* exist_soldier)
{
	if (exist_soldier == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}


	soldier* new_soldier = Soldier_Create(exist_soldier->ID, exist_soldier->pos);
	if (new_soldier == NULL) {
		return NULL;
	}
	return new_soldier;
}

void Soldier_Print(soldier* sol) {
	if (sol == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , %s\n", sol->ID, sol->pos);
	return;
}

bool Soldier_Valid_ID_Pos(char* ID, char* pos)
{
	if (pos == NULL || ID == NULL)
		return false;
	if (ID[0] != 'S'|| strlen(ID + 1) > LENGTH_OF_NUMS)
		return false;
	if (!strcmp(pos, "DRIVER") || !strcmp(pos, "MED") || !strcmp(pos, "ENG") || !strcmp(pos, "INT") || !strcmp(pos, "GUNNER"))
		return true;
	return false;
}

char* Soldier_Get_ID(soldier* s)
{
	return s->ID;
}
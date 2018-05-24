#include "Soldier.h"
#include "List.h"


struct Soldier_ {
	char pos[MAX_POS_LENGTH];
	char ID[MAX_ID_LENGTH];
};

soldier* Soldier_Create(char* ID, char* pos)
{
	soldier* s;
	if (ID == NULL || pos == NULL) {
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

	soldier* new_soldier = Soldier_Create(exist_soldier->pos, exist_soldier->ID);
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

/* User's Function*/

bool Soldier_Compare_Func(PKey ID1, PKey ID2)
{
	return !strcmp((char*)ID1, (char*)ID2);
}
void Soldier_Destroy_Func(PElem pElem)
{
	soldier* s = (soldier*)pElem;
	Soldier_Delete(s);
	return;
}
PElem Soldier_Clone_Func(PElem pElem)
{
	soldier* s = (soldier*)pElem;
	s = Soldier_Duplicate(s);
	return s;
}
void Soldier_Print_Func(PElem pElem)
{
	soldier* s = (soldier*)pElem;
	Soldier_Print(s);
	return;
}
PKey Soldier_Get_Key_Function(PElem pElem)
{
	soldier* s = (soldier*)pElem;
	return s->ID;
}


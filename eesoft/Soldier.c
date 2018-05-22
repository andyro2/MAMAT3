#include "Soldier.h"

struct Soldier {
	char Pos[MAX_ID_LENGTH];
	char ID[MAX_ID_LENGTH];
};


PSoldier Soldier_Duplicate(PSoldier Soldier) {
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PSoldier New_Soldier = Soldier_Create(Soldier->Pos, Soldier->ID);
	if (New_Soldier == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	return New_Soldier;
}


void Soldier_Print(PSoldier Soldier) {
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return ;
	}
	printf("%s , %s\n", Soldier->ID, Soldier->Pos);
}



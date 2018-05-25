#include "WarZone.h"
#include "Squad.h"


struct War_Zone_ {
	PList squads;
	int alertness;
	char ID[MAX_ID_LENGTH];
};

PWZ Squad_Create(char* ID, CLONE_FUNC clone_func_sold, DESTROY_FUNC destroy_func_sold, COMPARE_KEYS_FUNC comp_keys_func_sold, PRINT_FUNC print_func_sold, GET_KEY_FUNC get_key_func_sold)
{
	PWZ w;
	if (!War_Zone_Valid_ID(ID))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if ((clone_func_sold == NULL) || (destroy_func_sold == NULL) || (comp_keys_func_sold == NULL) || (print_func_sold == NULL) || get_key_func_sold == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	w = (PWZ)malloc(sizeof(WZ));
	if (w == NULL)
	{
		free(w);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	w->squads = List_Create(clone_func_sold, destroy_func_sold, comp_keys_func_sold, print_func_sold, get_key_func_sold);
	w->alertness = 0;
	strcpy(w->ID, ID);
	return w;
}


void WarZone_Delete(PWZ WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	ListDestroy(WarZone->squads);
	free(WarZone);
}

void WarZone_Print(PWZ WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("WarZone: %s , Alert State: %d\n\n", WarZone->ID, WarZone->alertness);
	ListPrint(WarZone->squads);
}

PWZ WarZone_Duplicate(PWZ war_zone) {

}


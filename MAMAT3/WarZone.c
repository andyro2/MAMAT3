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

PWZ WarZone_Duplicate(PWZ war_zone) 
{
	if (war_zone == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PList squad = war_zone->squads;
	PWZ new_war_zone = War_Zone_Create(war_zone->ID,
		List_Get_Clone_Func(war_zone), List_Get_Des_Func(war_zone), List_Get_Cmp_Func(war_zone), List_Get_Print_Func(war_zone),
		List_Get_Get_Key_Func(war_zone));

	if (new_war_zone == NULL) {
		return NULL;
	}
	List_Duplicate(war_zone->squads, new_war_zone->squads);
	new_war_zone->alertness = war_zone->alertness;
	return new_war_zone;
}

int WarZone_Raise_Alert(PWZ war_zone)
{
	if (war_zone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	int new_alertness = war_zone->alertness + 1;
	if (new_alertness == 3)
	{
		war_zone->alertness = 0;
		return new_alertness;
	}
	war_zone->alertness = new_alertness;
	return new_alertness
}

#include "WarZone.h"
#include "Squad.h"
#include "Soldier.h"
#include "APC.h"
#include "defs.h"

struct War_Zone_ {
	PList squads;
	int alertness;
	char ID[MAX_ID_LENGTH];
};

PWZ WarZone_Create(char* ID, CLONE_FUNC clone_func_sold, DESTROY_FUNC destroy_func_sold, COMPARE_KEYS_FUNC comp_keys_func_sold, PRINT_FUNC print_func_sold, GET_KEY_FUNC get_key_func_sold)
{
	PWZ w;
	if (!WarZone_Valid_ID(ID))
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

bool WarZone_Valid_ID(char* ID)
{
	if (ID == NULL)
		return false;
	if (ID[0] != 'W'||strlen(ID + 1) > LENGTH_OF_NUMS)
		return false;
	return true;
}

void WarZone_Delete(PWZ WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	List_Delete(WarZone->squads);
	free(WarZone);
}

void WarZone_Print(PWZ WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("WarZone: %s , Alert State: %d\n\n", WarZone->ID, WarZone->alertness);
	List_Print(WarZone->squads);
}

PWZ WarZone_Duplicate(PWZ war_zone) 
{
	if (war_zone == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PList squad = war_zone->squads;

	PWZ new_war_zone = WarZone_Create(war_zone->ID,
		List_Get_Clone_Func(squad), List_Get_Des_Func(squad), List_Get_Cmp_Func(squad), List_Get_Print_Func(squad),
		List_Get_Get_Key_Func(squad));

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
		return -1;
	}
	int new_alertness = war_zone->alertness + 1;
	if (new_alertness == 3)
	{
		war_zone->alertness = 0;
		return new_alertness;
	}
	war_zone->alertness = new_alertness;
	return new_alertness;
}

char* WarZone_Get_ID(PWZ wz)
{
		return wz->ID;
}


/* Functions for Main*/
void WarZone_Add_Squad(PWZ wz, char* squad_ID)
{
	PSquad squad = Squad_Create(squad_ID, Soldier_Clone_Func, Soldier_Destroy_Func, Soldier_Compare_Func, Soldier_Print_Func, Soldier_Get_Key_Function,
		APC_Clone_Func, APC_Destroy_Func, APC_Compare_Func, APC_Print_Func, APC_Get_Key_Function); // prints error from create if failed
	if (squad == NULL)
		return;
	List_Add_Elem(wz->squads, squad); // Error msg in function
	Squad_Delete(squad);
	return;
}

void WarZone_Remove_Squad(PWZ wz, char* squad_ID)
{
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, squad_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	List_Remove_Elem(wz->squads, squad_ID);
	return;
}

void WarZone_Move_Squad(PWZ origin_w, PWZ dest_w, char* squad_ID)
{
	PSquad squad = (PSquad)List_Get_Elem(origin_w->squads, squad_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	if (origin_w->ID == dest_w->ID)
		return;

	List_Add_Elem(dest_w->squads, squad);
	List_Remove_Elem(origin_w->squads, squad_ID);
	return;
}

void WarZone_Add_Soldier(PWZ wz, char* sq_ID, char* sol_ID, char* pos) {
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, sq_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	Squad_Add_Soldier(squad, pos, sol_ID); // prints error in function
	return;
}

void WarZone_Remove_Soldier(PWZ wz, char* sq_ID, char* sol_ID) {
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, sq_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	Squad_Delete_Soldier(squad, sol_ID); // prints error in function
	return;
}

void WarZone_Add_APC(PWZ wz, char* sq_ID, char* apc_ID)
{
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, sq_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	Squad_Add_APC(squad,apc_ID); // prints error in function
	return;
}

void WarZone_Remove_APC(PWZ wz, char* sq_ID, char* apc_ID) {
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, sq_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	Squad_Delete_APC(squad, apc_ID); // prints error in function
	return;
}

void WarZone_Sold_Insert(PWZ wz, char* sq_ID, char* apc_ID, char* sol_ID)
{
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, sq_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	Squad_Insert_Sold_APC(squad, sol_ID, apc_ID); // prints error in function
	return;
}
void WarZone_APC_Pop(PWZ wz, char* sq_ID, char* apc_ID)
{
	PSquad squad = (PSquad)List_Get_Elem(wz->squads, sq_ID);
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return;
	}
	Squad_APC_Pop(squad, apc_ID); // prints error in function
	return;
}

PList WarZone_Get_Squad_List(PWZ wz)
{
	return wz->squads;
}




/* Squad Functions */

bool Squad_Compare_Func(PKey ID1, PKey ID2)
{
	if (ID1 == NULL || ID2 == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}
	if (!strcmp((char*)ID1, (char*)ID2))
		return true;
	return false;
}
void Squad_Destroy_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad* a = (Squad*)pElem;
	Squad_Delete(a);
	return;
}
PElem Squad_Clone_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	Squad* a = (Squad*)pElem;
	a = Squad_Duplicate(a);
	return a;
}
void Squad_Print_Func(PElem pElem) {
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)pElem);
}

PKey Squad_Get_Key_Function(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	Squad* a = (Squad*)pElem;
	return Squad_Get_ID(a);
}

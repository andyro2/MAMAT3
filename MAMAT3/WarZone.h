#ifndef  _WAR_ZONE_H
#define _WAR_ZONE_H

#include "List.h"
#include "defs.h"

typedef struct War_Zone_ WZ, *PWZ;

PWZ WarZone_Create(char*, CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC); /*Creates a Warzone*/

void WarZone_Delete(PWZ); /*Deletes a Warzone*/
void WarZone_Print(PWZ); /*Prints a Warzone*/
PWZ WarZone_Duplicate(PWZ); /*Duplicates a Warzone*/
int WarZone_Raise_Alert(PWZ); /*Raises Alert Level of a Warzone*/

char* WarZone_Get_ID(PWZ); /*Returns Warzone's ID*/
bool WarZone_Valid_ID(char* ID); /*Checks if given Warzone ID is valid*/
void WarZone_Add_Squad(PWZ wz, char* squad_ID); /*Adds a Squad to Warzone*/
void WarZone_Remove_Squad(PWZ wz, char* squad_ID); /*Removes a Squad from Warzone*/
void WarZone_Move_Squad(PWZ origin_w, PWZ dest_w, char* squad_ID); /*Moves Squad from one Warzone to another*/
void WarZone_Add_Soldier(PWZ wz, char* sq_ID, char* sol_ID, char* pos); /*Adds a Soldier to a Squad within a Warzone*/
void WarZone_Remove_Soldier(PWZ wz, char* sq_ID, char* sol_ID); /*Removes a Soldier from a Squad within a Warzone*/
void WarZone_Add_APC(PWZ wz, char* sq_ID, char* apc_ID); /*Adds an APC to a Squad within a Warzone*/
void WarZone_Remove_APC(PWZ wz, char* sq_ID, char* apc_ID); /*Removes an APC from a Squad within a Warzone*/
void WarZone_Sold_Insert(PWZ wz, char* sq_ID, char* apc_ID, char* sol_ID); /*Inserts a Soldier into an APC within a Squad within a Warzone*/
void WarZone_APC_Pop(PWZ wz, char* sq_ID, char* apc_ID); /*Pops from an APC within a Squad within a Warzone*/
PList WarZone_Get_Squad_List(PWZ wz); /*Returns the Squad List from a Warzone*/

/* Squad Functions*/
bool Squad_Compare_Func(PKey ID1, PKey ID2);
void Squad_Destroy_Func(PElem pElem);
PElem Squad_Clone_Func(PElem pElem);
void Squad_Print_Func(PElem pElem);
PKey Squad_Get_Key_Function(PElem pElem);

#endif
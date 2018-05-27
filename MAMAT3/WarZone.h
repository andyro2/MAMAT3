#ifndef  _WAR_ZONE_H
#define _WAR_ZONE_H

#include "List.h"
#include "defs.h"

typedef struct War_Zone_ WZ, *PWZ;

PWZ WarZone_Create(char*, CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC);

void WarZone_Delete(PWZ);
void WarZone_Print(PWZ);
PWZ WarZone_Duplicate(PWZ);
int WarZone_Raise_Alert(PWZ);

char* WarZone_Get_ID(PWZ);
bool WarZone_Valid_ID(char* ID);
void WarZone_Add_Squad(PWZ wz, char* squad_ID);
void WarZone_Remove_Squad(PWZ wz, char* squad_ID);
void WarZone_Move_Squad(PWZ origin_w, PWZ dest_w, char* squad_ID);

bool Squad_Compare_Func(PKey ID1, PKey ID2);
void Squad_Destroy_Func(PElem pElem);
PElem Squad_Clone_Func(PElem pElem);
void Squad_Print_Func(PElem pElem);
PKey Squad_Get_Key_Function(PElem pElem);

#endif
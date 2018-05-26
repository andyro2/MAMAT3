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

#endif
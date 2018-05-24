#ifndef _SOLDIER_H_
#define _SOLDIER_H_

//typedef struct Soldier_ soldier; /*struct of soldier*/
#include "defs.h"
#include "List.h"

typedef struct Soldier_ soldier;

soldier* Soldier_Create(char*, char*); /*builds struct of soldier with given ID and pos*/

void Soldier_Delete(soldier*); /*deletes struct of given soldier*/

soldier* Soldier_Duplicate(soldier*);/*duplicates struct of given soldier*/

void Soldier_Print(soldier*); /* prints ID and pos of given soldier*/

bool Soldier_Compare_Func(PKey, PKey);
void Soldier_Destroy_Func(PElem);
PElem Soldier_Clone_Func(PElem);
void Soldier_Print_Func(PElem);
PKey Soldier_Get_Key_Function(PElem);

#endif
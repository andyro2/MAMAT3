#ifndef _SOLDIER_H_
#define _SOLDIER_H_

//typedef struct Soldier_ soldier; /*struct of soldier*/
#include "defs.h"

typedef struct Soldier_ soldier;

soldier* Soldier_Create(char*, char*); /*builds struct of soldier with given ID and pos*/

void Soldier_Delete(soldier*); /*deletes struct of given soldier*/

soldier* Soldier_Duplicate(soldier*);/*duplicates struct of given soldier*/

void Soldier_Print(soldier*); /* prints ID and pos of given soldier*/
char* Soldier_Get_ID(soldier* s);
bool Soldier_Valid_ID_Pos(char* ID, char* pos);

#endif
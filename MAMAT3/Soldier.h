#ifndef _Soldier_h
#define _Soldier_h

typedef struct Soldier_ soldier; /*struct of soldier*/

soldier* Soldier_Create(char*, char*); /*builds struct of soldier with given ID and pos*/

void Soldier_Delete(soldier*); /*deletes struct of given soldier*/

soldier* Soldier_Duplicate(soldier*);/*duplicates struct of given soldier*/

void Soldier_Print(soldier*); /* prints ID and pos of given soldier*/

#endif
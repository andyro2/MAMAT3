#include "Soldier.h"
#include "defs.h"
#include "List.h"

#ifndef _APC_H
#define _APC_H

typedef struct APC_ APC; /*struct of APC*/

APC* APC_Create(char*); /*Creates default struct according to given ID*/

void APC_Delete(APC*); /*deletes APC and Soldiers in it*/

void APC_Print(APC*); /*Prints APC ID and vacancy and all Soldiers inside*/

APC* APC_Duplicate(APC*); /*Duplicates apc and soldiers inside*/

Result APC_Insert_Soldier(APC*, soldier* ); /*inserts new soldier in to APC*/

soldier* APC_Pop(APC*); /*removes last soldier from APC*/

bool APC_Compare_Func(PKey, PKey);
void APC_Destroy_Func(PElem);
PElem APC_Clone_Func(PElem);
void APC_Print_Func(PElem);
PKey APC_Get_Key_Function(PElem);
#endif

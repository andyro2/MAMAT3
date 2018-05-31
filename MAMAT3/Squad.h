#ifndef  _SQUAD_H
#define _SQUAD_H

/**Includes**/
#include "defs.h"
#include "List.h"

typedef struct Squad_ Squad , *PSquad;


PSquad Squad_Create(char*,
	CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC,
	CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC); 

void Squad_Delete(PSquad squad); 
void Squad_Print(PSquad squad); 
Result Squad_Add_Soldier(PSquad squad, char* pos, char* ID);
PSquad Squad_Duplicate(PSquad);
Result Squad_Add_APC(PSquad squad, char* ID);
Result Squad_Insert_Sold_APC(PSquad squad, char* sol_ID, char* apc_ID);
Result Squad_APC_Pop(PSquad squad, char* apc_ID);
Result Squad_Delete_Soldier(PSquad squad, char* sol_ID);
Result Squad_Delete_APC(PSquad, char*);
bool Squad_Valid_ID(char*);
char* Squad_Get_ID(PSquad);
PList Squad_Get_Soldier_List(PSquad squad);
PList Squad_Get_APC_List(PSquad squad);

/*User Functions*/

/* Soldier Functions*/
bool Soldier_Compare_Func(PKey, PKey);
void Soldier_Destroy_Func(PElem);
PElem Soldier_Clone_Func(PElem);
void Soldier_Print_Func(PElem);
PKey Soldier_Get_Key_Function(PElem);

/* APC Functions*/
bool APC_Compare_Func(PKey, PKey);
void APC_Destroy_Func(PElem);
PElem APC_Clone_Func(PElem);
void APC_Print_Func(PElem);
PKey APC_Get_Key_Function(PElem);
#endif 

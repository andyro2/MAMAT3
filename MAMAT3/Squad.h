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
void Squad_print(PSquad squad);
Result Squad_Add_Soldier(PSquad squad, char* pos, char* ID);
PSquad Squad_Duplicate(PSquad);
Result Squad_Add_APC(PSquad squad, char* ID);
Result Squad_Insert_Sold_APC(PSquad squad, char* sol_ID, char* apc_ID);
Result Squad_APC_Pop(PSquad squad, char* apc_ID);
Result Squad_Delete_Soldier(PSquad squad, char* sol_ID);
Result Squad_Delete_APC(PSquad, char*);

void Squad_Print_Func(PElem);

#endif 

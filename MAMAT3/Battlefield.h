#ifndef _Battlefield_h
#define _Battlefield_h

/*includes & defines*/
#include "WarZone.h"
#include "defs.h"

typedef struct Battlefield_ Battlefield, *PBf;
typedef struct Command_ Command, *PCommand;

PBf Battlefield_Create(CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC,
					   CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC);
void Battlefield_Delete(PBf);
void Battlefield_Add_WarZone(PBf, char*);
void Battlefield_Del_WarZone(PBf, char*);
void Battlefield_Move_all_Squads(PWZ, PBf);
PWZ Battlefield_Get_WarZone(PBf, char*);

bool Battlefield_Check_Squad(PBf bf, char* sq_ID);
bool Battlefield_Check_Soldier(PBf bf, char* sol_ID);
bool Battlefield_Check_APC(PBf bf, char* apc_ID);

void Add_Command(PBf, char* arg[MAX_ARG], int);
void Delete_Command(PBf, PCommand);
PList Command_Sort(PBf);
PList Get_Command(PBf);
void Set_Command(PBf, PList);
int Get_Command_Num(PBf);
void Print_Battlefield(PBf bf);

/* Warzone Functions*/
bool WarZone_Compare_Func(PKey, PKey);
void WarZone_Destroy_Func(PElem);
PElem WarZone_Clone_Func(PElem);
void WarZone_Print_Func(PElem);
PKey WarZone_Get_Key_Function(PElem);

/* Command Functions*/
PCommand Command_Create(char* arg[MAX_ARG] ,int);
void Command_Delete(PCommand);
PCommand Command_Duplicate(PCommand);
int* Command_Get_Index(PCommand);
char* Command_Get_Arg(PCommand, int);

bool Command_Compare_Func(PKey, PKey);
void Command_Destroy_Func(PElem);
PElem Command_Clone_Func(PElem);
void Command_Print_Func(PElem);
PKey Command_Get_Key_Function(PElem);

#endif

#ifndef _Battlefield_h
#define _Battlefield_h

/*includes & defines*/
#include "WarZone.h"
#include "defs.h"

typedef struct Battlefield_ Battlefield, *PBf;
typedef struct Command_ Command, *PCommand;

PBf Battlefield_Create(CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC,
					   CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, GET_KEY_FUNC);
void Battlefield_Delete(PBf);

void Add_Command(PBf, char*, int);
void Delete_Command(PBf, PCommand);
PList Command_Sort(PBf);
PList Get_Command(PBf);
void Set_Command(PBf, PList);

/* Warzone Functions*/
bool Warzone_Compare_Func(PKey, PKey);
void Warzone_Destroy_Func(PElem);
PElem Warzone_Clone_Func(PElem);
void Warzone_Print_Func(PElem);
PKey Warzone_Get_Key_Function(PElem);

/* Command Functions*/
PCommand Command_Create(char*,int);
void Command_Delete(PCommand);
PCommand Command_Duplicate(PCommand);
char* Command_Get_Index(PCommand);

bool Command_Compare_Func(PKey, PKey);
void Command_Destroy_Func(PElem);
PElem Command_Clone_Func(PElem);
PKey Command_Get_Key_Function(PElem);

#endif

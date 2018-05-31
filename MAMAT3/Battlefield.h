#ifndef _Battlefield_h
#define _Battlefield_h

/*includes & defines*/
#include "WarZone.h"
#include "defs.h"

typedef struct Battlefield_ Battlefield, *PBf;
typedef struct Command_ Command, *PCommand;

PBf Battlefield_Create(CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC,
					   CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC); /*Creates empty battlefield*/
void Battlefield_Delete(PBf); /*Deletes the battlefield*/
void Battlefield_Add_WarZone(PBf, char*); /*Adds a Warzone by ID*/
void Battlefield_Del_WarZone(PBf, char*); /*Deletes a Warzone by ID*/
void Battlefield_Move_all_Squads(PWZ, PBf); /*Moves all Squads in Battlefield to a given Warzone*/
PWZ Battlefield_Get_WarZone(PBf, char*); /*Returns a pointer to a Warzone by ID*/

bool Battlefield_Check_Squad(PBf bf, char* sq_ID); /*Checks if Squad ID exists in Battlefield*/
bool Battlefield_Check_Soldier(PBf bf, char* sol_ID); /*Checks if Soldier ID exists in Battlefield*/
bool Battlefield_Check_APC(PBf bf, char* apc_ID); /*Checks if APC ID exists in Battlefield*/

void Add_Command(PBf, char* arg[MAX_ARG], int); /*Adds a Command to Command List*/
void Delete_Command(PBf, PCommand); /*Deletes a Command from Command List*/
PList Command_Sort(PBf); /*Sorts Command List by Index*/
PList Get_Command(PBf); /*Returns the Command List*/
void Set_Command(PBf, PList); /*Sets the Command List*/
int Get_Command_Num(PBf); /*Returns # of Commands in List*/
void Print_Battlefield(PBf bf); /*Prints Battlefield*/

/* Warzone Functions*/
bool WarZone_Compare_Func(PKey, PKey);
void WarZone_Destroy_Func(PElem);
PElem WarZone_Clone_Func(PElem);
void WarZone_Print_Func(PElem);
PKey WarZone_Get_Key_Function(PElem);

/* Command Functions*/
PCommand Command_Create(char* arg[MAX_ARG] ,int); /*Creates and returns a new command */
void Command_Delete(PCommand); /*Deletes a command*/
PCommand Command_Duplicate(PCommand); /*Duplicates a command*/
int* Command_Get_Index(PCommand); /*Returns a Command's index*/
char* Command_Get_Arg(PCommand, int); /*Returns a Command's arguments*/

bool Command_Compare_Func(PKey, PKey);
void Command_Destroy_Func(PElem);
PElem Command_Clone_Func(PElem);
void Command_Print_Func(PElem);
PKey Command_Get_Key_Function(PElem);

#endif

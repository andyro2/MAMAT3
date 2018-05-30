#include "Battlefield.h"
#include "defs.h"
#include "WarZone.h"
#include "Squad.h"
#include "Soldier.h"
#include "APC.h"


struct Battlefield_ {
	PList warzones;
	PList commands;
	int comm_num;
};

struct Command_ {
	char* Command_Arguments[MAX_ARG];
	int command_index;
};

/**Funcs**/

PBf Battlefield_Create(CLONE_FUNC clone_func_warzone, DESTROY_FUNC destroy_func_warzone, COMPARE_KEYS_FUNC comp_keys_func_warzone, PRINT_FUNC print_func_warzone, GET_KEY_FUNC get_key_func_warzone
					 , CLONE_FUNC clone_func_command, DESTROY_FUNC destroy_func_command, COMPARE_KEYS_FUNC comp_keys_func_command, PRINT_FUNC print_func_command, GET_KEY_FUNC get_key_func_command)
{
	PBf bf;
	
	if ((clone_func_warzone == NULL) || (destroy_func_warzone == NULL) || (comp_keys_func_warzone == NULL) || (print_func_warzone == NULL) || ( get_key_func_warzone == NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if ((clone_func_command == NULL) || (destroy_func_command == NULL) || (comp_keys_func_command == NULL) || (print_func_command == NULL ) || ( get_key_func_command == NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	bf = (PBf)malloc(sizeof(Battlefield));
	if (bf == NULL)
	{
		free(bf);
		//printf(MALLOC_ERR_MSG);
		printf("Program Init Error\n");
		return NULL;
	}
	bf->warzones = List_Create(clone_func_warzone, destroy_func_warzone, comp_keys_func_warzone, print_func_warzone, get_key_func_warzone);
	bf->commands = List_Create(clone_func_command, destroy_func_command, comp_keys_func_command, print_func_command, get_key_func_command);
	bf->comm_num = 0;
	return bf;
}

PList Command_Sort(PBf bf) //bf !NULL
{
	PList unor_list = bf->commands;
	PList ordered_list = List_Create(List_Get_Clone_Func(unor_list), List_Get_Des_Func(unor_list),
		List_Get_Cmp_Func(unor_list), List_Get_Print_Func(unor_list), List_Get_Get_Key_Func(unor_list));
	PCommand curr_comm;
	int i = 1;
	while (i <= bf->comm_num)
	{
		curr_comm = (PCommand)List_Get_Elem(unor_list, &i);
		List_Add_Elem(ordered_list, curr_comm);
		i++;
	}
	return ordered_list;
}

void Battlefield_Delete(PBf bf) //bf !NULL
{
	if (bf == NULL) {
		//printf(ARG_ERR_MSG);
		return;
	}
	List_Delete(bf->warzones);
	List_Delete(bf->commands);
	free(bf);
	return;
} 

void Battlefield_Move_all_Squads(PWZ to_wz, PBf bf)
{
	PWZ curr_wz = (PWZ)List_Get_First(bf->warzones);
	PSquad squad;
	char* sq_ID;
	while (curr_wz != NULL) {
		if (strcmp(WarZone_Get_ID(curr_wz), WarZone_Get_ID(to_wz)))
		{
			squad = List_Get_First(WarZone_Get_Squad_List(curr_wz));
			while (squad != NULL)
			{
				sq_ID = Squad_Get_ID(squad);
				WarZone_Move_Squad(curr_wz, to_wz, sq_ID);
				squad = List_Get_First(WarZone_Get_Squad_List(curr_wz));
			}
		}
		curr_wz = List_Get_Next(bf->warzones, WarZone_Get_ID(curr_wz));
	}
	return;
}

void Battlefield_Add_WarZone(PBf bf, char* wz)
{
	if (List_Get_Elem(bf->warzones,wz) != NULL)
		printf("Error: War Zone Already Exists\n");
	else
	{
		PWZ warzone = WarZone_Create(wz, Squad_Clone_Func, Squad_Destroy_Func, Squad_Compare_Func, Squad_Print_Func, Squad_Get_Key_Function);
		List_Add_Elem(bf->warzones, warzone);
	}
	return;
}

void Battlefield_Del_WarZone(PBf bf, char* wz)
{
	if (List_Get_Elem(bf->warzones, wz) == NULL)
		printf("Error: No Such War Zone\n");
	else
		List_Remove_Elem(bf->warzones, wz);
	return;
}

PWZ Battlefield_Get_WarZone(PBf bf, char* wz)
{
	PWZ warzone = (PWZ)List_Get_Elem(bf->warzones, wz);
	return warzone;
}

bool Battlefield_Check_Squad(PBf bf, char* sq_ID)
{
	if(sq_ID == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}
	PWZ wz = List_Get_First(bf->warzones);
	char* wz_ID;
	while (wz != NULL)
	{
		wz_ID = WarZone_Get_ID(wz);
		if (List_Get_Elem(WarZone_Get_Squad_List(wz), sq_ID) != NULL) {
			return true;
		}
		wz = List_Get_Next(bf->warzones, wz_ID);
		
	}
	return false;
}

bool Battlefield_Check_Soldier(PBf bf, char* sol_ID)
{
	if (sol_ID == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}
	PWZ wz = List_Get_First(bf->warzones);
	PList sq_list, apc_list;
	PSquad squad; 
	APC* apc;
	char* wz_ID, *sq_ID, *apc_ID;
	while (wz != NULL)
	{
		wz_ID = WarZone_Get_ID(wz);
		sq_list = WarZone_Get_Squad_List(wz);
		squad = List_Get_First(sq_list);
		while (squad != NULL)
		{
			sq_ID = Squad_Get_ID(squad);
			if (List_Get_Elem(Squad_Get_Soldier_List(squad), sol_ID) != NULL)
				return true;
			apc_list = Squad_Get_APC_List(squad);
			apc = List_Get_First(apc_list);
			while (apc != NULL) {
				apc_ID = APC_Get_ID(apc);
				if (APC_Get_Sold(apc, sol_ID) != NULL)
					return true;
				apc = List_Get_Next(apc_list, apc_ID);
			}

			squad = List_Get_Next(sq_list, sq_ID);
		}
		wz = List_Get_Next(bf->warzones, wz_ID);
	}
	return false;
}

bool Battlefield_Check_APC(PBf bf, char* APC_ID)
{
	if (APC_ID == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}
	PWZ wz = List_Get_First(bf->warzones);
	PList sq_list;
	PSquad squad;
	char* wz_ID, *sq_ID;
	while (wz != NULL)
	{
		wz_ID = WarZone_Get_ID(wz);
		sq_list = WarZone_Get_Squad_List(wz);
		squad = List_Get_First(sq_list);
		while (squad != NULL)
		{
			sq_ID = Squad_Get_ID(squad);
			if (List_Get_Elem(Squad_Get_APC_List(squad), APC_ID) != NULL)
				return true;
			squad = List_Get_Next(sq_list, sq_ID);
		}
		wz = List_Get_Next(bf->warzones, wz_ID);
	}
	return false;
}

/**User Functions**/


void Add_Command(PBf bf, char* args[MAX_ARG], int index)
{ 

	//printf("arg[0]: %s, arg[1]: %s", args[0], args[1]);
	if (List_Add_Elem(bf->commands, Command_Create(args, index)) == SUCCESS);
		bf->comm_num++;
	return;
}

void Delete_Command(PBf bf, PCommand command)
{
	if (List_Remove_Elem(bf->commands, &(command->command_index)) == SUCCESS);
		bf->comm_num--;
	return;
}				

PList Get_Command(PBf bf)
{
	return bf->commands;
}

void Set_Command(PBf bf, PList commands)
{
	PList new_commands = List_Create(List_Get_Clone_Func(commands),List_Get_Des_Func(commands),
						List_Get_Cmp_Func(commands),List_Get_Print_Func(commands),List_Get_Get_Key_Func(commands));
	List_Delete(bf->commands);
	List_Duplicate(commands, new_commands);
	bf->commands = new_commands;
	return;
}

int Get_Command_Num(PBf bf)
{
	return bf->comm_num;
}

/* WarZone Functions*/

bool WarZone_Compare_Func(PKey ID1, PKey ID2)
{
	if (ID1 == NULL || ID2 == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}
	if (!strcmp((char*)ID1, (char*)ID2))
		return true;
	return false;
}
void WarZone_Destroy_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	WZ* s = (WZ*)pElem;
	WarZone_Delete(s);
	return;
}
PElem WarZone_Clone_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	WZ* s = (WZ*)pElem;
	s = WarZone_Duplicate(s);
	return s;
}
void WarZone_Print_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	WZ* s = (WZ*)pElem;
	WarZone_Print(s);
	return;
}
PKey WarZone_Get_Key_Function(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	WZ* s = (WZ*)pElem;
	return WarZone_Get_ID(s);
}
// returns char* while expecting PKey - prone to ERROR?

/* Command Functions*/

PCommand Command_Create(char* args[MAX_ARG], int index)
{
	//printf("arg[0]: %s, arg[1]: %s", args[0], args[1]);
	PCommand command = (PCommand)malloc(sizeof(Command));
	//char* curr_arg;
	if (command == NULL) {
		free(command);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	for (int i = 0; i < MAX_ARG; i++)
	{
		if (args[i] == NULL)
			command->Command_Arguments[i] = NULL;
		else
		{ 
			//strcpy(&((*command->Command_Arguments)[i]), &((*args)[i])); //Array of args- check validity
			//curr_arg = (command->Command_Arguments)[i];
			//command->Command_Arguments[i] = "Hello";
			command->Command_Arguments[i] = malloc(strlen(args[i]) + 1);
			strcpy(command->Command_Arguments[i], args[i]);
		}
	}
	command->command_index = index;
	return command;
}

void Command_Delete(PCommand command)
{
	if (command == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	for (int i = 0; (i < MAX_ARG) && (command->Command_Arguments[i] != NULL); i++)
		free(command->Command_Arguments[i]);
	free(command);
	return;
}

PCommand Command_Duplicate(PCommand exist_command)
{
	if (exist_command == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	PCommand new_command = Command_Create(exist_command->Command_Arguments, exist_command->command_index);
	if (new_command == NULL) {
		return NULL;
	}
	return new_command;
}

int* Command_Get_Index(PCommand c)
{
	return &(c->command_index);
}

char* Command_Get_Arg(PCommand c, int i)
{
	return c->Command_Arguments[i];
}

void Print_Battlefield(PBf bf)
{
	if (bf == NULL) {
		printf("Error: No Battlefield\n");
		return;
	}
	printf("Battlefield:\n");
	List_Print(bf->warzones);
}

bool Command_Compare_Func(PKey key1, PKey key2)
{
	if (key1 == NULL || key2 == NULL) {
		printf(ARG_ERR_MSG);
		return false;
	}
	if (*((int*)key1) == *((int*)key2))
		return true;
	return false;
}
void Command_Destroy_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	PCommand a = (PCommand)pElem;
	Command_Delete(a);
	return;
}
PElem Command_Clone_Func(PElem pElem)
{

	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PCommand a = (PCommand)pElem;
	a = Command_Duplicate(a);
	return a;
}
void Command_Print_Func(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	return;
}
PKey Command_Get_Key_Function(PElem pElem)
{
	if (pElem == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PCommand a = (PCommand)pElem;
	return Command_Get_Index(a);
}


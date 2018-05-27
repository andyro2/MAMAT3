#include "Battlefield.h"
#include "defs.h"
#include "WarZone.h"


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
					 , CLONE_FUNC clone_func_command, DESTROY_FUNC destroy_func_command, COMPARE_KEYS_FUNC comp_keys_func_command, GET_KEY_FUNC get_key_func_command)
{
	PBf bf;
	
	if ((clone_func_warzone == NULL) || (destroy_func_warzone == NULL) || (comp_keys_func_warzone == NULL) || (print_func_warzone == NULL) || get_key_func_warzone == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if ((clone_func_command == NULL) || (destroy_func_command == NULL) || (comp_keys_func_command == NULL) || get_key_func_command == NULL) {
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
	bf->commands = List_Create(clone_func_command, destroy_func_command, comp_keys_func_command, NULL, get_key_func_command);
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
		curr_comm = List_Get_Elem(unor_list, i);
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

void Battlefield_Add_WarZone(PBf bf, char* wz)
{
	if (List_Get_Elem(bf->warzones,wz) != NULL)
		fprintf(stderr, "Error: War Zone Already Exists\n");
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
		fprintf(stderr, "Error: No Such War Zone\n");
	else
		List_Remove_Elem(bf->warzones, wz);
	return;
}

bool Battlefield_Emergency_WarZone(PBf bf, char* wz)
{
	PWZ warzone = (PWZ)List_Get_Elem(bf->warzones, wz);
	if (warzone == NULL)
		fprintf(stderr, "Error: No Such War Zone\n");
	else if (WarZone_Raise_Alert(warzone) == 3)
		return true;
	return false;
}

PWZ Battlefield_Get_WarZone(PBf bf, char* wz)
{
	PWZ warzone = (PWZ)List_Get_Elem(bf->warzones, wz);
	if (warzone == NULL)
		fprintf(stderr, "Error: No Such War Zone\n");
	return warzone;
}
/**User Functions**/


void Add_Command(PBf bf, char* args, int index)
{
	if (List_Add_Elem(bf->commands, Command_Create(args, index)) == SUCCESS);
		bf->comm_num++;
	return;
}

void Delete_Command(PBf bf, PCommand command)
{
	if (List_Remove_Elem(bf->commands, command->command_index) == SUCCESS);
		bf->comm_num--;
	return;
}				
//Unused so far

PList Get_Command(PBf bf)
{
	return bf->commands;
}

void Set_Command(PBf bf, PList commands)
{
	PList new_commands = List_Create(List_Get_Clone_Func(commands),List_Get_Des_Func(commands),
						List_Get_Cmp_Func(commands),List_Get_Print_Func(commands),List_Get_Get_Key_Func(commands));
	List_Delete(bf->commands);
	List_Duplicate(new_commands, commands);
	bf->commands = new_commands;
	return;
}

int Get_Command_Num(PBf bf)
{
	return bf->commands;
}

/* WarZone Functions*/

bool Warzone_Compare_Func(PKey ID1, PKey ID2)
{
	if (!strcmp((char*)ID1, (char*)ID2))
		return true;
	return false;
}
void Warzone_Destroy_Func(PElem pElem)
{
	WZ* s = (WZ*)pElem;
	WarZone_Delete(s);
	return;
}
PElem WarZone_Clone_Func(PElem pElem)
{
	WZ* s = (WZ*)pElem;
	s = WarZone_Duplicate(s);
	return s;
}
void WarZone_Print_Func(PElem pElem)
{
	WZ* s = (WZ*)pElem;
	WarZone_Print(s);
	return;
}
PKey WarZone_Get_Key_Function(PElem pElem)
{

	WZ* s = (WZ*)pElem;
	return WarZone_Get_ID(s);
}
// returns char* while expecting PKey - prone to ERROR?

/* Command Functions*/

PCommand Command_Create(char* args, int index)
{
	PCommand command = (PCommand)malloc(sizeof(Command));
	if (command == NULL) {
		free(command);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(command->Command_Arguments, args); //Array of args- check validity
	command->command_index = index;
	return command;
}

void Command_Delete(PCommand command)
{
	if (command == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	free(command);
	return;
}

PCommand Command_Duplicate(PCommand exist_command)
{
	if (exist_command == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	PCommand new_command = Soldier_Create(exist_command->Command_Arguments, exist_command->command_index);
	if (new_command == NULL) {
		return NULL;
	}
	return new_command;
}

char* Command_Get_Index(PCommand c)
{
	return c->command_index;
}

char* Command_Get_Arg(PCommand c, int i)
{
	return c->Command_Arguments[i];
}

bool Command_Compare_Func(PKey ID1, PKey ID2)
{
	if (!strcmp((char*)ID1, (char*)ID2))
		return true;
	return false;
}
void Command_Destroy_Func(PElem pElem)
{
	PCommand a = (PCommand)pElem;
	Command_Delete(a);
	return;
}
PElem Command_Clone_Func(PElem pElem)
{
	PCommand a = (PCommand)pElem;
	a = Command_Duplicate(a);
	return a;
}
PKey Command_Get_Key_Function(PElem pElem)
{
	PCommand a = (PCommand)pElem;
	return Command_Get_Index(a);
}


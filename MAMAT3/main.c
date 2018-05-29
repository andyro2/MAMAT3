/* Includes */

#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"
#include "Squad.h"
#include "Warzone.h"
#include "Battlefield.h"

#define MAX_LINE_SIZE 256
//#pragma warning(disable:4996)


void main()
{
	/* Command List Construction */
	/*
	PList Commands_List = List_Create(/--/); // Complete here...
	if (Commands_List == NULL) {
		printf("Program Init Error\n");
		return EXIT_FAILURE;
	}

	//2) Battlefield List
	PList Battlefield = NULL;
	
	
	*/
	//3) /**STRTOK**
	/**Need two copies of program's input line: one for each strtok.(because strtok changes it's input string)**/
	char Input_Line[MAX_INPUT_LINE] = { 0 };				// stores program's input line by line
	//char Input_Line_Copy[MAX_INPUT_LINE] = { 0 };
	char delimiters[] = " \t\n";
	int Args_Num;											// number of arguments in current command
	char* Curr_Command_Index;								//	will hold the current command index
	char* Command_Arguments[MAX_ARG];						//	all command's arguments after strtok completed.
	int command_index;
	//PBf battlefield = NULL;
	bool ended = false;
	bool Battlefield_Created = false;

	PBf battlefield = Battlefield_Create(WarZone_Clone_Func, WarZone_Destroy_Func, WarZone_Compare_Func, WarZone_Print_Func, WarZone_Get_Key_Function,
		Command_Clone_Func, Command_Destroy_Func, Command_Compare_Func, Command_Print_Func, Command_Get_Key_Function);
	if (battlefield == NULL)
	{
		fprintf(stderr, "Houston, we have a problem\n"); //self-check (after creating)
		Battlefield_Created = false;
	}

	//char szLine[MAX_LINE_SIZE];		//char* delimiters = " []\t\n";

/* Command Proccessing */

while (!ended) {												//program didnt end
	fgets(Input_Line, MAX_INPUT_LINE, stdin);					//scan next input line
	//strcpy(Input_Line_Copy, Input_Line);						//making backup of input line (going to use strtok)
	Curr_Command_Index = strtok(Input_Line, delimiters);	//getting the index of current command - copied string Changed!
	Args_Num = 0;
	while (1) {
		Command_Arguments[Args_Num] = strtok(NULL, delimiters);
		if (Command_Arguments[Args_Num] == NULL) {
			//Args_Num++;
			for (int i = Args_Num + 1; i < MAX_ARG; i++)
				Command_Arguments[i] = NULL; //Initialize each Command
			break;
		}
		Args_Num++;
	}

	/**Cases according to command's index**/

	if (!strcmp(Curr_Command_Index, "Exit")) {
		if (!Battlefield_Created)
			fprintf(stderr, "Error: No Battlefield\n");
		else
			Battlefield_Delete(battlefield);
		ended = true; //Not really necessary
		return;
	}
	//C.1) index is "Exe" - need to execute all commands by current order
	else if (!strcmp(Curr_Command_Index, "Exe")) {
		
			Set_Command(battlefield, Command_Sort(battlefield));
			PCommand currCommand = (PCommand)List_Get_First(Get_Command(battlefield));
			//int commands_num = Get_Command_Num(battlefield);
			char* currArgs0, *currArgs1, *currArgs2, *currArgs3, *currArgs4;
			if (currCommand == NULL)
				printf("No Commands to Execute\n");	
			while (currCommand)
			{
				currArgs0 = Command_Get_Arg(currCommand, 0);
				currArgs1 = Command_Get_Arg(currCommand, 1);
				currArgs2 = Command_Get_Arg(currCommand, 2);
				currArgs3 = Command_Get_Arg(currCommand, 3);
				currArgs4 = Command_Get_Arg(currCommand, 4);
				if ((!strcmp(currArgs0, "Create_B")) && (currArgs1 == NULL))
				{
					/*battlefield = Battlefield_Create(WarZone_Clone_Func, WarZone_Destroy_Func, WarZone_Compare_Func, WarZone_Print_Func, WarZone_Get_Key_Function,
						Command_Clone_Func, Command_Destroy_Func, Command_Compare_Func, Command_Print_Func, Command_Get_Key_Function);
					if (battlefield == NULL)
					{
						fprintf(stderr, "Houston, we have a problem\n"); //self-check (after creating)
						Battlefield_Created = false;
					}
					else */
					if (Battlefield_Created)
						fprintf(stderr, "Error: Battlefield Already Created!\n"); //Kistuah!!!
					else
					{
						Battlefield_Created = true;
						printf("Battlefield Created!\n");
					}
				}
				else if (!Battlefield_Created)
					fprintf(stderr, "Error: No Battlefield\n");
				else
				{
					if ((!strcmp(currArgs0, "Add_W")) && (currArgs2 == NULL) && (currArgs1 != NULL))
						Battlefield_Add_WarZone(battlefield, currArgs1);
					else if ((!strcmp(currArgs0, "Del_W")) && (currArgs2 == NULL) && (currArgs1 != NULL))
						Battlefield_Del_WarZone(battlefield, currArgs1);
					else if ((!strcmp(currArgs0, "R_W")) && (currArgs2 == NULL) && (currArgs1 != NULL))
						{
							PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
							if (warzone == NULL) {
								fprintf(stderr, "Error: No Such War Zone\n");
								break;
							}
							if (WarZone_Raise_Alert(warzone) == 3) {
								Battelfield_Move_all_Squads(warzone, battlefield);
							}
						}
					else if ((!strcmp(currArgs0, "Add_Sq")) && (currArgs3 == NULL) && (currArgs2 != NULL))
						{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Add_Squad(warzone, currArgs2);
						}
					else if ((!strcmp(currArgs0, "Del_Sq")) && (currArgs3 == NULL) && (currArgs2 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Remove_Squad(warzone, currArgs2);
					}
					else if ((!strcmp(currArgs0, "M_Sq")) && (currArgs4 == NULL) && (currArgs3 != NULL))
					{
						PWZ origin_w = Battlefield_Get_WarZone(battlefield, currArgs1);
						PWZ dest_w = Battlefield_Get_WarZone(battlefield, currArgs2);
						if (origin_w == NULL) {
							fprintf(stderr, "Error: No Such Origin War Zone\n");
							break;
						}
						if (dest_w == NULL) {
							fprintf(stderr, "Error: No Such Dest War Zone\n");
							break;
						}
						WarZone_Move_Squad(origin_w, dest_w, currArgs3);
					}
					else if ((!strcmp(currArgs0, "Add_Sold")) && (currArgs4 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Add_Soldier(warzone, currArgs2, currArgs3, currArgs4);
					}
					else if ((!strcmp(currArgs0, "Del_Sold")) && (currArgs4 == NULL) && (currArgs3 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Remove_Soldier(warzone, currArgs2, currArgs3);
					}
					else if ((!strcmp(currArgs0, "Add_APC")) && (currArgs4 == NULL) && (currArgs3 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Add_APC(warzone, currArgs2, currArgs3);
					}
					else if ((!strcmp(currArgs0, "Del_APC")) && (currArgs4 == NULL) && (currArgs3 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Remove_APC(warzone, currArgs2, currArgs3);
					}
					else if ((!strcmp(currArgs0, "Sold_Insert")) && (currArgs4 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_Sold_Insert(warzone, currArgs2, currArgs3, currArgs4);
					}
					else if ((!strcmp(currArgs0, "APC_Pop")) && (currArgs4 == NULL) && (currArgs3 != NULL))
					{
						PWZ warzone = Battlefield_Get_WarZone(battlefield, currArgs1);
						if (warzone == NULL) {
							fprintf(stderr, "Error: No Such War Zone\n");
							break;
						}
						WarZone_APC_Pop(warzone, currArgs2, currArgs3);
					}
					else if ((!strcmp(currArgs0, "Print")) && (currArgs1 == NULL))
					{
						Print_Battelfield(battlefield);
					}	
				}
				Delete_Command(battlefield, currCommand);
				currCommand = (PCommand)List_Get_First(Get_Command(battlefield));
			}
			printf("**********All Commands Executed**********\n\n");

		}
	else if (strlen(Curr_Command_Index) == 1) { //collect valid executions

		command_index = atoi(Curr_Command_Index);
		if (command_index == 0)
			fprintf(stderr, "Error: Illegal Command\n");
		else
		{
			if (((!strcmp(Command_Arguments[0], "Add_W")) && (Command_Arguments[2] == NULL) && (Command_Arguments[1] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Del_W")) && (Command_Arguments[2] == NULL) && (Command_Arguments[1] != NULL)) ||
				((!strcmp(Command_Arguments[0], "R_W")) && (Command_Arguments[2] == NULL) && (Command_Arguments[1] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Add_Sq")) && (Command_Arguments[3] == NULL) && (Command_Arguments[2] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Del_Sq")) && (Command_Arguments[3] == NULL) && (Command_Arguments[2] != NULL)) ||
				((!strcmp(Command_Arguments[0], "M_Sq")) && (Command_Arguments[4] == NULL) && (Command_Arguments[3] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Add_Sold")) && (Command_Arguments[5] == NULL) && (Command_Arguments[4] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Del_Sold")) && (Command_Arguments[4] == NULL) && (Command_Arguments[3] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Add_APC")) && (Command_Arguments[4] == NULL) && (Command_Arguments[3] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Del_APC")) && (Command_Arguments[4] == NULL) && (Command_Arguments[3] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Sold_Insert")) && (Command_Arguments[5] == NULL) && (Command_Arguments[4] != NULL)) ||
				((!strcmp(Command_Arguments[0], "APC_Pop")) && (Command_Arguments[4] == NULL) && (Command_Arguments[3] != NULL)) ||
				((!strcmp(Command_Arguments[0], "Print")) && (Command_Arguments[1] == NULL)))
			{//valid executions 

				//if (!Battlefield_Created) //battlefield yet created
				//	fprintf(stderr, "Error: No Battlefield\n");
				//else
					Add_Command(battlefield, Command_Arguments, command_index); //Command_Arguments[0]
			}
			else if ((!strcmp(Command_Arguments[0], "Create_B")) && (Command_Arguments[1] == NULL))
			{
				 //Needs to be created in order to store Command List
				
					Add_Command(battlefield, Command_Arguments, command_index);
			}
			else
				fprintf(stderr, "Error: Illegal Command\n");
		}
		}
	else
		fprintf(stderr, "Error: Illegal Command\n");
	}
	return; //ended = true
};
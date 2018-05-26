/* Includes */

#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"
#include "Squad.h"
#include "Warzone.h"
#include "Battlefield.h"

#define MAX_LINE_SIZE 256


void main()
{
	/* Command List Construction */

	PList Commands_List = List_Create(/**********/); // Complete here...
	if (Commands_List == NULL) {
		printf("Program Init Error\n");
		return EXIT_FAILURE;
	}

	//2) Battlefield List
	PList Battlefield = NULL;
	bool Battlefield_Created = false;
	bool ended = false;

	//3) /**STRTOK**
	/**Need two copies of program's input line: one for each strtok.(because strtok changes it's input string)**/
	char Input_Line[MAX_INPUT_LINE] = { 0 };				// stores program's input line by line
	char Input_Line_Copy[MAX_INPUT_LINE] = { 0 };
	char delimiters[] = " \t\n";
	int Args_Num;											// number of arguments in current command
	char* Curr_Command_Index;								//	will hold the current command index
	char* Command_Arguments[MAX_ARG];						//	all command's arguments after strtok completed.
	int command_index;
	//int inner_loop = 1;
	PBf battlefield = NULL;

	//char szLine[MAX_LINE_SIZE];		//char* delimiters = " []\t\n";

	/* Command Proccessing */

	while (!ended) {												//program didnt end
		fgets(Input_Line, MAX_INPUT_LINE, stdin);					//scan next input line
		strcpy(Input_Line_Copy, Input_Line);						//making backup of input line (going to use strtok)
		Curr_Command_Index = strtok(Input_Line_Copy, delimiters);	//getting the index of current command - copied string Changed!
		Args_Num = 0;
		while (1) {
			Command_Arguments[Args_Num] = strtok(NULL, delimiters);
			if (Command_Arguments[Args_Num] == NULL) {
				Args_Num++;
				break;
			}
			Args_Num++;
		}
		
																	/**Cases according to command's index**/
		
		if (!strcmp(Curr_Command_Index, "Exit")) {
			if (battlefield == NULL)
				fprintf(stderr, "Error: No Battlefield\n");
			else
				Battlefield_Delete(battlefield);
			return;
		}
																	//C.1) index is "Exe" - need to execute all commands by current order
		else if (!strcmp(Curr_Command_Index, "Exe")) {
			if (battlefield == NULL)
				fprintf(stderr, "Error: No Battlefield\n");
			else
			{
				Set_Command(battlefield,Command_Sort(battlefield));
				PList currCommand = Get_Command(battlefield); 
				while (currCommand)
				{
					//TODO
				}
			}

		}
		else if (strlen(Curr_Command_Index) == 1) { //collect valid executions

			command_index = atoi(Curr_Command_Index);
			if (command_index == 0)	
				fprintf(stderr, "Error: Illegal Command\n");
			else
			{
				if ( ( (!strcmp(Command_Arguments[0], "Create_B")) && (Command_Arguments[1] == NULL) ||
					 (	() && () ) || ( () && () )
						 ) {//valid executions 
				
					if (battlefield == NULL) //battlefield yet created
						fprintf(stderr, "Error: No Battlefield\n");
					else
						Add_Command(battlefield, Command_Arguments, command_index); //Command_Arguments[0]
			}
				else 
					fprintf(stderr, "Error: Illegal Command\n");

			
		}
	}
}

	// Create_B -- battlefield = Battlefield_Create(Warzone_Clone_Func, Warzone_Destroy_Func, Warzone_Compare_Func, Warzone_Print_Func, Warzone_Get_Key_Function,
	//Command_Clone_Func, Command_Destroy_Func, Command_Compare_Func, Command_Get_Key_Function);
	//if (battlefield == NULL)
	//fprintf(stderr, "Houston, we have a problem\n"); //self-check (after creating)

	/*while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
		command = strtok(szLine, delimiters);
		
		//name1 = strtok(NULL, delimiters);
		//name2 = strtok(NULL, delimiters);

		

		else if (!strcmp("Exe", command))
			Network_print();

		else if (!strcmp("Insert", command)) {
			if (name1 == NULL) // if name1 = NULL also name2 = NULL
				fprintf(stderr, "Insert failed: not enough parameters\n");
			else {
				r = Network_addUser(name1, name2); // if name2 = null covered inside the function
				if (r == FAILURE)
				{
					if (name2 == NULL)
						fprintf(stderr, "Insert failed: not enough parameters\n");
					else
						fprintf(stderr, "Insert execution failed\n");
				}
			}
		}

		else if (!strcmp("Add", command)) {
			if (name1 == NULL || name2 == NULL)
				fprintf(stderr, "Add Relationship failed: not enough parameters\n");
			else {
				r = Network_addRelationship(name1, name2);
				if (r == FAILURE)
					fprintf(stderr, "Add Relationship execution failed\n");
			}
		}

		else if (!strcmp("Remove", command)) {
			if (name1 == NULL || name2 == NULL)
				fprintf(stderr, "Remove Relationship failed: not enough parameters\n");
			else {
				r = Network_removeRelationship(name1, name2);
				if (r == FAILURE)
					fprintf(stderr, "Remove Relationship execution failed\n");
			}
		}
		else
			fprintf(stderr, "Command not found\n");
	}

	Network_delete();*/
};
#include "defs.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"
#include "Squad.h"
//#include "Warzone.h"

#define MAX_LINE_SIZE 256


void main()
{
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " []\t\n";
	char* command;
	int num;

	/* Command List Construction */



	/* Command Proccessing */

	while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
		command = strtok(szLine, delimiters);
		if (strlen(command) == 1) {
			num = atoi(command);
			command = strtok(NULL, delimiters);
		}
}
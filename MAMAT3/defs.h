#ifndef _Defs_h
#define _Defs_h


/**includes & defines**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARG 10					// for main input line
#define MAX_INPUT_LINE 100			// for main input line
#define MAX_ID_LENGTH 5
#define MAX_POS_LENGTH 6
#define APC_MAX_SOLDIERS 6

#define MALLOC_ERR_MSG "Error: Cant perform Malloc\n"
#define ARG_ERR_MSG "Error: Function's Args Error\n"



typedef enum Result_ { FAILURE, SUCCESS } Result;


#endif

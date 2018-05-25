#ifndef _LIST_H_
#define _LIST_H_

/**Includes**/
#include "defs.h"


typedef struct Node_ Node, *PNode;
typedef struct List_ List, *PList;
typedef void* PElem;
typedef void* PKey;
typedef PElem(*CLONE_FUNC)(PElem);
typedef void(*DESTROY_FUNC)(PElem);
typedef bool(*COMPARE_KEYS_FUNC)(PKey, PKey);
typedef void(*PRINT_FUNC)(PElem);
typedef PKey(*GET_KEY_FUNC)(PElem);

PList List_Create(CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC, GET_KEY_FUNC); /*Creates a List ADT*/

void List_Delete(PList); /*Delete a List from Memory*/

void List_Print(PList); /*Prints Content of a List*/

Result List_Add_Elem(PList, PElem); /*Adds an Element to a List*/

Result List_Remove_Elem(PList, PKey); /*Removes Element corresponding to a key from List*/

PElem List_Get_First(PList); /*Returns 1st Element of the List*/

PElem List_Get_Next(PList); /*Returns next Element of the List, NULL if end of List*/

void List_Duplicate(PList, PList); /*Duplicates all Elements from Origin List to Empty Destination List*/

PElem List_Get_Elem(PList, PKey); /*Returns Element from List corresponding to Key, NULL if doesnt exist*/

#endif
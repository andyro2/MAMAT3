#include "Squad.h"
#include "Soldier.h"
#include "defs.h"
#include "List.h"
#include "APC.h"

struct Squad_ {
	PList Soldiers;
	PList APCs;
	int Count;
	char ID[MAX_ID_LENGTH];
};

PSquad Squad_Create(char* ID,
	CLONE_FUNC clone_func_sold, DESTROY_FUNC destroy_func_sold, COMPARE_KEYS_FUNC comp_keys_func_sold, PRINT_FUNC print_func_sold, GET_KEY_FUNC get_key_func_sold
	, CLONE_FUNC clone_func_apc, DESTROY_FUNC destroy_func_apc, COMPARE_KEYS_FUNC comp_keys_func_apc, PRINT_FUNC print_func_apc, GET_KEY_FUNC get_key_func_apc)
{
	PSquad s;
	if (ID == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if ((clone_func_sold == NULL) || (destroy_func_sold == NULL) || (comp_keys_func_sold == NULL) || (print_func_sold == NULL) || get_key_func_sold == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if ((clone_func_apc == NULL) || (destroy_func_apc == NULL) || (comp_keys_func_apc == NULL) || (print_func_apc == NULL) || get_key_func_apc == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	s = (PSquad)malloc(sizeof(Squad));
	if (s == NULL)
	{
		free(s);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	s->Soldiers = List_Create(clone_func_sold, destroy_func_sold, comp_keys_func_sold, print_func_sold, get_key_func_sold);
	s->APCs = List_Create(clone_func_apc, destroy_func_apc, comp_keys_func_apc, print_func_apc, get_key_func_apc);
	s->Count = 0;
	strcpy(s->ID, ID);
	return s;
}

void Squad_Delete(PSquad squad)
{
	if (squad == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	List_Delete(squad->Soldiers);
	List_Delete(squad->APCs);
	free(squad);
	return;
}

void Squad_Print(PSquad squad)
{
	if (squad == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	printf("Squad: %s , Total troops: %d\n", squad->ID, squad->Count);
	printf("APCs:\n");
	List_Print(squad->APCs);
	printf("Soldiers:\n");
	List_Print(squad->Soldiers);
}



PSquad Squad_Duplicate(PSquad Squad) {
	if (Squad == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	 // why not squad->Soldiers ???
	//PList Soldiers = Squad_Get_Soldiers(Squad);
	/*PList APCs = Squad_Get_APCs(Squad);
	PSquad New_Squad = Squad_Create(Squad->ID, List_Get_Clone_Func(Soldiers), List_Get_Des_Func(Soldiers), List_Get_Cmp_Func(Soldiers), List_Get_Print_Func(Soldiers),
		List_Get_Clone_Func(APCs), List_Get_Des_Func(APCs), List_Get_Cmp_Func(APCs), List_Get_Print_Func(APCs));*/ //why not soldiers->clone_func ??!?!?!?
	PList Soldiers = Squad->Soldiers;
	PList APCs = Squad->APCs;
	PSquad New_Squad = Squad_Create(Squad->ID,
		Soldier_Clone_Func, Soldier_Destroy_Func, Soldier_Compare_Func, Soldier_Print_Func, Soldier_Get_Key_Function,
		APC_Clone_Func, APC_Destroy_Func, APC_Compare_Func, APC_Print_Func, APC_Get_Key_Function);
	
	
	if (New_Squad == NULL) {
		return NULL;
	}
	List_Duplicate(Squad->APCs, New_Squad->APCs);
	List_Duplicate(Squad->Soldiers, New_Squad->Soldiers);
	New_Squad->Count = Squad->Count;
	return New_Squad;
}

Result Squad_Add_Soldier(PSquad squad, char* pos, char* ID)
{
	if (squad == NULL || pos == NULL || ID == NULL)
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	//PList sol = List_Create(Soldier_Clone_Func, Soldier_Destroy_Func, Soldier_Compare_Func, Soldier_Print_Func, Soldier_Get_Key_Function);
	soldier* s = Soldier_Create(ID, pos);//TODO needs to be done without soldier struct (? or not ? ) 
	return List_Add_Elem(squad->Soldiers, s);
}

Result Squad_Add_APC(PSquad squad, char* ID)
{
	if (squad == NULL || ID == NULL)
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	APC* a = APC_Create(ID);//TODO needs to be done without APC struct (? or not ? ) 
	return List_Add_Elem(squad->APCs, a);
}

Result Squad_Insert_Sold_APC(PSquad squad, char* sol_ID, char* apc_ID)
{
	if (squad == NULL || sol_ID == NULL || apc_ID == NULL)
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	APC* a = (APC*)List_Get_Elem(squad->APCs, apc_ID);
	soldier* s = (soldier*)List_Get_Elem(squad->Soldiers, sol_ID);
	if (s == NULL || a == NULL)
		return FAILURE;

	return APC_Insert_Soldier(a, s);
}

Result Squad_APC_Pop(PSquad squad, char* apc_ID)
{
	if (squad == NULL || apc_ID == NULL)
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	APC* a = (APC*)List_Get_Elem(squad->APCs, apc_ID);
	soldier* s = APC_Pop(a);
	if (s == NULL)
		return FAILURE;
	return SUCCESS;
}

Result Squad_Delete_Soldier(PSquad squad, char* sol_ID)
{
	if (squad == NULL || sol_ID == NULL)
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	soldier* s = (soldier*)List_Get_Elem(squad->Soldiers, sol_ID);

}

Result Squad_Delete_APC(PSquad squad, char* apc_ID)
{
	return;
}






/*User fuctions*/

void Squad_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)Data);
}





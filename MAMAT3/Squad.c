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

PSquad Squad_Create()

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


void Squad_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)Data);
}

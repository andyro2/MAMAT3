#include "Squad.h"

struct Squad {
	PList Soldiers;
	PList APCs;
	int Count;
	char ID[MAX_ID_LENGTH];
};

PSquad Squad_Duplicate(PSquad Squad) {
	if (Squad == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PList Soldiers = Squad_Get_Soldiers(Squad);
	PList APCs = Squad_Get_APCs(Squad);
	PSquad New_Squad = Squad_Create(Squad->ID, List_Get_Clone_Func(Soldiers), List_Get_Des_Func(Soldiers), List_Get_Cmp_Func(Soldiers), List_Get_Print_Func(Soldiers),
												List_Get_Clone_Func(APCs), List_Get_Des_Func(APCs), List_Get_Cmp_Func(APCs), List_Get_Print_Func(APCs));
	if (New_Squad == NULL) {
		return NULL;
	}
	List_Duplicate(Squad->APCs, New_Squad->APCs);
	List_Duplicate(Squad->Soldiers, New_Squad->Soldiers);
	New_Squad->Count = Squad->Count;
	return New_Squad;
}


/**User Functions**/
void Squad_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)Data);
}





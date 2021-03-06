#include "APC.h"
#include "Soldier.h"
#include "defs.h"

struct APC_ {
	soldier* soldiers[APC_MAX_SOLDIERS];
	char ID[MAX_ID_LENGTH];
	int soldiers_num;
};

APC* APC_Create(char* ID)
{
	APC* apc;
	if (!APC_Valid_ID(ID))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	apc = (APC*)malloc(sizeof(APC));
	if (apc == NULL) {
		free(apc);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(apc->ID, ID);
	apc->soldiers_num = 0;
	return apc;
}

void APC_Delete(APC* apc)
{
	if (apc == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	for (int i=0; i < apc->soldiers_num; i++)
		Soldier_Delete(apc->soldiers[i]);
	free(apc);
	return;
}


void APC_Print(APC* apc) {
	if (apc == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}

	printf("%s , Occupancy: %d/%d\n", apc->ID, apc->soldiers_num, APC_MAX_SOLDIERS);
	if (apc->soldiers_num > 0) {
		for (int i = 0; i < apc->soldiers_num; i++) {
			printf("Seat %d: ", i + 1);
			Soldier_Print(apc->soldiers[i]);
		}
	}
}

APC* APC_Duplicate(APC* apc)
{
	APC* new_apc;
	if (apc == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	new_apc = APC_Create(apc->ID);
	for (int i = 0; i < apc->soldiers_num; i++) {
		new_apc->soldiers[i] = Soldier_Duplicate(apc->soldiers[i]);
		new_apc->soldiers_num++;
	}
	return new_apc;
}

Result APC_Insert_Soldier(APC* apc, soldier* sold)
{
	if (apc == NULL || sold == NULL)
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	if (apc->soldiers_num < APC_MAX_SOLDIERS)
	{
		apc->soldiers[apc->soldiers_num] = sold; 
		apc->soldiers_num++;
		return SUCCESS;
	}
	
	printf("Error: APC is Full\n");
	return FAILURE;
}

soldier* APC_Pop(APC* apc)
{
	if (apc == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	soldier* sold;
	if (apc->soldiers_num != 0)
	{
		sold = apc->soldiers[apc->soldiers_num - 1];
		apc->soldiers_num--;
		return sold;
	}
	printf("Error: APC is Empty\n");
	return NULL;
}

soldier* APC_Get_Sold(APC* apc, char* sol_ID)
{
	if (apc == NULL || sol_ID == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	for (int i = 0; i < apc->soldiers_num; i++) {
		if (!strcmp(Soldier_Get_ID(apc->soldiers[i]), sol_ID))
			return apc->soldiers[i];
	}
	return NULL;
}

int Get_Num_Soldiers(APC* a) {
	if (a == NULL) {
		printf(ARG_ERR_MSG);
		return -1;
	}
	return a->soldiers_num;
}

bool APC_Valid_ID(char* ID) {
	if (ID == NULL || ID[0] != 'A'|| strlen(ID + 1) > LENGTH_OF_NUMS)
		return false;
	return true;
}

char* APC_Get_ID(APC* a)
{
	if (a == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return a->ID;
}

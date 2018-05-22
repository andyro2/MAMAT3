#include "APC.h"


void APC_Print(PAPC APC) {
	if (APC == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , Occupancy: %d/%d\n", APC->ID, APC->Stack_Top, APC_MAX_Soldiers);
	if (APC->Stack_Top > 0) {
		for (int i = 0; i < APC->Stack_Top; i++) {
			printf("Seat %d: ", i + 1);
			Soldier_Print(APC->Soldiers[i]);
		}
	}
}








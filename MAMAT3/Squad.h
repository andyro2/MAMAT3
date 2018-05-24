#ifndef  _SQUAD_H
#define _SQUAD_H

/**Includes**/
#include "defs.h"

typedef struct Squad_ Squad , *PSquad;
PSquad Squad_Duplicate(PSquad);
void Squad_Print_Func(PElem);

#endif 

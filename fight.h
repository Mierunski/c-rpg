#ifndef FIGHT_H_INCLUDED
#define FIGHT_H_INCLUDED

#include "fight.c"
#include "structures.h"
#include "console.h"

double przeliczDef(int obrona);

void walka(struct Postac *bohater, struct potwor *potwor, CHAR_INFO buforTekstu[]);

#endif // FIGHT_H_INCLUDED

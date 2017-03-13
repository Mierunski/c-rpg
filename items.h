#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#include "console.h"

struct przedmiot* wczytajPrzedmioty(int* liczba);

struct przedmiot losujPrzedmiot(int ilosc, struct przedmiot lista[], int reg);

#endif // ITEMS_H_INCLUDED

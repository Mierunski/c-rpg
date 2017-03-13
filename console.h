#include <windows.h> /* for HANDLE type, and console functions */
#include <stdio.h> /* standard input/output */
#include <stdlib.h> /* included for rand */
#include <string.h>
#include "structures.h"

// Odczytanie bufera wejscia
DWORD getInput(INPUT_RECORD **eventBuffer);

// Centruje napis w wierszu
void centruj(char napis[], char wynik[], int width);

// Przelicza region
char * region(int x);

// Tworzy linie
void linia(char wynik[]);

// Przygotowuje okno
void initializeHUD(int width, int height);

// Pobiera imie
void initializeHero(struct Postac *bohater, CHAR_INFO buforTekstu[]);

// Wyswietla nazwe
void displayName(int width, int height);

// Wyswietla linie tekstu
void displayTextline(char napis[], CHAR_INFO consoleBuffer[], int atrybut);

// Wyswietla gracza
void displayHud(struct Postac *gracz);

// Wyswietla menu
void displayMenu(CHAR_INFO consoleBuffer[]);

// Menu podrozy
void podroz(CHAR_INFO consoleBuffer[], int x);

// Wybor opcji
int wybor(CHAR_INFO consoleBuffer[], int ilosc);

// Wyswietla potwora
void displayMonster(struct potwor *x);

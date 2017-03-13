#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED



// struktura potwora
struct potwor
{

    char nick[35];
    int poziom, HP, cHP, atk, def, exp, pozycja;

};

struct przedmiot
{
    char nazwa[35];
    int stat, typ, poziom;
};

// Struktura Postaci
struct Postac
{
    int poziom, cHP, HP, atk, def, exp, wiek, nextLvl, pozycja;
    char nick[20];
    struct przedmiot sword, shield, armor, helmet;

};

// Lista Kolorow
enum kolory {darkblue = 1, green, teal, darkred, purple, darkyellow, normal, grey, blue, lightgreen, lightblue, red, pink, yellow, white};

// Lista Przedmiotow
enum przedmioty {miecz = 1, tarcza, zbroja, helm};


#endif // STRUCTURES_H_INCLUDED

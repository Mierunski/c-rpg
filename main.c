#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "console.h"
#include "monsters.h"
#include "structures.h"
#include "fight.h"
#include "items.h"





// Funkcja glowna
int main(void)
{
    // Stworzenie i zdeklarowanie struktury postaci
    struct Postac bohater;
    bohater.atk = 10;
    bohater.cHP = 150;
    bohater.poziom = 1;
    bohater.def = 10;
    bohater.exp = 0;
    bohater.HP = 150;
    bohater.wiek = 0;
    bohater.nextLvl = 100;
    bohater.pozycja = 1;
    bohater.helmet.stat = 0;
    bohater.armor.stat = 0;
    bohater.sword.stat = 0;
    bohater.shield.stat = 0;
    struct Postac *boh = &bohater;


    // Zmienna do ró¿nych pêtli
    int i, statPoziom = 1;

    // Zmienne wyboru

    int wyborI, x;

    // Bufory do wyswietlania linii
    char buforLini[70], buforLini2[70];

    // Ustawienie konsoli
    const int width = 70, height = 35;
    initializeHUD(width, height);

    // Stworzenie bufora tekstowego
    CHAR_INFO buforTekstu[width*26];
    for(i = 0; i < width*26; i++)
    {
        buforTekstu[i].Char.AsciiChar = ' ';
        buforTekstu[i].Attributes = 15;
    }
    // Wypisanie nazwy
    displayName(width, height);

    // Wczytanie potworów
    int iloscPotworow, iloscPrzedmiotow = 2;
    struct potwor *listaPotworow = wczytaj(&iloscPotworow);
    struct potwor potwor;
    struct potwor *pot = &potwor;

    // Wczytanie przedmiotow
    struct przedmiot *listaPrzedmiotow = wczytajPrzedmioty(&iloscPrzedmiotow);
    struct przedmiot item;

    sprintf(buforLini, "Wczytano %d potworow i %d przedmiotow", iloscPotworow, iloscPrzedmiotow);
    displayTextline(buforLini, buforTekstu, white);
    // Przekazanie seeda dla rand()
    srand(time(0));

    // Ustawienie nazwy postaci
    initializeHero(boh, buforTekstu);
    displayTextline("1. Miasto", buforTekstu, red);
    displayTextline("Budzisz sie w miescie, a raczej w tym co z niego zostalo,", buforTekstu, white);
    displayTextline("wszedzie walaja sie dopalajace szczatki budowli, a takze", buforTekstu, white);
    displayTextline("ludzkie ciala, zeruja na nich ogromne szczury, wygladajace jakby", buforTekstu, white);
    displayTextline("pochodzily prosto z piekla, przy bramach miasta widzisz ", buforTekstu, white);
    displayTextline("bojowe trole, jedyna droga wyjscia beda podziemia.", buforTekstu, white);
    displayTextline("Nie pamietasz co sie wydarzylo, wiesz tylko ze musisz", buforTekstu, white);
    displayTextline("stac sie silniejszy, zeby udalo Ci sie przezyc...", buforTekstu, white);
    displayTextline("", buforTekstu, lightgreen);
    displayTextline("Uzyj strzalek do poruszania sie po menu i enter aby zatwierdzic.", buforTekstu, lightgreen);
    // Petla glowna
    while(bohater.cHP > 0)
    {
        bohater.wiek++;
        displayHud(boh);
        displayMenu(buforTekstu);
        wyborI = wybor(buforTekstu, 4);

        switch(wyborI)
        {
        // Walka
        case 1:
            if(bohater.pozycja == 7)
            {
                int termin = 1;
                displayTextline("Dajesz sygnal do ataku!", buforTekstu, red);
                displayTextline("Po wejsciu do jaskini rozpoczela sie istna rzez.", buforTekstu, white);
                displayTextline("W ciagu pieciu pierwszych minut zginelo 90% wojownikow", buforTekstu, white);
                displayTextline("Podczas gdy szeregi demonow zdawaly sie nie miec konca.", buforTekstu, white);
                displayTextline("Ostatnia nadzieja byl szturm w kierunku ich przywodcy.", buforTekstu, white);
                Sleep(10000);
                displayTextline("Zostales sam. Wszyscy inni zgineli.", buforTekstu, white);
                Sleep(3500);
                displayTextline("Stoisz sam twarza w twarz z wladca demonow.", buforTekstu, white);
                Sleep(3500);
                displayTextline("To Twoj starosta, czerpiacy energie z innych studentow", buforTekstu, red);
                displayTextline("zeby zdac najblizsza sesje.", buforTekstu, red);
                Sleep(3500);
                displayTextline("Tylko pokonanie go odwroci zaklecie i uratuje wszystkich.", buforTekstu, white);
                Sleep(3500);
                displayTextline("Z gniewem na twarzy ruszasz do walki!", buforTekstu, red);
                Sleep(10000);

                pot = losujPotwora(iloscPotworow, listaPotworow, bohater.pozycja);
                walka(boh, pot, buforTekstu);
                if(bohater.cHP <= 0 && termin == 1)
                {
                    termin++;
                    Sleep(5000);
                    displayTextline("\"To nie moze sie tak skonczyc\"", buforTekstu, lightblue);
                    Sleep(3500);
                    displayTextline("\"Nie po to przebylem cala ta droge\"", buforTekstu, lightblue);
                    Sleep(3500);
                    displayTextline("\"Zeby polec na samym jej koncu\"", buforTekstu, lightblue);
                    Sleep(3500);
                    displayTextline("\"Widze inna droge.\"", buforTekstu, lightblue);
                    Sleep(3500);
                    displayTextline("\"To jeszcze nie koniec!\"", buforTekstu, lightblue);
                    Sleep(3500);
                    displayTextline("Czujesz w sobie rosnaca sile", buforTekstu, lightgreen);
                    Sleep(3500);
                    displayTextline("To sila drugiego terminu!", buforTekstu, lightgreen);
                    Sleep(7000);
                    bohater.HP += 800;
                    bohater.atk += 80;
                    bohater.def += 80;
                    bohater.cHP = bohater.HP;
                    walka(boh, pot, buforTekstu);
                }
                if(bohater.cHP > 0)
                {
                    sprintf(buforLini, "Gratulacje! Pokonales swojego staroste!");
                    centruj(buforLini, buforLini2, 68);
                    displayTextline(buforLini2, buforTekstu, yellow);
                    sprintf(buforLini, "Teraz wszystko powrocilo do normy!");
                    centruj(buforLini, buforLini2, 68);
                    displayTextline(buforLini2, buforTekstu, yellow);
                    sprintf(buforLini, "A takze zdales sesje!");
                    centruj(buforLini, buforLini2, 68);
                    displayTextline(buforLini2, buforTekstu, yellow);
                    sprintf(buforLini, "Czego nie mozna powiedziec o Twoim staroscie...");
                    centruj(buforLini, buforLini2, 68);
                    displayTextline(buforLini2, buforTekstu, white);
                    bohater.cHP = -1;
                    bohater.nextLvl = 9999999;
                }
            }
            else
            {
                displayTextline("Wybrales walke!", buforTekstu, white);
                pot = losujPotwora(iloscPotworow, listaPotworow, bohater.pozycja);
                walka(boh, pot, buforTekstu);
                free(pot);
                if(bohater.cHP > 0)
                {
                    item = losujPrzedmiot(iloscPrzedmiotow, listaPrzedmiotow, bohater.pozycja);
                    switch(item.typ)
                    {
                    case miecz:
                        if(item.stat > bohater.sword.stat)
                        {
                            bohater.sword = item;
                            sprintf(buforLini, "Znalazles bron: %s o bonusie +%d", item.nazwa, item.stat);
                            displayTextline(buforLini, buforTekstu, green);
                        }
                        break;
                    case tarcza:
                        if(item.stat > bohater.shield.stat)
                        {
                            bohater.shield = item;
                            sprintf(buforLini, "Znalazles tarcze: %s o bonusie +%d", item.nazwa, item.stat);
                            displayTextline(buforLini, buforTekstu, green);
                        }
                        break;
                    case zbroja:
                        if(item.stat > bohater.armor.stat)
                        {
                            bohater.armor = item;
                            sprintf(buforLini, "Znalazles opancerzenie: %s o bonusie +%d", item.nazwa, item.stat);
                            displayTextline(buforLini, buforTekstu, green);
                        }
                        break;
                    case helm:
                        if(item.stat > bohater.helmet.stat)
                        {
                            bohater.helmet = item;
                            sprintf(buforLini, "Znalazles helm: %s o bonusie +%d", item.nazwa, item.stat);
                            displayTextline(buforLini, buforTekstu, green);
                        }
                        break;
                    }
                }
            }
            break;
        // Odpoczynek
        case 2:

            displayTextline("Odpoczywasz... Twoje zdrowie wraca do normy", buforTekstu, green);
            bohater.cHP = bohater.HP;

            break;

        case 3:

            podroz(buforTekstu, bohater.pozycja);

            if(bohater.pozycja < 7)
            {
                x = wybor(buforTekstu, 2);
                if(x == 3)
                {
                    displayTextline("Pozostajesz na miejscu.", buforTekstu, white);

                }
                else if(x == 4)
                {
                    bohater.pozycja++;
                    if(bohater.pozycja != 7)
                    {
                        pot = losujPotwora(iloscPotworow, listaPotworow, bohater.pozycja);
                        walka(boh, pot, buforTekstu);
                        free(pot);
                    }
                    switch(bohater.pozycja)
                    {
                    case 2:
                        displayTextline("2. Podziemia", buforTekstu, red);
                        displayTextline("Otaczaja Cie ciemnosci, zaczynasz zastanawiac sie czy", buforTekstu, white);
                        displayTextline("nie latwiej byloby przekrasc sie kolo troli, widzisz", buforTekstu, white);
                        displayTextline("ze nie tylko Ty wybrales te droge ucieczki z miasta", buforTekstu, white);
                        displayTextline("moze uda Ci sie znalezc lepszy ekwipunek. Twoj umysl", buforTekstu, white);
                        displayTextline("powoli zaczyna sie rozjasniac, moze uda Ci sie zrozumiec", buforTekstu, white);
                        displayTextline("dlaczego sie tu znalazles, ale najpierw musisz wyjsc z", buforTekstu, white);
                        displayTextline("tych cholernych tuneli...", buforTekstu, white);
                        break;
                    case 3:
                        displayTextline("3. Pola", buforTekstu, red);
                        displayTextline("Nareszcie swiatlo. Widzisz ze ludzie rozdzielili sie", buforTekstu, white);
                        displayTextline("na 2 grupy, jedna poszla w kierunku morza, prawdopodobnie", buforTekstu, white);
                        displayTextline("proboja sie ewakuowac, druga wydeptana sciezka wiedzie", buforTekstu, white);
                        displayTextline("w kierunku lasu, widzisz przy niej martwego zbrojnego", buforTekstu, white);
                        displayTextline("juz bez ekwipunku. Wszedzie biegaja rozszalale zwierzeta.", buforTekstu, white);
                        displayTextline("Moze w lesie uda Ci sie znalezc jakies odpowiedzi?", buforTekstu, white);
                        break;
                    case 4:
                        displayTextline("4. Lasy", buforTekstu, red);
                        displayTextline("Zwierzeta lesne takze zostaly dotkniete spaczeniem", buforTekstu, white);
                        displayTextline("atakuja Cie na sam widok, jest tu wiecej trupow zolnierzy", buforTekstu, white);
                        displayTextline("i duzo przydatnego ekwipunku, teren staje sie bardziej stromy", buforTekstu, white);
                        displayTextline("czujesz ze zblizasz sie do swojego celu.", buforTekstu, white);
                        break;
                    case 5:
                        displayTextline("5. Wzgorza", buforTekstu, red);
                        displayTextline("Przed soba widzisz rozlegly obszar, byle pole walki", buforTekstu, white);
                        displayTextline("na zwlokach zywia sie demoniczne pomioty, i piekielne", buforTekstu, white);
                        displayTextline("ogary. Chyba juz wiesz kto za tym wszystkim stoi...", buforTekstu, white);
                        displayTextline("W oddali widzisz gory, napewno musi sie tam ukrywac", buforTekstu, white);
                        displayTextline("ale najpierw musze poszukac lepszego wyposazenia...", buforTekstu, white);
                        break;
                    case 6:
                        displayTextline("6. Gory", buforTekstu, red);
                        displayTextline("Hordy demonów i trolli rozlegaja sie po calym terenie", buforTekstu, white);
                        displayTextline("w oddali widzisz ogniska, wygladajace na jakis oboz.", buforTekstu, white);
                        displayTextline("Przeczucie graniczace z pewnoscia podpowiada Ci ze", buforTekstu, white);
                        displayTextline("to ostatnie Twoje kroki przed ostatecznym starciem...", buforTekstu, white);
                        break;
                    case 7:
                        displayTextline("7. Siedlisko Potwora", buforTekstu, red);
                        displayTextline("Dotarles do obozu, widzisz tu resztki ocalalych", buforTekstu, white);
                        displayTextline("czekajacych przed wejsciem do jaskini, po krotkiej", buforTekstu, white);
                        displayTextline("rozmowie dowiadujesz sie ze demon odpowiadajacy za", buforTekstu, white);
                        displayTextline("to wszystko znajduje sie wlasnie w niej.", buforTekstu, white);
                        displayTextline("Nikt nie wie kim on jest.", buforTekstu, white);
                        displayTextline("Nikt oprocz Ciebie.", buforTekstu, white);
                        displayTextline("Wszyscy czekaja na Twoj znak aby przystapic do ataku...", buforTekstu, white);
                        break;
                    }

                }
            }
            else if (bohater.pozycja == 7)
            {
                displayTextline("Teraz nie mozesz juz sie wycofac...", buforTekstu, red);

            }
            else
            {
                displayTextline("Pozostajesz na miejscu.", buforTekstu, white);
            }


            break;

        // Zakonczenie gry
        case 4:
            bohater.cHP = -1;
            break;

        // Brak wyboru
        default:
            bohater.wiek--;
            break;
        }
        if(bohater.exp >= bohater.nextLvl)
        {
            centruj("++ Zdobywasz kolejny poziom!! ++", buforLini, 68);
            displayTextline(buforLini, buforTekstu, yellow);
            sprintf(buforLini, "Poziom: %d -> %d", bohater.poziom, bohater.poziom + 1);
            displayTextline(buforLini, buforTekstu, white);
            bohater.poziom++;
            sprintf(buforLini, "HP:     %d -> %d", bohater.HP, bohater.HP + 5*statPoziom);
            displayTextline(buforLini, buforTekstu, white);
            bohater.HP += 5*statPoziom;
            bohater.cHP = bohater.HP;
            sprintf(buforLini, "Atak:   %d -> %d", bohater.atk, bohater.atk + statPoziom);
            displayTextline(buforLini, buforTekstu, white);
            bohater.atk += statPoziom;
            sprintf(buforLini, "Obrona: %d -> %d", bohater.def, bohater.def + statPoziom);
            displayTextline(buforLini, buforTekstu, white);
            bohater.def += statPoziom;
            sprintf(buforLini, "Nastepny poziom za %d", bohater.nextLvl*2);
            displayTextline(buforLini, buforTekstu, white);
            for(i = 0; i < 68; i++) buforLini[i] = '=';
            displayTextline(buforLini, buforTekstu, yellow);
            bohater.exp = bohater.exp - bohater.nextLvl;
            bohater.nextLvl *=2;
            statPoziom++;

        }

    }

    sprintf(buforLini, "%s!", bohater.nick);
    centruj(buforLini, buforLini2, 68);
    displayTextline(buforLini2, buforTekstu, yellow);
    sprintf(buforLini, "Ukonczyles gre na poziomie %d z %d pkt doswiadczenia.", bohater.poziom, bohater.exp);
    centruj(buforLini, buforLini2, 68);
    displayTextline(buforLini2, buforTekstu, yellow);
    sprintf(buforLini, "Przezyles %d dni.", bohater.wiek);
    centruj(buforLini, buforLini2, 68);
    displayTextline(buforLini2, buforTekstu, yellow);
    sprintf(buforLini, "Dziekuje za gre!");
    centruj(buforLini, buforLini2, 68);
    displayTextline(buforLini2, buforTekstu, yellow);
    gets(buforLini);
    free(listaPotworow);
    free(listaPrzedmiotow);

    return 0;

}

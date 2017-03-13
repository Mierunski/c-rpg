#include "console.h"

HANDLE wHnd; /* write (output) handle */
HANDLE rHnd; /* read (input handle */

/* Read console input buffer and return malloc'd INPUT_RECORD array */
DWORD getInput(INPUT_RECORD **eventBuffer)
{
    /* Variable for holding the number of current events, and a point to it */
    DWORD numEvents = 0;

    /* Variable for holding how many events were read */
    DWORD numEventsRead = 0;

    /* Put the number of console input events into numEvents */
    GetNumberOfConsoleInputEvents(rHnd, &numEvents);

    if (numEvents) /* if there's an event */
    {
        /* Allocate the correct amount of memory to store the events */
        *eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);

        /* Place the stored events into the eventBuffer pointer */
        ReadConsoleInput(rHnd, *eventBuffer, numEvents, &numEventsRead);
    }

    /* Return the amount of events successfully read */
    return numEventsRead;
}

void centruj(char napis[], char wynik[], int width)
{
    int lenght = strlen(napis);
    int spaces = width - lenght;
    spaces = spaces / 2;
    //printf("Start/n");
    int i = 0, x = 0;
    for(x = 0; x < width; x++)
    {
        if(x < spaces) wynik[x] = ' ';
        if(x < spaces+lenght && x >= spaces)
        {
            wynik[x] = napis[i];
            i++;
        }
        if(x >= lenght+spaces) wynik[x] = ' ';
        //printf("%s%d", wynik, x);

    }
    if(spaces%2 == 1) wynik[width-1] = ' ';
}

char * region(int x)
{
    char * reg = malloc(20*(sizeof(char)));
    switch(x)
    {
    case 1:
        strcpy(reg, "Miasto");
        break;
    case 2:
        strcpy(reg, "Podziemia");
        break;
    case 3:
        strcpy(reg, "Pola");
        break;
    case 4:
        strcpy(reg, "Lasy");
        break;
    case 5:
        strcpy(reg, "Wzgorza");
        break;
    case 6:
        strcpy(reg, "Gory");
        break;
    case 7:
        strcpy(reg, "Siedlisko Potwora");
        break;
    }
    return reg;
}

void linia(char wynik[])
{
    printf("9");
    int width = 70;
    int i = 0;
    printf("4");
    for(i = 0; i < width; i++)
    {
        wynik[i] = '=';
    }
    wynik[0] = '+';
    wynik[width - 1] = '+';
    printf("5");
}

void initializeHUD(int width, int height)
{
    /* Window size coordinates, be sure to start index at zero! */
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};

    /* A COORD struct for specificying the console's screen buffer dimensions */
    COORD bufferSize = {width, height};

    /* initialize handles */
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    /* Set the console's title */
    SetConsoleTitle("Sashir cRPG v0.2");

    /* Set the screen's buffer size */
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    /* Set the window size */
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);



}

// Pobiera imie
void initializeHero(struct Postac *bohater, CHAR_INFO con[])
{
    char buforLini[70], wyborC[20];

    displayTextline("Jakie jest Twe imie wedrowcze?", con, white);
    while(1)
    {
        gets(bohater->nick);
        sprintf(buforLini, "Jestes pewien ze nazywasz sie: %s? (T/N)", bohater->nick);
        displayTextline(buforLini, con, white);
        gets(wyborC);

        if(strcmp(wyborC, "T") != 1) break;
        else displayTextline("Wiec jak sie nazywasz?", con, white);
    }
    sprintf(buforLini, "Witaj %s! Czeka Cie tu wiele przygod!", bohater->nick);
    displayTextline(buforLini, con, white);
    DWORD numEventsRead = 0;
    INPUT_RECORD *eventBuffer;
    do
    {
        numEventsRead = getInput(&eventBuffer);
        free(eventBuffer);
    }
    while(numEventsRead);
}

void displayName(int width, int height)
{
    /* Setting up different variables for passing to WriteConsoleOutput */
    COORD characterBufferSize = {width, height};
    COORD characterPosition = {0, 0};
    SMALL_RECT consoleWriteArea = {0, 0, width - 1, height - 1};

    char name[width];
    centruj("Sashir cRPG v0.05", name, width);

    char lineczka[width];
    linia(lineczka);

    CHAR_INFO consoleBuffer[width*height];

    int i;
    for(i = 0; i < width*height; i++)
    {
        consoleBuffer[i].Char.AsciiChar = ' ';
        consoleBuffer[i].Attributes = red;
    }
    for(i = 0; i < height; i++)
    {
        consoleBuffer[i*width].Char.AsciiChar = '|';

        consoleBuffer[(i+1)*width - 1].Char.AsciiChar = '|';
    }
    for(i = 3; i < 7; i++) consoleBuffer[i*width+34].Char.AsciiChar = '|';
    for(i = 0; i < width; i++)
    {
        consoleBuffer[i].Char.AsciiChar = lineczka[i];
        consoleBuffer[i+width].Char.AsciiChar = name[i];
        consoleBuffer[i+2*width].Char.AsciiChar = lineczka[i];
        consoleBuffer[i+7*width].Char.AsciiChar = lineczka[i];
        consoleBuffer[i+(height-1)*width].Char.AsciiChar = lineczka[i];
    }
    consoleBuffer[width].Char.AsciiChar = '|';
    consoleBuffer[2*width - 1].Char.AsciiChar = '|';
    consoleBuffer[2*width+34].Char.AsciiChar = '+';
    consoleBuffer[7*width+34].Char.AsciiChar = '+';
    WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

// Wyswietla linie tekstu w glownym polu
void displayTextline(char napis[], CHAR_INFO consoleBuffer[], int atrybut)
{
    // Zmienne potrzebne do wypisywania
    int x, y, WIDTH = 68, HEIGHT = 26;
    COORD characterBufferSize = {WIDTH, HEIGHT};
    COORD characterPosition = {0, 0};
    SMALL_RECT consoleWriteArea = {1, 8, WIDTH, 33};
    char wrzut[WIDTH];
    for(x = 0; x < WIDTH; x++) wrzut[x] = ' ';

    for(x = 0; x < strlen(napis); x++) wrzut[x] = napis[x];


    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < (HEIGHT - 1); y++)
        {
            consoleBuffer[x + WIDTH * y].Char.AsciiChar = consoleBuffer[x + WIDTH * (y + 1)].Char.AsciiChar;
            consoleBuffer[x + WIDTH * y].Attributes = consoleBuffer[x + WIDTH * (y + 1)].Attributes;
        }

        consoleBuffer[x + WIDTH * (HEIGHT-2)].Char.AsciiChar = wrzut[x];
        consoleBuffer[x + WIDTH * (HEIGHT-2)].Attributes = atrybut;
        consoleBuffer[x + WIDTH * (HEIGHT-1)].Char.AsciiChar = ' ';
        consoleBuffer[x + WIDTH * (HEIGHT-1)].Attributes = 15;
    }
    COORD cursorPosition = {1, 33};
    WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
    SetConsoleCursorPosition(wHnd, cursorPosition);

}

// Wyswietla informacje o graczu
void displayHud(struct Postac *gracz)
{
    // Zmienne potrzebne do wypisywania
    int x, width = 34;
    COORD characterBufferSize = {width, 4};
    COORD characterPosition = {0, 0};
    SMALL_RECT consoleWriteArea = {1, 3, width, 7};
    char wrzut[width];
    char * reg;
    reg = region(gracz->pozycja);

    CHAR_INFO consoleBuffer[width*4];

    for(x = 0; x < width*4; x++)
    {
        consoleBuffer[x].Char.AsciiChar = ' ';
        consoleBuffer[x].Attributes = lightblue;
    }
    for(x = 0; x < width; x++) wrzut[x] = ' ';


    sprintf(wrzut, "%s Dzien %d %s", gracz->nick, gracz->wiek, reg);
    for(x = 0; x < width; x++)
    {
        consoleBuffer[x+0*width].Char.AsciiChar = wrzut[x];
        wrzut[x] = ' ';
    }
    sprintf(wrzut, "Poziom = %d, HP = %d/%d", gracz->poziom, gracz->cHP, gracz->HP);
    for(x = 0; x < width; x++)
    {
        consoleBuffer[x+1*width].Char.AsciiChar = wrzut[x];
        wrzut[x] = ' ';
    }
    sprintf(wrzut, "Atak = %d+%d, Obrona = %d+%d", gracz->atk, gracz->sword.stat, gracz->def, (gracz->shield.stat + gracz->helmet.stat + gracz->armor.stat));
    for(x = 0; x < width; x++)
    {
        consoleBuffer[x+2*width].Char.AsciiChar = wrzut[x];
        wrzut[x] = ' ';
    }
    sprintf(wrzut, "Doswiadczenie = %d/%d", gracz->exp, gracz->nextLvl);
    for(x = 0; x < width; x++)
    {
        consoleBuffer[x+3*width].Char.AsciiChar = wrzut[x];
        wrzut[x] = ' ';
    }
    for(x = 0; x < 4; x++)
    {
        consoleBuffer[(x+1)*width - 1].Char.AsciiChar = '|';
        consoleBuffer[(x+1)*width - 1].Attributes = red;
    }

    WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

// Wyswietla menu
void displayMenu(CHAR_INFO consoleBuffer[])
{

    displayTextline("Co robisz?", consoleBuffer, green);
    displayTextline("1. Walka", consoleBuffer, white);
    displayTextline("2. Odpoczynek", consoleBuffer, white);
    displayTextline("3. Podroz", consoleBuffer, white);
    displayTextline("4. Wyjscie", consoleBuffer, white);
    DWORD numEventsRead = 0;
    INPUT_RECORD *eventBuffer;
    do
    {
        numEventsRead = getInput(&eventBuffer);
        free(eventBuffer);
    }
    while(numEventsRead);
}

// Menu podrozy
void podroz(CHAR_INFO consoleBuffer[], int x)
{
    char bufor[35];

    displayTextline("Gdzie sie udajesz?", consoleBuffer, green);
    sprintf(bufor, "%d. Pozostan w %s", x, region(x));
    displayTextline(bufor, consoleBuffer, white);
    if(x < 7)
    {
        sprintf(bufor, "%d. %s", x+1, region(x+1));
        displayTextline(bufor, consoleBuffer, white);
    }
}

// Wybor opcji
int wybor(CHAR_INFO consoleBuffer[], int ilosc)
{
    int WIDTH = 68, HEIGHT = 26;
    COORD characterBufferSize = {WIDTH, HEIGHT};
    COORD characterPosition = {0, 0};
    SMALL_RECT consoleWriteArea = {1, 8, WIDTH, 33};
    DWORD numEventsRead = 0;
    INPUT_RECORD *eventBuffer;
    int i, j, write = 1, aktualnywybor = (ilosc - 1), dalej = 1;

    for(j = 0; j < WIDTH; j++) consoleBuffer[j+(WIDTH*((HEIGHT-aktualnywybor)-2))].Attributes = yellow;

    /**/
    while(dalej)
    {
        /* Get the input and number of events successfully obtained */
        numEventsRead = getInput(&eventBuffer);

        /* if more than 0 are read */
        if (numEventsRead)
        {
            /* loop through the amount of records */
            for (i = 0; i < numEventsRead; i++)
            {
                /* check each event */
                if (eventBuffer[i].EventType == KEY_EVENT)
                {
                    switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
                    {
                    // Nacisniecie strzalki w gore
                    case VK_UP:
                        // Tylko przy opuszczaniu klawisza
                        if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0 && aktualnywybor < (ilosc - 1))
                        {
                            for(j = 0; j < WIDTH; j++) consoleBuffer[j+(WIDTH*(HEIGHT-2-aktualnywybor))].Attributes = white;
                            aktualnywybor++;
                            for(j = 0; j < WIDTH; j++) consoleBuffer[j+(WIDTH*(HEIGHT-2-aktualnywybor))].Attributes = yellow;
                            /* Update screen this loop pass */
                            write = 1;
                        }
                        break;
                    // Nacisniecie strzalki w dol
                    case VK_DOWN:
                        // Tylko przy opuczszaniu klawisza
                        if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0 && aktualnywybor > 0)
                        {

                            for(j = 0; j < WIDTH; j++) consoleBuffer[j+(WIDTH*(HEIGHT-aktualnywybor-2))].Attributes = white;
                            aktualnywybor--;
                            for(j = 0; j < WIDTH; j++) consoleBuffer[j+(WIDTH*(HEIGHT-aktualnywybor-2))].Attributes = yellow;
                            /* Update screen this loop pass */
                            write = 1;
                        }
                        break;
                    case VK_RETURN:
                        if (eventBuffer[i].Event.KeyEvent.bKeyDown == 0) dalej = 0;
                        break;
                    }


                }
            }
            /* Delete your used INPUT_RECORD array */
            free(eventBuffer);
        }

        /* If write is 1, meaning the screen needs to be updated */
        if (write)
        {
            /* Write our character buffer (a single dimensional array) to the console buffer */
            WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
            write = 0;
        }
    }
    aktualnywybor++;
    aktualnywybor = 5 - aktualnywybor;
    return aktualnywybor;

}

// Wyswietla informacje o potworze
void displayMonster(struct potwor *x)
{
    int i;
    const int width = 34;
    COORD characterBufferSize = {width, 4};
    COORD characterPosition = {0, 0};
    SMALL_RECT consoleWriteArea = {35, 3, 68, 7};
    char wrzut[width], buf[width];
    CHAR_INFO consoleBuffer[width*4];

    for(i = 0; i < width*4; i++)
    {
        consoleBuffer[i].Char.AsciiChar = ' ';
        consoleBuffer[i].Attributes = purple;
    }

    for(i = 0; i < width; i++)
    {
        wrzut[i] = ' ';
        buf[i] = ' ';
    }
    sprintf(wrzut, "%s", x->nick);
    centruj(wrzut, buf, width);
    for(i = 0; i < width; i++)
    {
        consoleBuffer[i+0*width].Char.AsciiChar = buf[i];
        wrzut[i] = ' ';
        buf[i] = ' ';
    }
    sprintf(wrzut, "Poziom = %d, HP = %d/%d", x->poziom, x->cHP, x->HP);
    centruj(wrzut, buf, width);
    for(i = 0; i < width; i++)
    {
        consoleBuffer[i+1*width].Char.AsciiChar = buf[i];
        wrzut[i] = ' ';
        buf[i] = ' ';
    }
    sprintf(wrzut, "Atak = %d, Obrona = %d", x->atk, x->def);
    centruj(wrzut, buf, width);
    for(i = 0; i < width; i++)
    {
        consoleBuffer[i+2*width].Char.AsciiChar = buf[i];
        wrzut[i] = ' ';
        buf[i] = ' ';
    }
    sprintf(wrzut, "Nagroda %d pkt dos", x->exp);
    centruj(wrzut, buf, width);
    for(i = 0; i < width; i++)
    {
        consoleBuffer[i+3*width].Char.AsciiChar = buf[i];
        wrzut[i] = ' ';
        buf[i] = ' ';
    }

    WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}






#include "fight.h"


// Liczy redukcje przez pancerz
double przeliczDef(int obrona)
{
    const double stala = 0.03; // Sta³a pancerza

    double pancerz = (obrona*stala)/(1+(obrona*stala));

    pancerz = 1 - pancerz;

    return pancerz;
}

void walka(struct Postac *bohater, struct potwor *potwor, CHAR_INFO buforTekstu[])
{
    char buforLini[70];
    double defGracz = przeliczDef(bohater->def+bohater->helmet.stat+bohater->shield.stat+bohater->armor.stat);
    double defPotwor  = przeliczDef(potwor->def);
    int dmg;
    int szansaAtk;

    displayMonster(potwor);

    // Petla walki
    while(bohater->cHP > 0 && potwor->cHP > 0)
    {

        {
            // Tura Gracza
            szansaAtk = rand()%((bohater->atk+1)+bohater->sword.stat);
            if (szansaAtk == 0)
            {
                dmg = 0;
                sprintf(buforLini, "Atakuje %s! Pudlo!", bohater->nick);
                displayTextline(buforLini, buforTekstu, grey);

            }
            else if (szansaAtk == (bohater->atk+bohater->sword.stat))
            {
                dmg = szansaAtk*2*defPotwor;
                sprintf(buforLini, "Atakuje %s... Krytyczne trafienie!", bohater->nick);
                displayTextline(buforLini, buforTekstu, green);
            }
            else
            {
                dmg = szansaAtk*defPotwor;
                sprintf(buforLini, "Atakuje %s... Trafienie!", bohater->nick);
                displayTextline(buforLini, buforTekstu, lightgreen);
            }

            potwor->cHP -= dmg;
            displayMonster(potwor);
            if(potwor->cHP <= 0)
            {
                sprintf(buforLini, "%s umiera!", potwor->nick);
                displayTextline(buforLini, buforTekstu, lightgreen);
                sprintf(buforLini, "%s wygrywa walke i zdobywa %d pkt doswiadczenia!", bohater->nick, potwor->exp);
                displayTextline(buforLini, buforTekstu, lightgreen);
                bohater->exp += potwor->exp;
                break;
            }
            else
            {
                sprintf(buforLini, "%s otrzymuje %d obrazen.", potwor->nick, dmg);
                displayTextline(buforLini, buforTekstu, white);
            }
            Sleep(200);
        }

        {
            // Tura Potwora
            szansaAtk = rand()%(potwor->atk+1);
            if (szansaAtk == 0)
            {
                dmg = 0;
                sprintf(buforLini, "Atakuje %s! Pudlo!", potwor->nick);
                displayTextline(buforLini, buforTekstu, grey);

            }
            else if (szansaAtk == potwor->atk)
            {
                dmg = szansaAtk*2*defGracz;
                sprintf(buforLini, "Atakuje %s... Krytyczne trafienie!", potwor->nick);
                displayTextline(buforLini, buforTekstu, darkred);
            }
            else
            {
                dmg = szansaAtk*defGracz;
                sprintf(buforLini, "Atakuje %s... Trafienie!", potwor->nick);
                displayTextline(buforLini, buforTekstu, red);
            }

            bohater->cHP -= dmg;
            displayHud(bohater);
            if(bohater->cHP <= 0)
            {
                sprintf(buforLini, "%s umiera! Przegrales...", bohater->nick);
                displayTextline(buforLini, buforTekstu, white);
                break;
            }
            else
            {
                sprintf(buforLini, "%s otrzymuje %d obrazen.", bohater->nick, dmg);
                displayTextline(buforLini, buforTekstu, white);
            }
            Sleep(200);
        }
    }
}

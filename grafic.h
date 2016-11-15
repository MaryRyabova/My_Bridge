#ifndef GRAFIC_H
#define GRAFIC_H

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>

#include"logic.h"

namespace BridgGame
{
    

    typedef unsigned char UCHAR;

#define HORISONTAL 45u
#define VERTICAL 179u
#define TOP_REV_CONER 191u
#define BUTTOM_CONNER 192u
#define BGRAUND 176u
#define BUTTOM_REV_CONNER 217u
#define TOP_CONER 218u

    enum eKeys
    {
        ENTER = 13,
        ESC = 27,
        UP = 72,
        LEFT = 75,
        RIGHT = 77,
        DOWN = 80
    };

    struct sCardInfo
    {
        char lear;
        char range;
        COORD rUpConer;
    };


    void drawCard( SHORT x, SHORT y, char lear, char range );
    sCardInfo strValue( SHORT x, SHORT y, char lear, char range );
    void drawVerticalCard( SHORT x, SHORT y );
    void drawYourDeck( sCardInfo *currentPlDeck, SHORT x, SHORT y, char lear, char range );
    void drawVerticalDeck( SHORT x, SHORT y );
    void wipeCard( sCardInfo *currentCrd );
    void selectCard( sCardInfo *currentCrd, SHORT startX, SHORT startY, SHORT centX, SHORT centY );
    //void selectCard( sCardInfo *currentCrd );
    void drawPlDeck( sCardInfo *currentPlDeck );
    void wipeDeck( SHORT x, SHORT y );
    //void sCardInfoPl( SHORT x, SHORT y, sPlayer &curentPl, sCardInfo *plInfo );
}
#endif GRAFIC_H

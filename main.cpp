#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#include"logic.h"
#include"grafic.h"

#define ESC 27
using namespace BridgGame;


sPlayer plOne, plTwo, plThree, plFour;
sCardInfo *infOne, *infTwo, *infThree, *infFour;

HANDLE hStdOutMain = GetStdHandle( STD_OUTPUT_HANDLE );


void sCardInfoPl( SHORT x, SHORT y, sPlayer &curentPl, sCardInfo *plInfo )
{
    sDeck *Cards = &curentPl.myDeck;

    char learList[] = { 3, 4, 5, 6 };
    std::string Range[] = { "2", "3", "4", "5", "6", "7" , "8", "9", "10", "J", "Q", "A", "T" };

    int learIndx[13];
    int rangeIndx[13];

    for ( int i = 0; i < 13; i++ )
    {
        sCard card = Cards->cards[i];

        learIndx[i] = card.lear;
        rangeIndx[i] = card.rank;
    }

    for ( int i = 0; i < 13; i++ )
    {
        
        plInfo[i] = strValue( x, y, learList[learIndx[i]], *Range[rangeIndx[i]].c_str() );
        x += 2;
    }

  
    
}


int main()
{
    eSequence plSeq = FIRST_PL;
    int seq = FIRST_PL;
    sDeck mainDeck = getRandomDeck();
    infOne = new sCardInfo[13];
    infTwo = new sCardInfo[13];
    infThree = new sCardInfo[13];
    infFour = new sCardInfo[13];


    getPlayerDeck( mainDeck, plOne );
    getPlayerDeck( mainDeck, plTwo );
    getPlayerDeck( mainDeck, plThree );
    getPlayerDeck( mainDeck, plFour );
 
    sCardInfoPl( 25, 15, plOne, infOne );
    sCardInfoPl(0, 0, plTwo, infTwo );
    sCardInfoPl( 25, 2, plThree, infThree );
    sCardInfoPl( 0, 0, plFour, infFour );

    drawPlDeck( infOne );
    drawVerticalDeck( 12, 3 ); // for sec pl
    drawPlDeck( infThree );
    drawVerticalDeck( 60, 3 ); //for fourt pl


    selectCard( infOne, 25, 14, 37, 10 );

    //switch ( seq )
    //{
    //case BridgGame::FIRST_PL:
    //{
    //    selectCard( infOne, 25, 14, 35, 10 );
    //    seq++;
    //}
    //    break;

    //case BridgGame::SECOND_PL:
    //{
    //    drawCard( 20, 5, infTwo[0].lear, infTwo[0].range );
    //}
    //    break;
    //case BridgGame::THIRD_PL:
    //    break;
    //case BridgGame::FOURTH_PL:
    //    break;
    //default:
    //    break;
    //}



    delete []infOne;
    delete []infTwo;
    delete []infThree;
    delete []infFour;


    SetConsoleCursorPosition( hStdOutMain, { 1, 20 } );
    system( "pause" );
    return 0;
}







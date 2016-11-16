#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>

#include"grafic.h"

namespace BridgGame
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

    void drawCard( SHORT x, SHORT y, char lear, char range )
    {

        COORD myCoord = { x, y };



        std::cout.fill( HORISONTAL );
        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (UCHAR) TOP_CONER << std::setw( 2 ) << (UCHAR) TOP_REV_CONER;
        myCoord.Y++;
        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (UCHAR) VERTICAL << lear << (UCHAR) VERTICAL;
        myCoord.Y++;
        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (UCHAR) VERTICAL << range << (UCHAR) VERTICAL;
        myCoord.Y++;
        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (UCHAR) BUTTOM_CONNER << std::setw( 2 ) << (UCHAR) BUTTOM_REV_CONNER;
    }

    sCardInfo strValue( SHORT x, SHORT y, char lear, char range )
    {
        sCardInfo currentInf;

        currentInf.rUpConer = { x, y };
        currentInf.lear = lear;
        currentInf.range = range;

        return currentInf;
    }

    void drawVerticalCard( SHORT x, SHORT y )
    {
        COORD myCoord = { x, y };
        std::cout.fill( HORISONTAL );

        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (char) TOP_CONER << std::setw( 4 ) << (char) TOP_REV_CONER;
        myCoord.Y++;
        std::cout.fill( '+' );
        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (char) VERTICAL << std::setw( 4 ) << (char) VERTICAL;
        std::cout.fill( HORISONTAL );
        myCoord.Y++;
        SetConsoleCursorPosition( hStdOut, myCoord );
        std::cout << (char) BUTTOM_CONNER << std::setw( 4 ) << (char) BUTTOM_REV_CONNER;

    }


    void drawYourDeck( sCardInfo *currentPlDeck, SHORT x, SHORT y, char lear, char range )
    {
        for ( int i = 0; i < 13; i++ )
        {

            drawCard( x, y, lear, range );
            currentPlDeck[i] = strValue( x, y, lear, range );
            x += 2;
        }
    }

    void drawVerticalDeck( SHORT x, SHORT y )
    {
        for ( int i = 0; i < 13; i++ )
        {
            drawVerticalCard( x, y );
            y++;
        }
    }

    void wipeCard( sCardInfo *currentCrd )
    {

        currentCrd->rUpConer.Y--;
        for ( int i = 0; i < 6; i++ )
        {
            SetConsoleCursorPosition( hStdOut, currentCrd->rUpConer );
            std::cout << "   ";
            currentCrd->rUpConer.Y++;
        }

        currentCrd->rUpConer.Y = currentCrd->rUpConer.Y - 5;
    }

    void wipeDeck( SHORT x, SHORT y )
    {
        COORD funcCoord = { x, y };
        for ( int i = 0; i < 6; i++ )
        {
            SetConsoleCursorPosition( hStdOut, { x, y } );
            std::cout << "                             ";
            y++;
        }
    }


    void selectCard( sCardInfo *currentCrd, SHORT startX, SHORT startY, SHORT centX, SHORT centY )
    {
        int iKey = 67;
        int mSelectedCard = 0;
        size_t usedCard = 0;
        SetConsoleCursorPosition( hStdOut, { startX, startY } /*(currentCrd + 0)->rUpConer*/ );
        int  initPos = ( currentCrd + 0 )->rUpConer.X -2; //для отрисовки колоды карт после выбора одной карты


        while ( 1 )
        {
            if ( mSelectedCard != -1 )
            {
                wipeDeck( startX, startY );

                for ( int i = 0; i < 13; i++ )
                {
                    if ( i != mSelectedCard )
                    {
                        drawCard( ( currentCrd + i )->rUpConer.X, ( currentCrd + i )->rUpConer.Y, ( currentCrd + i )->lear, ( currentCrd + i )->range );
                    }
                    else
                    {
                        drawCard( ( currentCrd + mSelectedCard )->rUpConer.X, ( currentCrd + mSelectedCard )->rUpConer.Y - 1, ( currentCrd + mSelectedCard )->lear, ( currentCrd + mSelectedCard )->range );
                    }

                }
            }

            iKey = _getch();
         
            switch ( iKey )
            {
            case LEFT:
            {
                if ( mSelectedCard > -1 )
                {
                    mSelectedCard--;
                    if ( mSelectedCard == -1 )
                    {
                        mSelectedCard = 13 - 1;
                    }
                }
                break;
            }

            case RIGHT:
            {
                if ( mSelectedCard < 13 )
                {
                    mSelectedCard++;
                    if ( mSelectedCard == 13 )
                    {
                        mSelectedCard = 0;
                    }
                }
                break;
            }

            case ENTER:
                {
                    usedCard++;
                    drawCard( centX, centY, ( currentCrd + mSelectedCard )->lear, ( currentCrd + mSelectedCard )->range ); //отрисовка выбраной карты

                    wipeDeck( startX, startY );
                    for ( int i = 0; i < 13 - usedCard; i++ )
                    {
                        if ( i != mSelectedCard )
                        {
                            drawCard(initPos+2, ( currentCrd + i )->rUpConer.Y - 1, ( currentCrd + i )->lear, ( currentCrd + i )->range );
                            initPos += 2;

                        }
                    }
                    

                    break;
                }

            } 
        }

       
    }


        void printInfo( sCardInfo *currentPlDeck )
        {
            for ( int i = 0; i < 14; i++ )
            {
                std::cout << ( currentPlDeck + i )->rUpConer.X << " " << ( currentPlDeck + i )->rUpConer.Y << " " << ( currentPlDeck + i )->range << " " << ( currentPlDeck + i )->lear;
                std::cout << std::endl;
            }

        }

        void drawPlDeck( sCardInfo *currentPlDeck )
        {
            for ( int i = 0; i < 13; i++ )
            {

                drawCard( currentPlDeck[i].rUpConer.X, currentPlDeck[i].rUpConer.Y, currentPlDeck[i].lear, currentPlDeck[i].range );
                currentPlDeck[i].rUpConer.X += 2;
            }
        }
  }




//int main()
//{
//    
//    sCardInfo *currentPlDeck1 = new sCardInfo[13];
//    sCardInfo *currentPlDeck2 = new sCardInfo[13];
//
//   drawVerticalDeck( 10, 3 );
//   drawVerticalDeck( 60, 3 );
//
//
//   drawYourDeck( currentPlDeck2, 25, 3, '1', '2' );
//   drawYourDeck( currentPlDeck1, 25, 15, '1', '2');
//
//   selectCard( currentPlDeck2 );
//
//
//    delete[]currentPlDeck1;
//    delete[]currentPlDeck2;
//
//    SetConsoleCursorPosition( hStdOut, { 0, 15 } );
//    system( "pause" );
//    return 0;
//}



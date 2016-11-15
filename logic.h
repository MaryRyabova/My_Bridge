#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <ctime>
#include <conio.h>
#include <map>

#include"grafic.h"

namespace BridgGame
{
    enum eSequence
    {
        FIRST_PL = 0,
        SECOND_PL,
        THIRD_PL,
        FOURTH_PL
    };

    enum eLear
    {
        CLUBS = 0,
        DIAMOND,
        HEARTS,
        SPADES
    };

    enum eRank
    {
        TWO = 0,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        LADY,
        KING,
        ACE
    };
    //**********************************
    struct sCard
    {
        eLear lear;
        eRank rank;
    };

    struct sDeck
    {
        sCard* cards;
        unsigned int count; //сколько эл. в массиве

        sDeck()
            : count( 0 )
            , cards( nullptr )
        {}

        ~sDeck()
        {

        }
    };

    struct sPlayer
    {
        char name[15];
        int yourMove;
        sDeck myDeck;

    };


    void outputDeck( sDeck* deck );
    sDeck getFullDeck();
    int* getRandomIndex();
    sDeck getRandomDeck();
    void deleteCard( sDeck* oldDeck, int delIndex );
    void sortDeck( sDeck* src );
    void addCard( sDeck* oldDeck, sCard newCard );
    bool addCardWithoutDubl( sDeck* currentDeck, sCard newCard );
    void removeCardsByIndexs( sDeck* oldDeck, int indexses[], int size );
    void removeFromToInd( sDeck* deck, int startInd, int stopInd );
    void addCards( sDeck* dst, sCard* src, unsigned int size );
    void copyPartOfCards( sDeck* src, sDeck* dst, int startPos, unsigned int count );
    void cutCards( sDeck* src, sDeck* dst, int startPos, unsigned int count );
   // void plGetDeck( sDeck mainDeck, sPlayer player );
    void getPlayerDeck( sDeck &mainDeck, sPlayer &curentPl );
    //void sCardInfoPl( SHORT x, SHORT y, sPlayer &curentPl, sCardInfo *plInfo );

}
#endif LOGIC_H
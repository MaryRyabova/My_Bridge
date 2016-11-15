#include"logic.h"
//*************************************
namespace BridgGame
{


    //Определяет соответствие енамов с привычными нам символами 
    void outputDeck( sDeck* deck )
    {
        char learList[] = { 3, 4, 5, 6 };
        std::string Range[] = { "2", "3", "4", "5", "6", "7" , "8", "9", "10", "J", "Q", "A", "T" };

        for ( int i = 0 ; i < deck->count ; ++i )
        {
            if ( i && !( i % 13 ) )
            {
                std::cout << std::endl;
            }

            sCard card = deck->cards[i];
            std::cout << learList[card.lear] << Range[card.rank].c_str() << " ";
        }
    }

    //Формирование последовательной колоды карт 
    sDeck getFullDeck()
    {
        sDeck result;

        result.count = 52;
        result.cards = new sCard[result.count];


        for ( int i = 0 ; i < result.count ; ++i )
        {
            result.cards[i].lear = static_cast<eLear>( i / 13 );
            result.cards[i].rank = static_cast<eRank>( i % 13 );
        }

        return result;
    }
    //Формирование массива рандомных чисел
    int* getRandomIndex()
    {

        const int sizeAllDeck = 52;

        int* indexMas = new int[sizeAllDeck];

        int index;

        for ( int i = 0; i < sizeAllDeck; i++ )
        {
            index = rand() % sizeAllDeck;
            indexMas[i] = index;

            for ( int j = 0; j < i; j++ )
            {
                if ( indexMas[i] == indexMas[j] )
                {
                    index = rand() % sizeAllDeck;
                    indexMas[i] = index;
                    j = -1;
                }
            }
        }

        return indexMas;
    }
    //Создание колоды карт не по порядку
    sDeck getRandomDeck()
    {
        int* mas = getRandomIndex();
        sDeck result;

        result.count = 52;
        result.cards = new sCard[result.count];


        for ( int i = 0 ; i < result.count ; ++i )
        {
            result.cards[i].lear = static_cast<eLear>( mas[i] / 13 );
            result.cards[i].rank = static_cast<eRank>( mas[i] % 13 );
        }

        return result;

    }
    //Удалить одну выбранную карту
    void deleteCard( sDeck* oldDeck, int delIndex )
    {
        sCard* newCards = nullptr;
        unsigned int newCount = 0;

        if ( oldDeck->count > 1 )
        {
            newCount = oldDeck->count - 1;
            newCards = new sCard[newCount];

            for ( int i = 0, j = 0; i < oldDeck->count; i++ )
            {
                if ( i != delIndex )
                {
                    newCards[j] = oldDeck->cards[i];
                    j++;
                }

            }
        }

        if ( oldDeck->cards )
        {
            delete[] oldDeck->cards;
        }

        oldDeck->cards = newCards;
        oldDeck->count = newCount;
    }

    //Cортировка колоді по убыванию
    void sortDeck( sDeck* src )
    {
        sCard temp;
        for ( int i = 1; i < src->count - 1; i++ )
        {
            for ( int j = 0; j < src->count - i; j++ )
            {
                if ( src->cards[j].lear < src->cards[j + 1].lear || ( src->cards[j].lear == src->cards[j + 1].lear && src->cards[j].rank < src->cards[j + 1].rank ) )
                {
                    temp = src->cards[j];
                    src->cards[j] = src->cards[j + 1];
                    src->cards[j + 1] = temp;
                }
            }
        }
    }

    //Добавление одной карты
    void addCard( sDeck* oldDeck, sCard newCard )
    {
        unsigned int newCount = oldDeck->count + 1;
        sCard* newCards = new sCard[oldDeck->count];

        for ( int i = 0; i < oldDeck->count; i++ )
        {

            newCards[i] = oldDeck->cards[i];
        }

        newCards[newCount - 1] = newCard;

        if ( oldDeck->cards )
        {
            delete[] oldDeck->cards;
        }

        oldDeck->cards = newCards ;
        oldDeck->count = newCount;
    }

    //добавление без дублей
    bool addCardWithoutDubl( sDeck* currentDeck, sCard newCard )
    {
        bool ifAdd = true;
        for ( int i = 0; i < currentDeck->count; i++ )
        {
            if ( currentDeck->cards[i].lear == newCard.lear && currentDeck->cards[i].rank == newCard.rank )
                ifAdd = false;
        }

        if ( ifAdd )
        {
            addCard( currentDeck, newCard );
        }

        return ifAdd;

    }
    //удаление карт по индексам
    void removeCardsByIndexs( sDeck* oldDeck, int indexses[], int size )
    {

        sCard* newCards = nullptr;
        unsigned int newCount = 0;


        if ( oldDeck->count > size + 1 )
        {
            newCount = oldDeck->count - size;
            newCards = new sCard[newCount];

            for ( int i = 0, j = 0; i < oldDeck->count; i++ )
            {
                bool isRemove = true;
                for ( int k = 0; k < size; k++ )
                {
                    if ( i == indexses[k] )
                    {
                        isRemove = false;
                        break;
                    }
                }

                if ( isRemove )
                {
                    newCards[j] = oldDeck->cards[i];
                    j++;
                }
            }
        }

        if ( oldDeck->cards )
        {
            delete[] oldDeck->cards;
        }

        oldDeck->cards = newCards;
        oldDeck->count = newCount;


    }


    //удаление карт в дипазоне
    void removeFromToInd( sDeck* deck, int startInd, int stopInd )
    {


        const unsigned int masSize = ( stopInd - startInd ) + 1;
        int* masive = new int[masSize + 1];
        masive[0] = startInd;

        for ( int i = 1; i < masSize; i++ )
        {
            masive[i] = ++startInd;
        }

        removeCardsByIndexs( deck, masive, masSize );

        delete[] masive;
    }

    //добавить несколько карт
    void addCards( sDeck* dst, sCard* src, unsigned int size )
    {
        unsigned int newCount = dst->count + size;
        sCard* newCards = new sCard[newCount];

        for ( int i = 0; i < dst->count; i++ )
        {

            newCards[i] = dst->cards[i];
        }

        for ( int i = dst->count; i < newCount; i++ )
        {

            newCards[i] = *src++;
        }

        if ( dst->cards )
        {
            delete[] dst->cards;
        }

        dst->cards = newCards ;
        dst->count = newCount;

    }


    //Скопировать часть карт
    void copyPartOfCards( sDeck* src, sDeck* dst, int startPos, unsigned int count = 1 )
    {
        if ( !dst->cards  )
        {
            dst->count = count;
            dst->cards = new sCard[count];

            unsigned int j = 0;
            for ( int i = startPos; i < startPos + count; i++ )
            {
                if ( j != count )
                {
                    dst->cards[j] = src->cards[i];

                }

                j++;
            }
        }

        else if ( dst != nullptr )
        {
            unsigned int newCount = dst->count + count;
            sCard* newCards = new sCard[newCount];

            for ( int i = 0; i < dst->count; i++ )
            {

                newCards[i] = dst->cards[i];
            }

            unsigned int j = dst->count;
            for ( int i = startPos; i < startPos + count; i++ )
            {
                if ( j != newCount )
                {
                    newCards[j] = src->cards[i];

                }

                j++;
            }

            if ( dst->cards )
            {
                delete[] dst->cards;
                dst = 0;
            }

            dst->cards = newCards;
            dst->count = newCount;

        }
        else
        {
            std::cout << "Null ptr";
        }


    }

    //Вырезать часть карт
    void cutCards( sDeck* src, sDeck* dst, int startPos, unsigned int count = 1 )
    {
        copyPartOfCards( src, dst, startPos, count );
        removeFromToInd( src, startPos, ( startPos + count ) - 1 );

    }




    void getPlayerDeck( sDeck &mainDeck, sPlayer &curentPl )
    {
        cutCards( &mainDeck, &curentPl.myDeck, 0, 13 );
        sortDeck( &curentPl.myDeck );
    }

  
}


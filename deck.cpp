//deck.cpp
//Luis Vazquez 4/17/20.
//EE312 Prog 06: GO FISH

#include <ctime>
#include "deck.h"

Deck::Deck()
{
    for(int i=0; i<=3; i++){        //suit
        for(int j=1;j<=13;j++){     //rank
            myCards[i*13+j-1] = Card(j, static_cast<Card::Suit>(i));
        }
    }

    myIndex = 0;

    unsigned int currentTime = (unsigned) time(0);
    srand(currentTime);
}

void Deck::shuffle()
{
    int numSwaps = 5*SIZE;
    for(int i=0;i <numSwaps;i++){
        long offset1 = (rand()%SIZE);
        long offset2 = (rand()%SIZE);
        Card temp = Card(myCards[offset1].getRank(), myCards[offset1].getSuit());
        myCards[offset1]=myCards[offset2];
        myCards[offset2]=Card(temp.getRank(), temp.getSuit());          //MIGHT REACH END OF SCOPE NOT VIABLE
    }



}

Card Deck::dealCard()
{
    if(myIndex<52) {
        Card temp= myCards[myIndex];
        myIndex++;
        return temp;
    } else {
        cout << "All Cards Dealt - deck empty" << endl;
    }
}

int Deck::size() const
{
    return (SIZE-myIndex);
}

int Deck::getIndex()
{
    return myIndex;
}
//
string Deck::showDeck()
{
    string temp="";
    for (int i=0; i<SIZE; i++)
        temp = temp + myCards[i].toString() + " ";

    return temp;
}


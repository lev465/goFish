//card.cpp
//Luis Vazquez on 4/17/20.
//EE312 Go Fish

#include <iostream>
#include <string>
#include "card.h"
using namespace std;

Card::Card()
{
    myRank=1;
    mySuit=spades;
}

Card::Card(int rank, Card::Suit s) {
    if (rank > 0 && rank < 14)
        myRank = rank;

    else{
        myRank = 1;
        cout << "Invalid rank - rank set to A"<< endl;
    }

    if ( s >= 0 && s <= 3)
        mySuit = s;

    else{
        mySuit = spades;
        cout << "Invalid suit - suit set to s"<<endl;
    }
}

string Card::toString() const
{
    return (this->rankString(this->myRank))+(this->suitString(this->mySuit));
}

bool Card::sameSuitAs(const Card& c) const
{
    return (this->mySuit) == (c.mySuit);
}

int  Card::getRank() const
{
    return myRank;
}

Card::Suit Card::getSuit() const
{
    return mySuit;
}

string Card::suitString(Suit s)      const  // return "s", "h",...
{
    string suitStr;
    switch(s) {
        case spades:
            suitStr = "s";
            break;

        case hearts:
            suitStr = "h";
            break;

        case diamonds:
            suitStr = "d";
            break;

        case clubs:
            suitStr = "c";
            break;
    }

    return suitStr;
    }

string Card::rankString(int r)       const  // return "A", "2", ..."Q"
{
    if(r == 1)
        return "A";

    else if ((r > 1) && (r < 11))
        return to_string(r);

    else if(r == 11)
        return "J";

    else if (r == 12)
        return "Q";

    else
        return "K";
}

bool Card::operator == (const Card& rhs) const
{
    return ((myRank == rhs.myRank) && (mySuit == rhs.mySuit));
}

bool Card::operator != (const Card& rhs) const
{
    return ((myRank != rhs.myRank) && (mySuit != rhs.mySuit));
}


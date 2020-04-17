//
// Created by Luis Vazquez Delgado on 4/14/20.
//

#include "player.h"

void Player::addCard(Card c)
{
    myHand.push_back(c);
}

void Player::bookCards(Card c1, Card c2)
{
    myBook.push_back(c1);
    myBook.push_back(c2);
    removeCardFromHand(c1);
    removeCardFromHand(c2);
}

bool Player::checkHandForBook(Card &c1, Card &c2)
{
    for(int i=0; i<myHand.size()-1;i++){
        for (int j=i+1; j<myHand.size();j++){
            if(myHand[i].getRank()==myHand[j].getRank()){
                c1=myHand[i];
                c2=myHand[j];
                return true;
            }
        }
    }
    return false;
}

Card Player::chooseCardFromHand() const
{
    unsigned long randomCard = (rand()%myHand.size());
    for(int i=0; i < myHand.size(); i++) {
        if (myHand[randomCard].getRank() == myHand[i].getRank()){
            randomCard = (rand()%myHand.size());
        }
    }
    return myHand[randomCard];
}

bool Player::cardInHand(Card c) const
{
    for(int i=0; i < myHand.size(); i++){
        if (myHand[i]==c)
            return true;
    }
    return false;
}

Card Player::removeCardFromHand(Card c)
{
    for (int i = 0; i < myHand.size(); i++) {
        if (myHand[i].getRank()== c.getRank()) {
            Card temp = myHand[i];
            myHand.erase(myHand.begin() + i);
            return temp;                                    //MIGHT NOT WORK , SCOPE MIGHT END TEMP
        }
    }
}

string Player::showHand() const {
    string temp;
    for (int i=0; i<myHand.size(); i++){
        temp= temp+myHand[i].toString()+ " ";
    }
    return temp;
}

string Player::showBooks() const
{
    string temp = "";
    for(int i=0; i < myBook.size(); i++){
        temp = temp + myBook[i].toString() + " ";
    }
    return temp;
}

int Player::getHandSize() const
{
    return myHand.size();
}

int Player::getBookSize() const
{
    return myBook.size();
}

bool Player::sameRankInHand(Card c) const
{
    for(int i=0; i < myHand.size(); i++){
        if (myHand[i].getRank()==c.getRank())
            return true;
    }
    return false;
}




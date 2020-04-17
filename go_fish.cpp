// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include <string>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
void addPlayer(vector<Player> &players, string playerName);
void goFish(Deck &d, Player &p);
int sumBooks(vector<Player> players);

int main( )
{
    vector<Player> players;
    int numCards;           //7 cards given to each player for 2-player game


    ofstream oFile;
    oFile.open("goFish_results.txt");
    oFile << "Output test!!!" << endl;

    addPlayer(players,"Joe");
    addPlayer(players, "Jane");

    if(players.size()==2)
        numCards=7;
    else if (players.size()>2)
        numCards=5;
    else {
        oFile << "not enough players - minimum 2 players" << endl;
        return -1; //FAILURE
    }

    Deck d;  //create a deck of cards
//    cout<<d.showDeck()<<" \n"<< d.size()<<endl;
    d.shuffle();

    for(int i=0; i<players.size(); i++) {
        dealHand(d, players[i], numCards);
        cout << players[i].getName() << " has : " << players[i].showHand() << endl;
    }
//    cout << d.showDeck()<<"\n" << d.size() << endl;

    while(sumBooks(players)!=52) {
        Card temp1, temp2;

        for(int i=0; i<players.size(); i++){
            bool hasPair = false;
            if(players[i].getHandSize()!=0)
                hasPair = players[i].checkHandForBook(temp1, temp2);


            while (hasPair) {
                players[i].bookCards(temp1, temp2);
                oFile << players[i].getName() << " books a pair of " << temp1.rankString(temp1.getRank()) << endl;
                cout << players[i].getName() << " books a pair of " << temp1.rankString(temp1.getRank()) << endl;
                if(players[i].getHandSize()!=0)
                    hasPair = players[i].checkHandForBook(temp1, temp2);
                else
                    hasPair = false;
            }

            //if(players[i].getHandSize()!=0){           //did player book anything this round?
                unsigned long randomplayer =(rand()%players.size());

                if(randomplayer==i)
                    randomplayer=(i+1)%players.size();

                if(players[i].getHandSize()!=0) {
                    Card currentCard = players[i].chooseCardFromHand();

                    if (players[randomplayer].sameRankInHand(currentCard)) {
                        players[i].addCard(players[randomplayer].removeCardFromHand(currentCard));
                        hasPair = players[i].checkHandForBook(temp1, temp2);

                        if (hasPair) {
                            players[i].bookCards(temp1, temp2);
                            oFile << players[i].getName() << " books a pair of " << temp1.rankString(temp1.getRank())
                                  << endl;
                            cout << players[i].getName() << " books a pair of " << temp1.rankString(temp1.getRank())
                                 << endl;
                        }
                        if (players[i].getHandSize() == 0) {
                            if (d.size() != 0) {
                                players[i].addCard(d.dealCard());   //gofish
                                oFile << players[i].getName() << " books a pair of "
                                      << temp1.rankString(temp1.getRank())
                                      << endl;
                                cout << players[i].getName() << " books a pair of " << temp1.rankString(temp1.getRank())
                                     << endl;
                            }
                        }
                    } else {
                        if (d.size() != 0) {
                            players[i].addCard(d.dealCard());
                        }
                    }
                }
                else {
                    if (d.size() != 0) {
                        players[i].addCard(d.dealCard());
                    }
                }
            //}
        }
    }

    oFile.close();

    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

void addPlayer(vector<Player> &players,string playerName)
{
    players.emplace_back(playerName);
}
void goFish(Deck &d, Player &p)
{

}

int sumBooks(vector<Player> players)
{
    int sum=0;
    for (int i = 0; i<players.size(); i++)
        sum+=players[i].getBookSize();
    cout << sum << endl;
    return sum;
}


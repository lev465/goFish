// FILE: go_fish.cpp
// This program runs a two-player Go Fish game
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include <string>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES

//FUNCTION: dealHand
//INPUTS: deck of cards, players, and number of cards to deal per player
//OUTPUT: none
//Deals the initial hands to all players from given deck
void dealHand(Deck &d, vector<Player> &p, int numCards);

//FUNCTION: addPlayer
//INPUTS: vector of players and name of player to add
//OUTPUT: none
//adds another player to a given vector of players
void addPlayer(vector<Player> &players, string playerName);

//FUNCTION: goFish
//INPUTS: deck of cards and player to deal card to
//OUTPUT: string of card drawn from deck
//Draws the next card from the deck and adds it to the hand of the player
string goFish(Deck &d, Player &p);

//FUNCTION: sumBooks
//INPUTS: vector of players in game
//OUTPUT: number of books in players' possession
//determines the amount of cards that have been booked so far in the game
int sumBooks(vector<Player> players);

//FUNCTION: declareWinner
//INPUTS: vector of players in game
//OUTPUT: string with name of winner and number of books in their deck
//determines a winner or tie based on number of books
string declareWinner (vector<Player> players);

//FUNCTION: determineNumCards
//INPUTS: vector of players and variable to store number of cards to deal
//OUTPUT: none
//determines the number of cards per hand for initial deal assuming more than 1 player is playing
// 7 if 2 players
// 5 if more than 2
void determineNumCards (vector<Player> &players, int &numCards);

//FUNCTION: checkandBook
//INPUTS: player, card slots to book, and variable to store whether a pair was found
//OUTPUT: string of cards booked
//checks the player's hand for a book and adds it to the player's books if found
string checkandBook (Player &p, Card &c1, Card &c2, bool *pair);

int main( )
{
    vector<Player> players;
    int numCards;           //7 cards given to each player for 2-player game


    ofstream oFile;
    oFile.open("gofish_results.txt");

    addPlayer(players,"Joe");
    addPlayer(players, "Jane");

    if(players.size()>1)
        determineNumCards(players, numCards);

    else {
        cout << "not enough players - minimum 2 players" << endl;
        return -1; //FAILURE
    }

    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, players, numCards); //deal initial hands

    while(sumBooks(players)!=52) {          //play until all 52 cards are in books
        Card temp1, temp2;

        for(int i=0; i<players.size(); i++) {
            bool hasPair;
            bool drew = false;                  //no card drawn yet

            if(players[i].getHandSize()!=0)        //show hand - not empty
                oFile <<"\n"<< players[i].getName() << " has : " << players[i].showHand() << endl;

            else if(d.getIndex()!=52){                                  //empty hand
                oFile << "\n" << players[i].getName() << " has : an empty hand. Go Fish." << players[i].showHand()
                      << endl;

                if(d.getIndex()!=52) {                      //deck empty?
                    oFile << players[i].getName() << " draws - " << goFish(d, players[i]) << endl;
                } else oFile << "deck empty." << endl;
                drew=true;
            }

            unsigned long randomplayer = (rand() % players.size());  //random player to ask for card
            if (randomplayer == i)
                randomplayer = (i + 1) % players.size();

            while(!drew) {                                                              //drawn card?
                if (players[i].getHandSize() != 0) {
                    Card currentCard = players[i].chooseCardFromHand();

                    string bookResult = checkandBook(players[i],temp1, temp2, &hasPair);
                    while (hasPair) {                                                      //book all pairs
                        oFile << bookResult << endl;
                        bookResult = checkandBook(players[i], temp1, temp2, &hasPair);
                    }

                    oFile << players[i].getName() << " asks - " << players[randomplayer].getName() << " do you have a "
                         << currentCard.rankString(currentCard.getRank()) << "?" << endl;

                    if (players[randomplayer].sameRankInHand(currentCard)) {            //other player has card asked
                        players[i].addCard(players[randomplayer].removeCardFromHand(currentCard));
                        bookResult = checkandBook(players[i],temp1, temp2, &hasPair);
                        oFile << players[randomplayer].getName() << " says - Yes I have a "
                             << currentCard.rankString(currentCard.getRank()) << endl;

                        if (hasPair) {                                               //book pairs
                            oFile << bookResult << endl;
                            bookResult = checkandBook(players[i], temp1, temp2, &hasPair);
                        }

                        if (players[i].getHandSize() == 0) {                            //empty hand
                            if(d.getIndex()!=52) {
                                oFile << "Empty hand - Go Fish" << endl;
                                oFile << players[i].getName() << " draws - " << goFish(d, players[i]) << endl;
                            }
                            drew=true;
                        }
                    }

                    else {
                        bookResult = checkandBook(players[i],temp1, temp2, &hasPair);
                        if (hasPair)
                            oFile << bookResult << endl;

                        oFile << players[randomplayer].getName() << " says - Go Fish" << endl;
                        oFile << players[i].getName() << " draws - " << goFish(d, players[i]) << endl;

                        bookResult = checkandBook(players[i],temp1, temp2, &hasPair);
                        if (hasPair)                                                    //book all pairs
                            oFile << bookResult  << endl;

                        drew = true;
                    }
                }

                else {                                                                 //empty hand
                    goFish(d, players[i]);
                    drew =true;
                }
            }
        }
    }

    oFile << "\n\nThe winner is - " << declareWinner(players) << endl;

    oFile.close();

    return EXIT_SUCCESS;
}



void dealHand(Deck &d, vector<Player> &players, int numCards)
{
    for(int i=0; i<players.size(); i++) {
        for (int j = 0; j < numCards; j++)
            players[i].addCard(d.dealCard());
    }
}

void addPlayer(vector<Player> &players,string playerName)
{
    players.emplace_back(playerName);
}

string goFish(Deck &d, Player &p) {
    if (d.size() != 0) {
        Card temp  = d.dealCard();
        p.addCard(temp);
        return temp.toString();
    } else
        return "nothing. Deck empty.";
}

int sumBooks(vector<Player> players) {
    int sum = 0;
    for (int i = 0; i < players.size(); i++) {
        sum += players[i].getBookSize();
    }
    return sum;
}

string declareWinner(vector<Player> players) {
    int winning = 0;
    for (int i = 1; i < players.size(); i++) {
        if (players[i].getBookSize() == players[winning].getBookSize())
            return " no one - there is a tie.";
        if (players[i].getBookSize() > players[winning].getBookSize())
            winning = i;

    }
    return players[winning].getName() + " with " + to_string(players[winning].getBookSize() / 2) + "/26 books.";
}

void determineNumCards (vector<Player> &players, int &numCards) {
    if (players.size() == 2)
        numCards = 7;
    else
        numCards = 5;
}

string checkandBook (Player &p, Card &c1,Card &c2, bool *pair)
{
    if(p.getHandSize()!=0) {
        *pair = p.checkHandForBook(c1,c2);
        if(*pair){
            p.bookCards(c1,c2);
            return ( p.getName() + " books a pair of " + c1.rankString( c1.getRank() ) );
        }
        else{
            return "";
        }
    }
    else{
        *pair = false;
        return "";
    }
}

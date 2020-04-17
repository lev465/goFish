final: go_fish.o player.o deck.o card.o
	g++ -std=c++11 -o go_Fish  go_fish.o player.o deck.o card.o
go_fish.o: go_fish.cpp player.h deck.h card.h
	g++ -std=c++11 -c go_fish.cpp
player.o: player.cpp player.h deck.h
	g++ -std=c++11 -c player.cpp
deck.o: deck.cpp deck.h card.h
	g++ -std=c++11 -c deck.cpp
card.o: card.cpp card.h
	g++ -std=c++11 -c card.cpp

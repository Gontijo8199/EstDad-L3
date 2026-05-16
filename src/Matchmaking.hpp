#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"

class Matchmaking {

private:
    const int MAX_PLAYERS = 100000;
    Player* players;
    int size;
    void sortByScoreMerge(int low_bound, int up_bound);

public:

    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();

    Player* formGroup(int groupSize, int delta, int* n);

    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();
    void printArrayPlayers(Player* player_array, int n, std::string title);
};

#endif
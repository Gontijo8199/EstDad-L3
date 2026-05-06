#include "Matchmaking.hpp"

Matchmaking::Matchmaking(){
    this->size = 0;
}

Matchmaking::~Matchmaking(){
    delete[] this->players;
}

bool Matchmaking::insert(Player player){
    if (this->size == MAX_PLAYERS)
        return 0;
    
    this->players[this->size] = player;
    this->size++;

    return 1;
}
bool Matchmaking::removePlayer(int id){
}

void Matchmaking::sortByScoreInsertion(){}
void Matchmaking::sortByScoreMerge(){}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){}

Player* Matchmaking::getWaitingPlayers(int* n){
    *n = this->size;
    return this->players;
}

void Matchmaking::printWaitingPlayers(){}
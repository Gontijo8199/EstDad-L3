#include "Matchmaking.hpp"
#include<iostream>

Matchmaking::Matchmaking(){
    this->size = 0;
}

Matchmaking::~Matchmaking(){
    delete[] this->players;
}

bool Matchmaking::insert(Player player){
    if (this->size == MAX_PLAYERS)
        return false;
    
    this->players[this->size] = player;
    this->size++;

    return true;
}
bool Matchmaking::removePlayer(int id){

    for (int i = 0; i < this->size; i++) {
        if (this->players[i].getId() == id) {
            for (int j = i; j < this->size - 1; j++) {
                this->players[j] = this->players[j + 1];
            }
            this->size--;
            return true;
        }
    }

    return false;
}

void Matchmaking::sortByScoreInsertion(){}
void Matchmaking::sortByScoreMerge(){}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){}

Player* Matchmaking::getWaitingPlayers(int* n){
    *n = this->size;
    return this->players;
}

void Matchmaking::printWaitingPlayers(){
    Player* p = nullptr;
    std::cout << "Waiting Players:" << std::endl;
    for (int i = 0; i<this->size; i++){
        p = &this->players[i];
        std::cout << "[" << p->getId() << " | " << p->getName() << " | " << p->getScore() <<  " | " << p->getTimestamp() << " ]" << std::endl; 
    }
}
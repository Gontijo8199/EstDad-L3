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

void Matchmaking::sortByScoreInsertion(){
    Player temp;
    int sorted_size = 1;
    for (int i=1; i<this->size; i++) {
        for (int j=i; j>0; j--) {
            if (this->players[j-1].getScore() > this->players[j].getScore())
                continue; // como a parte esquerda da lista estava ordenada, basta colocaro novo na posição certa

            if ((this->players[j-1].getScore() == this->players[j].getScore()) 
                && (this->players[j-1].getTimestamp() >= this->players[j].getTimestamp()))
                continue; // critério de desempate
            
            temp = this->players[j-1];
            this->players[j-1] = this->players[j];
            this->players[j] = temp;
        }
    }
}

void Matchmaking::sortByScoreMerge(int low_bound, int up_bound) {
    if (up_bound - low_bound <= 0) 
        return;

    int mid = (low_bound + up_bound) / 2; // arredonda para baixo
    this->sortByScoreMerge(low_bound, mid);
    this->sortByScoreMerge(mid + 1, up_bound);

    int size = up_bound - low_bound + 1;
    int i = low_bound;
    int j = mid + 1;

    Player newSegment[size];
    for (int k=0; k<size && i<=mid && j<=up_bound; k++) {
        if (this->players[i].getScore() < this->players[j].getScore()) {
            newSegment[k] = this->players[i];
            i++;
        }
        else if (this->players[i].getScore() > this->players[j].getScore()) {
            newSegment[k] = this->players[j];
            j++;
        }
        else { // empate
            if (this->players[i].getTimestamp() < this->players[j].getTimestamp()) {
                newSegment[k] = this->players[i];
                i++;
            }
            else {
                newSegment[k] = this->players[j];
                j++;
            }
        }
    }

    // sempre termina uma sub lista antes da outra
    int t, end;
    if (i > mid) {
        t = j;
        end = up_bound;
    }
    else {
        t = i;
        end = mid;
    }

    for (int k=0; k+t<end; k++) 
        newSegment[k] = this->players[k+t];
    
    for (int k=0; k<size; k++) 
        this->players[low_bound + k] = newSegment[k];
}

void Matchmaking::sortByScoreMerge(){
    this->sortByScoreMerge(0, this->size - 1);
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    Player grupo[groupSize]; 
    for (int i=0; i<this->size - groupSize; i++) {
        if (this->players[i+groupSize].getScore() - this->players[i].getScore() < delta) {
            int maxScore = this->players[i+groupSize].getScore();
        }
    }
}

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
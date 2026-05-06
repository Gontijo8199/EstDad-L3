#include "Matchmaking.hpp"

Matchmaking::Matchmaking(){};
Matchmaking::~Matchmaking(){};

bool Matchmaking::insert(Player player){};
bool Matchmaking::removePlayer(int id){};

void Matchmaking::sortByScoreInsertion(){};
void Matchmaking::sortByScoreMerge(){};

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){};

Player* Matchmaking::getWaitingPlayers(int* n){};

void Matchmaking::printWaitingPlayers(){};
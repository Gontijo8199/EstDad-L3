#include "Matchmaking.hpp"
#include "Player.hpp"

int main(){
    Player* p1 = new Player(1, "Rudá", 1000, 1);
    Player* p2 = new Player(2, "Rafael", 1010, 2);
    Player* p3 = new Player(3, "Maria", 1010, 3);
    Player* p4 = new Player(4, "Matheus", 3000, 4);
    Player* p5 = new Player(5, "Pedro", 500, 5);

    Matchmaking* game = new Matchmaking();

    game->insert(*p1);
    game->insert(*p2);
    game->insert(*p3);
    game->insert(*p4);
    game->insert(*p5);
    
    game->printWaitingPlayers();




    return 0;
}
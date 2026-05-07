#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

int main(){

/*
    inserção de jogadores;
    remoção de jogadores;
    ordenação utilizando insertion sort;
    ordenação utilizando merge sort;
    ordenação com empate de score;
    formação bem-sucedida de grupo;
    tentativa de formação de grupo sem sucesso;
    recuperação dos dados por meio do método getWaitingPlayers;
    exibição do estado do sistema.
 */
    cout << "Criando usuários..." << endl;
    Player* p1 = new Player(1, "Ruda", 1000, 1);
    Player* p2 = new Player(2, "Rafael", 1010, 2);
    Player* p3 = new Player(3, "Maria", 1010, 3);
    Player* p4 = new Player(4, "Matheus", 3000, 4);
    Player* p5 = new Player(5, "Pedro", 500, 5);

    Matchmaking* game = new Matchmaking();

    cout << "Inserindo usuários..." << endl;
    game->insert(*p1);
    game->insert(*p2);
    game->insert(*p3);
    game->insert(*p4);
    game->insert(*p5);


    game->printWaitingPlayers();

    cout << "Removendo usuário de ID=5..." << endl;

    game->removePlayer(5);

    cout << "Ordenando por Insertion e por Merge..." << endl;

    Matchmaking* game_clone = game;

    cout << "Insertion: (resultado)" << endl;

    game->sortByScoreInsertion();
    game->printWaitingPlayers();

    cout << "Merge: (resultado)" << endl;

    game_clone->sortByScoreMerge();
    game->printWaitingPlayers();

    // TODO: Adicionar teste de grupo
    
    int n;
    Player* backup_players = game->getWaitingPlayers(&n);

    cout << "Criando jogo com backup_players..." << endl;

    Matchmaking* game_backup = new Matchmaking();

    for (int i = 0; i < n; i++)
        game_backup->insert(backup_players[i]);
    
    game_backup->printWaitingPlayers();


    cout << "Fim dos testes..." << endl;



    return 0;
}
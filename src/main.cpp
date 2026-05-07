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
    Player p1 = Player(1, "Ruda", 1000, 1);
    Player p2 = Player(2, "Rafael", 1010, 2);
    Player p3 = Player(3, "Maria", 1010, 3);
    Player p4 = Player(4, "Matheus", 3000, 4);
    Player p5 = Player(5, "Pedro", 500, 5);

    Matchmaking* game = new Matchmaking();

    cout << "Inserindo usuários..." << endl;
    game->insert(p1);
    game->insert(p3);
    game->insert(p2);
    game->insert(p4);
    game->insert(p5);

    cout << "\nSalvando um backup_players..." << endl;

    int n;
    Player* backup_players = game->getWaitingPlayers(&n);

    game->printWaitingPlayers();

    cout << "\nRemovendo usuário de ID=5..." << endl;

    game->removePlayer(5);
    game->printWaitingPlayers();

    delete game;
    game = new Matchmaking();
    for (int i = 0; i < n; i++)
        game->insert(backup_players[i]);
    
    cout << "\nOrdenando por Insertion e por Merge..." << endl;

    cout << "\n\tInsertion: (resultado)" << endl;

    game->sortByScoreInsertion();
    game->printWaitingPlayers();

    delete game;
    game = new Matchmaking();
    for (int i = 0; i < n; i++)
        game->insert(backup_players[i]);

    cout << "\n\tMerge: (resultado)" << endl;

    game->sortByScoreMerge();
    game->printWaitingPlayers();
    
    delete game;
    game = new Matchmaking();
    for (int i = 0; i < n; i++)
        game->insert(backup_players[i]);

    cout << "\nTestando grupo válido (size=3, delta=50)..." << endl;

    game->sortByScoreMerge();
    int size;
    Player* grupo = game->formGroup(3, 50, &size);
    game->printArrayPlayers(grupo, size, "Grupo removido");
    delete[] grupo;

    cout << "Nova lista de espera: " << endl;
    game->printWaitingPlayers();
    
    delete game;
    game = new Matchmaking();
    for (int i = 0; i < n; i++)
        game->insert(backup_players[i]);

    cout << "\nTestando grupo inválido (size=4, delta=20)..." << endl;

    game->sortByScoreMerge();
    grupo = game->formGroup(4, 20, &size);
    game->printArrayPlayers(grupo, size, "Grupo removido");
    delete[] grupo;

    cout << "Nova lista de espera: " << endl;
    game->printWaitingPlayers();
    
    delete game;
    game = new Matchmaking();
    for (int i = 0; i < n; i++)
        game->insert(backup_players[i]);

    cout << "Fim dos testes..." << endl;

    delete game;
    delete[] backup_players;

    return 0;
}
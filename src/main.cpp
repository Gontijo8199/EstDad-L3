#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

Matchmaking* gerar_jogo_ordenado(int n_players) {
    Matchmaking* mm = new Matchmaking();

    Player p;
    for (int i=0; i<n_players; i++) {
        p = Player(i, "p"+to_string(i), (i+1)*10, i);
        mm->insert(p);
    }

    return mm;
}

Matchmaking* gerar_jogo_desordenado(int n_players) {
    Matchmaking* mm = new Matchmaking();

    Player p;
    for (int i=0; i<(n_players / 2); i++) {
        p = Player(2*i, "p"+to_string(2*i), (i+1)*10, 2*i);
        mm->insert(p);

        p = Player(2*i + 1, "p"+to_string(2*i + 1), (i+1)*100, 2*i + 1);
        mm->insert(p);
    }

    if (n_players%2 != 0) {
        p = Player(n_players, "p"+to_string(n_players), (n_players+1)*10, n_players);
        mm->insert(p);
    }

    return mm;
}

Matchmaking* gerar_jogo_desordenado_empatado(int n_players) {
    Matchmaking* mm = new Matchmaking();

    Player p;
    for (int i=0; i<(n_players / 4); i++) {
        p = Player(4*i, "p"+to_string(4*i), (i+1)*10, 4*i+1);
        mm->insert(p);
        p = Player(4*i+1, "p"+to_string(4*i+1), (i+1)*10, 4*i);
        mm->insert(p);

        p = Player(4*i+2, "p"+to_string(4*i+2), (i+1)*100, 4*i+3);
        mm->insert(p);
        p = Player(4*i+3, "p"+to_string(4*i+3), (i+1)*100, 4*i+2);
        mm->insert(p);
    }

    int next = n_players/4; // 
    for (int i=0; i<(n_players%4); i++) {
        p = Player(4*next+i, "p"+to_string(4*next+i), (next+1)*10, n_players-i);
        mm->insert(p);
    }

    return mm;
}

void buscar_grupo(int n_players, int g_size, int delta) {
    cout << "\nGerando jogo com " << n_players << " jogadores não ordenados com empate\n";

    Matchmaking* mm = gerar_jogo_desordenado_empatado(n_players);
    mm->printWaitingPlayers();
    mm->sortByScoreMerge();

    cout << "\nBuscando grupo com " << g_size << " jogadores e delta = " << delta << endl;

    int n;
    Player* gp = mm->formGroup(g_size, delta, &n);
    cout << "\nn esperado: " << g_size;
    cout << "\nn obtido: " << n << endl;

    if (gp == nullptr)
        cout << "Retorno de formGroup: nullptr" << endl;
    else 
        mm->printArrayPlayers(gp, n, "Grupo encontrado");
    mm->printWaitingPlayers();

    delete[] gp;
    delete mm;
    return;
}

//inserção ordenada
void teste_1_1(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores ordenados\n";
    Matchmaking* mm = gerar_jogo_ordenado(n_players);

    mm->printWaitingPlayers();
    delete mm;
    return;
}

//inserção não ordenada por score
void teste_1_2(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores não ordenados\n";
    Matchmaking* mm = gerar_jogo_desordenado(n_players);

    mm->printWaitingPlayers();
    delete mm;
    return;
}

// ordenação via insertion sort por score sem empate
void teste_2_1(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores não ordenados sem empate\n";
    
    Matchmaking* mm = gerar_jogo_desordenado(n_players);
    mm->printWaitingPlayers();

    cout << "\nOrdenando via insertion sort\n";
    mm->sortByScoreInsertion();
    mm->printWaitingPlayers();
    delete mm;
    return;
}

// ordenação via insertion sort por score com empate
void teste_2_2(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores não ordenados com empate\n";

    Matchmaking* mm = gerar_jogo_desordenado_empatado(n_players);
    mm->printWaitingPlayers();

    cout << "\nOrdenando via insertion sort\n";
    mm->sortByScoreInsertion();
    mm->printWaitingPlayers();
    delete mm;
    return;
}

// ordenação via merge sort por score sem empate
void teste_3_1(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores não ordenados sem empate\n";
    
    Matchmaking* mm = gerar_jogo_desordenado(n_players);
    mm->printWaitingPlayers();

    cout << "\nOrdenando via merge sort\n";
    mm->sortByScoreMerge();
    mm->printWaitingPlayers();
    delete mm;
    return;
}

// ordenação via merge sort por score com empate
void teste_3_2(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores não ordenados com empate\n";

    Matchmaking* mm = gerar_jogo_desordenado_empatado(n_players);
    mm->printWaitingPlayers();

    cout << "\nOrdenando via merge sort\n";
    mm->sortByScoreMerge();
    mm->printWaitingPlayers();
    delete mm;
    return;
}

// seleção de grupo válida
void teste_4_1(int n_players) {
    int g_size = n_players/2;
    int delta = n_players*5;

    buscar_grupo(n_players, g_size, delta);
    
    return;
}

//seleção de grupo inválida
void teste_4_2(int n_players) {
    int g_size = n_players/2;
    int delta = n_players;

    buscar_grupo(n_players, g_size, delta);

    return;
}

int main(){
    int n_players = 10;
    teste_1_1(n_players);
    teste_1_2(n_players);
    teste_2_1(n_players);
    teste_2_2(n_players);
    teste_3_1(n_players);
    teste_3_2(n_players);
    teste_4_1(n_players);
    teste_4_2(n_players);

    return 0;
}
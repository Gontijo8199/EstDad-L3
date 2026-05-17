#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

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

//verificação de getWaitingPlayers
void teste_0(int n_players) {
    cout << "\nGerando jogo com " << n_players << " jogadores ordenados\n";
    Matchmaking* mm = gerar_jogo_ordenado(n_players);

    cout << "Copiando lista...\n";
    int n;
    Player* wp = mm->getWaitingPlayers(&n);

    cout << "Número de jogadores retornado: " << n << endl;
    cout << "Deletando original e acessnado cópia...\n";

    delete mm;
    cout << "Nome | Timestamp\n";
    for (int i=0; i<n; i++) {
        cout << wp[i].getName() << " | " << wp[i].getTimestamp() << endl;
    }

    delete[] wp;
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

void run_tests(int n_players) {
    teste_0(n_players);
    teste_1_1(n_players);
    teste_1_2(n_players);
    teste_2_1(n_players);
    teste_2_2(n_players);
    teste_3_1(n_players);
    teste_3_2(n_players);
    teste_4_1(n_players);
    teste_4_2(n_players);

    return;
}

Matchmaking* gerar_jogo_aleatorio(int n_players, unsigned int seed) {
    Matchmaking* mm = new Matchmaking();

    mt19937 gen(seed);
    uniform_int_distribution<> dist(1, n_players);
    int rn;

    Player p;
    for (int i=0; i<n_players; i++) {
        rn = dist(gen);
        p = Player(i, "p"+to_string(i), rn, i);
        mm->insert(p);
    }

    return mm;
}

bool get_tempo_exec(int n_players, double* t_insert, double* t_merge) {
    if (n_players < 1 || t_insert == nullptr || t_merge == nullptr)
        return false;

    random_device rd;

    Matchmaking* mm = gerar_jogo_aleatorio(n_players, rd());
    auto start = chrono::steady_clock::now();
    mm->sortByScoreInsertion();
    auto end = chrono::steady_clock::now();

    chrono::duration<double> elapsed = end - start;
    *t_insert = elapsed.count();
    delete mm;

    mm = gerar_jogo_aleatorio(n_players, rd());
    start = chrono::steady_clock::now();
    mm->sortByScoreMerge();
    end = chrono::steady_clock::now();

    elapsed = end - start;
    *t_merge = elapsed.count();

    return true;
}

void comparar_funcs(int amostras) {
    int MAX = Matchmaking::MAX_PLAYERS;
    int n_players;
    double t_insert, t_merge;
    bool sucesso;
    cout << "n_players,func,t_exec" << endl;

    while (amostras--) {
        sucesso = true;
        n_players = MAX;
        while(sucesso) {
            sucesso = get_tempo_exec(n_players, &t_insert, &t_merge);
            if (!sucesso)   continue;

            cout << n_players << ",insert," << t_insert << endl;
            cout << n_players << ",merge," << t_merge << endl;

            n_players = n_players * 2 / 3;
        }
    }
}

int main(){
    int n_players = 10;
    run_tests(n_players);

    // rodar apenas essa parte com `.\src\a >> src\out.csv` para adicionar testes ao arquivo de dados
    // int amostras = 10;
    // comparar_funcs(amostras);

    return 0;
}
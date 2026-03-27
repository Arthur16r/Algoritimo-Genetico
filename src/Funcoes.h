#ifndef FUNCOES_H
#define FUNCOES_H

#include <vector>
#include <fstream>

using namespace std;

// ===== STRUCTS =====
struct individuo{
    float a;
    float b;
    float fitness;
};

struct pontosReferencias{
    float x;
    float y;
};

// ===== LEITURA =====
vector<individuo> LerIndividuos(ifstream& arquivo, int quantidade);
void LerParametros(ifstream& arquivo, int& qtdIndividuos, int& geracoes, float& probMutacao);

// ===== ACESSO =====
individuo PegarIndividuo(const vector<individuo>& populacao, int indice);
pontosReferencias PegarPonto(const vector<pontosReferencias>& ptsmatriz, int indice);

// ===== GERAÇÃO =====
vector<pontosReferencias> GerarPontos(int quantidade, int seed);

// ===== ERRO =====
float calcularErroUnitario(pontosReferencias pontoref, individuo individuoteste);
void mediaErro(const vector<pontosReferencias>& ptsmatriz, individuo individuoPteste);

// ===== ORDENAÇÃO =====
bool comparar(individuo x, individuo y);
vector<individuo> PopOrdenadaPMedia(const vector<individuo>& populacao);
void descartarOsPiores(vector<individuo>& populacao);

// ===== GENÉTICO =====
void SelecaoNatural(vector<individuo>& populacao, float probabilidademutacao);
individuo Crossover(individuo mae, individuo pai);
individuo Mutacao(individuo individuoPmutacao);

// ===== EXECUÇÃO =====
void analisar(vector<individuo>& populacao, vector<pontosReferencias>& ptsmatriz, float probabilidadeMutacao);

#endif
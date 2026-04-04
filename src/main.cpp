#include <iostream>
#include <fstream>
#include "Funcoes.h"

using namespace std;
struct Posicao {
    int x;
    int y;
};
int main() {
    srand(1);
   ifstream arquivo("input.data");
   ofstream arquivoSai("output.data");
   if(!arquivo){
    cout << "Erro ao abrir arquivo!" << endl;
    return 1;
    }
    int qtdIndividuos;
    int geracoes;
    float probMutacao;
    int i=0;
    LerParametros(arquivo, qtdIndividuos, geracoes, probMutacao);
    vector<pontosReferencias> pontos = GerarPontos(10, 1);
    vector<individuo> populacaoInicial=LerIndividuos(arquivo,qtdIndividuos);
    while(i<geracoes){
       
        analisar(populacaoInicial, pontos, probMutacao, arquivoSai, i);
        i++;
        
        
    };
    populacaoInicial=PopOrdenadaPMedia(populacaoInicial);
    PrintTop2(populacaoInicial);
    PrintPopulacao(populacaoInicial);

    arquivoSai.close();
    return 0;
}
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

struct individuo{
    float a;
    float b;
    float fitness=0;
};


vector<individuo> LerIndividuos(ifstream& arquivo,int quantidade){
    vector<individuo> populacao;
    float a ,b;
    for(int i=0;i<quantidade;i++){
        arquivo >>a>>b;
        populacao.push_back({a,b,0});
    }
    return populacao;
}

void LerParametros(std::ifstream& arquivo, int& qtdIndividuos, int& geracoes, float& probMutacao){
    arquivo >> qtdIndividuos >> geracoes >> probMutacao;
}


individuo& PegarIndividuo( vector<individuo>& populacao , int indice){
    return populacao[indice];
}


struct pontosReferencias{
    float x;
    float y;
};  

vector<pontosReferencias> GerarPontos(int quantidade, int seed){
    vector<pontosReferencias> ptsmatriz;

    srand(seed);

    for(int i = 0; i < quantidade; i++){
        float x = rand() % 15; 
        float y = rand() % 15;

        ptsmatriz.push_back({x, y});
    }

    return ptsmatriz;
}

pontosReferencias PegarPonto(const vector<pontosReferencias>& ptsmatriz , int indice){
    return ptsmatriz[indice];
}


float calcularErroUnitario(pontosReferencias pontoref, individuo individuoteste){
        float erro=0;
        float y1;
        y1=(individuoteste.a * pontoref.x)+individuoteste.b;
        erro=pow(pontoref.y - y1,2);
        return erro;
}


void mediaErro(const vector<pontosReferencias>& ptsmatriz ,individuo& individuoPteste ){
    int i;
    float soma=0;
    float erro;
    float media;
    for(i=0;i<ptsmatriz.size();i++){
       erro=calcularErroUnitario(ptsmatriz[i],individuoPteste);
        soma+=erro;
    }
    media=soma/ptsmatriz.size();
    individuoPteste.fitness=media;
}
bool comparar(individuo x, individuo y){
            return x.fitness < y.fitness;
        }


vector<individuo> PopOrdenadaPMedia(const vector<individuo>& populacao){
        vector<individuo> copia = populacao;
        sort(copia.begin(), copia.end(), comparar);
        return copia;

}


void PrintPopulacao(const vector<individuo>& populacao){
    for(int i = 0; i < populacao.size(); i++){
        cout << "\nIndividuo " << i << ": "
             << "a = " << populacao[i].a << ", "
             << "b = " << populacao[i].b << ", "
             << "fitness = " << populacao[i].fitness
             << endl;
    }
    
}

void descartarOsPiores(vector<individuo>& populacao){
    int metade=populacao.size()/2;
   populacao.resize(populacao.size() - metade);
}

individuo Crossover(individuo mae,individuo pai){

    //forçar mutaçao if(mae.a == pai.a && mae.b == pai.b){return Mutacao(mae);}
           int sorte= rand() %2;
           individuo novoindividuo;
           if (sorte==1) {
            novoindividuo.a=mae.a;
            novoindividuo.b=pai.b;

           }else{
            novoindividuo.a=pai.a;
            novoindividuo.b=mae.b;
           }
           return novoindividuo;
}

individuo Mutacao(individuo individuoPmutacao){
    int sorte = rand() % 4;

    switch(sorte){
        case 0:
            individuoPmutacao.a = (individuoPmutacao.a + rand() % 15)+1;
            break;

        case 1:
            individuoPmutacao.a = (individuoPmutacao.a - rand() % 15)-1;
            break;

        case 2:
            individuoPmutacao.b = (individuoPmutacao.b + rand() % 15)+1;
            break;

        case 3:
            individuoPmutacao.b = (individuoPmutacao.b - rand() % 15)-1;
            break;
    }

    return individuoPmutacao;
}


void SelecaoNatural(vector<individuo>& populacao,float probabilidademutacao,const vector<pontosReferencias>& ptsmatriz){
    populacao = PopOrdenadaPMedia(populacao);
    // tenho q dps salvar isso em um arquiuvo
    PrintPopulacao(populacao);
    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    descartarOsPiores(populacao);
    PrintPopulacao(populacao);
    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    vector<individuo> novos;
    cout<<"\n----------------------------\n";
    int i=0;
     while(i < populacao.size()){

        float prob = (rand() % 100) / 100.0;

        if(prob < probabilidademutacao){ 
            int indice = rand() % populacao.size();
            individuo mutado = Mutacao(populacao[indice]);
            novos.push_back(mutado);//é ou nao é para substituir o individuo apos a amutação DUVIDA MICHEL
        }
        else{ 
            int indice1 = rand() % populacao.size();
            int indice2 = rand() % populacao.size();

            while(indice1 == indice2){
                indice2 = rand() % populacao.size();
            }

            individuo filho = Crossover(populacao[indice1], populacao[indice2]);
            novos.push_back(filho);
        }

        i++;
    }

    
    for(int i = 0; i < novos.size(); i++){
        mediaErro(ptsmatriz,novos[i]);
        populacao.push_back(novos[i]);} 
        populacao=PopOrdenadaPMedia(populacao);
     PrintPopulacao(populacao);
     cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    }
   



void analisar(vector<individuo>& populacao,vector<pontosReferencias>& ptsmatriz,float probabilidadeMutacao){
    int i=0;
    int n=0;

    while(i<populacao.size()){
        
        mediaErro(ptsmatriz,populacao[i]);
        i++;
        
    }
    SelecaoNatural(populacao,probabilidadeMutacao,ptsmatriz);

}
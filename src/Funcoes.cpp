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
float randomFloat(float min, float max){
    float valor= min + static_cast<float>(rand()) / RAND_MAX * (max - min);
    valor = round(valor * 1000) / 1000;

    return valor;
}

vector<individuo> PopOrdenadaPMedia(const vector<individuo>& populacao){
        vector<individuo> copia = populacao;
        sort(copia.begin(), copia.end(), comparar);
        return copia;

}

void PrintTop2(const vector<individuo>& populacao){
    vector<individuo> ordenada = PopOrdenadaPMedia(populacao);

    cout << "Top 2 individuos:\n";

    for(int i = 0; i < 2 && i < ordenada.size(); i++){
        cout << i+1 << "º -> "
             << "(a=" << ordenada[i].a 
             << ", b=" << ordenada[i].b 
             << ") | fitness=" << ordenada[i].fitness 
             << endl;
    }

    cout << "----------------------------\n";
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

void PrintTop2Arquivo(ofstream &arq, vector<individuo>& pop, int geracao){
    arq << "Geracao " << geracao << ":\n";

    arq << "1: (" << pop[0].a << ", " << pop[0].b 
        << ") erro: " << pop[0].fitness << "\n";

    arq << "2: (" << pop[1].a << ", " << pop[1].b 
        << ") erro: " << pop[1].fitness << "\n\n";
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
          // cout << "\n=== CROSSOVER ===\n";
           // cout << "Pai1: (" << mae.a << "," << pai.b << ") ";
           // cout << "Pai2: (" << mae.a << "," << pai.b << ")\n";
            //cout << "Filho: (" << novoindividuo.a << "," << novoindividuo.b << ")\n";
           return novoindividuo;
}

individuo Mutacao(individuo individuoPmutacao){
    int sorte = rand() % 2;
    float variacao = randomFloat(-1.0, 1.0);
    float a_antes = individuoPmutacao.a;
    float b_antes = individuoPmutacao.b;
    switch(sorte){
        case 0:
            individuoPmutacao.a +=variacao;
            break;

        case 1:
            individuoPmutacao.b +=variacao;
            break;

    }
    //cout << "\n=== MUTACAO ===\n";
    //cout << "(" << a_antes << "," << b_antes << ") -> ("
    // << individuoPmutacao.a << "," << individuoPmutacao.b << ")\n";


    return individuoPmutacao;
}
vector<individuo>  Elitismo(vector<individuo>& populacaoAntiga){
    vector<individuo> nova;

    // elitismo
    nova.push_back(populacaoAntiga[0]);
    nova.push_back(populacaoAntiga[1]);
    return nova;
}

void SelecaoNatural(vector<individuo>& populacao,float probabilidademutacao,const vector<pontosReferencias>& ptsmatriz){
    populacao = PopOrdenadaPMedia(populacao);
    // tenho q dps salvar isso em um arquiuvo
    //PrintPopulacao(populacao);
    //PrintTop2(populacao);
    int tamanhoAntigo = populacao.size();
    vector<individuo> novaPopulacao=Elitismo(populacao);
    descartarOsPiores(populacao);
    
    
     while(novaPopulacao.size() < tamanhoAntigo){

        float prob = (rand() % 100) / 100.0;

        if(prob < probabilidademutacao){ 
            int indice = rand() % populacao.size();
            individuo mutado = Mutacao(populacao[indice]);
            novaPopulacao.push_back(mutado);
        }
        else{ 
            int indice1 = rand() % populacao.size();
            int indice2 = rand() % populacao.size();

            while(indice1 == indice2){
                indice2 = rand() % populacao.size();
            }

            individuo filho;
            bool valido = false;

            int tentativas = 0;
            int maxTentativas = 20;

            while(!valido && tentativas < maxTentativas){
                filho = Crossover(populacao[indice1], populacao[indice2]);

                if(
                    (filho.a != populacao[indice1].a || filho.b != populacao[indice1].b) &&
                    (filho.a != populacao[indice2].a || filho.b != populacao[indice2].b)
                ){
                    valido = true;
                }

                indice1 = rand() % populacao.size();
                indice2 = rand() % populacao.size();
                while(indice1 == indice2){
                    indice2 = rand() % populacao.size();
                }

                tentativas++;
            }
            if(!valido){
                 filho.a = randomFloat(-10,10);
                 filho.b = randomFloat(-10,10);
                }
            novaPopulacao.push_back(filho);
            }

                
        }
        for(int i=0;i<novaPopulacao.size();i++){
            mediaErro(ptsmatriz,novaPopulacao[i]);
        }
        PopOrdenadaPMedia(novaPopulacao);
        populacao = novaPopulacao;
    }
   




void analisar(vector<individuo>& populacao,vector<pontosReferencias>& ptsmatriz,float probabilidadeMutacao,ofstream &arquivo, int geracao){

  
    for(int i = 0; i < populacao.size(); i++){
        mediaErro(ptsmatriz, populacao[i]);
    }

    SelecaoNatural(populacao, probabilidadeMutacao, ptsmatriz);
    
        PrintTop2Arquivo(arquivo, populacao, geracao);
    
}
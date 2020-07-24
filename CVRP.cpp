//*************************************************************//
//    Parte 3 do projeto - Analise de Projeto e Algoritmos;    //
//    Alunas: Elaine Cristina Lins de Souza;                   //
//            Letícia Sousa Leite.                             //
//*************************************************************//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h> //biblioteca para o cálculo do tempo de execução

using namespace std;

int Re_Insertion(vector<vector<int>> vect, vector<vector<int>> dist, int distPercorrida)
{

    int mRemocao = 9999, mInsercao = 0; // variáveis que guardam melhor custo de remocao e insercao
    int auxDist = 0;
    int mDistancia, mRota; // melhor rota
    int aux = 0;

    mDistancia = distPercorrida;

    for (int i = 0; i < vect.size(); i++) //percorre as rotas
    {
        for (int j = 1; j < vect[i].size() - 1; j++) //percorre cada índice de cada rota
        {
            if (vect[i][j] != 0)
            {
                for (int k = 1; k < vect[i].size(); k++) // Melhor inserção / k = aresta de antes;
                {
                    if (k == j || k == j + 1) // quando os mesmo vertices se encontram
                        continue;

                    auxDist = distPercorrida - dist[vect[i][j - 1]][vect[i][j]] - dist[vect[i][j]][vect[i][j + 1]] + dist[vect[i][j - 1]][vect[i][j + 1]] - dist[vect[i][k - 1]][vect[i][k]] + dist[vect[i][k - 1]][vect[i][j]] + dist[vect[i][j]][vect[i][k]];

                    if (auxDist < mDistancia)
                    {
                        mDistancia = auxDist;
                        mRemocao = j;
                        mInsercao = k;
                        mRota = i;
                    }
                }
            }
        }
    }

    if (mInsercao > mRemocao) //quando o vértice a ser removido está a esquerda do lugar onde sera inserido
    {
        aux = vect[mRota][mRemocao]; //auxiliar que recebe o vértice a ser removido

        for (int i = mRemocao; i < mInsercao - 1; i++) //for que realiza as trocas de posiçoes
        {
            vect[mRota][i] = vect[mRota][i + 1]; //o indice atual na rota recebe o valor do seu sucessor
        }

        vect[mRota][mInsercao - 1] = aux; //vértice removido é colocado em sua nova posição
    }

    if (mRemocao > mInsercao) //quando o vértice a ser removido está a direita do lugar onde sera inserido
    {
        aux = vect[mRota][mRemocao]; //auxiliar recebe vértice a ser removido

        for (int i = mRemocao; i > mInsercao; i--) //for que realiza as trocas de posiçoes
        {
            vect[mRota][i] = vect[mRota][i - 1]; //o indice atual na rota recebe o valor do seu antecessor
        }
        vect[mRota][mInsercao] = aux; //vértice removido é colocado em sua nova posição
    }

    cout << endl;
    cout << "Reinsertion: ";

    for (int i = 0; i < vect[mRota].size(); i++) //mostrando na tela a rota alterada
    {
        cout << vect[mRota][i] << " ";
    }

    return mDistancia;
}

int TwoOpt(vector<vector<int>> vect, vector<vector<int>> dist, int distPercorrida)
{

    int mDistancia, auxDist = 0;
    int mRota = 0;
    int mUltimo = 0, mPrimeiro = 0; //melhor primeiro e ultimo indice da sequencia
    int x = 0, aux = 0;

    mDistancia = distPercorrida;

    for (int i = 0; i < vect.size(); i++) //percorre as rotas
    {
        if (vect[i].size() < 4) //se a rota tem menos que 4 elementos ele não faz o 2-opt, pois seria o mesmo que um swap
            continue;

        for (int j = 0; j < vect[i].size(); j++) //percorre cada indice de cada rota
        {
            if (vect[i][j] != 0)
            {
                for (int k = j + 3; k < vect[i].size() - 1; k++)
                {
                    auxDist = distPercorrida - dist[vect[i][j - 1]][vect[i][j]] - dist[vect[i][k]][vect[i][k + 1]] + dist[vect[i][j - 1]][vect[i][k]] + dist[vect[i][j]][vect[i][k + 1]];

                    if (auxDist < mDistancia)
                    {
                        mDistancia = auxDist;
                        mPrimeiro = j;
                        mUltimo = k;
                        mRota = i;
                    }
                }
            }
        }
    }

    x = mUltimo;

    for (int k = mPrimeiro; k < mPrimeiro + ((mUltimo - mPrimeiro + 1) / 2); k++) //inverte a sequencia de vértices
    {
        aux = vect[mRota][k];
        vect[mRota][k] = vect[mRota][x];
        vect[mRota][x] = aux;
        x--;
    }

    cout << endl;
    cout << "2opt: ";

    for (int i = 0; i < vect[mRota].size(); i++)
    {
        cout << vect[mRota][i] << " ";
    }

    return mDistancia;
}

int Swap(vector<vector<int>> vect, vector<vector<int>> dist, int distPercorrida)
{

    int mDistancia, auxDist = 0;
    int mRota = 0;
    int mUltimo = 0, mPrimeiro = 0;
    int aux = 0;
    mDistancia = distPercorrida;

    for (int i = 0; i < vect.size(); i++)
    {
        if (vect[i].size() < 3)
            continue;

        for (int j = 0; j < vect[i].size(); j++)
        {
            if (vect[i][j] != 0)
            {
                for (int k = j + 1; k < vect[i].size() - 1; k++)
                {
                    if (k == j + 1)
                    {
                        auxDist = distPercorrida - dist[vect[i][j - 1]][vect[i][j]] - dist[vect[i][k]][vect[i][k + 1]] + dist[vect[i][j - 1]][vect[i][k]] + dist[vect[i][j]][vect[i][k + 1]];
                    }
                    else
                    {
                        auxDist = distPercorrida - dist[vect[i][j - 1]][vect[i][j]] - dist[vect[i][j]][vect[i][j + 1]] - dist[vect[i][k - 1]][vect[i][k]] - dist[vect[i][k]][vect[i][k + 1]] + dist[vect[i][k - 1]][vect[i][j]] + dist[vect[i][j]][vect[i][k + 1]] + dist[vect[i][j - 1]][vect[i][k]] + dist[vect[i][k]][vect[i][j + 1]];
                    }

                    if (auxDist < mDistancia)
                    {
                        mDistancia = auxDist;
                        mPrimeiro = j;
                        mUltimo = k;
                        mRota = i;
                    }
                }
            }
        }
    }

    aux = vect[mRota][mPrimeiro];
    vect[mRota][mPrimeiro] = vect[mRota][mUltimo];
    vect[mRota][mUltimo] = aux;

    cout << endl;
    cout << "Swap: ";

    for (int i = 0; i < vect[mRota].size(); i++)
    {
        cout << vect[mRota][i] << " ";
    }

    return mDistancia;
}

int VND(vector<vector<int>> vect, vector<vector<int>> dist, int distPercorrida)
{

    int melhorSolucao = distPercorrida;
    int solucaoAtual;
    vector<vector<int>> rota = vect;
    vector<vector<int>> distancias = dist;
    int r = 3;           // numero de vizinhanças
    int k = 1;           // opções
    clock_t tempoOrdVND; // variavél para armazenar o tempo de execução do vND;

    tempoOrdVND = clock();
    while (k <= r)
    {

        if (k == 1)
        {
            solucaoAtual = Swap(rota, distancias, melhorSolucao);

            if (solucaoAtual < melhorSolucao)
            {
                melhorSolucao = solucaoAtual;
            }
            if (solucaoAtual == melhorSolucao)
            {
                k = k + 1;
            }
        }
        if (k == 2)
        {
            solucaoAtual = Re_Insertion(rota, distancias, melhorSolucao);

            if (solucaoAtual < melhorSolucao)
            {

                melhorSolucao = solucaoAtual;
                k = 1;
            }
            if (solucaoAtual == melhorSolucao)
            {
                k = k + 1;
            }
        }
        if (k == 3)
        {
            solucaoAtual = TwoOpt(rota, distancias, melhorSolucao);
            if (solucaoAtual < melhorSolucao)
            {

                melhorSolucao = solucaoAtual;
                k = 1;
            }
            if (solucaoAtual == melhorSolucao) //if(solucaoAtual == melhorSolucao)
            {
                k = k + 1;
            }
        }

        break;
    }
    tempoOrdVND = clock() - tempoOrdVND;

    printf("\n\nO tempo de Execucao do VND foi de:  %f milisegundos\n", ((float)tempoOrdVND) / CLOCKS_PER_SEC);

    return melhorSolucao;
}

int main(void)
{

    ifstream arquivo;
    int l, c;            // l vai guardar o tamanho e c vai guardar a capacidade;
    clock_t tempoOrdVMP; // variavel para armazenar o tempo do VMP

    arquivo.open("P-n55-k7(8).txt");

    arquivo >> l; // salvando o tamanho do array como int;
    arquivo >> c; // salvando a capacidade do carro como int;

    int d[l];    // declarando array para a demanda;
    int m[l][l]; // declarando um array bidimencional do tamanho da matriz;

    for (int i = 0; i < l; i++) // salva os valores das demandas no array;
    {
        arquivo >> d[i];
    }

    for (int i = 0; i < l; i++) // le toda a matriz e salva na variavel;
    {
        for (int j = 0; j < l; j++)
        {
            arquivo >> m[i][j];
        }
    }

    cout << "Tamanho da matriz: " << l << "x" << l << endl
         << endl;
    cout << "Capacidade: " << c << endl
         << endl;
    cout << "Demandas:" << endl
         << endl;

    for (int i = 0; i < l; i++) // mostra na tela os valores das demandas;
    {
        cout << d[i] << endl;
    }

    cout << "\n\nConteudo da matriz de distancias: \n"
         << endl;

    for (int i = 0; i < l; i++) // mostra na tela todos os valores da matriz
    {
        for (int j = 0; j < l; j++)
        {
            cout << m[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl
         << endl;

    int passou[l] = {0}; // variável que indica se a cidade já foi visitada ou não;
    int posicaoatual = 0;
    int menorvalor = 999;
    int pmv = 0;    // posicao do menor valor
    int nrotas = 0; //numero de rotas
    int distanciatotal = 0;
    int catual = 0; //capacidade atual
    int acabou = 0;
    vector<vector<int>> rotas;
    vector<int> aux;

    cout << "Inicio do VMP" << endl;
    tempoOrdVMP = clock();
    while (1) // deposito
    {
        catual = c;
        posicaoatual = 0;
        passou[0] = 1;
        cout << posicaoatual << " ";
        aux.push_back(posicaoatual);

        while (1) // proxima posicao
        {
            menorvalor = 999;

            for (int i = 0; i < l; i++) // procura proxima posicao
            {
                if (passou[i] == 1)
                    continue;

                if (catual < d[i])
                    continue;

                if (m[posicaoatual][i] < menorvalor)
                {
                    menorvalor = m[posicaoatual][i];
                    pmv = i;
                }
            }

            if (menorvalor == 999)
            {
                distanciatotal += m[posicaoatual][0];
                nrotas++;
                cout << "0" << endl;
                aux.push_back(0);
                rotas.push_back(aux);
                aux.clear();
                break;
            }

            distanciatotal += menorvalor;
            posicaoatual = pmv;
            passou[posicaoatual] = 1;
            catual -= d[posicaoatual];
            cout << posicaoatual << " ";

            aux.push_back(posicaoatual);
        }

        for (int i = 0; i < l; i++)
        {
            if (passou[i] == 0)
            {
                acabou = 0;
                break;
            }

            acabou = 1;
        }

        if (!acabou)
            continue;

        cout << "\nNúmero de rotas: ";
        cout << nrotas << endl;
        cout << "Distancia total pela heuristica do VMP: ";
        cout << distanciatotal << endl;
        break;
    }
    tempoOrdVMP = clock() - tempoOrdVMP;

    printf("\nO tempo de Execucao do VMP foi de:  %f milisegundos\n", ((float)tempoOrdVMP) / CLOCKS_PER_SEC);

    vector<vector<int>> distancias;
    vector<int> auxm;

    for (int i = 0; i < l; i++) //passando a matriz de distancias para um vector
    {
        for (int j = 0; j < l; j++)
        {
            auxm.push_back(m[i][j]);
        }

        distancias.push_back(auxm);
        auxm.clear();
    }

    int resultadoReInsertion = Re_Insertion(rotas, distancias, distanciatotal);
    cout << "\nDistancia final Reinsertion: " << resultadoReInsertion << endl;

    int resultadoTwoOpt = TwoOpt(rotas, distancias, distanciatotal);
    cout << "\nDistancia final 2-Opt: " << resultadoTwoOpt << endl;

    int resultadoSwap = Swap(rotas, distancias, distanciatotal);
    cout << "\nDistancia final Swap: " << resultadoSwap << endl;

    cout << endl
         << "---------------------- VND -----------------------" << endl;
    int resultadoVND = VND(rotas, distancias, distanciatotal);
    cout << endl
         << "Distancia final VND: " << resultadoVND << endl;

    return 0;
}

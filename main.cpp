
#include "Graph.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>

using namespace std;

int main() {
    try {
        string arquivo;
        int opcao;
        int verticeInicial;

        cout << "===== BIBLIOTECA DE GRAFOS =====\n";

        cout << "Digite o nome do arquivo do grafo: ";
        cin >> arquivo;

        cout << "\nEscolha a representacao do grafo:\n";
        cout << "1 - Lista de adjacencia\n";
        cout << "2 - Matriz de adjacencia\n";
        cout << "Opcao: ";
        cin >> opcao;

        Representation representacao;

        if (opcao == 1) {
            representacao = Representation::ADJACENCY_LIST;
        } else if (opcao == 2) {
            representacao = Representation::ADJACENCY_MATRIX;
        } else {
            cout << "Opcao invalida!\n";
            return 1;
        }

        // Cria o grafo a partir do arquivo
        Graph grafo(arquivo, representacao);

        // Exibe as informacoes do grafo
        cout << "\n===== INFORMACOES DO GRAFO =====\n";
        cout << "Numero de vertices: "
             << grafo.getNumVertices() << '\n';

        cout << "Numero de arestas: "
             << grafo.getNumEdges() << '\n';

        cout << "Grau minimo: "
             << grafo.getMinDegree() << '\n';

        cout << "Grau maximo: "
             << grafo.getMaxDegree() << '\n';

        cout << "Grau medio: "
             << grafo.getAverageDegree() << '\n';

        // Solicita o vertice inicial da BFS
        cout << "\nDigite o vertice inicial da BFS: ";
        cin >> verticeInicial;

        // Mede o tempo de execucao da BFS
        auto inicio = chrono::high_resolution_clock::now();

        BFSResult resultado = grafo.bfs(verticeInicial);

        auto fim = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> duracao = fim - inicio;

        // Salva o resultado em arquivo
        string arquivoSaida = "resultado_bfs.txt";

        grafo.saveBFSResult(resultado, arquivoSaida);

        cout << "\n===== RESULTADO DA BFS =====\n";
        cout << "Vertice | Pai | Nivel\n";

        for (int i = 1; i <= grafo.getNumVertices(); i++) {
            cout << "   " << i << "    | "
                 << resultado.parent[i] << "   | "
                 << resultado.level[i] << '\n';
        }

        cout << "\nTempo da BFS: "
             << duracao.count() << " ms\n";

        cout << "Resultado salvo em: "
             << arquivoSaida << '\n';

    } catch (const exception& erro) {
        cerr << "\nErro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}

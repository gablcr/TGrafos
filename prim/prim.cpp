#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>

using namespace std;

typedef pair<int, int> iPair;

struct Grafo {
    int V;
    vector<vector<int>> adj;

    Grafo(int V) : V(V), adj(V, vector<int>(V, 0)) {}

    void addAresta(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w;
    }
};

vector<pair<int, int>> primAGM(const Grafo& grafo) {
    vector<bool> naAGM(grafo.V, false);
    vector<pair<int, int>> arestas;
    vector<int> pesos(grafo.V, INT_MAX);
    vector<int> pais(grafo.V, -1);

    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    pesos[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        naAGM[u] = true;

        for (int v = 0; v < grafo.V; ++v) {
            if (grafo.adj[u][v] && !naAGM[v] && grafo.adj[u][v] < pesos[v]) {
                pesos[v] = grafo.adj[u][v];
                pais[v] = u;
                pq.push({pesos[v], v});
            }
        }
    }

    for (int i = 1; i < grafo.V; ++i)
        arestas.push_back({pais[i], i});

    return arestas;
}

int main(int argc, char *argv[]) {
    string arquivo_entrada = "";
    string arquivo_saida = "";
    bool mostrar_solucao = false;
    int vertice_inicial = 1;

    // Interpretar argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda:" << endl;
            cout << "-h: Ajuda" << endl;
            cout << "-f <arquivo_entrada>: indica o arquivo de input" << endl;
            cout << "-o <arquivo_saida>: direciona o output para o arquivo" << endl;
            cout << "-i: vértice inicial de acordo com o algoritmo de Prim" << endl;
            cout << "-s: solução" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            arquivo_saida = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            arquivo_entrada = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            mostrar_solucao = true;
        } else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            vertice_inicial = atoi(argv[++i]);
        }
    }

    if (arquivo_entrada == "") {
        cerr << "Nenhum arquivo de entrada especificado. Use o parâmetro -f." << endl;
        return 1;
    }

    ifstream fin(arquivo_entrada);
    if (!fin) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << arquivo_entrada << endl;
        return 1;
    }

    int N, m;
    fin >> N >> m;
    Grafo g(N);

    int a, b, wt;
    for (int i = 0; i < m; i++) {
        fin >> a >> b >> wt;
        g.addAresta(a, b, wt);
    }

    fin.close();

    vector<pair<int, int>> arestasAGM = primAGM(g);

    if (!(arquivo_saida == "")) {
        ofstream fout(arquivo_saida);
        if (!fout) {
            cerr << "Não foi possível abrir o arquivo de saída: " << arquivo_saida << endl;
            return 1;
        }

        if (mostrar_solucao) {
            for (const auto& aresta : arestasAGM)
                fout << "(" << aresta.first << "," << aresta.second << ") ";
        } else {
            fout << endl;
        }

        fout.close();
    }

    if (mostrar_solucao) {
        for (const auto& aresta : arestasAGM)
            cout << "(" << aresta.first << "," << aresta.second << ") ";
    } else {
        cout << endl;
    }

    return 0;
}
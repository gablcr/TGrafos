#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<vector<int>> adjTranspose;
    vector<bool> visited;

public:
    Graph(int V);
    void addEdge(int u, int v);
    void DFS(int v, stack<int> &order);
    void DFSUtil(int v, vector<int> &component);
    vector<vector<int>> findSCCs();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
    adjTranspose.resize(V);
    visited.resize(V, false);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adjTranspose[v].push_back(u);
}

void Graph::DFS(int v, stack<int> &order) {
    visited[v] = true;

    for (int u : adj[v]) {
        if (!visited[u]) {
            DFS(u, order);
        }
    }

    order.push(v);
}

void Graph::DFSUtil(int v, vector<int> &component) {
    visited[v] = true;
    component.push_back(v);

    for (int u : adjTranspose[v]) {
        if (!visited[u]) {
            DFSUtil(u, component);
        }
    }
}

vector<vector<int>> Graph::findSCCs() {
    stack<int> order;
    vector<vector<int>> stronglyConnectedComponents;

    // Passo 1: Faz uma DFS e empilha os vértices pela ordem de finalização
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            DFS(i, order);
        }
    }

    // Passo 2: Inverte as arestas do grafo
    reverse(adjTranspose.begin(), adjTranspose.end());

    // Passo 3: Faz DFS nas arestas transpostas usando a ordem de finalização
    fill(visited.begin(), visited.end(), false);
    while (!order.empty()) {
        int v = order.top();
        order.pop();

        if (!visited[v]) {
            vector<int> component;
            DFSUtil(v, component);
            stronglyConnectedComponents.push_back(component);
        }
    }

    return stronglyConnectedComponents;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file> [-o <output_file>] [-s]" << endl;
        cerr << "Use -h for help." << endl;
        return 1;
    }

    string input_file = argv[1];
    string output_file = "";
    bool show_solution = false;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda:" << endl;
            cout << "-h: Ajuda" << endl;
            cout << "-o <output_file>: direciona  o output para o arquivo" << endl;
            cout << "-s: solução" << endl;
            cout << "<input_file>: arquivo de entrada" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            show_solution = true;
        }
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;
    Graph g(V);

    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        g.addEdge(u, v);
    }
    fin.close();

    vector<vector<int>> SCCs = g.findSCCs();

    if (output_file != "") {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        if (show_solution) {
            for (const auto &component : SCCs) {
                fout << "[ ";
                for (int v : component) {
                    fout << v << " ";
                }
                fout << "]" << endl;
            }
        } else {
            fout << "Number of Strongly Connected Components: " << SCCs.size() << endl;
        }
        fout.close();
    }

    if (show_solution) {
        for (const auto &component : SCCs) {
            cout << "[ ";
            for (int v : component) {
                cout << v << " ";
            }
            cout << "]" << endl;
        }
    } else {
        cout << "Number of Strongly Connected Components: " << SCCs.size() << endl;
    }

    return 0;
}
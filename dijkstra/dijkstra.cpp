#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph {
    int V;
    list<pair<int, int>>* adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    vector<int> shortestPath(int src);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<iPair>[V + 1];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

vector<int> Graph::shortestPath(int src) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(V + 1, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& i : adj[u]) {
            int v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    int startVertex = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda:" << endl;
            cout << "-h: Ajuda" << endl;
            cout << "-f <input_file>: indica o arquivo de input" << endl;
            cout << "-o <output_file>: direciona o output para o arquivo" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            startVertex = atoi(argv[++i]);
        }
    }

    if (input_file == "") {
        cerr << "Nenhum arquivo de entrada especificado. Use o parâmetro -f." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;
    Graph g(V);

    int a, b, wt;
    for (int i = 0; i < E; i++) {
        fin >> a >> b >> wt;
        g.addEdge(a, b, wt);
    }

    fin.close();

    vector<int> distances = g.shortestPath(startVertex);

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Não foi possível abrir o arquivo de saída: " << output_file << endl;
            return 1;
        }
        
        for (int i = 1; i <= V; ++i) {
            fout << i << ":" << distances[i] << " ";
        }
        fout << endl;

        fout.close();
    }

    for (int i = 1; i <= V; ++i) {
        cout << i << ":" << distances[i] << " ";
    }
    cout << endl;

    return 0;
}
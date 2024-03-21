#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int end_vertex;
    int weight;
};

void BellmanFord(vector<vector<Edge>>& graph, vector<vector<int>>& weights, int n, int start_vertex) {
    vector<int> distance(n + 1, numeric_limits<int>::max());
    distance[start_vertex] = 0;

    for (int u = 1; u <= n; u++) {
        for (const Edge& edge : graph[u]) {
            int v = edge.end_vertex;
            int weight = edge.weight;

            if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    for (int u = 1; u <= n; u++) {
        for (const Edge& edge : graph[u]) {
            int v = edge.end_vertex;
            int weight = edge.weight;

            if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                cerr << "Negative weight cycle detected." << endl;
                return;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (distance[i] == 2147483647)
        {
             cout << "Não existe caminho no grafo de " << start_vertex << " para " << i << "." << endl;
        }
        else
        cout << "distancia mínima de " << start_vertex << " para " << i << ": " << distance[i] << endl;
    }
}

int main(int argc, char* argv[]) {
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int start_vertex = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help:" << endl;
            cout << "-h: Mostra help" << endl;
            cout << "-o <arquivo>: redireciona output para arquivo" << endl;
            cout << "-f <arquivo>: especifica o arquivo com o grafo de input" << endl;
            cout << "-i: vertice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            input_file = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            start_vertex = atoi(argv[++i]);
        }
    }

    if (input_file == "") {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin;
    fin.open(input_file);

    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    vector<vector<int>> weights(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));

    for (int i = 0; i < m; i++) {
        int u, v, weight;
        fin >> u >> v >> weight;

        if (u < 0 || v < 0) {
            cout << "Invalid input" << endl;
            return 0;
        }

        Edge new_edge;
        new_edge.end_vertex = v;
        new_edge.weight = weight;

        graph[u].push_back(new_edge);
        weights[u][v] = weight;
        weights[v][u] = weight;
    }

    BellmanFord(graph, weights, n, start_vertex);

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

void BellmanFord(vector<vector<int>> graph, int num_vertices, int write_to_file, string output_file, int source_vertex) {
    vector<int> distance(num_vertices, INT_MAX);
    distance[source_vertex - 1] = 0;
    
    for (int i = 0; i < num_vertices - 1; i++) {
        for (auto edge : graph) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            if (distance[u] != INT_MAX && (distance[u] + weight) < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Verifica se há ciclo negativo
    for (auto edge : graph) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        if (distance[u] != INT_MAX && (distance[u] + weight) < distance[v]) {
            cout << "O grafo contém um ciclo negativo!" << endl;
            return;
        }
    }

    // Imprime as distâncias mínimas
    int counter = 1;
    vector<string> write(num_vertices);
    for (auto dist : distance) {
        write[counter - 1] = to_string(counter) + ":" + to_string(dist);
        cout << counter << ":" << dist << " ";
        counter++;
    }
    cout << endl;

    // Escreve no arquivo, se necessário
    if (write_to_file != 0) {
        ofstream file(output_file);
        if (file.is_open()) {
            for (int i = 0; i < num_vertices - 1; i++) {
                file << write[i] << "\n";
            }
            file.close();
            cout << "Array escrito no arquivo com sucesso." << endl;
        } else {
            cout << "Não foi possível criar o arquivo." << endl;
        }
    }
}

int main(int argc, char const *argv[]) {
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int start_vertex = 1;
    int write_to_file = 0;

    // Menu de ajuda
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        cout << "Help:" << endl;
        cout << "-h : Ajuda" << endl;
        cout << "-f <input_file>: indica o arquivo de input" << endl;
        cout << "-o <output_file>: direciona o output para o arquivo" << endl;
        cout << "-i : Vértice inicial" << endl;
        cout << "-s: solução" << endl;
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            write_to_file = 1;
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            show_solution = true;
        } else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            start_vertex = atoi(argv[++i]);
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

    int num_vertices, num_edges;
    fin >> num_vertices >> num_edges;
    vector<vector<int>> graph;
    for (int i = 0; i < num_edges; i++) {
        int u, v, weight;
        fin >> u >> v >> weight;
        u--, v--;  // Para garantir que os vértices sejam zero-indexados
        graph.push_back({u, v, weight});
    }

    fin.close();

    BellmanFord(graph, num_vertices, write_to_file, output_file, start_vertex);

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

struct Network {
    int V, E;
    vector<pair<int, Pair>> links;

    Network(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addLink(int u, int v, int w) {
        links.push_back({w, {u, v}});
    }

    int computeMinimumSpanningTree(vector<pair<int, int>> &mstPairs, int startVertex);
};

struct UnionFind {
    int *parent, *rank;
    int n;

    UnionFind(int n) {
        this->n = n;
        parent = new int[n + 1];
        rank = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);

        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rank[x] == rank[y])
            rank[y]++;
    }
};

int Network::computeMinimumSpanningTree(vector<pair<int, int>> &mstPairs, int startVertex) {
    int mstWeight = 0;
    sort(links.begin(), links.end());
    UnionFind uf(V);

    for (auto &link : links) {
        int u = link.second.first;
        int v = link.second.second;

        int setU = uf.find(u);
        int setV = uf.find(v);

        if (setU != setV) {
            mstPairs.push_back({u, v});
            mstWeight += link.first;
            uf.merge(setU, setV);
        }
    }

    return mstWeight;
}

int main(int argc, char *argv[]) {
    string inputFile = "";
    string outputFile = "";
    bool showSolution = false;
    int startingVertex = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Ajuda:" << endl;
            cout << "-h: Ajuda" << endl;
            cout << "-f <input_file>: indica o arquivo de input" << endl;
            cout << "-o <output_file>: direciona o output para o arquivo" << endl;
            cout << "-i: vértice inicial" << endl;
            cout << "-s: solução" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            inputFile = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            showSolution = true;
        } else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            startingVertex = atoi(argv[++i]);
        }
    }

    if (inputFile == "") {
        cerr << "Nenhum arquivo de entrada especificado. Use o parâmetro -f." << endl;
        return 1;
    }

    ifstream fin(inputFile);
    if (!fin) {
        cerr << "Não foi possível abrir o arquivo de entrada: " << inputFile << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;
    Network network(V, E);

    int a, b, wt;
    for (int i = 0; i < E; i++) {
        fin >> a >> b >> wt;
        network.addLink(a, b, wt);
    }

    fin.close();

    vector<pair<int, int>> mstPairs;

    if (!(outputFile == "")) {
        ofstream fout(outputFile);
        if (!fout) {
            cerr << "Não foi possível abrir o arquivo de saída: " << outputFile << endl;
            return 1;
        }

        if (showSolution) {
            int mstWeight = network.computeMinimumSpanningTree(mstPairs, startingVertex);

            for (const auto &pair : mstPairs) {
                fout << "(" << pair.first << "," << pair.second << ") ";
            }
            fout << endl;
        } else {
            int mstWeight = network.computeMinimumSpanningTree(mstPairs, startingVertex);
            fout << mstWeight << endl;
        }

        fout.close();
    }

    if (showSolution) {
        int mstWeight = network.computeMinimumSpanningTree(mstPairs, startingVertex);

        for (const auto &pair : mstPairs) {
            cout << "(" << pair.first << "," << pair.second << ") ";
        }
        cout << endl;
    } else {
        int mstWeight = network.computeMinimumSpanningTree(mstPairs, startingVertex);
        cout << mstWeight << endl;
    }

    return 0;
}
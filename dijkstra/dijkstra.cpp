#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adjacencia;

void dijkstra(int comeco, ostream& out){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;

    vector<int> distancia(adjacencia.size(), INT_MAX);

    fila.push(make_pair(0, comeco));
    distancia[comeco] = 0;

    while(!fila.empty()){
        int v1 = fila.top().second;
        fila.pop();

        for(const auto &[v2, peso] : adjacencia[v1]){
            if(distancia[v2] > distancia[v1] + peso){
                distancia[v2] = distancia[v1] + peso;
                fila.push(make_pair(distancia[v2], v2));
            }
        }
    }

    for(int i = 0; i < adjacencia.size(); ++i){
        if (distancia[i] == INT_MAX){
            out << i + 1 << ":-1 ";
        }
        else{
            out << i + 1 << ":" << distancia[i] << " ";
        }
    }
}

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    int inicial = 0;

    for(int i = 1; i < argc; i++){
        string arg = argv[i];

        if(arg == "-h"){
            cout << "Help:" << endl;
            cout << "-h: Mostra help" << endl;
            cout << "-o <arquivo>: redireciona output para arquivo" << endl;
            cout << "-f <arquivo>: especifica o arquivo com o grafo de input" << endl;
            cout << "-i: vertice inicial" << endl;
            return 0;
        } 
        else if(arg == "-o" && i < argc - 1){
            output_file = argv[++i];
        } 
        else if(arg == "-f" && i < argc - 1){
            input_file = argv[++i];
        } 
        else if(arg == "-i" && i < argc - 1){
            inicial = atoi(argv[++i]);
            inicial--;
        }
    }

    if(input_file == ""){
        cerr << "Arquivo de entrada nao especificado. Use o parametro -f." << endl;
        return 1;
    }

    ifstream fin(input_file);

    if(!fin){
        cerr << "Nao foi possivel abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int qtd_v, qtd_a;
    fin >> qtd_v >> qtd_a;

    adjacencia.resize(qtd_v);

    for(int i = 0; i < qtd_a; i++){
        int v1, v2, peso;
        fin >> v1 >> v2 >> peso;
        adjacencia[v1-1].emplace_back(v2-1, peso);
        adjacencia[v2-1].emplace_back(v1-1, peso);
    }

    fin.close();

    if(!output_file.empty()){
        ofstream fout(output_file);
        if(!fout){
            cerr << "Nao foi possivel criar o arquivo de saida: " << output_file << endl;
            return 1;
        }
        dijkstra(inicial, fout);
        fout.close();
    } 
    dijkstra(inicial, cout);
    return 0;
}

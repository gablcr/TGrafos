#include <bits/stdc++.h>
using namespace std;

typedef struct solucao{
    vector<int> prev;
    vector<int> custo;
}prim_solucao;

prim_solucao prim(int n, vector<vector<pair<int,int>>> graph, int r)
{
    priority_queue<pair<int, int>,vector<pair<int, int> >, greater<pair<int, int>>> pq;

    vector<bool> visitado(n, false);
    vector<int> custo(n, INT_MAX);
    vector<int> prev(n, -1);
    
    custo[r] = 0;
    pq.push({0, r});
    
    while(!pq.empty()){
        auto v = pq.top();
        pq.pop();

        int node = v.second;
        int wt = v.first;
        
        visitado[node] = true;

        for (auto u: graph[node]){
            int w = u.first;
            int p = u.second;
            if (!visitado[w] && p < custo[w]){
                custo[w] = p;
                pq.push({p, w});
                prev[w] = node;
            }
        }
    }
    
    prim_solucao solucao;
    solucao.prev = prev;
    solucao.custo = custo;
    return solucao;
}



int main(int argc, char *argv[]){

    string input_file = "";
    string output_file = "";
    int inicial = 1;
    int printagm = 0;

    for(int i = 0; i < argc; i++){
        string arg = argv[i];

        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: Mostra help" << endl;
            cout << "-o <arquivo>: redireciona output para arquivo" << endl;
            cout << "-f <arquivo>: especifica o arquivo com o grafo de input" << endl;
            cout << "-s: solução" << endl;
            cout << "-i: vertice inicial" << endl;
            return 0;;
        }
        else if(arg == "-o" && i < argc - 1){
            output_file = argv[++i];
        } 
        else if(arg == "-f" && i < argc - 1){
            input_file = argv[++i];
        } 
        else if(arg == "-s"){
            printagm = 1;
        }
        else if(arg == "-i" && i < argc - 1){
            inicial = atoi(argv[++i]);
            inicial--;
        }

    }
    ifstream fin(input_file);
    if(fin.fail() == 1){
        cout << "Arquivo não encontrado";
        return 1;
    }
    if(input_file == ""){
        cerr << "Arquivo de entrada nao especificado. Use o parametro -f." << endl;
        return 1;
    }

    if(!fin){
        cerr << "Nao foi possivel abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }
    
    int qtd_v, qtd_a;
    fin >> qtd_v >> qtd_a;
    if(inicial >= qtd_v || inicial < 0){
        cout << "Vertice inicial nao pertence ao grafo";
        return 2;
    }
    

	vector<vector<pair<int,int>>> graph(qtd_v);

    for(int i = 0; i < qtd_a; i++){
        int v1, v2, p;
        fin >> v1 >> v2 >> p;
        pair<int, int> edge;
        edge.first = v2 - 1;
        edge.second = p;
        graph[v1 - 1].push_back(edge);

        edge.first = v1 - 1;
        graph[v2 - 1].push_back(edge);
    }

    fin.close();

    vector<vector<int>> graph_agm(qtd_v);
	prim_solucao result = prim(qtd_v, graph, inicial);


    int soma = 0;

    for(int peso: result.custo){
        soma += peso;
    }
    for(int i = 0; i < qtd_v; i++){
        if (result.prev[i] != -1)
            graph_agm[i].push_back(result.prev[i]);
    }
    if(!output_file.empty()){
        ofstream fout(output_file);
        if(fout.fail() == 1){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }
        if(printagm==1){
            for (int i = 0; i < graph_agm.size(); i++)
                if (graph_agm[i].size() > 0)
                    for (int v: graph_agm[i])
                        fout << "(" << i + 1 << "," << v + 1 << ") ";
        }
        else{
            fout << soma << endl;
        }
        fout.close();
    }
    if(printagm==1){
        for (int i = 0; i < graph_agm.size(); i++){
            if (graph_agm[i].size() > 0)
                for (int v: graph_agm[i]){
                    cout << "(" << i + 1 << "," << v + 1 << ") ";
                }
        }
    }
    else{
        cout << soma << endl;
    }

	return 0;
}

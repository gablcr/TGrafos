#include <bits/stdc++.h>
using namespace std;

struct edge{
    int v1;
    int v2;
    int peso;
};

int soma = 0;

vector<int>pai, rank0;

int Find(int x){
    if(pai[x]!=x){
        pai[x] = Find(pai[x]);
    }
    return pai[x];
}

void Makeset(int x){
    pai[x]=x;
    rank0[x]=0;
}

void Union(int x, int y){
    if(rank0[x]>=rank0[y]){
        pai[y]=x;
        if(rank0[x]==rank0[y]){
            rank0[x]+=1;
        }
    }
    else{
        pai[x]=y;
    }
}

vector<edge> kruskal(int vertices, vector<edge> arestas){
    pai.resize(vertices);
    rank0.resize(vertices);

    for(int i=0; i<vertices; i++){
        Makeset(i);
    }

    sort(arestas.begin(), arestas.end(), [](const edge& a, const edge& b){
        return a.peso < b.peso;
    });

    vector<edge> mst;

    for(auto& aresta : arestas){
        int peso = aresta.peso;
        int par1 = aresta.v1;
        int par2 = aresta.v2;

        if(Find(par1) != Find(par2)){
            mst.push_back(aresta);
            soma += aresta.peso;
            Union(Find(par1), Find(par2));
        }
    }

    return mst;
}

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    int solucao = 0;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: Mostra help" << endl;
            cout << "-o <arquivo>: redireciona output para arquivo" << endl;
            cout << "-f <arquivo>: especifica o arquivo com o grafo de input" << endl;
            cout << "-i: vertice inicial" << endl;
            cout << "-s: solução" << endl;
            return 0;
        }
        else if(strcmp(argv[i], "-o") == 0 && i < argc - 1){
            output_file = argv[++i];
        }
        else if(strcmp(argv[i], "-f") == 0 && i < argc - 1){
            input_file = argv[++i];
        }
        else if(strcmp(argv[i], "-s") == 0){
            solucao = 1;
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

    vector<edge> edges;
    int v1, v2, p;
    for(int i = 0; i < qtd_a; i++){
        fin >> v1 >> v2 >> p;
        edges.push_back({v1-1, v2-1, p});
    }

    fin.close();
    vector<edge> MST = kruskal(qtd_v, edges);
    
    if(!output_file.empty()){
        ofstream fout(output_file);
        if(fout.fail() == 1){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }
        if(solucao==1){
            for (const auto& aresta : MST)
                fout << "(" << aresta.v1 + 1 << "," << aresta.v2 + 1 << ") ";
        }
        else{
            fout << soma << endl;
        }
        fout.close();
    }

    if(solucao == 1){
        for(const auto& aresta : MST){
            cout << "(" << aresta.v1 + 1 << "," << aresta.v2 + 1 << ") ";
        }
    }
    else{
        cout << soma << endl;
    }

    return 0;
}

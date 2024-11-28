#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

struct node {
    int vertex;
    int weight;
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }

    bool operator==(const Edge& other) const {
        return u == other.u && v == other.v && w == other.w;
    }
};

node make_node(int vertex, int weight) {
    node n;
    n.vertex = vertex;
    n.weight = weight;
    return n;
}

class Graph{
    public:
        vector<vector<node>> adj_list;
        vector<Edge> edge_list;
        int num_V;
        int num_E;
        char type;

        Graph(int num_V, int num_E, int type) {
            this->num_V = num_V;
            this->num_E = num_E;
            this->type = type;
            adj_list = vector<vector<node>>(num_V, vector<node>());
            edge_list = vector<Edge>();
        }

        void add_edge(int u, int v, int w) {
            node n1 = make_node(v, w);

            edge_list.push_back({u, v, w});

            adj_list[u].push_back(n1);
            if (type == 'u') {
                node n2 = make_node(u, w);
                adj_list[v].push_back(n2);
            }
        }

    vector<Edge> kruskalMST();
};

// Disjoint Set Union (DSU) or Union-Find for Kruskal's algorithm
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v]) {
                parent[u] = v;
            } else if (rank[u] > rank[v]) {
                parent[v] = u;
            } else {
                parent[v] = u;
                rank[u]++;
            }
        }
    }
};

vector<Edge> Graph::kruskalMST() {
    sort(edge_list.begin(), edge_list.end());
    DSU dsu(num_V);
    vector<Edge> mst; // record the edges in the MST
    for(int i = num_E - 1; i >= 0; i--) { // start from the largest weight
        if (dsu.find(edge_list[i].u) != dsu.find(edge_list[i].v)) {
            dsu.unite(edge_list[i].u, edge_list[i].v);
            mst.push_back(edge_list[i]);
        }
    }
    return mst;
}


int main(int argc, char* argv[])
{
    if (argc != 3) {
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return 1;
    }

    auto start = chrono::high_resolution_clock::now();

    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    char type;
    int num_V, num_E, junk;
    fin >> type >> num_V >> num_E; // type = u or d (undirected or directed)
    
    Graph G(num_V, num_E, type);

    for (int i = 0; i < num_E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        G.add_edge(u, v, w);
    }

    fin >> junk; // should be 0

    vector<Edge> mst = G.kruskalMST();

    int remove_weight = 0;
    vector<Edge> non_mst;
    for(auto& e : G.edge_list) {
        if (find(mst.begin(), mst.end(), e) == mst.end()) {
            remove_weight += e.w;
            non_mst.push_back(e);
        }
    }

    fout << remove_weight << endl;
    for(auto& e : non_mst) {
        fout << e.u << " " << e.v << " " << e.w << endl;
    }

    // Stop measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Total running time: " << elapsed.count() << " seconds" << endl;

    fin.close();
    fout.close();
    return 0;
}
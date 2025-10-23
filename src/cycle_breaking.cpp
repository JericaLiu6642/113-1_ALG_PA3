#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

struct node {
    int vertex;
    int weight;
};

// AI generated begin
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
// AI generated end

class Graph{
    public:
        vector<vector<node>> adj_list;
        vector<vector<node>> reverse_adj_list;
        vector<Edge> edge_list;
        int num_V;
        int num_E;
        char type;
        int remove_weight; // for directed graph only
        bool has_cycle; // for directed graph only
        vector<Edge> remove_edge; // for directed graph only

        Graph(int num_V, int num_E, int type) { // constructor
            this->num_V = num_V;
            this->num_E = num_E;
            this->type = type;
            remove_weight = 0;
            has_cycle = true;
            adj_list = vector<vector<node>>(num_V, vector<node>());
            reverse_adj_list = vector<vector<node>>(num_V, vector<node>());
            edge_list = vector<Edge>();
            remove_edge = vector<Edge>();
        }

        void add_edge(int u, int v, int w) {
            if(type == 'u'){
                edge_list.push_back({u, v, w});
            }
            else{
                edge_list.push_back({u, v, w});
                node n1 = make_node(v, w);
                adj_list[u].push_back(n1);
                node n2 = make_node(u, w);
                reverse_adj_list[v].push_back(n2);
            }
        }

    vector<Edge> kruskalMST();
    void DFS1(int u, vector<bool>& visited, stack<int>& s);
    void DFS2(int u, vector<bool>& visited, vector<int>& scc);
    void SCC();
    void edge_removal(vector<int>& scc);
    bool topological_sort();
};

// AI generated begin
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

void Graph::DFS1(int u, vector<bool>& visited, stack<int>& s) {
    visited[u] = true;
    for (auto& n : adj_list[u]) {
        if (!visited[n.vertex]) {
            DFS1(n.vertex, visited, s);
        }
    }
    s.push(u);
}

void Graph::DFS2(int u, vector<bool>& visited, vector<int>& scc) {
    visited[u] = true;
    scc.push_back(u);
    for (auto& n : reverse_adj_list[u]) {
        if (!visited[n.vertex]) {
            DFS2(n.vertex, visited, scc);
        }
    }
}
// AI generated end

void Graph::SCC() {
    vector<bool> visited(num_V, false);
    stack<int> s;
    for (int i = 0; i < num_V; i++) {
        if (!visited[i]) {
            DFS1(i, visited, s);
        }
    }

    visited.assign(num_V, false);
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        if (!visited[u]) {
            vector<int> scc;
            DFS2(u, visited, scc);
            
            if(scc.size() > 1){
                has_cycle = true;
                edge_removal(scc);
                // if one edge is removed, we need to recompute the SCC
                return;
            }
        }
    }

    // if no edge is removed, means the graph is acyclic
    has_cycle = false;
    return;
}

void Graph::edge_removal(vector<int>& scc) {
    int min_weight = INT_MAX;
    int min_u, min_v; // the vertices of the lightest edge in the SCC
    for (int i = 0; i < scc.size(); i++) {
        for (auto& n : adj_list[scc[i]]) {
            if (find(scc.begin(), scc.end(), n.vertex) != scc.end()) {
                if (n.weight < min_weight) {
                    min_weight = n.weight;
                    min_u = scc[i];
                    min_v = n.vertex;
                }
            }
        }
    }

    // record the edge to be removed
    remove_weight += min_weight;
    remove_edge.push_back({min_u, min_v, min_weight});
    
    // remove the edge from the adjacency list
    for (auto it = adj_list[min_u].begin(); it != adj_list[min_u].end(); ++it) {
        if (it->vertex == min_v) {
            adj_list[min_u].erase(it);
            break; // Exit the loop after erasing the element
        }
    }

    for (auto it = reverse_adj_list[min_v].begin(); it != reverse_adj_list[min_v].end(); ++it) {
        if (it->vertex == min_u) {
            reverse_adj_list[min_v].erase(it);
            break; // Exit the loop after erasing the element
        }
    }

    return;
}

// check acyclic
bool Graph::topological_sort() {
    vector<int> in_degree(num_V, 0);
    for (int i = 0; i < num_V; i++) {
        for (auto& n : adj_list[i]) {
            in_degree[n.vertex]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < num_V; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    int count = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        count++;
        for (auto& n : adj_list[u]) {
            if (--in_degree[n.vertex] == 0) {
                q.push(n.vertex);
            }
        }
    }

    return count == num_V;
}


int main(int argc, char* argv[])
{
    if (argc != 3) {
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return 1;
    }

    //auto start = chrono::high_resolution_clock::now();

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

    // for undirected graph we try to find the maximum spanning tree
    if(type == 'u'){
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
        /*
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Total running time: " << elapsed.count() << " seconds" << endl;*/
    }
    else{ // for directed graph we try to find SCCs and remove the lightest edge
        G.SCC();
        while(G.has_cycle){
            G.SCC();
        }

        fout << G.remove_weight << endl;
        for(auto& e : G.remove_edge) {
            fout << e.u << " " << e.v << " " << e.w << endl;
        }
        
        /*
        // check if the graph is acyclic
        if (G.topological_sort()) {
            cout << "The graph is acyclic" << endl;
        } else {
            cout << "The graph has a cycle" << endl;
        }

        // Stop measuring time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Total running time: " << elapsed.count() << " seconds" << endl;
        */
    }
    

    fin.close();
    fout.close();
    return 0;
}
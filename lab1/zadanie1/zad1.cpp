#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>

struct Edge {
    int u;
    int v;
};

class Graph {
private:
    int n;
    int m;
    bool directed;
    std::vector<std::vector<int>> adj;

public:
    Graph(int vertices, int edges, bool is_directed) 
        : n(vertices), m(edges), directed(is_directed), adj(vertices + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) {
            adj[v].push_back(u);
        }
    }

    int get_n() const { return n; }
    int get_m() const { return m; }
    bool is_directed() const { return directed; }

    void run_bfs(bool print_tree) const {
        std::vector<bool> visited(n + 1, false);
        std::vector<int> visit_order;
        std::vector<Edge> tree_edges;

        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                std::queue<int> q;
                visited[i] = true;
                q.push(i);

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    visit_order.push_back(u);

                    for (int v : adj[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            tree_edges.push_back({u, v});
                            q.push(v);
                        }
                    }
                }
            }
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        std::cout << "\n--- BFS ---" << std::endl;
        std::cout << "Kolejnosc odwiedzin (" << visit_order.size() << " wierzcholkow):" << std::endl;
        for (int v : visit_order) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        if (print_tree) {
            std::cout << "Krawedzie drzewa BFS (" << tree_edges.size() << " krawedzi):" << std::endl;
            for (const auto& edge : tree_edges) {
                std::cout << edge.u << " -> " << edge.v << "\n";
            }
        }
        std::cout << "Czas wykonania BFS: " << elapsed.count() << " ms\n";
    }

    void dfs_visit(int u, std::vector<bool>& visited, std::vector<int>& visit_order, std::vector<Edge>& tree_edges) const {
        visited[u] = true;
        visit_order.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                tree_edges.push_back({u, v});
                dfs_visit(v, visited, visit_order, tree_edges);
            }
        }
    }

    void run_dfs(bool print_tree) const {
        std::vector<bool> visited(n + 1, false);
        std::vector<int> visit_order;
        std::vector<Edge> tree_edges;

        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                dfs_visit(i, visited, visit_order, tree_edges);
            }
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        std::cout << "\n--- DFS ---" << std::endl;
        std::cout << "Kolejnosc odwiedzin (" << visit_order.size() << " wierzcholkow):" << std::endl;
        for (int v : visit_order) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        if (print_tree) {
            std::cout << "Krawedzie drzewa DFS (" << tree_edges.size() << " krawedzi):" << std::endl;
            for (const auto& edge : tree_edges) {
                std::cout << edge.u << " -> " << edge.v << "\n";
            }
        }
        std::cout << "Czas wykonania DFS: " << elapsed.count() << " ms\n";
    }
};

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    bool print_tree = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--tree") {
            print_tree = true;
        }
    }

    char type;
    if (!(std::cin >> type)) {
        return 0;
    }

    bool is_directed = (type == 'D' || type == 'd');
    int n, m;
    std::cin >> n >> m;

    Graph g(n, m, is_directed);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    g.run_bfs(print_tree);
    g.run_dfs(print_tree);

    return 0;
}
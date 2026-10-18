#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

class TopologicalSort {
private:
    int n;
    int m;
    bool directed;
    std::vector<std::vector<int>> adj;
    std::vector<int> in_degree;

public:
    TopologicalSort(int vertices, int edges, bool is_directed)
        : n(vertices), m(edges), directed(is_directed), adj(vertices + 1), in_degree(vertices + 1, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        in_degree[v]++;
    }

    void run() const {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::vector<int> current_in_degree = in_degree;
        std::queue<int> q;

        for (int i = 1; i <= n; ++i) {
            if (current_in_degree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> topo_order;
        topo_order.reserve(n);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);

            for (int v : adj[u]) {
                current_in_degree[v]--;
                if (current_in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        if (static_cast<int>(topo_order.size()) == n) {
            std::cout << "Graf nie ma cyklu\n";
            if (n <= 200) {
                std::cout << "Porzadek topologiczny (" << topo_order.size() << " wierzcholkow):\n";
                for (int v : topo_order) {
                    std::cout << v << " ";
                }
                std::cout << "\n";
            }
        } else {
            std::cout << "Graf ma cykl\n";
        }

        std::cout << "Czas wykonania: " << elapsed.count() << " ms\n";
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char type;
    if (!(std::cin >> type)) return 0;

    bool is_directed = (type == 'D' || type == 'd');
    int n, m;
    std::cin >> n >> m;

    TopologicalSort g(n, m, is_directed);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    g.run();

    return 0;
}
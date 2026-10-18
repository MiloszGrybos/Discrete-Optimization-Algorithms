#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

class BipartiteChecker {
private:
    int n;
    int m;
    bool directed;
    std::vector<std::vector<int>> adj;

public:
    BipartiteChecker(int vertices, int edges, bool is_directed)
        : n(vertices), m(edges), directed(is_directed), adj(vertices + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void check_bipartite() const {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::vector<int> color(n + 1, -1);
        bool is_bipartite = true;

        for (int i = 1; i <= n; ++i) {
            if (color[i] != -1) continue;

            std::queue<int> q;
            color[i] = 0;
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        is_bipartite = false;
                        break;
                    }
                }
                if (!is_bipartite) break;
            }
            if (!is_bipartite) break;
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        if (is_bipartite) {
            std::cout << "Graf jest dwudzielny.\n";
            if (n <= 200) {
                std::vector<int> v0, v1;
                for (int i = 1; i <= n; ++i) {
                    if (color[i] == 0) {
                        v0.push_back(i);
                    } else {
                        v1.push_back(i);
                    }
                }

                std::cout << "Podzbior V0 (" << v0.size() << " wierzcholkow): ";
                for (int v : v0) std::cout << v << " ";
                std::cout << "\n";

                std::cout << "Podzbior V1 (" << v1.size() << " wierzcholkow): ";
                for (int v : v1) std::cout << v << " ";
                std::cout << "\n";
            }
        } else {
            std::cout << "Graf nie jest dwudzielny.\n";
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

    BipartiteChecker graph(n, m, is_directed);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.add_edge(u, v);
    }

    graph.check_bipartite();

    return 0;
}
#include <iostream>
#include <vector>
#include <chrono>

class SCCKosaraju {
private:
    int n;
    int m;
    bool directed;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> adj_rev;

public:
    SCCKosaraju(int vertices, int edges, bool is_directed)
        : n(vertices), m(edges), directed(is_directed), 
          adj(vertices + 1), adj_rev(vertices + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    void iterative_dfs1(int start_node, std::vector<bool>& visited, std::vector<int>& order) const {
        std::vector<std::pair<int, size_t>> st;
        visited[start_node] = true;
        st.push_back({start_node, 0});

        while (!st.empty()) {
            int u = st.back().first;
            size_t& edge_idx = st.back().second;

            if (edge_idx < adj[u].size()) {
                int v = adj[u][edge_idx];
                edge_idx++;
                if (!visited[v]) {
                    visited[v] = true;
                    st.push_back({v, 0});
                }
            } else {
                order.push_back(u);
                st.pop_back();
            }
        }
    }

    void iterative_dfs2(int start_node, std::vector<bool>& visited, std::vector<int>& current_component) const {
        std::vector<int> st;
        visited[start_node] = true;
        st.push_back(start_node);

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            current_component.push_back(u);

            for (int v : adj_rev[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    st.push_back(v);
                }
            }
        }
    }

    void find_scc() const {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::vector<bool> visited(n + 1, false);
        std::vector<int> order;
        order.reserve(n);

        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                iterative_dfs1(i, visited, order);
            }
        }

        std::fill(visited.begin(), visited.end(), false);
        std::vector<std::vector<int>> scc_list;

        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (!visited[u]) {
                std::vector<int> current_component;
                iterative_dfs2(u, visited, current_component);
                scc_list.push_back(current_component);
            }
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        std::cout << "Liczba silnie spojnych skladowych: " << scc_list.size() << "\n";
        for (size_t i = 0; i < scc_list.size(); ++i) {
            std::cout << "Skladowa " << (i + 1) << ": " << scc_list[i].size() << " wierzcholkow";
            if (n <= 200) {
                std::cout << " -> wierzcholki: ";
                for (int v : scc_list[i]) {
                    std::cout << v << " ";
                }
            }
            std::cout << "\n";
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

    SCCKosaraju g(n, m, is_directed);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    g.find_scc();

    return 0;
}
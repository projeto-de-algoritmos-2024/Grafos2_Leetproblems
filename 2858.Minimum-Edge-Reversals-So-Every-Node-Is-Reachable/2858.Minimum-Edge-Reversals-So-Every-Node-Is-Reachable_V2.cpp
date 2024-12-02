class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> graph(n); // Lista de adjacência: {vizinho, custo}
        vector<int> reversals(n, 0); // Reversões necessárias para cada nó
        vector<int> result(n, 0);    // Resultado final
        
        // Construir o grafo: custo 0 para aresta direta, custo 1 para aresta inversa
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].emplace_back(v, 0); // Aresta direta
            graph[v].emplace_back(u, 1); // Aresta inversa
        }
        
        // DFS para calcular o custo total inicial usando o nó 0 como raiz
        function<void(int, int)> dfsCount = [&](int node, int parent) {
            for (auto& [neighbor, cost] : graph[node]) {
                if (neighbor != parent) {
                    reversals[0] += cost; // Contar reversões necessárias
                    dfsCount(neighbor, node);
                }
            }
        };
        
        // DFS para reaproveitar os custos para todos os outros nós
        function<void(int, int)> dfsRecompute = [&](int node, int parent) {
            for (auto& [neighbor, cost] : graph[node]) {
                if (neighbor != parent) {
                    // Ajustar o custo de reversões ao mudar a raiz
                    reversals[neighbor] = reversals[node] + (cost == 0 ? 1 : -1);
                    dfsRecompute(neighbor, node);
                }
            }
        };
        
        dfsCount(0, -1);     // Inicializar reversals[0] usando o nó 0 como raiz
        dfsRecompute(0, -1); // Reaproveitar o custo para os outros nós
        
        // O vetor reversals agora contém os custos mínimos para cada nó
        return reversals;
    }
};

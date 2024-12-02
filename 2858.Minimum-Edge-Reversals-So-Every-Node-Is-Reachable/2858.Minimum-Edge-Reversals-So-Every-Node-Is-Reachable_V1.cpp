class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> graph(n); // Lista de adjacência: {vizinho, custo}
    
    // Construir o grafo modificado
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        graph[u].push_back({v, 0}); // Aresta direta (custo 0)
        graph[v].push_back({u, 1}); // Aresta inversa (custo 1)
    }
    
    // Função para rodar Dijkstra a partir de um nó inicial
    auto dijkstra = [&](int start) {
        vector<int> dist(n, INT_MAX); // Distâncias iniciais como infinito
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Min-Heap {custo, nó}
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();
            
            if (cost > dist[node]) continue;
            
            for (auto& [neighbor, weight] : graph[node]) {
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }
        
        return dist;
    };
    
    vector<int> answer(n);
    
    // Calcular o resultado para cada nó
    for (int i = 0; i < n; ++i) {
        auto dist = dijkstra(i);
        
        // A resposta para o nó i é o máximo custo no vetor de distâncias
        int maxDist = *max_element(dist.begin(), dist.end());
        answer[i] = (maxDist == INT_MAX) ? -1 : maxDist; // Verificar se é impossível alcançar algum nó
    }
    
    return answer;
}};

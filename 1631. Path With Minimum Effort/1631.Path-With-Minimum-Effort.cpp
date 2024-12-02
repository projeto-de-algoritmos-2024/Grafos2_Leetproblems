class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        
        // Deltas para os 4 movimentos possíveis (cima, baixo, esquerda, direita)
        vector<int> directions = {-1, 0, 1, 0, 0, -1, 0, 1};
        
        // Matriz para armazenar o esforço mínimo até cada célula
        vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
        effort[0][0] = 0;  // Iniciamos no topo esquerdo
        
        // Fila de prioridade para Dijkstra (min-heap)
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, 0, 0});  // Começamos na célula (0, 0) com esforço 0
        
        while (!pq.empty()) {
            // Desempilhar o nó atual (célula)
            int x = pq.top()[0];
            int y = pq.top()[1];
            int currentEffort = pq.top()[2];
            pq.pop();
            
            // Se já chegamos na célula final, podemos retornar o esforço
            if (x == m - 1 && y == n - 1) {
                return currentEffort;
            }
            
            // Explorar os vizinhos
            for (int i = 0; i < 4; i++) {
                int newX = x + directions[i * 2];
                int newY = y + directions[i * 2 + 1];
                
                // Verificar se o vizinho está dentro dos limites da matriz
                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                    // Calcular a diferença de altura (esforço)
                    int newEffort = max(currentEffort, abs(heights[newX][newY] - heights[x][y]));
                    
                    // Se encontramos um caminho com menor esforço até o vizinho
                    if (newEffort < effort[newX][newY]) {
                        effort[newX][newY] = newEffort;
                        pq.push({newX, newY, newEffort});
                    }
                }
            }
        }
        
        return 0;
    }
};

class Solution {
public:
  struct estado {
    //variaveis para armazenar o no e o tempo 
    int tempo, no;
    estado(int t, int n) : tempo(t), no(n) {}
    bool operator>(const estado& other) const {
        return tempo > other.tempo;
    }
};

int secondMinimum(int n, vector<vector<int>>& arestas, int tempo, int mudancas) {
    //construindo o grafo 
    vector<vector<int>> grafo(n + 1);
    for (const auto& aresta : arestas) {
        grafo[aresta[0]].push_back(aresta[1]);
        grafo[aresta[1]].push_back(aresta[0]);
    }
    
    //controlando o tempo 
    vector<vector<int>> tempo(n + 1, vector<int>(2, INT_MAX));
    tempo[1][0] = 0;

    //fila de prioridade 
    priority_queue<estado, vector<estado>, greater<>> fila;
    fila.emplace(0, 1);


    //processando a fila 
    while (!fila.empty()) {
        auto [temp, no] = fila.top();
        fila.pop();

        for (int vizinho : grafo[no]) {
            int temporizador = temp + tempo;

            // Ajustar o tempo de acordo com o semáforo
            if ((temp / mudancas) % 2 == 1) {
                temporizador += mudancas - (temp % mudancas);
            }

            // Atualizar os tempos do vizinho
            if (temporizador < tempo[vizinho][0]) {
                tempo[vizinho][1] = tempo[vizinho][0];
                tempo[vizinho][0] = temporizador;
                fila.emplace(temporizador, vizinho);
            } else if (temporizador > tempo[vizinho][0] && temporizador < tempo[vizinho][1]) {
                tempo[vizinho][1] = temporizador;
                fila.emplace(temporizador, vizinho);
            }
        }
    }

    return tempo[n][1] == INT_MAX ? -1 : tempo[n][1];
}

};

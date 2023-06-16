#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

int encontraLoc(string str, string entrada) {
    int loc = str.find(entrada);
    if (loc != string::npos) {
        return loc;
    }
    return -1;
}

// função para verificar se a palavra existe no alfabeto
bool testaPalavra(vector<vector<string>> matriz, string palavra, string estFinais, string alfabeto,
                  string estados) {
    int locEntrada = 0;
    int estadoAtual = 0;
    string entrada;

    // verifica se a palavra está no alfabeto
    for (auto letra: palavra) {
        cout << "Letra: " << letra << endl;
        cout << "Estado: " << matriz[0][estadoAtual] << endl;
        entrada = letra;
        locEntrada = encontraLoc(alfabeto, entrada);
        estadoAtual = encontraLoc(estados, matriz[estadoAtual + 2][locEntrada]);
        if (estadoAtual == -1) {
            return false;
        }
        cout << "Estado atual: " << estadoAtual << endl;
    }
    auto estFinal = matriz[0][estadoAtual];
    if (encontraLoc(estFinal, std::move(estFinais)) != -1) {
        return true;
    }

    return false;

}


int main() {
    // get all from user
    string estados;
    string alfabeto;
    string estInicial;
    string estFinais;
    string palavra;
    string entrada;
    int locEntrada = 0;
    int estadoAtual = 0;
    vector<vector<string>> matriz;
    vector<string> palavras;

    // get all from user, get line
    cout << "Digite os estados: ";
    // get inteire line
    getline(cin, estados);


    cout << "Digite o alfabeto: ";
    getline(cin, alfabeto);

    // preenche a matriz com os estados
    matriz.emplace_back();
    for (auto estado: estados) {
        matriz[0].emplace_back(1, estado);
    }

    // printa a matriz
    cout << "Matriz: " << endl;
    for (const auto &estado: matriz[0]) {
        cout << estado << " ";
    }
    cout << endl;
    // pega as transições
    for (int i = 0; i < estados.size(); i++) {
        matriz.emplace_back();
        for (char j: alfabeto) {
            cout << "\nDigite a transição de " << estados[i] << " com " << j << ": ";
            getline(cin, entrada);
            matriz[i + 1].push_back(entrada);
        }
    }

    // pega os estado inicial e final
    cout << "\nDigite o estado inicial: ";
    cin >> estInicial;
    cout << "Digite o estado final: ";
    getline(cin, estFinais);

    // pega quantas palavras
    int qtdPalavras;
    cout << "Digite a quantidade de palavras: ";
    cin >> qtdPalavras;

    // pega as palavras
    for (int i = 0; i < qtdPalavras; i++) {
        palavra = "";
        cout << "Digite a palavra: ";
        getline(cin, palavra);
        palavras.push_back(palavra);
    }
    // testa os estados
    for (const auto &p: palavras) {
        if (testaPalavra(matriz, p, estFinais, alfabeto, estados)) {
            cout << p << ": Aceita" << endl;
        } else {
            cout << p << ": Rejeita" << endl;
        }
    }


    return 0;
}

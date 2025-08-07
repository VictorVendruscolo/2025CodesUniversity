
// Questão 1 - Fila Encadeada com Template (4,0 pts)
#include <iostream>
using namespace std;

template<typename T>
class Fila {
private:
    struct No {
        T dado;
        No* prox;
        No(const T& d) : dado(d), prox(nullptr) {}
    };
    No* inicio;
    No* fim;
    int tamanho;

public:
    Fila() : inicio(nullptr), fim(nullptr), tamanho(0) {}

    ~Fila() {
        while (inicio) pop();
    }

    void push(const T& valor) {
        No* novo = new No(valor);
        if (!fim) {
            inicio = fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
        tamanho++;
    }

    T pop() {
        if (!inicio) throw runtime_error("Fila vazia!");
        No* temp = inicio;
        T valor = temp->dado;
        inicio = inicio->prox;
        if (!inicio) fim = nullptr;
        delete temp;
        tamanho--;
        return valor;
    }

    T& operator[](int indice) {
        if (indice < 0 || indice >= tamanho) throw out_of_range("");
        No* atual = inicio;
        for (int i = 0; i < indice; ++i)
            atual = atual->prox;
        return atual->dado;
    }

    int size() const { return tamanho; }
};

void testeFila() {
    Fila<int> f;
    f.push(10);
    f.push(20);
    f.push(30);

    cout << "Elemento no indice 1: " << f[1] << endl;
    f[1] = 25;
    cout << "Novo valor no indice 1: " << f[1] << endl;

    while (f.size()) {
        cout << "Removido: " << f.pop() << endl;
    }
}

int main() {
    testeFila();
    return 0;
}

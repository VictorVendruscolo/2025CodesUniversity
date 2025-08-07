#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class PilhaDinamica {
private:
    std::unique_ptr<T[]> elementos; // Array dinâmico gerenciado
    size_t capacidade;              // Capacidade atual da pilha
    size_t topo;                    // Índice do topo da pilha
    const size_t capacidadeInicial; // Capacidade inicial da pilha

    void redimensionar(size_t novaCapacidade) {
        // Cria um novo array com a nova capacidade
        std::unique_ptr<T[]> novoArray = std::make_unique<T[]>(novaCapacidade);

        // Copia os elementos existentes para o novo array
        for (size_t i = 0; i < topo; ++i) {
            novoArray[i] = std::move(elementos[i]);
        }

        // Substitui o array antigo pelo novo
        elementos = std::move(novoArray);
        capacidade = novaCapacidade;
    }

    void ajustarCapacidade() {
        if (topo > capacidade) {
            redimensionar(capacidade * 2); // Dobra a capacidade
        } else if (topo < capacidade / 2 && capacidade > capacidadeInicial) {
            redimensionar(capacidade / 2); // Reduz a capacidade pela metade
        }
    }

public:
    PilhaDinamica(size_t capacidadeInicial = 10)
        : capacidade(capacidadeInicial), topo(0), capacidadeInicial(capacidadeInicial) {
        elementos = std::make_unique<T[]>(capacidadeInicial);
    }

    void push(const T& elemento) {
        if (topo == capacidade) {
            ajustarCapacidade(); // Ajusta a capacidade se necessário
        }
        elementos[topo++] = elemento;
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Pilha vazia");
        }
        --topo;
        ajustarCapacidade(); // Ajusta a capacidade se necessário
    }

    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Pilha vazia");
        }
        return elementos[topo - 1];
    }

    bool isEmpty() const {
        return topo == 0;
    }

    size_t size() const {
        return topo;
    }
};

int main() {
    PilhaDinamica<int> pilha;

    // Testando a pilha
    for (int i = 1; i <= 20; ++i) {
        pilha.push(i);
        std::cout << "Adicionado: " << i << ", Tamanho atual: " << pilha.size() << std::endl;
    }

    for (int i = 0; i < 15; ++i) {
        pilha.pop();
        std::cout << "Removido elemento, Tamanho atual: " << pilha.size() << std::endl;
    }

    return 0;
}
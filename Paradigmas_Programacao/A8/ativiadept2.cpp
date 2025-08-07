#include <iostream>
#include <memory>
#include <stdexcept>
#include <random>

template <typename T>
class PilhaDinamica {
private:
    std::unique_ptr<T[]> elementos;
    size_t capacidade;
    size_t topo;
    const size_t capacidadeInicial;

    void redimensionar(size_t novaCapacidade) {
        std::unique_ptr<T[]> novoArray = std::make_unique<T[]>(novaCapacidade);
        for (size_t i = 0; i < topo; ++i) {
            novoArray[i] = std::move(elementos[i]);
        }
        elementos = std::move(novoArray);
        capacidade = novaCapacidade;
    }

    void ajustarCapacidade() {
        // Dobra a capacidade se atingir o limite
        if (topo == capacidade) {
            redimensionar(capacidade * 2);
        }
        // Reduz pela metade se o número de elementos for igual a 1/4 da capacidade e não menor que a capacidade inicial
        else if (topo > 0 && topo == capacidade / 4 && capacidade / 2 >= capacidadeInicial) {
            redimensionar(capacidade / 2);
        }
    }

public:
    PilhaDinamica(size_t capacidadeInicial = 10)
        : capacidade(capacidadeInicial), topo(0), capacidadeInicial(capacidadeInicial) {
        elementos = std::make_unique<T[]>(capacidadeInicial);
    }

    void push(const T& elemento) {
        ajustarCapacidade();
        elementos[topo++] = elemento;
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Pilha vazia");
        }
        --topo;
        ajustarCapacidade();
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

    size_t getCapacidade() const {
        return capacidade;
    }
};

int main() {
    PilhaDinamica<int> pilha;
    int qtd;

    std::cout << "Quantos valores deseja adicionar? ";
    std::cin >> qtd;

    // Gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < qtd; ++i) {
        int valor = dist(gen);
        pilha.push(valor);
        std::cout << "Adicionado: " << valor
                  << " | Tamanho atual: " << pilha.size()
                  << " | Capacidade: " << pilha.getCapacidade() << std::endl;
    }

    // Remover metade dos elementos para testar redução
    int remover = pilha.size() / 2;
    for (int i = 0; i < remover; ++i) {
        pilha.pop();
        std::cout << "Removido elemento"
                  << " | Tamanho atual: " << pilha.size()
                  << " | Capacidade: " << pilha.getCapacidade() << std::endl;
    }

    return 0;
}
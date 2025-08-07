#include <iostream>
#include <stdexcept>

template<typename T>
class Fila {
private:
    struct No {
        T dado;
        No* proximo;
        
        No(const T& valor) : dado(valor), proximo(nullptr) {}
    };
    
    No* inicio;
    No* fim;
    int tamanho;
    
public:
    // Construtor
    Fila() : inicio(nullptr), fim(nullptr), tamanho(0) {}
    
    // Destrutor
    ~Fila() {
        while (!vazia()) {
            remover();
        }
    }
    
    // Construtor de cópia
    Fila(const Fila& outra) : inicio(nullptr), fim(nullptr), tamanho(0) {
        No* atual = outra.inicio;
        while (atual != nullptr) {
            inserir(atual->dado);
            atual = atual->proximo;
        }
    }
    
    // Operador de atribuição
    Fila& operator=(const Fila& outra) {
        if (this != &outra) {
            // Limpar fila atual
            while (!vazia()) {
                remover();
            }
            
            // Copiar elementos da outra fila
            No* atual = outra.inicio;
            while (atual != nullptr) {
                inserir(atual->dado);
                atual = atual->proximo;
            }
        }
        return *this;
    }
    
    // Inserção (enqueue)
    void inserir(const T& valor) {
        No* novoNo = new No(valor);
        
        if (vazia()) {
            inicio = fim = novoNo;
        } else {
            fim->proximo = novoNo;
            fim = novoNo;
        }
        tamanho++;
    }
    
    // Remoção (dequeue)
    T remover() {
        if (vazia()) {
            throw std::runtime_error("Fila vazia");
        }
        
        No* temp = inicio;
        T valor = temp->dado;
        inicio = inicio->proximo;
        
        if (inicio == nullptr) {
            fim = nullptr;
        }
        
        delete temp;
        tamanho--;
        return valor;
    }
    
    // Verificar se está vazia
    bool vazia() const {
        return inicio == nullptr;
    }
    
    // Obter tamanho
    int obterTamanho() const {
        return tamanho;
    }
    
    // Sobrecarga do operador [] para leitura e escrita
    T& operator[](int indice) {
        if (indice < 0 || indice >= tamanho) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        
        No* atual = inicio;
        for (int i = 0; i < indice; i++) {
            atual = atual->proximo;
        }
        return atual->dado;
    }
    
    // Sobrecarga do operador [] para leitura (versão const)
    const T& operator[](int indice) const {
        if (indice < 0 || indice >= tamanho) {
            throw std::out_of_range("Índice fora do intervalo");
        }
        
        No* atual = inicio;
        for (int i = 0; i < indice; i++) {
            atual = atual->proximo;
        }
        return atual->dado;
    }
    
    // Método para exibir a fila
    void exibir() const {
        std::cout << "Fila: ";
        No* atual = inicio;
        while (atual != nullptr) {
            std::cout << atual->dado << " ";
            atual = atual->proximo;
        }
        std::cout << std::endl;
    }
};

// Aplicativo de teste
int main() {
    std::cout << "=== Teste da Fila Template ===" << std::endl;
    
    // Teste com inteiros
    Fila<int> filaInt;
    
    std::cout << "\n1. Inserindo elementos na fila de inteiros:" << std::endl;
    for (int i = 1; i <= 5; i++) {
        filaInt.inserir(i * 10);
        std::cout << "Inserido: " << i * 10 << std::endl;
    }
    
    filaInt.exibir();
    std::cout << "Tamanho da fila: " << filaInt.obterTamanho() << std::endl;
    
    std::cout << "\n2. Testando operador [] para leitura:" << std::endl;
    for (int i = 0; i < filaInt.obterTamanho(); i++) {
        std::cout << "fila[" << i << "] = " << filaInt[i] << std::endl;
    }
    
    std::cout << "\n3. Testando operador [] para escrita:" << std::endl;
    filaInt[2] = 999;
    std::cout << "Alterado fila[2] para 999" << std::endl;
    filaInt.exibir();
    
    std::cout << "\n4. Removendo elementos:" << std::endl;
    while (!filaInt.vazia()) {
        int valor = filaInt.remover();
        std::cout << "Removido: " << valor << std::endl;
        filaInt.exibir();
    }
    
    // Teste com strings
    std::cout << "\n=== Teste com strings ===" << std::endl;
    Fila<std::string> filaString;
    
    filaString.inserir("Primeiro");
    filaString.inserir("Segundo");
    filaString.inserir("Terceiro");
    
    filaString.exibir();
    
    std::cout << "Acessando via índice: " << filaString[1] << std::endl;
    filaString[1] = "Modificado";
    filaString.exibir();
    
    // Teste de exceções
    std::cout << "\n=== Teste de exceções ===" << std::endl;
    try {
        Fila<int> filaVazia;
        filaVazia.remover(); // Deve lançar exceção
    } catch (const std::exception& e) {
        std::cout << "Exceção capturada: " << e.what() << std::endl;
    }
    
    try {
        Fila<int> fila;
        fila.inserir(1);
        int valor = fila[5]; // Deve lançar exceção
    } catch (const std::exception& e) {
        std::cout << "Exceção capturada: " << e.what() << std::endl;
    }
    
    return 0;
}
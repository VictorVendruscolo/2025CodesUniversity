#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

template <class T>
class DStack{
    unique_ptr<T> ptr;
    unsigned topIndex;
    unsigned capacity;

    void reserve(unsigned capacity){
        unique_ptr<T> pAux;

        //verificar se o novo capacity � maior que
        if(! (capacity>0))
            capacity = 1;

        //alocar novo array em pAux
        pAux.reset(new T[capacity]);

        //copiar o array de ptr p/ pAux
        memcpy(pAux.get(),ptr.get(),topIndex * sizeof(T));

        //fazer ptr paontar para p/ pAux
        ptr.swap(pAux);
        this->capacity = capacity;
    }
protected:
    T& at(unsigned i){
        return ptr[i];
    }

public:
    DStack(unsigned capacity = 2):
        topIndex(0),
        capacity(capacity),
        ptr(new T[capacity])
        {}
    //restorna o elemento que esta no topo da pilha
    T top() const{
        return *(ptr.get()+topIndex-1);
    }
    //insere elemento no topo da pilha
    void push(T elem){
        //se a pilha esta cheia, ent�o alocar mais espa�o
        if(capacity == topIndex)
            reserve(capacity*2);

        //inseri elementos
        *(ptr.get()+topIndex) = elem;
        ++topIndex;
    }
    bool pop(){
        //se pilha vazia ent�o retorne falso
        if(topIndex == 0)
            return false;

        //remover elemento da pilha
        --topIndex;

        //se capacidade * 3/4 > topIndex, ent�o reduzir o tamanho do array
        if(capacity * 3/4 > topIndex)
            reserve(capacity/2);

        //return verdadeiro
        return true;
    }
    unsigned size() const{
        return topIndex;
    }
};


// ! Código tarefa sala

// Classe Deck herdando publicamente de DStack
template <class T>
class VDeck : public DStack<T> { // adicionado: herança pública
public: // adicionado: início da seção pública

    // Construtor usando o construtor da base
    VDeck(unsigned capacity = 2) : DStack<T>(capacity) {} // adicionado

    // pushback: igual ao push da pilha (insere no topo)
    void pushback(T elem) { // adicionado
        this->push(elem); // adicionado
    }

    // popback: igual ao pop da pilha (remove do topo)
    bool popback() { // adicionado
        return this->pop(); // adicionado
    }

    // pushfront: insere no início (base) do deck
    void pushfront(T elem) { // adicionado
        // Insere no topo normalmente
        this->push(elem); // adicionado
        // Agora faz swaps até o elemento chegar na base (posição 0)
        for(unsigned i = this->size() - 1; i > 0; --i) { // adicionado
            std::swap(this->at(i), this->at(i-1)); // adicionado
        }
    }

    // popfront: remove do início (base) do deck
    bool popfront() { // adicionado
        if(this->size() == 0) // adicionado
            return false; // adicionado
        // Salva o elemento da base (opcional, se quiser retornar)
        // Move todos os elementos uma posição para trás
        for(unsigned i = 0; i < this->size() - 1; ++i) { // adicionado
            this->at(i) = this->at(i+1); // adicionado
        }
        // Remove o topo (último elemento)
        return this->pop(); // adicionado
    }
}; // adicionado



int main()
{
    // Teste da pilha original
    DStack<int> myStack;
    int i;

    cout << "Teste DStack (pilha):" << endl;
    for(i=0;i<4;++i)
        myStack.push(i);

    for(i=0;i<4;++i){
        cout<<myStack.top()<<' ';
        myStack.pop();
    }
    cout<<endl << endl;

    // Teste do deck
    VDeck<int> myDeck;

    cout << "Teste VDeck (deck):" << endl;

    // Teste pushback
    cout << "pushback 1, 2, 3:" << endl;
    myDeck.pushback(1);
    myDeck.pushback(2);
    myDeck.pushback(3);
    for(unsigned j=0; j<myDeck.size(); ++j)
        cout << myDeck.at(j) << ' ';
    cout << endl;

    // Teste pushfront
    cout << "pushfront 10:" << endl;
    myDeck.pushfront(10);
    for(unsigned j=0; j<myDeck.size(); ++j)
        cout << myDeck.at(j) << ' ';
    cout << endl;

    // Teste popback
    cout << "popback:" << endl;
    myDeck.popback();
    for(unsigned j=0; j<myDeck.size(); ++j)
        cout << myDeck.at(j) << ' ';
    cout << endl;

    // Teste popfront
    cout << "popfront:" << endl;
    myDeck.popfront();
    for(unsigned j=0; j<myDeck.size(); ++j)
        cout << myDeck.at(j) << ' ';
    cout << endl;

    // Teste múltiplas operações
    cout << "pushfront 20, pushback 30:" << endl;
    myDeck.pushfront(20);
    myDeck.pushback(30);
    for(unsigned j=0; j<myDeck.size(); ++j)
        cout << myDeck.at(j) << ' ';
    cout << endl;

    // Teste esvaziar o deck
    cout << "Esvaziando o deck com popfront:" << endl;
    while(myDeck.size() > 0) {
        cout << myDeck.at(0) << ' ';
        myDeck.popfront();
    }
    cout << endl;

    return 0;
}
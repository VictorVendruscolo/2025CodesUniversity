#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

template <class T>
class DStack
{
    unique_ptr<T> ptr;
    unsigned topIndex;
    unsigned capacity;

    void reserve(unsigned capacity)
    {
        unique_ptr<T> pAux;

        // verificar se o novo capacity � maior que
        if (!(capacity > 0))
            capacity = 1;

        // alocar novo array em pAux
        pAux.reset(new T[capacity]);

        // copiar o array de ptr p/ pAux
        memcpy(pAux.get(), ptr.get(), topIndex * sizeof(T));

        // fazer ptr paontar para p/ pAux
        ptr.swap(pAux);
        this->capacity = capacity;
    }

protected:
    T &at(unsigned i)
    {
        return *(ptr.get() + i);
    }

public:
    DStack(unsigned capacity = 2) : topIndex(0),
                                    capacity(capacity),
                                    ptr(new T[capacity])
    {
    }
    // restorna o elemento que esta no topo da pilha
    T top() const
    {
        return *(ptr.get() + topIndex - 1);
    }
    // insere elemento no topo da pilha
    void push(T elem)
    {
        // se a pilha esta cheia, ent�o alocar mais espa�o
        if (capacity == topIndex)
            reserve(capacity * 2);

        // inseri elementos
        *(ptr.get() + topIndex) = elem;
        ++topIndex;
    }
    bool pop()
    {
        // se pilha vazia ent�o retorne falso
        if (topIndex == 0)
            return false;

        // remover elemento da pilha
        --topIndex;

        // se capacidade * 3/4 > topIndex, ent�o reduzir o tamanho do array
        if (capacity * 3 / 4 > topIndex)
            reserve(capacity / 2);

        // return verdadeiro
        return true;
    }
    unsigned size() const
    {
        return topIndex;
    }
};
template <class T>
class DDeck : protected DStack<T>
{
    void swap(unsigned i, unsigned j)
    {
        T aux;

        aux = DStack<T>::at(i);
        DStack<T>::at(i) = DStack<T>::at(j);
        DStack<T>::at(j) = aux;
    }

public:
    DDeck() {}
    T back()
    {
        return DStack<T>::top();
    }
    void push_back(T elem)
    {
        DStack<T>::push(elem);
    }
    bool pop_back()
    {
        return DStack<T>::pop();
    }
    unsigned size()
    {
        return DStack<T>::size();
    }
    T front()
    {
        return DStack<T>::at(0);
    }
    void push_front(T elem)
    {
        unsigned i;
        DStack<T>::push(elem);
        for (i = size() - 1; i > 0; --i)
            swap(i, i - 1);
    }
    bool pop_front()
    {
        unsigned i;
        for (i = 0; i < size() - 1; ++i)
            swap(i, i + 1);
        return DStack<T>::pop();
    }
};
int main()
{
    DDeck<int> myDeck;
    int i;

    for (i = 0; i < 4; ++i)
    {
        myDeck.push_back(i);
        myDeck.push_front(i);
    }
    for (i = 0; i < 4; ++i)
    {
        cout << myDeck.back() << ' ';
        cout << myDeck.front() << ' ';
        myDeck.pop_back();
        myDeck.pop_front();
    }
    cout << endl;

    return 0;
}

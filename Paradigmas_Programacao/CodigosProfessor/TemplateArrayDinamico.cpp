#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
#include <memory>
using namespace std;

template <class T>
class DDinamicArray
{
    unique_ptr<T> V;
    unsigned arraySize;

public:
    DDinamicArray(unsigned arraySize = 10) : arraySize(arraySize),
                                             V(new T[arraySize])
    {
    }
    void reserve(unsigned newArraySize)
    {
        unique_ptr<T> vAux;

        if (newArraySize == 0)
            throw string("tamanho inv�lido");

        vAux.reset(new T[newArraySize]);
        memcpy(vAux.get(), V.get(), sizeof(T) * (arraySize < newArraySize ? arraySize : newArraySize));

        V.swap(vAux);
        arraySize = newArraySize;
    }
    unsigned getArraySize() const
    {
        return arraySize;
    }
    T getElementAt(unsigned i) const
    {
        if (i >= arraySize)
            throw string("Acesso invalido de memoria"); // estudem sobre exce��es
        else
            return *(V.get() + i);
    }
    void setElementAt(unsigned i, T element)
    {
        if (i >= arraySize)
            throw string("Acesso invalido de memoria"); // estudem sobre exce��es
        else
            *(V.get() + i) = element;
    }
};

int main()
{
    DDinamicArray<char> da(2);
    int i;
    for (i = 0; i < da.getArraySize(); ++i)
        da.setElementAt(i, 'a');
    da.reserve(4);
    for (i = 0; i < da.getArraySize(); ++i)
    {
        cout << da.getElementAt(i) << ' ';
        da.setElementAt(i, 'a' + 1);
    }
    cout << endl;
    da.reserve(2);
    for (i = 0; i < da.getArraySize(); ++i)
        cout << da.getElementAt(i) << ' ';
    cout << endl;

    system("pause");
    return 0;
}

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <class T>
class VDinamicArray {
    unique_ptr<T[]> V; // Use unique_ptr<T[]> para gerenciar arrays
    unsigned arraySize;

public:
    VDinamicArray(unsigned arraySize = 10)
        : arraySize(arraySize), V(make_unique<T[]>(arraySize)) {}

    void reserve(unsigned newArraySize) {
        if (newArraySize == 0) {
            throw runtime_error("Tamanho invalido");
        }

        unique_ptr<T[]> vAux(new T[newArraySize]);

        // Use std::copy para copiar os elementos
        std::copy(V.get(), V.get() + (arraySize < newArraySize ? arraySize : newArraySize), vAux.get());

        V = move(vAux);
        arraySize = newArraySize;
    }

    unsigned getArraySize() const {
        return arraySize;
    }

    T getElementAt(unsigned i) const {
        if (i >= arraySize) {
            throw out_of_range("Acesso invalido de memoria");
        }
        return V[i];
    }

    void setElementAt(unsigned i, T element) {
        if (i >= arraySize) {
            throw out_of_range("Acesso invalido de memoria");
        }
        V[i] = element;
    }
};

int main() {
    VDinamicArray<int> va(2);

    for (unsigned i = 0; i < va.getArraySize(); i++) {
        va.setElementAt(i, 0);
    }

    va.reserve(4);

    for (unsigned i = 0; i < va.getArraySize(); i++) {
        cout << va.getElementAt(i) << " ";
    }
    cout << endl;

    return 0;
}
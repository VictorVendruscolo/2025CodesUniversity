#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

class DDinamicArray
{
    int *V;
    unsigned arraySize;

public:
    DDinamicArray(unsigned arraySize = 10) : arraySize(arraySize),
                                             V(new int[arraySize])
    {
    }
    ~DDinamicArray()
    {
        delete[] V;
    }
    void reserve(unsigned newArraySize)
    {
        int *vAux;

        if (newArraySize == 0)
            throw string("tamanho inv�lido");

        vAux = new int[newArraySize];
        memcpy(vAux, V, sizeof(int) * (arraySize < newArraySize ? arraySize : newArraySize));
        delete[] V;
        V = vAux;
        arraySize = newArraySize;
    }
    /*const int* getV(){ //N�o fa�a isso
        return V;
    }*/
    unsigned getArraySize()
    {
        return arraySize;
    }
    int getElementAt(unsigned i)
    {
        if (i >= arraySize)
            throw string("Acesso invalido de memoria"); // estudem sobre exce��es
        else
            return V[i];
    }
    void setElementAt(unsigned i, int element)
    {
        if (i >= arraySize)
            throw string("Acesso invalido de memoria"); // estudem sobre exce��es
        else
            V[i] = element;
    }
};

int main()
{
    DDinamicArray da(2);
    int i;
    for (i = 0; i < da.getArraySize(); ++i)
        da.setElementAt(i, 0);
    da.reserve(4);
    for (i = 0; i < da.getArraySize(); ++i)
    {
        cout << da.getElementAt(i) << ' ';
        da.setElementAt(i, 1);
    }
    cout << endl;
    da.reserve(2);
    for (i = 0; i < da.getArraySize(); ++i)
        cout << da.getElementAt(i) << ' ';
    cout << endl;
    /*DDinamicArray da;

    try{
        cout<<da.getElementAt(10)<<endl;
    }
    catch(string c){
        cout<<endl<<c<<endl;
    }
    catch(...){
        cout<<endl<<"..."<<endl;
    }
    cout<<"passou da exception"<<endl;
*/
    /*DDinamicArray DA;
    DA.getV()[1] = 9;
    cout<<DA.getV()[1]<<endl;

    string s1,s2("alguma coisa"),s3("outra coisa");
    s1 = s2+' '+s3;
    cout << s1 << endl;

    s1.c_str()[1] = 'u';

    printf(s1.c_str());*/

    system("pause");
    return 0;
}

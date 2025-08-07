#include<iostream>
#include<stdlib.h>
#include<string.h>


using namespace std;

class VDinamicArray{
    
    int *V;
    unsigned arraySize;

    public:

        VDinamicArray(unsigned arraySize = 10) :
            V(new int[arraySize]), arraySize(arraySize)
            {}

        void reserve(unsigned newArraySize){
            int *vAux;

            if(newArraySize == 0){ throw string("Tamanho invalido"); } //? exceções (Estudar)

            vAux = new int[newArraySize]; 
            memcpy(vAux, V, (
                (arraySize < newArraySize ? arraySize : newArraySize)
                *sizeof(int))
            );                                              //? memcpy é mais rápido que for, mas não é seguro (Estudar)
            delete[] V;
            V = vAux;
            arraySize = newArraySize;
        }

        unsigned getArraySize(){
            return arraySize;
        }
        int getElementAt(unsigned i){
            if(i>=arraySize){                     // ! i<arraySize alterado para i>=arraySize
            throw string("Acesso invalido de memoria");  //? exceções (Estudar)
            }
            else {
                return V[i]; // ! V[1] alterado para V[i]
            }
        }
        void setElementAt(unsigned i, int element){
            if(i>=arraySize){  
                throw string("Acesso invalido de memoria");  //? exceções (Estudar)
            }
            else {
                V[i] = element;
            }
        }
        ~VDinamicArray(){
            delete[] V; //? [] opcional 
        }

};

int main(){

    VDinamicArray va(2);
    unsigned int i;
    for(i=0; i<va.getArraySize(); i++){
        va.setElementAt(i, 0);
    }
    
    va.reserve(4);
    for(i=0; i<va.getArraySize(); i++){
        cout << va.getElementAt(i) << " ";
        cout <<endl;

    }
    return 0;
}
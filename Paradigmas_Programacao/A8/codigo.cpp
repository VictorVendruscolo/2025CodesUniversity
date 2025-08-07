#include <iostream>
#include <memory>
#include<string.h>


using namespace std;

template<class T>

class VStack { 

    unsigned capacity;
    unique_ptr<T[]> ptr;
    unsigned topIndex;

    void reserve(unsigned capacity){
        unique_ptr<T[]> pAux;

        if(! (capacity > 0)){
            capacity = 1;
        }

        pAux.reset(new T[capacity]);

        memcpy(pAux.get(), ptr.get(), topIndex * sizeof(T));

        ptr.swap(pAux);
        this->capacity = capacity;

    }
    public:

        VStack(unsigned capacity = 2):
            capacity(capacity),
            ptr(new T[capacity]), 
            topIndex(0)
        {}
        
        T top() const {
            return *(ptr.get()+topIndex-1);
            
        }

        void push(T elem){
            if(capacity == topIndex){
                reserve(capacity*2);
                
            }
        
            *(ptr.get()+topIndex) = elem;
            ++topIndex;
        }

        bool pop(){
            if(topIndex == 0){
                return false;
            }

            --topIndex;


            if(capacity * 3/4 > topIndex){
                reserve(capacity/2);
                
            }

            return true;
        }



    
};
 
int main () { 
    
    VStack<int> myStack;
    int i;

    for(i=0; i<4; ++i)
        myStack.push(i);

    for(i=0; i<4; ++i){
        cout<<myStack.top()<<' ';
        myStack.pop();
    }
    cout<<endl;
    

    return 0;
}
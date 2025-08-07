// * Discription: Ex.1 aula templates
#include<iostream>
using namespace std;

template <typename T>

void ordena(T V[],unsigned n) {  
    unsigned i,j;
    T aux;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(V[i]>V[j]){
                aux=V[i];
                V[i]=V[j];
                V[j]=aux;
            }
}


int main() {
    int V []={10,50,14,95,215,3};
    int i;

    ordena<int>(V,6);
    for(i=0;i<6;i++) 
        std::cout << V[i] << ' ';
        

}


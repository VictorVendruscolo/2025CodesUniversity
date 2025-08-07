#include<iostream>
#include<map>
#include<string.h>

using namespace std;

class VArrayOpIndex{
    int V[10];

    public:
        int& operator []( char index){
            return V[index - 'a'];
        }
};

int main(){

    map<string,int> myMap;
    
    myMap.insert(pair<setring, int>("sei la",200))
    myMap.insert(pair<setring, int>("sei la oq",100))

    cout <<myMap["sei la"];
    myMap["sei la"] = 555
    cout<<myMap["sei la"];

    //implementar um map simples pra mapear qualquer coisa
    //usando operador de indice
    //a busca linear se não tiver insere

    VArrayOpIndex A;
    char i;

    for(i='a'; 1<'a'+10; ++i)
        A[i] = i;
    for(i=0; 1<10; ++i)
        cout << A[i] << ' ';

    return 0;
}
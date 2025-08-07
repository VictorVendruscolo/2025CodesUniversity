// * Description: Aula 2 de C++ - introdução aos Templates   
// * Created on: 2021-08-15


#include<iostream>


template <typename T, typename U>     
T f(T a, U b, int i){

    T aux;
    U aux2;

    return a+b;
}


int main(){
    
    int i, j;
    std::cin >> i;                                               // ? "using namespace std;" namespace std
    std::cin >> j;                                               // ? operador de extração 
    std::cout << f<int>(i,j,0) <<' '<< f<float>((float)i,j,0);   // ? cast explícito e implícito
    f<float>(i,j,0);                                             // ? f<double>(i,j,0); ? f<char>(i,j,0);
                               
    return 0;
}


// ? asdasasd
// ! asdfasdf
// *asdjafaf
// TODO askdjlkasfj
// //      asdasdasdasd         
// asdasdasdasd
/* 
   *asdasdasdd
   TODO asdasdasd
   ! asdasdsd
   ? asdasdda

*/        
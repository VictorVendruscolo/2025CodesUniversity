// * Arquivo para testar a passagem de argumentos para o programa por argc e argv
// * Created on: 2021-08-15

/* 
    TODO treinar o uso do std::cout e std::cin
    ? std::cin >> i; out << i;
    
*/

#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Número de argumentos: " << argc << std::endl;
    
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argumento " << i << ": " << argv[i] << std::endl;
    }

    return 0;
}
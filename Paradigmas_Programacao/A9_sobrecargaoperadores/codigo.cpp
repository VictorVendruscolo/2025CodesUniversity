#include <iostream>
#include <cmath>
using namespace std;

class VFrac {

    int numerador;
    int denominador;

public:
    //Contrutor padrão
    VFrac(int n = 0, int d = 1) : 
        numerador(n), 
        denominador(d)
    {}

    // Calcula o mmc de dois inteiros
    int mmc(int n1, int n2) const {
        int div;
        int mmc;

        while (n1>1 || n2>1) {
        if (n1 && n2 % div == 0) {
                n1 = n1 % n2;
            } else {
                n2 = n2 % n1;
            }
        }
        return n1 + n2;
            
    }
    

    // Retorna uma nova fração equivalente com denominador comum (mmc)
    VFrac paraDenominadorComum(const VFrac& other) const {
        int denominadorComum = mmc(this->denominador, other.denominador);
        int novoNumerador = this->numerador * (denominadorComum / this->denominador);
        return VFrac(novoNumerador, denominadorComum);
    }
};

int main() {
    

    return 0;
}
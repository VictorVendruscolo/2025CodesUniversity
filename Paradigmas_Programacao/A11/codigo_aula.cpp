#include<iostream>

using namespace std;

class VTCelcius {
    double temperatura;
    public:
        VTCelcius():temperatura(0)
        {}
        VTCelcius(const double &i): temperatura(i)
        //evita que seja alterado e seja cópia
        {}

        operator double() const{ //unico operador que a gente escreve sem tipo de retorno, o tipo é o int nesse caso
            return temperatura;
        }
};

class VTFahrenheit{
    double temperatura;
    public:
        VTFahrenheit():temperatura(0)
        {}
        VTFahrenheit(const VTCelcius &c)
        {
            temperatura = (c * 9/5) + 32;
            //objeto  passa por um casting int nesse caso
        }
        operator VTCelcius() const{
            return (temperatura - 32 * 5/9);
        }

};

int main() {

    VTCelcius c;
    VTFahrenheit f;
    double i = 100;
    c = i; // construtor copia
    i = c; // operador cast
    f = c; //construtor de copia
    c = f; // operador de cast
    return 0;
}
#include<iostream>
#include<math.h>

using namespace std;

class Vcircle{
    float raio;
    public:
        Vcircle(){
            raio = 1;
        }

        float getRaio(){
            return raio;
        }
        void setRaio( float raio){
            this->raio = raio;

        }
        float area(){
            return M_PI * raio * raio; // ? preferência
        }
    
        float circunferencia(){
            float circunferencia;
            circunferencia = 2 * M_PI * raio;
            return circunferencia;
        }


};

int main(){

    Vcircle c1;
    c1.setRaio(5);

    cout << "valor area: " << c1.area() << ',' << " valor circunferencia: " << c1.circunferencia() <<endl;

}
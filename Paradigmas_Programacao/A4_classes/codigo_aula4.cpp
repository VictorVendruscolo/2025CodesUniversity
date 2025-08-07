#include<iostream>
using namespace std;

class VTriangulo{
    float base, height;
    public:
        VTriangulo(){
            base = height = 1;
        }
        
       float getBase(){
           return base;
       }
        float getHeight(){
              return height;
         }
            void setBase(float base){
                this->base = base;
            }
                void setHeight(float height){
                    this->height = height;
                }
                ~VTriangulo(){  // ! destrutor, não é necessário nesse caso
                }               // * usado quando atribuimos alocação dinamica
                
};

int main(){
    VTriangulo t1;

    cout << t1.getBase() << "," << t1.getHeight() << endl;

    return 0;
}
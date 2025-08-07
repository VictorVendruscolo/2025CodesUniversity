#include<iostream>
#include<math.h>

using namespace std;

class VPointR2 {
    float x,y;

public:
    VPointR2(float x = 0, float y = 0):
        x(x),
        y(y)
    {}
    VPointR2(const VPointR2 &other) :
        x(other.x),
        y(other.y)
    {}
    void setX(float x){
        this -> x=x;
    
    }
    void setY(float y){
        this -> y=y;

    }
    float getX() const{
        return x;
    }
    float getY() const{
        return y;
    }
    float distance(const VPointR2 &other) const{
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};
class VCircunference{

    float radius;
    VPointR2 center; //! não é uma boa prática, deve-se usar herança
    
    public:

        VCircunference(){
            radius = 1.0;

        }
        /* outra sintaxe:
            VCircunference():
                radius(1.0)
        {}
        */
        
        VCircunference(float radius) : // ? um contrutor parametrizado
                radius(radius)
        {}
        VCircunference(float radius, VPointR2 center) : // ? um contrutor parametrizado
                radius(radius),
                center(center)

        {}
        
        VCircunference(const VCircunference &other){
            radius = (other.radius);
            center = (other.center);
        }
        void setRadius(float radius){
            this -> radius = radius;

        }
        void setCenter(VPointR2 center){
            this -> center = center;

        }
        void setCenter(float x, float y){
            center.setX(x);
            center.setY(y);

        }
        VPointR2 getCenter() const{
            return center;
        }
        float getRadius() const{
            return radius;
        }
        float area() const{
            return M_PI*pow(radius, 2.0);
        }
        float perimeter() const{
            return M_PI*2*radius;
        }
        float distance(const VCircunference &other) const{
            return center.distance(other.center) - radius - other.radius;

        }
        bool overlapping(const VCircunference &other) const{
            return distance(other) < 0; // ! ? true : false
        }
        ~VCircunference(){
        }
};

int main(){
    
    VCircunference c1, c2(c1), c3(3.0, VPointR2(1.0, 1.0));// ? c1 é o construtor padrão, c2 é o construtor de cópia e c3 é o construtor parametrizado
    // ? VCircunference c1(2,0); (chamar contrutor parametrizado)
  // ? VCircunference *pC = new VCircunference(2.0) ponteiro
                                                             
    cout << c1.area() << ' ' << c1.perimeter() << endl;

    system("dir");
    // ? delete pC;
    return 0;
}
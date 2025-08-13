#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
class DPointR2
{
    float x, y;

public:
    DPointR2(float x = 0, float y = 0) : x(x),
                                         y(y)
    {
    }
    DPointR2(const DPointR2 &other) : x(other.x),
                                      y(other.y)
    {
    }
    void setX(float x)
    {
        this->x = x;
    }
    void setY(float y)
    {
        this->y = y;
    }
    float getX() const
    {
        return x;
    }
    float getY() const
    {
        return y;
    }
    float distance(const DPointR2 &other) const
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

class DCircunference
{
    float radius;
    DPointR2 center;

public:
    DCircunference() : // construtor padr�o
                       radius(1.0)
    {
    }
    DCircunference(float radius) : // um construtor parametrizado
                                   radius(radius)
    {
    }
    DCircunference(float radius, DPointR2 center) : // um construtor parametrizado
                                                    radius(radius),
                                                    center(center)
    {
    }
    DCircunference(const DCircunference &other) : radius(other.radius),
                                                  center(other.center)
    {
    }
    void setRadius(float radius)
    {
        this->radius = radius;
    }
    float getRadius() const
    {
        return radius;
    }
    ~DCircunference() {}

    float area() const
    {
        return M_PI * pow(radius, 2.0);
    }
    float perimeter() const
    {
        return 2 * M_PI * radius;
    }
};

int main()
{
    DCircunference c1(2.0), c2(c1), c3(3, DPointR2(1, 1));

    // DCircunference *pC =new DCircunference(2.0);

    cout << c2.area() << ' ' << c2.perimeter() << endl;
    // cout<<pC->area()<<' '<<pC->perimeter()<<endl;

    system("pause");
    // delete pC;
    return 0;
}
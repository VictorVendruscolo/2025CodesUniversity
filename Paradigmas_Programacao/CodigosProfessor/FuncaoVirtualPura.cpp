#include <iostream>
#include <vector>
using namespace std;

#define PI 3.1415

class DFigs
{
public:
    virtual float calcArea() = 0;
};
class DCircunf : public DFigs
{
    ;
    float r;

public:
    DCircunf(float r = 1.0) : r(r)
    {
    }
    virtual float calcArea()
    {
        return PI * r * r;
    }
};
class DQuad : public DFigs
{
    float l;

public:
    DQuad(float l = 1.0) : l(l)
    {
    }
    virtual float calcArea()
    {
        return l * l;
    }
};
class DTriang : public DFigs
{
    float b, h;

public:
    DTriang(float b = 1.0, float h = 1.0) : b(b), h(h)
    {
    }
    virtual float calcArea()
    {
        return b * h / 2.0;
    }
};
class DConjuntoDeFiguras : public vector<DFigs *>
{
public:
    float areaTotal()
    {
        vector<DFigs *>::iterator it;
        float areaTotal = 0.0;

        for (it = begin(); it != end(); ++it)
            areaTotal += (*it)->calcArea();
        return areaTotal;
    }
};
int main()
{

    DConjuntoDeFiguras VFigs;

    VFigs.push_back(new DQuad);
    VFigs.push_back(new DTriang);
    VFigs.push_back(new DCircunf);

    cout << VFigs.areaTotal() << endl;
    return 0;
}
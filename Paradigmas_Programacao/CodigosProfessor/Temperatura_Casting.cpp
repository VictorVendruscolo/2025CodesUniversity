#include <iostream>
using namespace std;

class DTCelcius
{
    double temperatura;

public:
    DTCelcius() : temperatura(0)
    {
    }
    DTCelcius(const double &i) : temperatura(i)
    {
    }
    operator double() const
    {
        return temperatura;
    }
};
class DTFahrenheit
{
    double temperatura;

public:
    DTFahrenheit() : temperatura(0)
    {
    }
    DTFahrenheit(const DTCelcius &c)
    {
        temperatura = c * 9 / 5 + 32;
        // o obj c passa por um casting para int, nesse caso
    }
    operator DTCelcius()
    {
        return (temperatura - 32) * 5 / 9;
    }
};
int main()
{
    DTCelcius c;
    DTFahrenheit f;
    double i = 100;
    c = i; // const copia
    i = c; // op cast
    f = c; // const copia
    c = f; // op cast
    return 0;
}
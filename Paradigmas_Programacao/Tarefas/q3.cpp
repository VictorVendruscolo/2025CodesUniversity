
// Questão 3 - Classe PontoPolar com Conversao (3,0 pts)
#include <iostream>
#include <cmath>
using namespace std;

class Ponto2D {
public:
    double x, y;
    Ponto2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

class PontoPolar {
public:
    double r, phi;

    PontoPolar(double r = 0.0, double phi = 0.0) : r(r), phi(phi) {}

    PontoPolar(const Ponto2D& p) {
        r = sqrt(p.x * p.x + p.y * p.y);
        phi = atan2(p.y, p.x);
    }

    Ponto2D paraCartesiano() const {
        return Ponto2D(r * cos(phi), r * sin(phi));
    }
};

void testePontoPolar() {
    Ponto2D p(3.0, 4.0);
    PontoPolar pol(p);
    cout << "Polar: r = " << pol.r << ", phi = " << pol.phi << endl;

    Ponto2D convertido = pol.paraCartesiano();
    cout << "Convertido de volta: (" << convertido.x << ", " << convertido.y << ")\n";
}

int main() {
    testePontoPolar();
    return 0;
}

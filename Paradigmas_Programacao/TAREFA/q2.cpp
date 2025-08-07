
// Questão 2 - Classe Ponto2D com Sobrecarga (3,0 pts)
#include <iostream>
using namespace std;

class Ponto2D {
public:
    double x, y;

    Ponto2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    bool operator==(const Ponto2D& p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Ponto2D& p) const {
        return !(*this == p);
    }

    Ponto2D operator+(const Ponto2D& p) const {
        return Ponto2D(x + p.x, y + p.y);
    }

    Ponto2D operator-(const Ponto2D& p) const {
        return Ponto2D(x - p.x, y - p.y);
    }

    Ponto2D& operator++() {
        x += 1;
        y += 1;
        return *this;
    }

    Ponto2D operator++(int) {
        Ponto2D temp = *this;
        ++(*this);
        return temp;
    }

    Ponto2D& operator--() {
        x -= 1;
        y -= 1;
        return *this;
    }

    Ponto2D operator--(int) {
        Ponto2D temp = *this;
        --(*this);
        return temp;
    }
};

void testePonto2D() {
    Ponto2D a(1.0, 2.0), b(3.0, 4.0);
    Ponto2D c = a + b;
    cout << "Soma: (" << c.x << ", " << c.y << ")\n";

    if (a != b) cout << "a e b sao diferentes.\n";
    ++a;
    cout << "Incremento de a: (" << a.x << ", " << a.y << ")\n";
}

int main() {
    testePonto2D();
    return 0;
}

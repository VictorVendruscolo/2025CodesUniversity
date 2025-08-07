#include <iostream>
#include <cmath>

class Ponto2D {
private:
    double x, y;
    
public:
    // Construtores
    Ponto2D() : x(0.0), y(0.0) {}
    Ponto2D(double x, double y) : x(x), y(y) {}
    
    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Setters
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    
    // Operadores de comparação
    bool operator==(const Ponto2D& outro) const {
        const double EPSILON = 1e-9;
        return (std::abs(x - outro.x) < EPSILON) && (std::abs(y - outro.y) < EPSILON);
    }
    
    bool operator!=(const Ponto2D& outro) const {
        return !(*this == outro);
    }
    
    // Operadores aritméticos
    Ponto2D operator+(const Ponto2D& outro) const {
        return Ponto2D(x + outro.x, y + outro.y);
    }
    
    Ponto2D operator-(const Ponto2D& outro) const {
        return Ponto2D(x - outro.x, y - outro.y);
    }
    
    // Operador ++ pré-fixado
    Ponto2D& operator++() {
        ++x;
        ++y;
        return *this;
    }
    
    // Operador ++ pós-fixado
    Ponto2D operator++(int) {
        Ponto2D temp(*this);
        ++x;
        ++y;
        return temp;
    }
    
    // Operador -- pré-fixado
    Ponto2D& operator--() {
        --x;
        --y;
        return *this;
    }
    
    // Operador -- pós-fixado
    Ponto2D operator--(int) {
        Ponto2D temp(*this);
        --x;
        --y;
        return temp;
    }
    
    // Operador de atribuição com soma
    Ponto2D& operator+=(const Ponto2D& outro) {
        x += outro.x;
        y += outro.y;
        return *this;
    }
    
    // Operador de atribuição com subtração
    Ponto2D& operator-=(const Ponto2D& outro) {
        x -= outro.x;
        y -= outro.y;
        return *this;
    }
    
    // Método para calcular a distância até a origem
    double distanciaOrigem() const {
        return std::sqrt(x * x + y * y);
    }
    
    // Método para calcular a distância até outro ponto
    double distancia(const Ponto2D& outro) const {
        double dx = x - outro.x;
        double dy = y - outro.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    // Operador de saída para stream
    friend std::ostream& operator<<(std::ostream& os, const Ponto2D& ponto) {
        os << "(" << ponto.x << ", " << ponto.y << ")";
        return os;
    }
    
    // Operador de entrada para stream
    friend std::istream& operator>>(std::istream& is, Ponto2D& ponto) {
        std::cout << "Digite x: ";
        is >> ponto.x;
        std::cout << "Digite y: ";
        is >> ponto.y;
        return is;
    }
};

// Aplicativo de teste
int main() {
    std::cout << "=== Teste da Classe Ponto2D ===" << std::endl;
    
    // Teste dos construtores
    std::cout << "\n1. Testando construtores:" << std::endl;
    Ponto2D p1;
    Ponto2D p2(3.0, 4.0);
    Ponto2D p3(1.5, -2.5);
    
    std::cout << "p1 (construtor padrão): " << p1 << std::endl;
    std::cout << "p2 (3.0, 4.0): " << p2 << std::endl;
    std::cout << "p3 (1.5, -2.5): " << p3 << std::endl;
    
    // Teste dos operadores de comparação
    std::cout << "\n2. Testando operadores de comparação:" << std::endl;
    Ponto2D p4(3.0, 4.0);
    std::cout << "p2 == p4: " << (p2 == p4 ? "true" : "false") << std::endl;
    std::cout << "p2 != p3: " << (p2 != p3 ? "true" : "false") << std::endl;
    std::cout << "p1 == p3: " << (p1 == p3 ? "true" : "false") << std::endl;
    
    // Teste dos operadores aritméticos
    std::cout << "\n3. Testando operadores aritméticos:" << std::endl;
    Ponto2D soma = p2 + p3;
    Ponto2D subtracao = p2 - p3;
    
    std::cout << "p2 + p3 = " << p2 << " + " << p3 << " = " << soma << std::endl;
    std::cout << "p2 - p3 = " << p2 << " - " << p3 << " = " << subtracao << std::endl;
    
    // Teste dos operadores de incremento e decremento
    std::cout << "\n4. Testando operadores ++ e --:" << std::endl;
    Ponto2D p5(2.0, 3.0);
    std::cout << "p5 inicial: " << p5 << std::endl;
    
    std::cout << "++p5: " << ++p5 << std::endl;
    std::cout << "p5 após ++: " << p5 << std::endl;
    
    std::cout << "p5++: " << p5++ << std::endl;
    std::cout << "p5 após p5++: " << p5 << std::endl;
    
    std::cout << "--p5: " << --p5 << std::endl;
    std::cout << "p5 após --: " << p5 << std::endl;
    
    std::cout << "p5--: " << p5-- << std::endl;
    std::cout << "p5 após p5--: " << p5 << std::endl;
    
    // Teste dos operadores de atribuição
    std::cout << "\n5. Testando operadores de atribuição:" << std::endl;
    Ponto2D p6(1.0, 1.0);
    std::cout << "p6 inicial: " << p6 << std::endl;
    
    p6 += p2;
    std::cout << "p6 após += p2: " << p6 << std::endl;
    
    p6 -= p3;
    std::cout << "p6 após -= p3: " << p6 << std::endl;
    
    // Teste das funções de distância
    std::cout << "\n6. Testando cálculos de distância:" << std::endl;
    std::cout << "Distância de p2 até a origem: " << p2.distanciaOrigem() << std::endl;
    std::cout << "Distância entre p2 e p3: " << p2.distancia(p3) << std::endl;
    
    // Teste de entrada e saída
    std::cout << "\n7. Testando entrada e saída:" << std::endl;
    Ponto2D p7;
    std::cout << "Digite as coordenadas para p7:" << std::endl;
    // Comentado para não interromper o teste automático
    // std::cin >> p7;
    // std::cout << "p7 inserido: " << p7 << std::endl;
    
    // Teste com operações encadeadas
    std::cout << "\n8. Testando operações encadeadas:" << std::endl;
    Ponto2D resultado = (p2 + p3) - p1;
    std::cout << "(p2 + p3) - p1 = " << resultado << std::endl;
    
    // Teste de cópia e atribuição
    std::cout << "\n9. Testando cópia e atribuição:" << std::endl;
    Ponto2D p8 = p2;  // Construtor de cópia
    Ponto2D p9;
    p9 = p3;          // Operador de atribuição
    
    std::cout << "p8 (cópia de p2): " << p8 << std::endl;
    std::cout << "p9 (atribuição de p3): " << p9 << std::endl;
    
    return 0;
}
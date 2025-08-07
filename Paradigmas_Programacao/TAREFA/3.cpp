#include <iostream>
#include <cmath>

// Incluir a classe Ponto2D da questão anterior
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
    
    // Operador de saída para stream
    friend std::ostream& operator<<(std::ostream& os, const Ponto2D& ponto) {
        os << "(" << ponto.x << ", " << ponto.y << ")";
        return os;
    }
};

// Classe para representar pontos em coordenadas polares
class PontoPolar {
private:
    double r;   // raio (distância da origem)
    double phi; // ângulo em radianos (0 a 2π)
    
    // Normalizar o ângulo para estar entre 0 e 2π
    void normalizarAngulo() {
        const double PI2 = 2.0 * M_PI;
        while (phi < 0) {
            phi += PI2;
        }
        while (phi >= PI2) {
            phi -= PI2;
        }
    }
    
public:
    // Construtores
    PontoPolar() : r(0.0), phi(0.0) {}
    
    PontoPolar(double r, double phi) : r(r), phi(phi) {
        // Garantir que o raio seja não-negativo
        if (r < 0) {
            this->r = -r;
            this->phi = phi + M_PI;
        }
        normalizarAngulo();
    }
    
    // Construtor de conversão de Ponto2D para PontoPolar
    PontoPolar(const Ponto2D& cartesiano) {
        double x = cartesiano.getX();
        double y = cartesiano.getY();
        
        r = std::sqrt(x * x + y * y);
        phi = std::atan2(y, x);
        
        // atan2 retorna valores entre -π e π, então normalizamos para 0 a 2π
        if (phi < 0) {
            phi += 2.0 * M_PI;
        }
    }
    
    // Getters
    double getR() const { return r; }
    double getPhi() const { return phi; }
    
    // Setters
    void setR(double r) {
        if (r < 0) {
            this->r = -r;
            this->phi += M_PI;
            normalizarAngulo();
        } else {
            this->r = r;
        }
    }
    
    void setPhi(double phi) {
        this->phi = phi;
        normalizarAngulo();
    }
    
    // Operador de conversão para Ponto2D
    operator Ponto2D() const {
        double x = r * std::cos(phi);
        double y = r * std::sin(phi);
        return Ponto2D(x, y);
    }
    
    // Método explícito de conversão para Ponto2D
    Ponto2D paraCartesiano() const {
        double x = r * std::cos(phi);
        double y = r * std::sin(phi);
        return Ponto2D(x, y);
    }
    
    // Operadores de comparação
    bool operator==(const PontoPolar& outro) const {
        const double EPSILON = 1e-9;
        
        // Se ambos estão na origem
        if (r < EPSILON && outro.r < EPSILON) {
            return true;
        }
        
        // Comparar raio e ângulo
        return (std::abs(r - outro.r) < EPSILON) && 
               (std::abs(phi - outro.phi) < EPSILON);
    }
    
    bool operator!=(const PontoPolar& outro) const {
        return !(*this == outro);
    }
    
    // Operadores aritméticos (convertendo para cartesiano, operando e voltando para polar)
    PontoPolar operator+(const PontoPolar& outro) const {
        Ponto2D cart1 = this->paraCartesiano();
        Ponto2D cart2 = outro.paraCartesiano();
        Ponto2D resultado = cart1 + cart2;
        return PontoPolar(resultado);
    }
    
    PontoPolar operator-(const PontoPolar& outro) const {
        Ponto2D cart1 = this->paraCartesiano();
        Ponto2D cart2 = outro.paraCartesiano();
        Ponto2D resultado = cart1 - cart2;
        return PontoPolar(resultado);
    }
    
    // Operador de rotação (somar ângulo)
    PontoPolar& rotacionar(double deltaAngulo) {
        phi += deltaAngulo;
        normalizarAngulo();
        return *this;
    }
    
    // Operador de escalonamento (multiplicar raio)
    PontoPolar& escalar(double fator) {
        if (fator < 0) {
            r *= -fator;
            phi += M_PI;
            normalizarAngulo();
        } else {
            r *= fator;
        }
        return *this;
    }
    
    // Método para obter o ângulo em graus
    double getPhiGraus() const {
        return phi * 180.0 / M_PI;
    }
    
    // Método para definir o ângulo em graus
    void setPhiGraus(double graus) {
        phi = graus * M_PI / 180.0;
        normalizarAngulo();
    }
    
    // Operador de saída para stream
    friend std::ostream& operator<<(std::ostream& os, const PontoPolar& ponto) {
        os << "(r=" << ponto.r << ", φ=" << ponto.phi << " rad)";
        return os;
    }
    
    // Operador de entrada para stream
    friend std::istream& operator>>(std::istream& is, PontoPolar& ponto) {
        std::cout << "Digite r: ";
        is >> ponto.r;
        std::cout << "Digite φ (radianos): ";
        is >> ponto.phi;
        
        if (ponto.r < 0) {
            ponto.r = -ponto.r;
            ponto.phi += M_PI;
        }
        ponto.normalizarAngulo();
        
        return is;
    }
};

// Aplicativo de teste
int main() {
    std::cout << "=== Teste da Classe PontoPolar ===" << std::endl;
    
    // Teste dos construtores
    std::cout << "\n1. Testando construtores:" << std::endl;
    PontoPolar pp1;
    PontoPolar pp2(5.0, M_PI / 4);  // 45 graus
    PontoPolar pp3(3.0, M_PI);      // 180 graus
    
    std::cout << "pp1 (construtor padrão): " << pp1 << std::endl;
    std::cout << "pp2 (5, π/4): " << pp2 << std::endl;
    std::cout << "pp3 (3, π): " << pp3 << std::endl;
    
    // Teste de conversão de cartesiano para polar
    std::cout << "\n2. Testando conversão Cartesiano → Polar:" << std::endl;
    Ponto2D pc1(3.0, 4.0);
    Ponto2D pc2(-1.0, 1.0);
    Ponto2D pc3(0.0, -2.0);
    
    PontoPolar pp_from_c1(pc1);
    PontoPolar pp_from_c2(pc2);
    PontoPolar pp_from_c3(pc3);
    
    std::cout << "Cartesiano " << pc1 << " → Polar " << pp_from_c1 << std::endl;
    std::cout << "Cartesiano " << pc2 << " → Polar " << pp_from_c2 << std::endl;  
    std::cout << "Cartesiano " << pc3 << " → Polar " << pp_from_c3 << std::endl;
    
    // Teste de conversão de polar para cartesiano
    std::cout << "\n3. Testando conversão Polar → Cartesiano:" << std::endl;
    Ponto2D pc_from_p1 = pp2.paraCartesiano();
    Ponto2D pc_from_p2 = pp3.paraCartesiano();
    Ponto2D pc_from_p3 = static_cast<Ponto2D>(pp_from_c1); // usando operador de conversão
    
    std::cout << "Polar " << pp2 << " → Cartesiano " << pc_from_p1 << std::endl;
    std::cout << "Polar " << pp3 << " → Cartesiano " << pc_from_p2 << std::endl;
    std::cout << "Polar " << pp_from_c1 << " → Cartesiano " << pc_from_p3 << std::endl;
    
    // Verificação de ida e volta (round-trip)
    std::cout << "\n4. Verificação de conversão ida e volta:" << std::endl;
    Ponto2D original(4.0, 3.0);
    PontoPolar temp_polar(original);
    Ponto2D volta_cartesiano = temp_polar.paraCartesiano();
    
    std::cout << "Original: " << original << std::endl;
    std::cout << "Polar intermediário: " << temp_polar << std::endl;
    std::cout << "De volta ao cartesiano: " << volta_cartesiano << std::endl;
    std::cout << "São iguais? " << (original == volta_cartesiano ? "Sim" : "Não") << std::endl;
    
    // Teste dos operadores aritméticos
    std::cout << "\n5. Testando operadores aritméticos:" << std::endl;
    PontoPolar pp4(2.0, 0.0);        // (2, 0°)
    PontoPolar pp5(2.0, M_PI / 2);   // (2, 90°)
    
    PontoPolar soma_polar = pp4 + pp5;
    PontoPolar sub_polar = pp4 - pp5;
    
    std::cout << "pp4: " << pp4 << " → Cartesiano: " << pp4.paraCartesiano() << std::endl;
    std::cout << "pp5: " << pp5 << " → Cartesiano: " << pp5.paraCartesiano() << std::endl;
    std::cout << "pp4 + pp5: " << soma_polar << " → Cartesiano: " << soma_polar.paraCartesiano() << std::endl;
    std::cout << "pp4 - pp5: " << sub_polar << " → Cartesiano: " << sub_polar.paraCartesiano() << std::endl;
    
    // Teste de rotação e escalonamento
    std::cout << "\n6. Testando rotação e escalonamento:" << std::endl;
    PontoPolar pp6(3.0, 0.0);
    std::cout << "pp6 original: " << pp6 << " (φ em graus: " << pp6.getPhiGraus() << "°)" << std::endl;
    
    pp6.rotacionar(M_PI / 2);  // Rotacionar 90°
    std::cout << "Após rotação de 90°: " << pp6 << " (φ em graus: " << pp6.getPhiGraus() << "°)" << std::endl;
    
    pp6.escalar(2.0);  // Escalar por 2
    std::cout << "Após escalonamento por 2: " << pp6 << std::endl;
    
    // Teste com ângulos em graus
    std::cout << "\n7. Testando ângulos em graus:" << std::endl;
    PontoPolar pp7(1.0, 0.0);
    std::cout << "pp7 inicial: " << pp7 << " (φ em graus: " << pp7.getPhiGraus() << "°)" << std::endl;
    
    pp7.setPhiGraus(45.0);
    std::cout << "Após definir ângulo para 45°: " << pp7 << " (φ em graus: " << pp7.getPhiGraus() << "°)" << std::endl;
    
    pp7.setPhiGraus(270.0);
    std::cout << "Após definir ângulo para 270°: " << pp7 << " (φ em graus: " << pp7.getPhiGraus() << "°)" << std::endl;
    
    // Teste de comparação
    std::cout << "\n8. Testando operadores de comparação:" << std::endl;
    PontoPolar pp8(5.0, M_PI / 3);
    PontoPolar pp9(5.0, M_PI / 3);
    PontoPolar pp10(5.0, M_PI / 4);
    
    std::cout << "pp8: " << pp8 << std::endl;
    std::cout << "pp9: " << pp9 << std::endl;
    std::cout << "pp10: " << pp10 << std::endl;
    
    std::cout << "pp8 == pp9: " << (pp8 == pp9 ? "true" : "false") << std::endl;
    std::cout << "pp8 != pp10: " << (pp8 != pp10 ? "true" : "false") << std::endl;
    
    // Teste com pontos na origem
    std::cout << "\n9. Testando pontos na origem:" << std::endl;
    PontoPolar origem1(0.0, 0.0);
    PontoPolar origem2(0.0, M_PI / 2);  // Ângulo diferente, mas raio zero
    
    std::cout << "origem1: " << origem1 << std::endl;
    std::cout << "origem2: " << origem2 << std::endl;
    std::cout << "origem1 == origem2: " << (origem1 == origem2 ? "true" : "false") << std::endl;
    
    // Teste com raios negativos
    std::cout << "\n10. Testando raios negativos (normalização):" << std::endl;
    PontoPolar pp_neg(-3.0, 0.0);
    std::cout << "PontoPolar(-3, 0): " << pp_neg << std::endl;
    std::cout << "Equivalente cartesiano: " << pp_neg.paraCartesiano() << std::endl;
    
    // Teste de casos especiais
    std::cout << "\n11. Testando casos especiais:" << std::endl;
    
    // Pontos nos eixos principais
    Ponto2D eixoX(5.0, 0.0);
    Ponto2D eixoY(0.0, 5.0);
    Ponto2D eixoXneg(-5.0, 0.0);
    Ponto2D eixoYneg(0.0, -5.0);
    
    PontoPolar polX(eixoX);
    PontoPolar polY(eixoY);
    PontoPolar polXneg(eixoXneg);
    PontoPolar polYneg(eixoYneg);
    
    std::cout << "Eixo X+ " << eixoX << " → " << polX << " (φ=" << polX.getPhiGraus() << "°)" << std::endl;
    std::cout << "Eixo Y+ " << eixoY << " → " << polY << " (φ=" << polY.getPhiGraus() << "°)" << std::endl;
    std::cout << "Eixo X- " << eixoXneg << " → " << polXneg << " (φ=" << polXneg.getPhiGraus() << "°)" << std::endl;
    std::cout << "Eixo Y- " << eixoYneg << " → " << polYneg << " (φ=" << polYneg.getPhiGraus() << "°)" << std::endl;
    
    // Teste final - demonstração prática
    std::cout << "\n12. Demonstração prática - Movimento circular:" << std::endl;
    PontoPolar ponto_circular(4.0, 0.0);  // Raio 4, começando no eixo X
    
    std::cout << "Movimento circular com raio 4:" << std::endl;
    for (int i = 0; i <= 8; i++) {
        double angulo = i * M_PI / 4;  // Incrementos de 45°
        ponto_circular.setPhi(angulo);
        Ponto2D cartesiano = ponto_circular.paraCartesiano();
        
        std::cout << "Ângulo " << (i * 45) << "°: Polar " << ponto_circular 
                  << " → Cartesiano " << cartesiano << std::endl;
    }
    
    return 0;
}
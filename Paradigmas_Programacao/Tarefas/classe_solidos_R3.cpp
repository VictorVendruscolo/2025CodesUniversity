#include <iostream>
#include <vector>
using namespace std;

#define PI 3.1415

// Classe base abstrata para sólidos
class DSolido
{
public:
    virtual float calcArea() = 0;
    virtual float calcVolume() = 0;
};

// Classe para Esfera
class DEsfera : public DSolido
{
    float r;

public:
    DEsfera(float r = 1.0) : r(r) {}

    virtual float calcArea()
    {
        return 4.0 * PI * r * r;
    }

    virtual float calcVolume()
    {
        return (4.0 / 3.0) * PI * r * r * r;
    }
};

// Classe para Cilindro
class DCilindro : public DSolido
{
    float r, h;

public:
    DCilindro(float r = 1.0, float h = 1.0) : r(r), h(h) {}

    virtual float calcArea()
    {
        return 2.0 * PI * r * (r + h);
    }

    virtual float calcVolume()
    {
        return PI * r * r * h;
    }
};

// Classe para conjunto de sólidos
class DConjuntoDeSolidos : public vector<DSolido *>
{
public:
    float areaTotal()
    {
        vector<DSolido *>::iterator it;
        float areaTotal = 0.0;

        for (it = begin(); it != end(); ++it)
            areaTotal += (*it)->calcArea();
        return areaTotal;
    }

    float volumeTotal()
    {
        vector<DSolido *>::iterator it;
        float volumeTotal = 0.0;

        for (it = begin(); it != end(); ++it)
            volumeTotal += (*it)->calcVolume();
        return volumeTotal;
    }
};

int main()
{
    DConjuntoDeSolidos solidos;
    int opcao;
    float r, h;

    do
    {
        cout << "\n1. Adicionar Esfera";
        cout << "\n2. Adicionar Cilindro";
        cout << "\n3. Calcular Area Total";
        cout << "\n4. Calcular Volume Total";
        cout << "\n0. Sair";
        cout << "\nOpcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            cout << "Raio da esfera: ";
            cin >> r;
            solidos.push_back(new DEsfera(r));
            break;
        case 2:
            cout << "Raio do cilindro: ";
            cin >> r;
            cout << "Altura do cilindro: ";
            cin >> h;
            solidos.push_back(new DCilindro(r, h));
            break;
        case 3:
            cout << "Area total: " << solidos.areaTotal() << endl;
            break;
        case 4:
            cout << "Volume total: " << solidos.volumeTotal() << endl;
            break;
        }
    } while (opcao != 0);

    // Libera memória alocada
    for (auto solido : solidos)
        delete solido;

    return 0;
}
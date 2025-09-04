/*#include <SFML/Graphics.hpp>

//cl /std:c++17 /EHsc /I"C:\Users\Victor Vendruscolo\Downloads\SFML-3.0.0-windows-vc17-64-bit\include" main.cpp /link /LIBPATH:"C:\Users\Victor Vendruscolo\Downloads\SFML-3.0.0-windows-vc17-64-bit\lib" sfml-window.lib sfml-graphics.lib sfml-system.lib
//C:\Users\Victor Vendruscolo\Downloads\SFML-3.0.0-windows-vc17-64-bit 
//local do SFML

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");//!
    sf::CircleShape shape(100.f);//! ele usa sf:: porque nao adicionou o "using namespace sf;" no início do código
    shape.setFillColor(sf::Color::Green);//! usa . para acessar os membros

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())//! função de template (is) 
                window.close(); 
        }

        window.clear();
        window.draw(shape);//! eventos (trabalhacom dois buffers)  
        window.display();
    }
    return 0;
}*/
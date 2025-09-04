/*#include <SFML/Graphics.hpp>

//cl /std:c++17 /EHsc /I"C:\librarys\SFML-3.0.0\include" main.cpp /link /LIBPATH:"C:\librarys\SFML-3.0.0\lib" sfml-window.lib sfml-graphics.lib sfml-system.lib

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}*/
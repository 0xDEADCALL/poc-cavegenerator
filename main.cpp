
//SFML
#include <SFML/Graphics.hpp>

//STD
#include <vector>
#include <iostream>
#include <random>
#include <functional>

// MATH
#include <math.h>

#include "MarchingSquares.h"
#include "PerlinNoise2D.h"
#include "CellularAutomaton.h"


// CONST
const float R = 10;
const float WIDTH = 800;
const float HEIGHT = 600;


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML WINDOWS");

    // DIMS
    int nx = ceil(WIDTH / R) + 1;
    int ny = ceil(HEIGHT / R) + 1;
    
    
    CellularAutomaton cel(nx, ny, 0.5);
    MarchingSquares ms(R, sf::Color::White);

    // Do 4 iterations
    cel.iterN(4);

    // Convert bool from the automaton to floats, kinda messy, but ok
    auto bgrid = cel.getGridVector();
    std::vector<std::vector<float>> fgrid(nx, std::vector<float>(ny));

    for (int i = 0; i < cel.width; i++) {
        for (int j = 0; j < cel.height; j++) {
            fgrid[i][j] = bgrid[i][j];
        }
    }

    // Update marching squares structure
    ms.update(fgrid, 0);

    // Draw some rects to show the cells
    std::vector<sf::RectangleShape*> rects;

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            sf::RectangleShape* r = new sf::RectangleShape(sf::Vector2f(R / 4, R / 4));

            if (bgrid[i][j]) {
                r->setFillColor(sf::Color::White);
            }
            else {
                r->setFillColor(sf::Color::Cyan);
            }

            r->setOrigin(R / 8, R / 8);
            r->setPosition(R * i, R * j);

            rects.push_back(r);
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw rect pointers
        for (auto r : rects) {
            window.draw(*r);
        }

        // Draw marching squares lines
        window.draw(ms);

        window.display();
    }

    return 0;
}
#pragma once

// Make the the grid drawbale
#include <SFML/Graphics/Drawable.hpp>

// STD
#include <vector>

// SFML aux libs
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


// Marching squares algorithm pattern lookup table
const std::vector<std::vector<sf::Vector2f>> MS_TABLE {
    {},                                                       // 0
    {sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f / 2, 1.f)},   // 1
    {sf::Vector2f(1.f / 2, 1.f), sf::Vector2f(1.f, 1.f / 2)}, // 2
    {sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f, 1.f / 2)},   // 3
    {sf::Vector2f(1.f / 2, 0), sf::Vector2f(1.f, 1.f / 2)},   // 4
    {sf::Vector2f(1.f / 2, 1.f), sf::Vector2f(1.f, 1.f / 2),  // 5
     sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f / 2, 0)},     // 5
    {sf::Vector2f(1.f / 2, 0), sf::Vector2f(1.f / 2, 1.f)},   // 6
    {sf::Vector2f(1.f / 2, 0), sf::Vector2f(0, 1.f / 2)},     // 7
    {sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f / 2, 0)},     // 8
    {sf::Vector2f(1.f / 2, 0), sf::Vector2f(1.f / 2, 1.f)},   // 9
    {sf::Vector2f(1.f / 2, 0), sf::Vector2f(1.f, 1.f / 2),    // 10
     sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f / 2, 1.f)},   // 10
    {sf::Vector2f(1.f / 2, 0), sf::Vector2f(1.f, 1.f / 2)},   // 11
    {sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f, 1.f / 2)},   // 12
    {sf::Vector2f(1.f / 2, 1.f), sf::Vector2f(1.f, 1.f / 2)}, // 13
    {sf::Vector2f(0, 1.f / 2), sf::Vector2f(1.f / 2, 1.f)},   // 14
    {}                                                        // 15
};



class MarchingSquares : public sf::Drawable {
    public:
        MarchingSquares(float resolution, sf::Color color);

        // Setters for color and resolution
        void setColor(sf::Color c);
        void setResolution(float resolution);

        // Update the binary grid and build new pattern
        void update(std::vector<std::vector<float>>& gridValues, float threshold);

        // Draw the pattern
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        float R;
        sf::Color color;
        std::vector<sf::Vertex> vertices;
};
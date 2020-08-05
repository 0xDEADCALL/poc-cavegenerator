#include "MarchingSquares.h"


// Constructor
MarchingSquares::MarchingSquares(float resolution, sf::Color color) : 
	R(resolution), color(color)
{

}

void MarchingSquares::setColor(sf::Color c)
{
	color = c;
}

void MarchingSquares::setResolution(float resolution)
{
	R = resolution;
}


void MarchingSquares::update(std::vector<std::vector<float>>& gridValues, float threshold) {
	vertices.clear();

	for (int i = 0; i < gridValues.size() - 1; i++) {
		for (int j = 0; j < gridValues[0].size() - 1; j++) {
			int v0 = gridValues[i][j] > threshold ? 1 : 0;
			int v1 = gridValues[i + 1][j] > threshold ? 1 : 0;
			int v2 = gridValues[i + 1][j + 1] > threshold ? 1 : 0;
			int v3 = gridValues[i][j + 1] > threshold ? 1 : 0;

			// Calc bitmask to use as index in the lookup table
			int mask = v0 << 3 | v1 << 2 | v2 << 1 | v3 << 0;
			
			
			// Scale and translate patterns
			for (auto line : MS_TABLE[mask]) {
				vertices.push_back(sf::Vertex(sf::Vector2f(i * R, j * R) + line * R, color));
			}
		}
	}
}



void MarchingSquares::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(&vertices[0], vertices.size(), sf::Lines, state);
}
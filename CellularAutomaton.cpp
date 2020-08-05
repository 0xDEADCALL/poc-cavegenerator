#include "CellularAutomaton.h"

// random
#include <random>
#include <functional>
#include <chrono>

// Contructor with basic init
CellularAutomaton::CellularAutomaton(size_t w, size_t h, float aliveRatio) : 
	width(w),
	height(h),
	grid(w, std::vector<bool>(h, false))
{

	for (int j = 0; j < height; j++) {
		grid[0][j] = true;
		grid[width - 1][j] = true;
	}

	for (int i = 0; i < width; i++) {
		grid[i][0] = true;
		grid[i][height - 1] = true;
	}

	fillGrid(aliveRatio);
}


void CellularAutomaton::fillGrid(float aliveRatio) {
	std::default_random_engine engine;
	std::uniform_real_distribution<float> dist(0, 1);

	engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
	auto r = std::bind(dist, engine);

	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			grid[i][j] = r() <= aliveRatio ? true : false;
		}
	}
}

int CellularAutomaton::getCellNeighbours(int i, int j) {
	int n = 0;
	int indices[MAX_NEIGHBOURS][2] = {{i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1},
									  {i + 1, j + 1}, {i + 1, j - 1}, {i - 1, j + 1}, 
									  {i - 1, j - 1}};

	for (int z = 0; z < MAX_NEIGHBOURS; z++) {
		int x = indices[z][0];
		int y = indices[z][1];

		bool invalidCell = x < 0 || x >= width ||
						   y < 0 || y >= height;

		if (!invalidCell) {
			n += grid[x][y];
		}
	}
	return n;
}


void CellularAutomaton::iter() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int n = getCellNeighbours(i, j);

			switch (n)
			{
				case 1:
				case 2:
					grid[i][j] = false;
					break;


				case 6:
				case 7:
				case 8:
					grid[i][j] = true;
					break;

				default:
					break;
			}
		}
	}
}


void CellularAutomaton::iterN(int N) {
	for (int i = 0; i < N; i++) {
		iter();
	}
}


std::vector<std::vector<bool>> CellularAutomaton::getGridVector() {
	return grid;
}



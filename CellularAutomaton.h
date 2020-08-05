#pragma once

// STD
#include <vector>

// Max number of neighbours
const int MAX_NEIGHBOURS = 8;

// Basic implementation of B678/S345678
// -> A cell to be born needs to have 6, 7 or 8 neighbours
// -> A cell to survive needs to have 3, 4, 5, 6, 7, 8 neighbours
// -> Dies otherwise :)

// We'll not use any optimizations because the grid will be usually small
class CellularAutomaton {
	private:
		std::vector<std::vector<bool>> grid;


	public:
		size_t width;
		size_t height;


	private:
		// Returns the (i, j) cell's alive neighbours
		int getCellNeighbours(int i, int j);

		// Defines the initial state of the grid by filling it with alive cells
		void fillGrid(float aliveRatio);


	public:
		CellularAutomaton(size_t w, size_t h, float aliveRatio);
		
		// Runs one iteration
		void iter (); 

		// Runs N iterations
		void iterN (int N);

		// Returns the grid of states
		std::vector<std::vector<bool>> getGridVector();


};

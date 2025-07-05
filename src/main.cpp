//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers

#include "solver.h"

int main()
{

	int clues[][16] = {
	    { 2, 2, 1, 3,
	    2, 2, 3, 1,
	    1, 2, 2, 3,
	    3, 2, 1, 3 }
	};
    int numClueSets = sizeof(clues) / sizeof(clues[0]);
	
    for (int i = 0; i < numClueSets; ++i)
	{
        int **b = Solver::SolvePuzzle(clues[i]);
        Solver::PrintGrid(b);
        Solver::DeleteGrid(b);
    }

	return 0;
}

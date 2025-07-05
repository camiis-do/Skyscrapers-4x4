//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers

#include "solver.h"

int main()
{

	int clues[][N_sqr] = {
	{ 2, 2, 1, 3,
	2, 2, 3, 1,
	1, 2, 2, 3,
	3, 2, 1, 3 }
	};
	
	int **b = Solver::SolvePuzzle(clues[0]);
	Solver::PrintGrid(b);
    Solver::DeleteGrid(b);

	return 0;
}

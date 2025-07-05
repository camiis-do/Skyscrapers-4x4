//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers

#include "solver.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

int equal(int **puzzle, int expected[4][4]) {
    if (!puzzle || !expected) return 0;
    for (int i = 0; i < 4; ++i) if (memcmp (puzzle[i], expected[i], 4*sizeof (int))) return 0;
    return 1;
}

int clues[][16] = {
    { 2, 2, 1, 3,
        2, 2, 3, 1,
        1, 2, 2, 3,
        3, 2, 1, 3 },
    { 0, 0, 1, 2,   
        0, 2, 0, 0,   
        0, 3, 0, 0, 
        0, 1, 0, 0 }
};

int outcomes[][4][4] = {
    { { 1, 3, 4, 2 },       
        { 4, 2, 1, 3 },       
        { 3, 4, 2, 1 },
        { 2, 1, 3, 4 } },
    { { 2, 1, 4, 3 }, 
        { 3, 4, 1, 2 }, 
        { 4, 2, 3, 1 }, 
        { 1, 3, 2, 4 } },
};

TEST_CASE( "Clues match outcomes", "[equal]" ) {
    int numClueSets = sizeof(clues) / sizeof(clues[0]);
    for (int i = 0; i < numClueSets; ++i)
	{
        int **b = Solver::SolvePuzzle(clues[i]);
        REQUIRE( equal(b, outcomes[i]) == 0 );
        Solver::PrintGrid(b);
        Solver::DeleteGrid(b);
    }
}

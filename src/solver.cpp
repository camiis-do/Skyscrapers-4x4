//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers

#include "solver.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

const int ONE   = 0b0001; // 1
const int TWO   = 0b0010; // 2
const int THREE = 0b0100; // 3
const int FOUR  = 0b1000; // 4
const int ALL   = ONE | TWO | THREE | FOUR; // 0b1111

constexpr int N = 4;
constexpr int N_sqr = N * N;

int ConvertCellBits(int val)
{
  if (val & ONE) 	return 1;
  if (val & TWO) 	return 2;
  if (val & THREE) 	return 3;
  if (val & FOUR) 	return 4;
  return val;
}

void PrintCellBits(int val) {
    cout << "[";
	cout << ConvertCellBits(val);
    cout << "]";
}

void Solver::PrintGrid(int** grid) {
    cout << "Current Grid State:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            PrintCellBits(grid[i][j]);
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int** Solver::ConvertGrid(int** grid)
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
		grid[i][j] = ConvertCellBits(grid[i][j]);
    }
  }
  return grid;
}

void Solver::DeleteGrid(int** grid)
{
	for (int i = 0; i < N; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

int** Solver::SolvePuzzle(int *clues)
{
	int **grid = new int*[N];
	for (int i = 0; i < N; i++)
	{
		grid[i] = new int[N];
		for (int j = 0; j < N; j++)
			grid[i][j] = ALL;
	}

	int *line[N_sqr][N] = { { &grid[0][0], &grid[1][0], &grid[2][0], &grid[3][0] },
	{ &grid[0][1], &grid[1][1], &grid[2][1], &grid[3][1] },
	{ &grid[0][2], &grid[1][2], &grid[2][2], &grid[3][2] },
	{ &grid[0][3], &grid[1][3], &grid[2][3], &grid[3][3] },

	{ &grid[0][3], &grid[0][2], &grid[0][1], &grid[0][0] },
	{ &grid[1][3], &grid[1][2], &grid[1][1], &grid[1][0] },
	{ &grid[2][3], &grid[2][2], &grid[2][1], &grid[2][0] },
	{ &grid[3][3], &grid[3][2], &grid[3][1], &grid[3][0] },

	{ &grid[3][3], &grid[2][3], &grid[1][3], &grid[0][3] },
	{ &grid[3][2], &grid[2][2], &grid[1][2], &grid[0][2] },
	{ &grid[3][1], &grid[2][1], &grid[1][1], &grid[0][1] },
	{ &grid[3][0], &grid[2][0], &grid[1][0], &grid[0][0] },

	{ &grid[3][0], &grid[3][1], &grid[3][2], &grid[3][3] },
	{ &grid[2][0], &grid[2][1], &grid[2][2], &grid[2][3] },
	{ &grid[1][0], &grid[1][1], &grid[1][2], &grid[1][3] },
	{ &grid[0][0], &grid[0][1], &grid[0][2], &grid[0][3] } };

	int count = 0;
	while (count < N_sqr)
	{
		for (int i = 0; i < N_sqr; i++)
		{
			switch (clues[i])
			{
			case 1:
			{
				*line[i][0] = FOUR;
				break;
			}
			case 2:
			{
				*line[i][0] &= ~FOUR; // Remove 4 from line[i][0] if it's still a possible value

				if (*line[i][3] == FOUR) {
					*line[i][0] = THREE;
				}

				if (*line[i][2] == FOUR) {
					if (*line[i][0] == TWO || *line[i][3] == THREE) {
						*line[i][0] = TWO;
						*line[i][1] = ONE;
						*line[i][3] = THREE;
					} else if (*line[i][3] == TWO) {
						*line[i][0] = THREE;
						*line[i][1] = ONE;
					} else if (*line[i][1] == TWO || *line[i][3] == ONE) {
						*line[i][0] = THREE;
						*line[i][1] = TWO;
						*line[i][3] = ONE;
					} else {
						*line[i][0] &= ~ONE;
						*line[i][1] &= ~THREE;
					}
				}
				break;
			}
			case 3:
			{
				*line[i][0] &= ~FOUR;
				*line[i][0] &= ~THREE;
				*line[i][1] &= ~FOUR;

				if (*line[i][3] == FOUR)
				{
					if (*line[i][1] == ONE || *line[i][2] == THREE)
					{
						*line[i][0] = TWO;
						*line[i][1] = ONE;
						*line[i][2] = THREE;
					} else if (*line[i][0] == ONE || *line[i][2] == TWO)
					{
						*line[i][0] = ONE;
						*line[i][1] = THREE;
						*line[i][2] = TWO;
					}
					else if (*line[i][2] == ONE)
					{
						*line[i][0] = TWO;
						*line[i][1] = THREE;
					}
				}
				else if (*line[i][2] == FOUR) {
					if (*line[i][3] == THREE || *line[i][1] == TWO)
					{
						*line[i][1] = TWO;
						*line[i][0] = ONE;
						*line[i][3] = THREE;
					}
					else if (*line[i][0] == TWO || *line[i][3] == ONE) {
						*line[i][0] = TWO;
						*line[i][1] = THREE;
						*line[i][3] = ONE;
					}
					else if (*line[i][3] == TWO)
					{
						*line[i][0] = ONE;
						*line[i][1] = THREE;
					}
				}
				break;
			}
			case 4:
			{
				*line[i][0] = ONE;
				*line[i][1] = TWO;
				*line[i][2] = THREE;
				*line[i][3] = FOUR;
				break;
			}
			default:
				break;
			}

		}
		count = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int val = grid[i][j];
		
				// If only one value remains (definitive), eliminate it from same row and column
				if (__builtin_popcount(val) == 1) {
					for (int k = 0; k < 4; k++) {
						if (k != i) grid[k][j] &= ~val;
						if (k != j) grid[i][k] &= ~val;
					}
					++count;
				}
			}
		}
		
		// Go through first 8 clues (lines from each direction) to identify if any value occurs exactly once
		for (int i = 0; i < 8; i++) {
			int countBits[N] = {0};
		
			for (int j = 0; j < N; j++) {
				int val = *line[i][j];
				if (val & ONE)   countBits[0]++;
				if (val & TWO)   countBits[1]++;
				if (val & THREE) countBits[2]++;
				if (val & FOUR)  countBits[3]++;
			}
		
			// For each value (1–4), if it occurs only once, assign it to that cell
			for (int v = 0; v < N; v++) {
				if (countBits[v] == 1) {
					for (int j = 0; j < N; j++) {
						if (*line[i][j] & (1 << v)) {
							*line[i][j] = (1 << v);
							break;
						}
					}
				}
			}
		}		
	}
	return ConvertGrid(grid);
}

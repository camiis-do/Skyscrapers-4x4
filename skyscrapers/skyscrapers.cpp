//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers


#include <iostream>
#include <cmath>

using namespace std;

const int ONE   = 0b0001; // 1
const int TWO   = 0b0010; // 2
const int THREE = 0b0100; // 3
const int FOUR  = 0b1000; // 4
const int ALL   = ONE | TWO | THREE | FOUR; // 0b1111

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

void PrintGrid(int** grid) {
    cout << "Current Grid State:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            PrintCellBits(grid[i][j]);
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int** ConvertGrid(int** grid)
{
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ConvertCellBits(grid[i][j]);
    }
  }
  return grid;
}

int** SolvePuzzle(int *clues)
{
	int **res = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		res[i] = new int[4];
		for (int j = 0; j < 4; j++)
			res[i][j] = ALL;
	}

	int *line[16][4] = { { &res[0][0], &res[1][0], &res[2][0], &res[3][0] },
	{ &res[0][1], &res[1][1], &res[2][1], &res[3][1] },
	{ &res[0][2], &res[1][2], &res[2][2], &res[3][2] },
	{ &res[0][3], &res[1][3], &res[2][3], &res[3][3] },

	{ &res[0][3], &res[0][2], &res[0][1], &res[0][0] },
	{ &res[1][3], &res[1][2], &res[1][1], &res[1][0] },
	{ &res[2][3], &res[2][2], &res[2][1], &res[2][0] },
	{ &res[3][3], &res[3][2], &res[3][1], &res[3][0] },

	{ &res[3][3], &res[2][3], &res[1][3], &res[0][3] },
	{ &res[3][2], &res[2][2], &res[1][2], &res[0][2] },
	{ &res[3][1], &res[2][1], &res[1][1], &res[0][1] },
	{ &res[3][0], &res[2][0], &res[1][0], &res[0][0] },

	{ &res[3][0], &res[3][1], &res[3][2], &res[3][3] },
	{ &res[2][0], &res[2][1], &res[2][2], &res[2][3] },
	{ &res[1][0], &res[1][1], &res[1][2], &res[1][3] },
	{ &res[0][0], &res[0][1], &res[0][2], &res[0][3] } };

	int count = 0;
	while (count < 16)
	{
		for (int i = 0; i < 16; i++)
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
				*line[i][0] &= ~FOUR; // Remove FOUR from line[i][0] if it's still a possible value

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

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int val = res[i][j];
		
				// If only one value remains (definitive), eliminate it from same row and column
				if (__builtin_popcount(val) == 1) {
					for (int k = 0; k < 4; k++) {
						if (k != i) res[k][j] &= ~val;
						if (k != j) res[i][k] &= ~val;
					}
					++count;
				}
			}
		}
		
		// Go through first 8 clues (lines from each direction) to identify if any value occurs exactly once
		for (int i = 0; i < 8; i++) {
			int countBits[4] = {0};
		
			for (int j = 0; j < 4; j++) {
				int val = *line[i][j];
				if (val & ONE)   countBits[0]++;
				if (val & TWO)   countBits[1]++;
				if (val & THREE) countBits[2]++;
				if (val & FOUR)  countBits[3]++;
			}
		
			// For each value (1–4), if it occurs only once, assign it to that cell
			for (int v = 0; v < 4; v++) {
				if (countBits[v] == 1) {
					for (int j = 0; j < 4; j++) {
						if (*line[i][j] & (1 << v)) {
							*line[i][j] = (1 << v);
							break;
						}
					}
				}
			}
		}		
	}
	return ConvertGrid(res);
}

int main()
{

	int clues[][16] = {
	{ 2, 2, 1, 3,
	2, 2, 3, 1,
	1, 2, 2, 3,
	3, 2, 1, 3 }
	};
	
	int **b = SolvePuzzle(clues[0]);
	PrintGrid(b);

	for (int i = 0; i < 4; i++) {
		delete[] res[i];
	}
	delete[] res;
	
	system("pause");
	return 0;
}
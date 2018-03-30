//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers


#include <iostream>

using namespace std;

int clues[16] = { 2, 2, 1, 3,
2, 2, 3, 1,
1, 2, 2, 3,
3, 2, 1, 3 };


int** SolvePuzzle()
{
	int **res = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		res[i] = new int[4];
		for (int j = 0; j < 4; j++)
			res[i][j] = 1234;
		//res[i] = { 1234 };
		
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
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				cout << res[i][j] << " ";
			cout << endl;
		}
		cout << endl;

		for (int i = 0; i < 16; i++)
		{
			switch (clues[i])
			{
			case 1:
			{
				*line[i][0] = 4;
				break;
			}
			case 2:
			{
				if (*line[i][0] % 10 == 4)
					*line[i][0] -= 4;
				if (*line[i][3] == 4)
				{
					*line[i][0] = 30;
				}
				if (*line[i][2] == 4)
				{
					if (*line[i][0] == 200 || *line[i][3] == 30)
					{
						*line[i][0] = 200;
						*line[i][1] = 1000;
						*line[i][3] = 30;
					}	else if (*line[i][3] == 200)
					{
						*line[i][0] = 30;
						*line[i][1] = 1000;
					} else if (*line[i][1] == 200 || *line[i][3] == 1000)
					{
						*line[i][0] = 30;
						*line[i][1] = 200;
						*line[i][3] = 1000;
					}
					else {
						if (*line[i][0] > 1000)
							*line[i][0] -= 1000;
						if (*line[i][1] % 100 >= 30)
							*line[i][1] -= 30;
					}
				}
				break;
			}
			case 3:
			{
				if (*line[i][0] % 10 == 4)
					*line[i][0] -= 4;
				if (*line[i][0] % 100 >= 30)
					*line[i][0] -= 30;
				if (*line[i][1] % 10 == 4)
					*line[i][1] -= 4;
				if (*line[i][3] == 4)
				{
					if (*line[i][1] == 1000 || *line[i][2] == 30)
					{
						*line[i][0] = 200;
						*line[i][1] = 1000;
						*line[i][2] = 30;
					} else if (*line[i][0] == 1000 || *line[i][2] == 200)
					{
						*line[i][0] = 1000;
						*line[i][1] = 30;
						*line[i][2] = 200;
					}
					else if (*line[i][2] == 1000)
					{
						*line[i][0] = 200;
						*line[i][1] = 30;
					}
				}	else if (*line[i][2] == 4)
				{
					if (*line[i][3] == 30 || *line[i][1] == 200)
					{
						*line[i][1] = 200;
						*line[i][0] = 1000;
						*line[i][3] = 30;
					}
					else if (*line[i][0] == 200 || *line[i][3] == 1000) {
						*line[i][0] = 200;
						*line[i][1] = 30;
						*line[i][3] = 1000;
					}
					else if (*line[i][3] == 200)
					{
						*line[i][0] = 1000;
						*line[i][1] = 30;
					}
				}
				break;
			}
			case 4:
			{
				*line[i][0] = 1000;
				*line[i][1] = 200;
				*line[i][2] = 30;
				*line[i][3] = 4;
				break;
			}
			default:
				break;
			}

		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				cout << res[i][j] << " ";
			cout << endl;
		}
		cout << endl;

		count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (res[i][j] == 1000)
				{
					for (int k = 0; k < 4; k++)
					{
						if (res[k][j] > 1000)
							res[k][j] -= 1000;
						if (res[i][k] > 1000)
							res[i][k] -= 1000;
					}
					++count;
				}
				else if (res[i][j] == 200)
				{
					for (int k = 0; k < 4; k++)
					{
						if (res[k][j] != 200 && res[k][j] % 1000 >= 200)
							res[k][j] -= 200;
						if (res[i][k] != 200 && res[i][k] % 1000 >= 200)
							res[i][k] -= 200;
					}
					++count;
				}
				else if (res[i][j] == 30)
				{
					for (int k = 0; k < 4; k++)
					{
						if (res[k][j]!= 30 && res[k][j] % 100 >= 30)
							res[k][j] -= 30;
						if (res[i][k] != 30 && res[i][k] % 100 >= 30)
							res[i][k] -= 30;
					}
					++count;
				}
				else if (res[i][j] == 4)
				{
					for (int k = 0; k < 4; k++)
					{
						if (res[k][j] != 4 && res[k][j] % 10 == 4)
							res[k][j] -= 4;
						if (res[i][k] != 4 && res[i][k] % 10 == 4)
							res[i][k] -= 4;
					}
					++count;
				}
			}


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				cout << res[i][j] << " ";
			cout << endl;
		}
		cout << endl;

		for (int i = 0; i < 8; i++)
		{
			int tmp[4] = { 0 };
			for (int j = 0; j < 4; j++)
			{
				if (*line[i][j] >= 1000)
					tmp[0]++;
				if (*line[i][j] % 1000 >= 200)
					tmp[1]++;
				if (*line[i][j] % 100 >= 30)
					tmp[2]++;
				if (*line[i][j] % 10 >= 4)
					tmp[3]++;
			}
			int coeff = 10000;
			for (int j = 0; j < 4; j++)
			{
				if (tmp[j] == 1)
				{
					for (int k = 0; k < 4; k++)
					{
						if (*line[i][k] % coeff >= coeff / 10)
						{
							*line[i][k] = ( j + 1 ) * pow(10, 3 - j);
							break;
						}
					}
					
				}
				coeff /= 10;
				
			}
		}


	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			while (res[i][j] % 10 == 0)
				res[i][j] /= 10;
	return res;
}


int main()
{
	int **b = SolvePuzzle();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}
	system("pause");
	return 0;
}
//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers

class Solver
{
public:
    static int** SolvePuzzle(int *clues);
    static void PrintGrid(int** grid);
    static void DeleteGrid(int** grid);
private:
    static int** ConvertGrid(int** grid);
    static bool PropagateConstraints(int** grid, int row, int col, int bitmask);
};

//Task is
//https://www.codewars.com/kata/4-by-4-skyscrapers

#include "solver.h"
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include <random>

constexpr int N = 4;
constexpr int N_sqr = N * N;

bool equal(int **grid, int expected[N][N]) {
    if (!grid) return false;
    for (int i = 0; i < N; ++i) if (memcmp(grid[i], expected[i], N * sizeof(int))) return false;
    return true;
}

bool isValidGrid(int** grid) {
    if (!grid) return false;
    for (int i = 0; i < N; ++i) {
        bool row[N] = {false}, col[N] = {false};
        for (int j = 0; j < N; ++j) {
            int r = grid[i][j], c = grid[j][i];
            if (r < 1 || r > N || row[r-1]) return false;
            if (c < 1 || c > N || col[c-1]) return false;
            row[r-1] = true;
            col[c-1] = true;
        }
    }
    return true;
}

bool checkClue(int clueIdx, int clueVal, int** grid) {
    int maxSeen = 0;
    int visibleCount = 0;

    for (int step = 0; step < N; ++step) {
        int i = 0, j = 0;
        switch (clueIdx / 4) {
            case 0: i = step; j = clueIdx % 4; break;               // top
            case 1: i = clueIdx % 4; j = 3 - step; break;           // right
            case 2: i = 3 - step; j = 11 - clueIdx; break;          // bottom
            case 3: i = 15 - clueIdx; j = step; break;              // left
        }

        int height = grid[i][j];
        if (height > maxSeen) {
            ++visibleCount;
            maxSeen = height;
        }
    }

    return visibleCount == clueVal;
}

void generateRandomClues(int clues[N_sqr]) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, N);
    for (int i = 0; i < N_sqr; ++i) clues[i] = dis(g);
}

TEST_CASE("Random clues produce valid solution") {
    for (int t = 0; t < 100; ++t) {
        int clues[N_sqr];
        generateRandomClues(clues);

        int** solution = Solver::SolvePuzzle(clues);
        REQUIRE(solution != nullptr);
        CHECK(isValidGrid(solution));
        for (int i = 0; i < N_sqr; ++i)
        {
            if (clues[i] > 0)
            {
                CHECK(checkClue(i, clues[i], solution));
            }
        }

        Solver::DeleteGrid(solution);
    }
}

TEST_CASE("Clues match outcomes") {
    int clues[][N_sqr] = {
        {
            2, 2, 1, 3,
            2, 2, 3, 1,
            1, 2, 2, 3,
            3, 2, 1, 3
        },
        {
            0, 0, 1, 2,   
            0, 2, 0, 0,   
            0, 3, 0, 0, 
            0, 1, 0, 0
        }
    };
    int outcomes[][N][N] = {
        {
            { 1, 3, 4, 2 },       
            { 4, 2, 1, 3 },       
            { 3, 4, 2, 1 },
            { 2, 1, 3, 4 }
        },
        {
            { 2, 1, 4, 3 }, 
            { 3, 4, 1, 2 }, 
            { 4, 2, 3, 1 }, 
            { 1, 3, 2, 4 }
        },
    };

    int numClueSets = sizeof(clues) / sizeof(clues[0]);
    for (int i = 0; i < numClueSets; ++i)
	{
        int **solution = Solver::SolvePuzzle(clues[i]);
        CHECK(isValidGrid(solution));
        REQUIRE(equal(solution, outcomes[i]));

        for (int clue_idx = 0; clue_idx < N_sqr; ++clue_idx)
            if (clues[i][clue_idx] > 0)
                CHECK(checkClue(clue_idx, clues[i][clue_idx], solution));

        Solver::DeleteGrid(solution);
    }
}

TEST_CASE("Integrated solve and format") {
    int clues[N_sqr] = {
        1, 2, 3, 2,
        2, 3, 1, 3,
        3, 1, 2, 2,
        2, 2, 3, 1
    };

    int** solution = SolvePuzzle(clues);
    REQUIRE(isValidGrid(solution));

    std::stringstream ss;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            ss << solution[i][j] << " ";
        ss << "\n";
    }
    std::string out = ss.str();
    CHECK(out.find("4") != std::string::npos);

    Solver::DeleteGrid(solution);
}

TEST_CASE("Solver completes under time limit") {
    int clues[N_sqr] = {
        1, 2, 3, 4,
        4, 3, 2, 1,
        2, 2, 2, 2,
        3, 3, 1, 1
    };

    auto start = std::chrono::steady_clock::now();

    int** solution = Solver::SolvePuzzle(clues);

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    REQUIRE(elapsed.count() < 100);
    REQUIRE(isValidGrid(solution));

    Solver::DeleteGrid(solution);
}

#include "n_puzzle.h"
#include <iostream>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;

int main() {
    int puzzleSize = 6;
    // Generate and print the goal state
    vector<vector<int>> goalState = generateGoalState(puzzleSize);
    cout << "\nGoal State:\n";
    printNPuzzle(goalState);

    // Generate and print the puzzle
    vector<vector<int>> puzzle = {
        {1, 2, 3, 4, 5, 6},
        {7, 8, 0, 10, 11, 12},
        {13, 14, 9, 15, 17, 18},
        {19, 20, 21, 16, 23, 24},
        {25, 26, 27, 22, 29, 30},
        {31, 32, 33, 28, 34, 35}


    };
    cout << "Generated Puzzle:" << endl;
    printNPuzzle(puzzle);

    // UCS test
    auto start_time = std::chrono::high_resolution_clock::now();
    ProblemSolveUCS(puzzle,goalState);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    std::cout << "Working Set Size: " << pmc.WorkingSetSize << " bytes" << std::endl;

    // A* test
    start_time = std::chrono::high_resolution_clock::now();
    aStar(puzzle, goalState);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    std::cout << "Working Set Size: " << pmc.WorkingSetSize << " bytes" << std::endl;

    return 0;
}

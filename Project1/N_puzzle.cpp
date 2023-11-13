#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "N_puzzle.h"

// Function to generate an N-puzzle
std::vector<std::vector<int>> generateNPuzzle(int size) {
    // Create a vector to represent the puzzle
    std::vector<int> puzzle(size * size);

    // Fill the vector with numbers from 1 to size*size-1
    for (int i = 0; i < size * size - 1; ++i) {
        puzzle[i] = i + 1;
    }

    // Set the last element as 0 to represent the empty space
    puzzle[size * size - 1] = 0;

    // Shuffle the puzzle using a random engine
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(puzzle.begin(), puzzle.end(), g);

    // Convert the 1D vector to a 2D vector
    std::vector<std::vector<int>> result(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = puzzle[i * size + j];
        }
    }

    return result;
}

// Function to print the N-puzzle
void printNPuzzle(const std::vector<std::vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        for (int value : row) {
            std::cout << value << '\t';
        }
        std::cout << '\n';
    }
}

std::vector<std::vector<int>> generateGoalState(int size) {
    std::vector<std::vector<int>> goal(size, std::vector<int>(size));

    int num = 1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            goal[i][j] = num++;
        }
    }

    // Set the last element as 0 to represent the empty space
    goal[size - 1][size - 1] = 0;

    return goal;
}

std::pair<int, int> findEmptySpace(const std::vector<std::vector<int>>& puzzle) {
    for (int i = 0; i < puzzle.size(); ++i) {
        for (int j = 0; j < puzzle[i].size(); ++j) {
            if (puzzle[i][j] == 0) {
                return std::make_pair(i, j);
            }
        }
    }
    // Return an invalid position if the empty space is not found (you may want to handle this differently)
    return std::make_pair(-1, -1);
}

std::vector<std::vector<int>> moveUp(std::vector<std::vector<int>> puzzle) {
    auto [emptyRow, emptyCol] = findEmptySpace(puzzle);
    if (emptyRow > 0) {
        std::swap(puzzle[emptyRow][emptyCol], puzzle[emptyRow - 1][emptyCol]);
    }
    else puzzle.clear();
    return puzzle;
}

std::vector<std::vector<int>> moveDown(std::vector<std::vector<int>> puzzle) {
    auto [emptyRow, emptyCol] = findEmptySpace(puzzle);
    if (emptyRow < puzzle.size() - 1) {
        std::swap(puzzle[emptyRow][emptyCol], puzzle[emptyRow + 1][emptyCol]);
    }
    else puzzle.clear();
    return puzzle;
}

std::vector<std::vector<int>> moveLeft(std::vector<std::vector<int>> puzzle) {
    auto [emptyRow, emptyCol] = findEmptySpace(puzzle);
    if (emptyCol > 0) {
        std::swap(puzzle[emptyRow][emptyCol], puzzle[emptyRow][emptyCol - 1]);
    }
    else puzzle.clear();
    return puzzle;
}

std::vector<std::vector<int>> moveRight(std::vector<std::vector<int>> puzzle) {
    auto [emptyRow, emptyCol] = findEmptySpace(puzzle);
    if (emptyCol < puzzle[emptyRow].size() - 1) {
        std::swap(puzzle[emptyRow][emptyCol], puzzle[emptyRow][emptyCol + 1]);
    }
    else puzzle.clear();
    return puzzle;
}

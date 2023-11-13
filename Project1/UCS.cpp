#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "N_puzzle.h"


void ProblemSolveUCS(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> GoalState) {
    std::vector<node> states;
    states.push_back(node(puzzle));
    int n = puzzle.size();
    while (puzzle != GoalState) {
        int chosen = std::numeric_limits<int>::max();
        int chosen_index = 0;
        for (int i = 0; i < states.size(); i++) {
            if (chosen > states[i].state.size()) {
                chosen_index = i;
                chosen = states[i].state.size();
            }
        }

        puzzle = states[chosen_index].state;

        // check movable and add to states
        auto [emptyRow, emptyCol] = findEmptySpace(puzzle);
        if (emptyRow < n - 1) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('D');
            states.push_back(node(moveDown(puzzle), path));
        }
        if (emptyRow > 0) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('U');
            states.push_back(node(moveUp(puzzle), path));
        }
        if (emptyCol > 0) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('L');
            states.push_back(node(moveLeft(puzzle), path));
        }
        if (emptyCol < n - 1) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('R');
            states.push_back(node(moveRight(puzzle), path));
        }
        if (puzzle == GoalState) {
            std::cout << "------------- start" << std::endl;
            if (states[chosen_index].path.size() > 0) {
                for (int i = 0; i < states[chosen_index].path.size(); i++) {
                    std::cout << states[chosen_index].path[i] << " ";
                }
                std::cout << std::endl;
            }
            printNPuzzle(puzzle);
            std::cout << "------------- end" << std::endl;
        }
        
        states.erase(states.begin() + chosen_index); 
    }
}
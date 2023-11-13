#pragma once
#include "N_puzzle.h"
#include <iostream>
#include <vector>
#include <algorithm>

int inversionDistance(const std::vector<int>& perm1, const std::vector<int>& perm2) {
    int size = perm1.size();
    int distance = 0;
    std::vector<int> tempPerm(perm1.begin(), perm1.end());
    std::vector<int> indexMap(size);

    for (int i = 0; i < size; ++i) {
        indexMap[tempPerm[i]] = i;
    }

    for (int i = 0; i < size; ++i) {
        int index = indexMap[perm2[i]];

        while (index != i) {
            std::swap(tempPerm[i], tempPerm[index]);
            indexMap[tempPerm[index]] = index;
            indexMap[tempPerm[i]] = i;
            ++distance;
            index = indexMap[perm2[i]];
        }
    }

    return distance;
}

std::vector<int> straighthen(const std::vector<std::vector<int>>& puzzle) {
    std::vector<int> permutation;
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[i].size(); j++) {
            permutation.push_back(puzzle[i][j]);
        }
    }
    return permutation;
}

void aStar(std::vector<std::vector<int>> puzzle,const std::vector<std::vector<int>>& GoalState) {
    std::vector<aNode> states;
    states.push_back(aNode(puzzle));
    int n = puzzle.size();

    while (puzzle != GoalState) {
        int chosen = std::numeric_limits<int>::max();
        int chosen_index = 0;
        for (int i = 0; i < states.size(); i++) {
            if (chosen > states[i].state.size() + states[i].cost) {
                chosen_index = i;
                chosen = states[i].state.size() + states[i].cost;
            }
        }

        puzzle = states[chosen_index].state;

        // check movable and add to states
        auto [emptyRow, emptyCol] = findEmptySpace(puzzle);
        if (emptyRow < n - 1) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('D');
            states.push_back(aNode(moveDown(puzzle), path,inversionDistance(straighthen(puzzle),straighthen(moveDown(puzzle)))));
        }
        if (emptyRow > 0) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('U');
            states.push_back(aNode(moveUp(puzzle), path, inversionDistance(straighthen(puzzle), straighthen(moveUp(puzzle)))));
        }
        if (emptyCol > 0) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('L');
            states.push_back(aNode(moveLeft(puzzle), path, inversionDistance(straighthen(puzzle), straighthen(moveLeft(puzzle)))));
        }
        if (emptyCol < n - 1) {
            std::vector<char> path = states[chosen_index].path;
            path.push_back('R');
            states.push_back(aNode(moveRight(puzzle), path, inversionDistance(straighthen(puzzle), straighthen(moveRight(puzzle)))));
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
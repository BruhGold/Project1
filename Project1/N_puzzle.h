#ifndef N_PUZZLE_H
#define N_PUZZLE_H

#include <vector>

std::vector<std::vector<int>> generateNPuzzle(int size);
void printNPuzzle(const std::vector<std::vector<int>>& puzzle);
std::vector<std::vector<int>> generateGoalState(int size);
std::pair<int, int> findEmptySpace(const std::vector<std::vector<int>>& puzzle);
std::vector<std::vector<int>> moveUp(std::vector<std::vector<int>> puzzle);
std::vector<std::vector<int>> moveDown(std::vector<std::vector<int>> puzzle);
std::vector<std::vector<int>> moveLeft(std::vector<std::vector<int>> puzzle);
std::vector<std::vector<int>> moveRight(std::vector<std::vector<int>> puzzle);
void ProblemSolveUCS(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> GoalState);
int inversionDistance(const std::vector<int>& perm1, const std::vector<int>& perm2);
std::vector<int> straighthen(const std::vector<std::vector<int>>& puzzle);
void aStar(std::vector<std::vector<int>> puzzle, const std::vector<std::vector<int>>& GoalState);

class node {
public:
	std::vector<std::vector<int>> state;
	std::vector<char> path;
	node(std::vector<std::vector<int>> puzzle) {
		state = puzzle;
	}

	node(std::vector<std::vector<int>> puzzle, std::vector<char> prePath){
		state = puzzle;
		path = prePath;
	}
};

class aNode {
public:
	std::vector<std::vector<int>> state;
	std::vector<char> path;
	int cost;
	aNode(std::vector<std::vector<int>> puzzle) {
		state = puzzle;
		cost = 0;
	}

	aNode(std::vector<std::vector<int>> puzzle, std::vector<char> prePath, int heuristic) {
		state = puzzle;
		path = prePath;
		cost = heuristic;
	}
};

#endif // N_PUZZLE_H

#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "DFSSolver.h"

// Iterative-deepening DFS solver for Rubik's Cube
// T: cube type; H: hash functor for that type

template<typename T, typename H>
class IDDFSSolver {
private:
    int maxDepth;                            // maximum search depth
    vector<RubiksCube::MOVE> moves;          // solution moves

public:
    T rubiksCube;                            // initial cube state

    // Constructor: take starting cube and optional depth limit
    IDDFSSolver(T cube, int depthLimit = 7)
        : rubiksCube(cube), maxDepth(depthLimit) {}

    // Increase depth from 1 to maxDepth, run DFS each time
    vector<RubiksCube::MOVE> solve() {
        for (int depth = 1; depth <= maxDepth; ++depth) {
            DFSSolver<T, H> dfs(rubiksCube, depth);
            moves = dfs.solve();
            if (dfs.rubiksCube.isSolved()) {
                rubiksCube = dfs.rubiksCube;
                break;
            }
        }
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
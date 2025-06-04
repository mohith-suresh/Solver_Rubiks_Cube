#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"

// BFS solver for a Rubik's Cube model T with hash H.
// T must support move(), invert(), isSolved(), and operator==.
// H is a hash functor for T.

template<typename T, typename H>
class BFSSolver {
private:
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, bool, H> visited;
    unordered_map<T, RubiksCube::MOVE, H> move_done;

    // Run breadth-first search from rubiksCube, return solved state.
    T bfs() {
        queue<T> q;
        q.push(rubiksCube);
        visited[rubiksCube] = true;

        while (!q.empty()) {
            T node = q.front(); 
            q.pop();
            if (node.isSolved()) {
                return node;
            }
            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                if (!visited[node]) {
                    visited[node] = true;
                    move_done[node] = curr_move;
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
        return rubiksCube; 
    }

public:
    T rubiksCube;

    BFSSolver(T _rubiksCube) : rubiksCube(_rubiksCube) {}

    // Perform BFS and reconstruct the move sequence to solve the cube.
    vector<RubiksCube::MOVE> solve() {
        T solved_cube = bfs();
        assert(solved_cube.isSolved());
        T curr_cube = solved_cube;
        while (!(curr_cube == rubiksCube)) {
            auto curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        rubiksCube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_BFSSOLVER_H
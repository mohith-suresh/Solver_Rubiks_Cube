#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"

// IDA* solver using a corner-pattern database heuristic.
// T: cube representation (3D, 1D, or bitboard).
// H: hash functor for T.

template<typename T, typename H>
class IDAstarSolver {
private:
    CornerPatternDatabase cornerDB;                    // heuristic data
    vector<RubiksCube::MOVE> moves;                    // solution moves
    unordered_map<T, RubiksCube::MOVE, H> move_done;   // backpointers
    unordered_map<T, bool, H> visited;                 // visited states

    struct Node {
        T cube;
        int depth;       // current search depth
        int estimate;    // heuristic estimate to goal

        Node(T c, int d, int e) : cube(c), depth(d), estimate(e) {}
    };

    struct Compare {
        bool operator()(const pair<Node, int>& a, const pair<Node, int>& b) {
            int f1 = a.first.depth + a.first.estimate;
            int f2 = b.first.depth + b.first.estimate;
            if (f1 == f2) {
                return a.first.estimate > b.first.estimate;
            }
            return f1 > f2;
        }
    };

    void resetSearch() {
        moves.clear();
        move_done.clear();
        visited.clear();
    }

    // Perform one iteration of IDA* with bound 'limit'.
    // Returns: {solved_cube, next_bound_if_not_solved}.
    pair<T,int> search(int limit) {
        priority_queue<pair<Node,int>, vector<pair<Node,int>>, Compare> pq;
        Node start{ rubiksCube, 0, cornerDB.getNumMoves(rubiksCube) };
        pq.push({ start, 0 });
        int nextBound = INT_MAX;

        while (!pq.empty()) {
            auto [node, lastMove] = pq.top();
            pq.pop();

            // Skip if we've already visited this state
            if (visited[node.cube]) continue;
            visited[node.cube] = true;
            move_done[node.cube] = static_cast<RubiksCube::MOVE>(lastMove);

            if (node.cube.isSolved()) {
                return { node.cube, limit };
            }

            int newDepth = node.depth + 1;
            for (int i = 0; i < 18; ++i) {
                RubiksCube::MOVE m = static_cast<RubiksCube::MOVE>(i);
                node.cube.move(m);
                if (!visited[node.cube]) {
                    int h = cornerDB.getNumMoves(node.cube);
                    int f = newDepth + h;
                    if (f > limit) {
                        nextBound = min(nextBound, f);
                    } else {
                        Node child{ node.cube, newDepth, h };
                        pq.push({ child, i });
                    }
                }
                node.cube.invert(m);
            }
        }
        return { rubiksCube, nextBound };
    }

public:
    T rubiksCube;  // initial cube state

    // Constructor: load a precomputed corner DB from file.
    IDAstarSolver(T cube, const string& dbFile) {
        rubiksCube = cube;
        cornerDB.fromFile(dbFile);
    }

    // Repeatedly increase bound until solved.
    vector<RubiksCube::MOVE> solve() {
        int bound = cornerDB.getNumMoves(rubiksCube);
        pair<T,int> result = search(bound);

        while (result.second != bound) {
            resetSearch();
            bound = result.second;
            result = search(bound);
        }

        T solvedCube = result.first;
        assert(solvedCube.isSolved());

        // Reconstruct path: follow backpointers from solvedCube back to initial.
        T current = solvedCube;
        while (!(current == rubiksCube)) {
            RubiksCube::MOVE m = move_done[current];
            moves.push_back(m);
            current.invert(m);
        }
        rubiksCube = solvedCube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
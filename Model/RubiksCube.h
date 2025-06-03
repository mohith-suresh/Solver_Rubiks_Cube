#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include <bits/stdc++.h>
using namespace std;

// Base class for different Rubik's Cube representations.
// Provides shared utilities; specific models implement details.
class RubiksCube {
public:
    enum class FACE {
        UP,
        LEFT,
        FRONT,
        RIGHT,
        BACK,
        DOWN
    };

    enum class COLOR {
        WHITE,
        GREEN,
        RED,
        BLUE,
        ORANGE,
        YELLOW
    };

    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };

    // Get the color at (row, col) on the specified face (0-indexed).
    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

    // Return the first letter of a COLOR (e.g., 'G' for GREEN).
    static char getColorLetter(COLOR color);

    // Check if the cube is solved.
    virtual bool isSolved() const = 0;

    // Convert a MOVE to its string (e.g., "U", "R'", "F2").
    static string getMove(MOVE move);

    // Display the cube in a flat net layout.
    void print() const;

    // Apply a series of random moves; returns the moves used.
    vector<MOVE> randomShuffleCube(unsigned int times);

    // Apply a single move.
    RubiksCube& move(MOVE move);

    // Apply the inverse of a move.
    RubiksCube& invert(MOVE move);

    // Face-turn methods; implemented by subclasses.
    virtual RubiksCube& f() = 0;
    virtual RubiksCube& fPrime() = 0;
    virtual RubiksCube& f2() = 0;
    virtual RubiksCube& u() = 0;
    virtual RubiksCube& uPrime() = 0;
    virtual RubiksCube& u2() = 0;
    virtual RubiksCube& l() = 0;
    virtual RubiksCube& lPrime() = 0;
    virtual RubiksCube& l2() = 0;
    virtual RubiksCube& r() = 0;
    virtual RubiksCube& rPrime() = 0;
    virtual RubiksCube& r2() = 0;
    virtual RubiksCube& d() = 0;
    virtual RubiksCube& dPrime() = 0;
    virtual RubiksCube& d2() = 0;
    virtual RubiksCube& b() = 0;
    virtual RubiksCube& bPrime() = 0;
    virtual RubiksCube& b2() = 0;

    // Corner utilities.
    string getCornerColorString(uint8_t index) const;
    uint8_t getCornerIndex(uint8_t index) const;
    uint8_t getCornerOrientation(uint8_t index) const;
};

#endif // RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
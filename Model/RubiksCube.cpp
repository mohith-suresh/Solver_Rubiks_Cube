// #include <iostream>
// using std::cout;
// using std::endl;

#include "RubiksCube.h"
#include <bits/stdc++.h>
using namespace std;

// Return the first letter of a color (e.g., 'G' for GREEN).
char RubiksCube::getColorLetter(COLOR color) {
    switch (color) {
        case COLOR::BLUE:   return 'B';
        case COLOR::GREEN:  return 'G';
        case COLOR::RED:    return 'R';
        case COLOR::YELLOW: return 'Y';
        case COLOR::WHITE:  return 'W';
        case COLOR::ORANGE: return 'O';
    }
}

// Convert a MOVE enum to its string representation.
string RubiksCube::getMove(MOVE ind) {
    switch (ind) {
        case MOVE::L:      return "L";
        case MOVE::LPRIME: return "L'";
        case MOVE::L2:     return "L2";
        case MOVE::R:      return "R";
        case MOVE::RPRIME: return "R'";
        case MOVE::R2:     return "R2";
        case MOVE::U:      return "U";
        case MOVE::UPRIME: return "U'";
        case MOVE::U2:     return "U2";
        case MOVE::D:      return "D";
        case MOVE::DPRIME: return "D'";
        case MOVE::D2:     return "D2";
        case MOVE::F:      return "F";
        case MOVE::FPRIME: return "F'";
        case MOVE::F2:     return "F2";
        case MOVE::B:      return "B";
        case MOVE::BPRIME: return "B'";
        case MOVE::B2:     return "B2";
    }
}

// Apply the given move to this cube.
RubiksCube& RubiksCube::move(MOVE ind) {
    switch (ind) {
        case MOVE::L:      return this->l();
        case MOVE::LPRIME: return this->lPrime();
        case MOVE::L2:     return this->l2();
        case MOVE::R:      return this->r();
        case MOVE::RPRIME: return this->rPrime();
        case MOVE::R2:     return this->r2();
        case MOVE::U:      return this->u();
        case MOVE::UPRIME: return this->uPrime();
        case MOVE::U2:     return this->u2();
        case MOVE::D:      return this->d();
        case MOVE::DPRIME: return this->dPrime();
        case MOVE::D2:     return this->d2();
        case MOVE::F:      return this->f();
        case MOVE::FPRIME: return this->fPrime();
        case MOVE::F2:     return this->f2();
        case MOVE::B:      return this->b();
        case MOVE::BPRIME: return this->bPrime();
        case MOVE::B2:     return this->b2();
    }
}

// Apply the inverse of a move.
RubiksCube& RubiksCube::invert(MOVE ind) {
    switch (ind) {
        case MOVE::L:      return this->lPrime();
        case MOVE::LPRIME: return this->l();
        case MOVE::L2:     return this->l2();
        case MOVE::R:      return this->rPrime();
        case MOVE::RPRIME: return this->r();
        case MOVE::R2:     return this->r2();
        case MOVE::U:      return this->uPrime();
        case MOVE::UPRIME: return this->u();
        case MOVE::U2:     return this->u2();
        case MOVE::D:      return this->dPrime();
        case MOVE::DPRIME: return this->d();
        case MOVE::D2:     return this->d2();
        case MOVE::F:      return this->fPrime();
        case MOVE::FPRIME: return this->f();
        case MOVE::F2:     return this->f2();
        case MOVE::B:      return this->bPrime();
        case MOVE::BPRIME: return this->b();
        case MOVE::B2:     return this->b2();
    }
}

// Display the cube in a flat net layout.
void RubiksCube::print() const {
    cout << "Rubik's Cube:\n\n";

    // Top face (U)
    for (int row = 0; row < 3; row++) {
        for (unsigned i = 0; i < 7; i++) cout << " ";
        for (int col = 0; col < 3; col++) {
            cout << getColorLetter(getColor(FACE::UP, row, col)) << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    // Middle faces (L, F, R, B)
    for (int row = 0; row < 3; row++) {
        // Left face
        for (int col = 0; col < 3; col++) {
            cout << getColorLetter(getColor(FACE::LEFT, row, col)) << " ";
        }
        cout << " ";
        // Front face
        for (int col = 0; col < 3; col++) {
            cout << getColorLetter(getColor(FACE::FRONT, row, col)) << " ";
        }
        cout << " ";
        // Right face
        for (int col = 0; col < 3; col++) {
            cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << " ";
        }
        cout << " ";
        // Back face
        for (int col = 0; col < 3; col++) {
            cout << getColorLetter(getColor(FACE::BACK, row, col)) << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    // Bottom face (D)
    for (int row = 0; row < 3; row++) {
        for (unsigned i = 0; i < 7; i++) cout << " ";
        for (int col = 0; col < 3; col++) {
            cout << getColorLetter(getColor(FACE::DOWN, row, col)) << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Shuffle the cube with a given number of random moves.
vector<RubiksCube::MOVE> RubiksCube::randomShuffleCube(unsigned int times) {
    vector<MOVE> moves_performed;
    srand(static_cast<unsigned>(time(nullptr)));
    for (unsigned int i = 0; i < times; i++) {
        unsigned int selectMove = rand() % 18;
        MOVE m = static_cast<MOVE>(selectMove);
        moves_performed.push_back(m);
        this->move(m);
    }
    return moves_performed;
}

// Return the colors of a corner cubie (in U-F-R, U-F-L, etc. order).
string RubiksCube::getCornerColorString(uint8_t ind) const {
    string str;

    switch (ind) {
        // U-F-R
        case 0:
            str += getColorLetter(getColor(FACE::UP, 2, 2));
            str += getColorLetter(getColor(FACE::FRONT, 0, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 0));
            break;
        // U-F-L
        case 1:
            str += getColorLetter(getColor(FACE::UP, 2, 0));
            str += getColorLetter(getColor(FACE::FRONT, 0, 0));
            str += getColorLetter(getColor(FACE::LEFT, 0, 2));
            break;
        // U-B-L
        case 2:
            str += getColorLetter(getColor(FACE::UP, 0, 0));
            str += getColorLetter(getColor(FACE::BACK, 0, 2));
            str += getColorLetter(getColor(FACE::LEFT, 0, 0));
            break;
        // U-B-R
        case 3:
            str += getColorLetter(getColor(FACE::UP, 0, 2));
            str += getColorLetter(getColor(FACE::BACK, 0, 0));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 2));
            break;
        // D-F-R
        case 4:
            str += getColorLetter(getColor(FACE::DOWN, 0, 2));
            str += getColorLetter(getColor(FACE::FRONT, 2, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 0));
            break;
        // D-F-L
        case 5:
            str += getColorLetter(getColor(FACE::DOWN, 0, 0));
            str += getColorLetter(getColor(FACE::FRONT, 2, 0));
            str += getColorLetter(getColor(FACE::LEFT, 2, 2));
            break;
        // D-B-R
        case 6:
            str += getColorLetter(getColor(FACE::DOWN, 2, 2));
            str += getColorLetter(getColor(FACE::BACK, 2, 0));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 2));
            break;
        // D-B-L
        case 7:
            str += getColorLetter(getColor(FACE::DOWN, 2, 0));
            str += getColorLetter(getColor(FACE::BACK, 2, 2));
            str += getColorLetter(getColor(FACE::LEFT, 2, 0));
            break;
    }
    return str;
}

// Compute an index for a corner based on its colors (encoded in 3 bits).
uint8_t RubiksCube::getCornerIndex(uint8_t ind) const {
    string corner = getCornerColorString(ind);
    uint8_t ret = 0;

    // Bit 2: Y vs W
    for (char c : corner) {
        if (c == 'Y') {
            ret |= (1 << 2);
            break;
        }
    }
    // Bit 1: O vs R
    for (char c : corner) {
        if (c == 'O') {
            ret |= (1 << 1);
            break;
        }
    }
    // Bit 0: G vs B
    for (char c : corner) {
        if (c == 'G') {
            ret |= (1 << 0);
            break;
        }
    }

    return ret;
}

// Compute orientation of a corner (0, 1, or 2) based on white/yellow position.
uint8_t RubiksCube::getCornerOrientation(uint8_t ind) const {
    string corner = getCornerColorString(ind);
    string whiteYellow;

    // Gather the white/yellow faces in order they appear
    for (char c : corner) {
        if (c == 'W' || c == 'Y') {
            whiteYellow.push_back(c);
        }
    }
    // If the U/D color is in middle position → orientation 1
    if (corner[1] == whiteYellow[0]) {
        return 1;
    }
    // If the U/D color is in last position → orientation 2
    if (corner[2] == whiteYellow[0]) {
        return 2;
    }
    // Otherwise orientation 0
    return 0;
}
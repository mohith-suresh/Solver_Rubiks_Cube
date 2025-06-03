#include "RubiksCube.h"

// 1D-array representation of a Rubik’s Cube
class RubiksCube1dArray : public RubiksCube {
private:
    // Convert (face, row, col) into a single index [0..53]
    static inline int getIndex(int face, int row, int col) {
        return face * 9 + row * 3 + col;
    }

    // Rotate one face (0..5) clockwise
    void rotateFace(int face) {
        char temp[9];
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                temp[r * 3 + c] = cube[getIndex(face, r, c)];

        for (int i = 0; i < 3; i++)
            cube[getIndex(face, 0, i)] = temp[getIndex(0, 2 - i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, i, 2)] = temp[getIndex(0, 0, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, 2, 2 - i)] = temp[getIndex(0, i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(face, 2 - i, 0)] = temp[getIndex(0, 2, 2 - i)];
    }

public:
    // Holds 54 stickers: face0[0..8], face1[9..17], …, face5[45..53]
    char cube[54];

    // Initialize each face to its color
    RubiksCube1dArray() {
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    cube[getIndex(f, r, c)] = getColorLetter(COLOR(f));
    }

    // Return the color at (face, row, col)
    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char ch = cube[getIndex((int)face, (int)row, (int)col)];
        switch (ch) {
            case 'B': return COLOR::BLUE;
            case 'R': return COLOR::RED;
            case 'G': return COLOR::GREEN;
            case 'O': return COLOR::ORANGE;
            case 'Y': return COLOR::YELLOW;
            default:  return COLOR::WHITE;
        }
    }

    // Check if every sticker matches its face’s color
    bool isSolved() const override {
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    if (cube[getIndex(f, r, c)] != getColorLetter(COLOR(f)))
                        return false;
        return true;
    }

    // U move: rotate up face and cycle top rows of side faces
    RubiksCube& u() override {
        rotateFace(0);
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(4, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(4, 0, 2 - i)] = cube[getIndex(1, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1, 0, 2 - i)] = cube[getIndex(2, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(2, 0, 2 - i)] = cube[getIndex(3, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3, 0, 2 - i)] = temp[i];
        return *this;
    }

    // U' is three U turns
    RubiksCube& uPrime() override {
        u(); u(); u();
        return *this;
    }

    // U2 is two U turns
    RubiksCube& u2() override {
        u(); u();
        return *this;
    }

    // L move: rotate left face and cycle its adjacent columns
    RubiksCube& l() override {
        rotateFace(1);
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(0, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(2, i, 0)] = temp[i];
        return *this;
    }

    RubiksCube& lPrime() override {
        l(); l(); l();
        return *this;
    }

    RubiksCube& l2() override {
        l(); l();
        return *this;
    }

    // F move: rotate front face and cycle its adjacent edges
    RubiksCube& f() override {
        rotateFace(2);
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(0, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(0, 2, i)] = cube[getIndex(1, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1, 2 - i, 2)] = cube[getIndex(5, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(5, 0, 2 - i)] = cube[getIndex(3, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3, i, 0)] = temp[i];
        return *this;
    }

    RubiksCube& fPrime() override {
        f(); f(); f();
        return *this;
    }

    RubiksCube& f2() override {
        f(); f();
        return *this;
    }

    // R move: rotate right face and cycle its adjacent edges
    RubiksCube& r() override {
        rotateFace(3);
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(0, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(0, 2 - i, 2)] = cube[getIndex(2, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(2, 2 - i, 2)] = cube[getIndex(5, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(5, 2 - i, 2)] = cube[getIndex(4, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(4, i, 0)] = temp[i];
        return *this;
    }

    RubiksCube& rPrime() override {
        r(); r(); r();
        return *this;
    }

    RubiksCube& r2() override {
        r(); r();
        return *this;
    }

    // B move: rotate back face and cycle its adjacent edges
    RubiksCube& b() override {
        rotateFace(4);
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(0, 0, 2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(0, 0, 2 - i)] = cube[getIndex(3, 2 - i, 2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3, 2 - i, 2)] = cube[getIndex(5, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1, i, 0)] = temp[i];
        return *this;
    }

    RubiksCube& bPrime() override {
        b(); b(); b();
        return *this;
    }

    RubiksCube& b2() override {
        b(); b();
        return *this;
    }

    // D move: rotate down face and cycle its adjacent edges
    RubiksCube& d() override {
        rotateFace(5);
        char temp[3];
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(2, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(2, 2, i)] = cube[getIndex(1, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1, 2, i)] = cube[getIndex(4, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(4, 2, i)] = cube[getIndex(3, 2, i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3, 2, i)] = temp[i];
        return *this;
    }

    RubiksCube& dPrime() override {
        d(); d(); d();
        return *this;
    }

    RubiksCube& d2() override {
        d(); d();
        return *this;
    }

    // Compare two 1D cubes
    bool operator==(const RubiksCube1dArray &other) const {
        for (int i = 0; i < 54; i++)
            if (cube[i] != other.cube[i])
                return false;
        return true;
    }

    // Copy assignment
    RubiksCube1dArray& operator=(const RubiksCube1dArray &other) {
        for (int i = 0; i < 54; i++)
            cube[i] = other.cube[i];
        return *this;
    }
};

// Hash functor for unordered_map keys
struct Hash1d {
    size_t operator()(const RubiksCube1dArray &c) const {
        string key;
        key.reserve(54);
        for (int i = 0; i < 54; i++)
            key.push_back(c.cube[i]);
        return hash<string>()(key);
    }
};
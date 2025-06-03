#include "RubiksCube.h"

// 3D-array implementation of a Rubik’s Cube
class RubiksCube3dArray : public RubiksCube {
private:
    // Rotate a single face (0–5) clockwise
    void rotateFace(int faceIndex) {
        char temp[3][3];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                temp[i][j] = cube[faceIndex][i][j];

        for (int i = 0; i < 3; i++) cube[faceIndex][0][i]       = temp[2 - i][0];
        for (int i = 0; i < 3; i++) cube[faceIndex][i][2]       = temp[0][i];
        for (int i = 0; i < 3; i++) cube[faceIndex][2][2 - i]   = temp[i][2];
        for (int i = 0; i < 3; i++) cube[faceIndex][2 - i][0]   = temp[2][2 - i];
    }

public:
    // cube[face][row][col] stores a char representing the color
    char cube[6][3][3];

    // Initialize each face with its own color
    RubiksCube3dArray() {
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    cube[f][r][c] = getColorLetter(COLOR(f));
    }

    // Return the color enum at (face, row, col)
    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char ch = cube[int(face)][row][col];
        switch (ch) {
            case 'B': return COLOR::BLUE;
            case 'R': return COLOR::RED;
            case 'G': return COLOR::GREEN;
            case 'O': return COLOR::ORANGE;
            case 'Y': return COLOR::YELLOW;
            default:  return COLOR::WHITE;
        }
    }

    // Check if every sticker matches its face color
    bool isSolved() const override {
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    if (cube[f][r][c] != getColorLetter(COLOR(f)))
                        return false;
        return true;
    }

    // U move: rotate Up face and cycle adjacent sides
    RubiksCube& u() override {
        rotateFace(0);
        char temp[3];
        // Save Back top row (face 4)
        for (int i = 0; i < 3; i++) temp[i] = cube[4][0][2 - i];
        // Back ← Left ← Front ← Right ← saved
        for (int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
        for (int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
        for (int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
        for (int i = 0; i < 3; i++) cube[3][0][2 - i] = temp[i];
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

    // L move: rotate Left face and cycle adjacent edges
    RubiksCube& l() override {
        rotateFace(1);
        char temp[3];
        for (int i = 0; i < 3; i++) temp[i] = cube[0][i][0];
        for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
        for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
        for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for (int i = 0; i < 3; i++) cube[2][i][0] = temp[i];
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

    // F move: rotate Front face and cycle adjacent edges
    RubiksCube& f() override {
        rotateFace(2);
        char temp[3];
        for (int i = 0; i < 3; i++) temp[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = temp[i];
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

    // R move: rotate Right face and cycle adjacent edges
    RubiksCube& r() override {
        rotateFace(3);
        char temp[3];
        for (int i = 0; i < 3; i++) temp[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = temp[i];
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

    // B move: rotate Back face and cycle adjacent edges
    RubiksCube& b() override {
        rotateFace(4);
        char temp[3];
        for (int i = 0; i < 3; i++) temp[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = temp[i];
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

    // D move: rotate Down face and cycle adjacent edges
    RubiksCube& d() override {
        rotateFace(5);
        char temp[3];
        for (int i = 0; i < 3; i++) temp[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = temp[i];
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

    // Compare two cubes for equality
    bool operator==(const RubiksCube3dArray &other) const {
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    if (cube[f][r][c] != other.cube[f][r][c])
                        return false;
        return true;
    }

    // Copy assignment copies all stickers
    RubiksCube3dArray& operator=(const RubiksCube3dArray &other) {
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    cube[f][r][c] = other.cube[f][r][c];
        return *this;
    }
};

// Hash functor for using RubiksCube3dArray as a key in unordered_map
struct Hash3d {
    size_t operator()(const RubiksCube3dArray &cube3d) const {
        string key;
        key.reserve(54);
        for (int f = 0; f < 6; f++)
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    key.push_back(cube3d.cube[f][r][c]);
        return hash<string>()(key);
    }
};
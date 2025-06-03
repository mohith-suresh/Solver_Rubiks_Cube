#include "RubiksCube.h"

// Bitboard representation of a Rubik’s Cube
class RubiksCubeBitboard : public RubiksCube {
private:
    uint64_t solved_side_config[6]{};
    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};
    uint64_t one_8 = (1 << 8) - 1, one_24 = (1 << 24) - 1;

    // Rotate a face’s 8 edge stickers
    void rotateFace(int face) {
        uint64_t side = bitboard[face];
        side = side >> (8 * 6);
        bitboard[face] = (bitboard[face] << 16) | side;
    }

    // Move three stickers from side s2 to side s1 at given indices
    void rotateSide(int s1, int s1_1, int s1_2, int s1_3,
                    int s2, int s2_1, int s2_2, int s2_3) {
        uint64_t clr1 = (bitboard[s2] & (one_8 << (8 * s2_1))) >> (8 * s2_1);
        uint64_t clr2 = (bitboard[s2] & (one_8 << (8 * s2_2))) >> (8 * s2_2);
        uint64_t clr3 = (bitboard[s2] & (one_8 << (8 * s2_3))) >> (8 * s2_3);

        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (clr1 << (8 * s1_1));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (clr2 << (8 * s1_2));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (clr3 << (8 * s1_3));
    }

    // Convert a 3-character corner string into a 5-bit code
    int get5bitCorner(const string &corner) {
        int code = 0;
        string whiteYellow;
        for (char c : corner) {
            if (c == 'W' || c == 'Y') {
                whiteYellow.push_back(c);
                if (c == 'Y') code |= (1 << 2);
            }
        }
        for (char c : corner) {
            if (c == 'O') code |= (1 << 1);
        }
        for (char c : corner) {
            if (c == 'G') code |= (1 << 0);
        }
        if (corner[1] == whiteYellow[0]) code |= (1 << 3);
        else if (corner[2] == whiteYellow[0]) code |= (1 << 4);
        return code;
    }

public:
    uint64_t bitboard[6]{};

    // Initialize each face’s 8 edges with its color bit
    RubiksCubeBitboard() {
        for (int side = 0; side < 6; side++) {
            uint64_t colorBit = 1ULL << side;
            bitboard[side] = 0;
            for (int idx = 0; idx < 8; idx++) {
                bitboard[side] |= colorBit << (8 * idx);
            }
            solved_side_config[side] = bitboard[side];
        }
    }

    // Return the color at (face, row, col)
    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        int idx = arr[row][col];
        if (idx == 8) return (COLOR)face;
        uint64_t side = bitboard[(int)face];
        uint64_t color = (side >> (8 * idx)) & one_8;
        int bitPos = 0;
        while (color) {
            color >>= 1;
            bitPos++;
        }
        return (COLOR)(bitPos - 1);
    }

    // Check if each face matches its solved configuration
    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != solved_side_config[i]) return false;
        }
        return true;
    }

    // U move: rotate top face and cycle the top three rows
    RubiksCube& u() override {
        rotateFace(0);
        uint64_t temp = bitboard[2] & one_24;
        bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24);
        bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24);
        bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24);
        bitboard[1] = (bitboard[1] & ~one_24) | temp;
        return *this;
    }

    RubiksCube& uPrime() override {
        u(); u(); u();
        return *this;
    }

    RubiksCube& u2() override {
        u(); u();
        return *this;
    }

    // L move: rotate left face and cycle its adjacent stickers
    RubiksCube& l() override {
        rotateFace(1);
        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);
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

    // F move: rotate front face and cycle its adjacent stickers
    RubiksCube& f() override {
        rotateFace(2);
        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);
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

    // R move: rotate right face and cycle its adjacent stickers
    RubiksCube& r() override {
        rotateFace(3);
        this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
        this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
        this->rotateSide(5, 2, 3, 4, 4, 7, 6, 0);
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

    // B move: rotate back face and cycle its adjacent stickers
    RubiksCube& b() override {
        rotateFace(4);
        this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
        this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);
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

    // D move: rotate down face and cycle its adjacent stickers
    RubiksCube& d() override {
        rotateFace(5);
        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);
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

    bool operator==(const RubiksCubeBitboard &other) const {
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != other.bitboard[i]) return false;
        }
        return true;
    }

    RubiksCubeBitboard& operator=(const RubiksCubeBitboard &other) {
        for (int i = 0; i < 6; i++) {
            bitboard[i] = other.bitboard[i];
        }
        return *this;
    }

    // Combine eight corners into a 40-bit value
    uint64_t getCorners() {
        auto getCornerStr = [&](FACE f1, int r1, int c1,
                                FACE f2, int r2, int c2,
                                FACE f3, int r3, int c3) {
            string s;
            s += getColorLetter(getColor(f1, r1, c1));
            s += getColorLetter(getColor(f2, r2, c2));
            s += getColorLetter(getColor(f3, r3, c3));
            return get5bitCorner(s);
        };

        uint64_t code = 0;
        code |= getCornerStr(FACE::UP,    2, 2, FACE::FRONT, 0, 2, FACE::RIGHT, 0, 0) << 35;
        code |= getCornerStr(FACE::UP,    2, 0, FACE::FRONT, 0, 0, FACE::LEFT,  0, 2) << 30;
        code |= getCornerStr(FACE::UP,    0, 2, FACE::BACK,  0, 0, FACE::RIGHT, 0, 2) << 25;
        code |= getCornerStr(FACE::UP,    0, 0, FACE::BACK,  0, 2, FACE::LEFT,  0, 0) << 20;
        code |= getCornerStr(FACE::DOWN,  0, 2, FACE::FRONT, 2, 2, FACE::RIGHT, 2, 0) << 15;
        code |= getCornerStr(FACE::DOWN,  0, 0, FACE::FRONT, 2, 0, FACE::LEFT,  2, 2) << 10;
        code |= getCornerStr(FACE::DOWN,  2, 2, FACE::BACK,  2, 0, FACE::RIGHT, 2, 2) << 5;
        code |= getCornerStr(FACE::DOWN,  2, 0, FACE::BACK,  2, 2, FACE::LEFT,  2, 0);

        return code;
    }
};

// Hash functor for bitboard cubes
struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard &c) const {
        uint64_t h = c.bitboard[0];
        for (int i = 1; i < 6; i++) h ^= c.bitboard[i];
        return (size_t)h;
    }
};
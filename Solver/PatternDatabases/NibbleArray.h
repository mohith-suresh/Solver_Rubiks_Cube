#ifndef RUBIKS_CUBE_SOLVER_NIBBLEARRAY_H
#define RUBIKS_CUBE_SOLVER_NIBBLEARRAY_H

#include <bits/stdc++.h>
using namespace std;

// Compact storage for 4-bit values
class NibbleArray {
    size_t size;             // number of nibbles
    vector<uint8_t> arr;     // two nibbles per byte

public:
    // Construct array of given size, filled with val
    NibbleArray(size_t size, uint8_t val = 0xFF);

    // Return the nibble value at position pos
    uint8_t get(size_t pos) const;

    // Set the nibble at position pos to val
    void set(size_t pos, uint8_t val);

    // Raw pointer to packed data
    unsigned char* data();
    const unsigned char* data() const;

    // Total storage in bytes
    size_t storageSize() const;

    // Expand all nibbles into dest vector
    void inflate(vector<uint8_t>& dest) const;

    // Reset every nibble to val
    void reset(uint8_t val = 0xFF);
};

#endif // RUBIKS_CUBE_SOLVER_NIBBLEARRAY_H
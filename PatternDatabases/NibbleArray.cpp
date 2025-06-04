#include "NibbleArray.h"

// Store 4-bit values packed into bytes (two nibbles per byte)
NibbleArray::NibbleArray(const size_t size, const uint8_t val)
    : size(size), arr(size / 2 + 1, val) {}

// Return the 4-bit value at position pos
uint8_t NibbleArray::get(const size_t pos) const {
    size_t i = pos / 2;
    assert(pos < this->size);
    uint8_t byte = arr.at(i);
    if (pos % 2) {
        return byte & 0x0F;          // low nibble
    } else {
        return byte >> 4;            // high nibble
    }
}

// Set the 4-bit value at position pos to val
void NibbleArray::set(const size_t pos, const uint8_t val) {
    size_t i = pos / 2;
    uint8_t byte = arr.at(i);
    assert(pos < this->size);
    if (pos % 2) {
        // Clear low nibble, then store val in low nibble
        arr.at(i) = (byte & 0xF0) | (val & 0x0F);
    } else {
        // Clear high nibble, then store val in high nibble
        arr.at(i) = (byte & 0x0F) | (val << 4);
    }
}

// Pointer to packed data
uint8_t* NibbleArray::data() {
    return arr.data();
}

const uint8_t* NibbleArray::data() const {
    return arr.data();
}

// Bytes needed to store all nibbles
size_t NibbleArray::storageSize() const {
    return arr.size();
}

// Expand each 4-bit value into dest vector (one byte per nibble)
void NibbleArray::inflate(vector<uint8_t>& dest) const {
    dest.reserve(this->size);
    for (size_t i = 0; i < this->size; ++i) {
        dest.push_back(get(i));
    }
}

// Fill all nibbles with val
void NibbleArray::reset(const uint8_t val) {
    fill(arr.begin(), arr.end(), val);
}
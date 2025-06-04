#include "PatternDatabase.h"
#include <fstream>

using namespace std;

PatternDatabase::PatternDatabase(const size_t size)
    : database(size, 0xFF), size(size), numItems(0) {
}

PatternDatabase::PatternDatabase(const size_t size, uint8_t init_val)
    : database(size, init_val), size(size), numItems(0) {
}

// Update entry at index if new move count is smaller.
// Returns true if updated; false otherwise.
bool PatternDatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves) {
    uint8_t oldMoves = this->getNumMoves(ind);

    // If this slot was unused, count it as a new entry
    if (oldMoves == 0xF) {
        ++this->numItems;
    }

    if (oldMoves > numMoves) {
        this->database.set(ind, numMoves);
        return true;
    }
    return false;
}

// Update entry based on cube configuration
bool PatternDatabase::setNumMoves(const RubiksCube &cube, const uint8_t numMoves) {
    return this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
}

// Get move count at index
uint8_t PatternDatabase::getNumMoves(const uint32_t ind) const {
    return this->database.get(ind);
}

// Get move count for given cube state
uint8_t PatternDatabase::getNumMoves(const RubiksCube &cube) const {
    return this->getNumMoves(this->getDatabaseIndex(cube));
}

size_t PatternDatabase::getSize() const {
    return this->size;
}

size_t PatternDatabase::getNumItems() const {
    return this->numItems;
}

// Check if database is fully populated
bool PatternDatabase::isFull() const {
    return this->numItems == this->size;
}

// Save raw database bytes to file
void PatternDatabase::toFile(const string &filePath) const {
    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);
    if (!writer.is_open())
        throw "Failed to open file for writing";

    writer.write(
        reinterpret_cast<const char*>(this->database.data()),
        this->database.storageSize()
    );
    writer.close();
}

// Load raw database bytes from file.
// Returns true on success, false if file can't be opened.
bool PatternDatabase::fromFile(const string &filePath) {
    ifstream reader(filePath, ios::in | ios::ate);
    if (!reader.is_open())
        return false;

    size_t fileSize = reader.tellg();
    if (fileSize != this->database.storageSize()) {
        reader.close();
        throw "Database corrupt or size mismatch";
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char*>(this->database.data()),
        this->database.storageSize()
    );
    reader.close();
    this->numItems = this->size;
    return true;
}

// Return a vector of decompressed byte values
vector<uint8_t> PatternDatabase::inflate() const {
    vector<uint8_t> inflated;
    this->database.inflate(inflated);
    return inflated;
}

// Reset all entries to unused (0xFF) and zero out count
void PatternDatabase::reset() {
    if (this->numItems != 0) {
        this->database.reset(0xFF);
        this->numItems = 0;
    }
}
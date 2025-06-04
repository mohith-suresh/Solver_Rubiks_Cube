#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

#include "../Model/RubiksCube.h"
#include "NibbleArray.h"
#include <vector>
#include <string>

// Abstract base for a pattern database used by the Rubik's Cube solver
class PatternDatabase {
    NibbleArray database;
    size_t size;
    size_t numItems;

    PatternDatabase();

public:
    // Initialize database with given size
    PatternDatabase(size_t size);

    // Initialize database with a default value
    PatternDatabase(size_t size, uint8_t initVal);

    // Derive a unique index from the cube state
    virtual uint32_t getDatabaseIndex(const RubiksCube &cube) const = 0;

    // Store the minimum moves for a given cube configuration
    virtual bool setNumMoves(const RubiksCube &cube, uint8_t numMoves);

    // Store the minimum moves using a raw index
    virtual bool setNumMoves(uint32_t index, uint8_t numMoves);

    // Retrieve stored move count for a cube state
    virtual uint8_t getNumMoves(const RubiksCube &cube) const;

    // Retrieve stored move count by index
    virtual uint8_t getNumMoves(uint32_t index) const;

    // Total number of entries (capacity)
    virtual size_t getSize() const;

    // Number of entries filled so far
    virtual size_t getNumItems() const;

    // Check if the database is completely filled
    virtual bool isFull() const;

    // Write database to a file
    virtual void toFile(const std::string &filePath) const;

    // Load database from a file
    virtual bool fromFile(const std::string &filePath);

    // Expand compressed data into a raw byte vector
    virtual std::vector<uint8_t> inflate() const;

    // Clear all stored entries
    virtual void reset();
};

#endif // RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
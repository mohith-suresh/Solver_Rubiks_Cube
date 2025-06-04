#ifndef RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H
#define RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H

#include <bits/stdc++.h>
#include <cmath>
using namespace std;

template <size_t N, size_t K = N>
class PermutationIndexer
{
    // Number of 1-bits for each number up to (1<<N)-1
    array<uint32_t, (1 << N) - 1> onesCountLookup;

    // Factorials or "n choose k" values, reversed
    array<uint32_t, K> factorials;

public:
    // Build lookup tables for bit counts and factorials/picks
    PermutationIndexer()
    {
        for (uint32_t i = 0; i < (1 << N) - 1; ++i) {
            onesCountLookup[i] = bitset<N>(i).count();
        }
        for (uint32_t i = 0; i < K; ++i) {
            factorials[i] = pick(N - 1 - i, K - 1 - i);
        }
    }

    // Compute lexicographic index of a K-length permutation over N items
    uint32_t rank(const array<uint8_t, K>& perm) const
    {
        array<uint32_t, K> lehmer{};  // Lehmer code
        bitset<N> seen;               // Tracks which numbers have appeared

        // First Lehmer digit is the value itself
        lehmer[0] = perm[0];
        seen.set(N - 1 - perm[0]);

        for (uint32_t i = 1; i < K; ++i) {
            seen.set(N - 1 - perm[i]);
            // Count how many smaller values have already been seen
            uint32_t mask = seen.to_ulong() >> (N - perm[i]);
            uint32_t numSeenLeft = onesCountLookup[mask];
            lehmer[i] = perm[i] - numSeenLeft;
        }

        // Convert Lehmer code to a single index
        uint32_t index = 0;
        for (uint32_t i = 0; i < K; ++i) {
            index += lehmer[i] * factorials[i];
        }
        return index;
    }
};

#endif // RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H
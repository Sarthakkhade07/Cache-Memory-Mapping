#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS_PER_SET 10
#define MAX_SETS 100
#define MAX_ADDRESSES 1000

typedef struct {
    int tags[MAX_BLOCKS_PER_SET];   // Tags in the set
    int front, rear, size;          // For FIFO queue
} CacheSet;

void insertFIFO(CacheSet *set, int tag, int associativity) {
    // FIFO Eviction if full
    if (set->size == associativity) {
        // Shift all tags to the left (evict oldest)
        for (int i = 1; i < associativity; i++) {
            set->tags[i - 1] = set->tags[i];
        }
        set->tags[associativity - 1] = tag;
    } else {
        set->tags[set->size++] = tag;
    }
}

int isHit(CacheSet *set, int tag, int associativity) {
    for (int i = 0; i < set->size; i++) {
        if (set->tags[i] == tag)
            return 1;
    }
    return 0;
}

int main() {
    int cacheSize, blockSize, memorySize, associativity;
    printf("Enter cache size (in bytes): ");
    scanf("%d", &cacheSize);

    printf("Enter block size (in bytes): ");
    scanf("%d", &blockSize);

    printf("Enter main memory size (in bytes): ");
    scanf("%d", &memorySize);

    printf("Enter associativity (e.g., 2 for 2-way): ");
    scanf("%d", &associativity);

    int numLines = cacheSize / blockSize;
    int numSets = numLines / associativity;

    CacheSet cache[MAX_SETS] = {0}; // Initialize all sets

    int numAddresses;
    printf("Enter number of memory accesses: ");
    scanf("%d", &numAddresses);

    int addresses[MAX_ADDRESSES];
    printf("Enter memory addresses (space-separated): ");
    for (int i = 0; i < numAddresses; i++) {
        scanf("%d", &addresses[i]);
    }

    int hits = 0, misses = 0;

    for (int i = 0; i < numAddresses; i++) {
        int addr = addresses[i];
        int blockNumber = addr / blockSize;
        int setIndex = blockNumber % numSets;
        int tag = blockNumber / numSets;

        printf("Address %d => ", addr);

        if (isHit(&cache[setIndex], tag, associativity)) {
            printf("Hit\n");
            hits++;
        } else {
            printf("Miss => ");
            if (cache[setIndex].size < associativity) {
                printf("Inserted tag %d into set %d\n", tag, setIndex);
            } else {
                printf("Evicted tag %d from set %d, inserted tag %d\n",
                       cache[setIndex].tags[0], setIndex, tag);
            }
            insertFIFO(&cache[setIndex], tag, associativity);
            misses++;
        }
    }

    printf("\nTotal Accesses: %d\n", numAddresses);
    printf("Hits: %d, Misses: %d\n", hits, misses);
    printf("Hit Rate: %.2f%%\n", (hits * 100.0) / numAddresses);

    return 0;
}

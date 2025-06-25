#include <stdio.h>
#include <stdlib.h>

#define MAX_CACHE_LINES 1000
#define MAX_ADDRESSES 1000

int cache[MAX_CACHE_LINES];  // Store tags
int size = 0;                // Current number of blocks in cache

// FIFO: Evict oldest tag and insert new one
void insertFIFO(int tag, int cacheSize) {
    if (size < cacheSize) {
        cache[size++] = tag;
    } else {
        // Shift all to the left (evict oldest)
        for (int i = 1; i < cacheSize; i++) {
            cache[i - 1] = cache[i];
        }
        cache[cacheSize - 1] = tag;
    }
}

int isHit(int tag, int cacheSize) {
    for (int i = 0; i < size; i++) {
        if (cache[i] == tag)
            return 1;
    }
    return 0;
}

int main() {
    int cacheSize, blockSize, memorySize;
    printf("Enter cache size (in bytes): ");
    scanf("%d", &cacheSize);

    printf("Enter block size (in bytes): ");
    scanf("%d", &blockSize);

    printf("Enter main memory size (in bytes): ");
    scanf("%d", &memorySize);

    int numLines = cacheSize / blockSize;

    // Initialize cache with -1
    for (int i = 0; i < numLines; i++)
        cache[i] = -1;

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
        int tag = blockNumber; // tag = blockNumber since no index

        printf("Address %d => ", addr);

        if (isHit(tag, numLines)) {
            printf("Hit\n");
            hits++;
        } else {
            printf("Miss => ");
            if (size < numLines) {
                printf("Inserted tag %d into cache\n", tag);
            } else {
                printf("Evicted tag %d, inserted tag %d\n", cache[0], tag);
            }
            insertFIFO(tag, numLines);
            misses++;
        }
    }

    printf("\nTotal Accesses: %d\n", numAddresses);
    printf("Hits: %d, Misses: %d\n", hits, misses);
    printf("Hit Rate: %.2f%%\n", (hits * 100.0) / numAddresses);

    return 0;
}

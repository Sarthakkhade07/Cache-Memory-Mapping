#include <stdio.h>
#include <stdlib.h>

#define MAX_CACHE_LINES 1000
#define MAX_ADDRESSES 1000

int main() {
    int cacheSize, blockSize, memorySize;
    printf("Enter cache size (in bytes): ");
    scanf("%d", &cacheSize);

    printf("Enter block size (in bytes): ");
    scanf("%d", &blockSize);

    printf("Enter main memory size (in bytes): ");
    scanf("%d", &memorySize);

    int numLines = cacheSize / blockSize;
    int cache[MAX_CACHE_LINES];

    // Initialize all cache lines as invalid (-1)
    for (int i = 0; i < numLines; i++) {
        cache[i] = -1;
    }

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
        int index = blockNumber % numLines;
        int tag = blockNumber / numLines;

        printf("Address %d => ", addr);

        if (cache[index] == tag) {
            printf("Hit\n");
            hits++;
        } else {
            printf("Miss => ");
            if (cache[index] == -1) {
                printf("Inserted tag %d into line %d\n", tag, index);
            } else {
                printf("Replaced tag %d with tag %d in line %d\n", cache[index], tag, index);
            }
            cache[index] = tag;
            misses++;
        }
    }

    printf("\nTotal Accesses: %d\n", numAddresses);
    printf("Hits: %d, Misses: %d\n", hits, misses);
    printf("Hit Rate: %.2f%%\n", (hits * 100.0) / numAddresses);

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

#define MAX_BLOCKS_PER_SET 10
#define MAX_SETS 100
#define MAX_ADDRESSES 1000

struct CacheSet {
    vector<int> tags;   
    int size;          

    CacheSet() : size(0) {}
};

void insertFIFO(CacheSet &set, int tag, int associativity) {
    if (set.size == associativity) {
        for (int i = 1; i < associativity; i++) {
            set.tags[i - 1] = set.tags[i];
        }
        set.tags[associativity - 1] = tag;
    } else {
        set.tags[set.size++] = tag;
    }
}

bool isHit(const CacheSet &set, int tag) {
    for (int i = 0; i < set.size; i++) {
        if (set.tags[i] == tag)
            return true;
    }
    return false;
}

int main() {
    int cacheSize, blockSize, memorySize, associativity;

    cout << "Enter cache size (in bytes): ";
    cin >> cacheSize;

    cout << "Enter block size (in bytes): ";
    cin >> blockSize;

    cout << "Enter main memory size (in bytes): ";
    cin >> memorySize;

    cout << "Enter associativity (e.g., 2 for 2-way): ";
    cin >> associativity;

    int numLines = cacheSize / blockSize;
    int numSets = numLines / associativity;

    vector<CacheSet> cache(numSets);
    for (int i = 0; i < numSets; i++) {
        cache[i].tags.resize(associativity, -1);
    }

    int numAddresses;
    cout << "Enter number of memory accesses: ";
    cin >> numAddresses;

    vector<int> addresses(numAddresses);
    cout << "Enter memory addresses (space-separated): ";
    for (int i = 0; i < numAddresses; i++) {
        cin >> addresses[i];
    }

    int hits = 0, misses = 0;

    for (int i = 0; i < numAddresses; i++) {
        int addr = addresses[i];
        int blockNumber = addr / blockSize;
        int setIndex = blockNumber % numSets;
        int tag = blockNumber / numSets;

        cout << "Address " << addr << " => ";

        if (isHit(cache[setIndex], tag)) {
            cout << "Hit" << endl;
            hits++;
        } else {
            cout << "Miss => ";
            if (cache[setIndex].size < associativity) {
                cout << "Inserted tag " << tag
                     << " into set " << setIndex << endl;
            } else {
                cout << "Evicted tag " << cache[setIndex].tags[0]
                     << " from set " << setIndex
                     << ", inserted tag " << tag << endl;
            }
            insertFIFO(cache[setIndex], tag, associativity);
            misses++;
        }
    }

    cout << "\nTotal Accesses: " << numAddresses << endl;
    cout << "Hits: " << hits << ", Misses: " << misses << endl;
    cout << "Hit Rate: "
         << (hits * 100.0 / numAddresses) << "%" << endl;

    return 0;
}

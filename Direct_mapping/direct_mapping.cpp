#include <iostream>
#include <vector>
using namespace std;

#define MAX_CACHE_LINES 1000
#define MAX_ADDRESSES 1000

int main() {
    int cacheSize, blockSize, memorySize;

    cout << "Enter cache size (in bytes): ";
    cin >> cacheSize;

    cout << "Enter block size (in bytes): ";
    cin >> blockSize;

    cout << "Enter main memory size (in bytes): ";
    cin >> memorySize;

    int numLines = cacheSize / blockSize;

    // Cache array initialized with -1 (invalid)
    vector<int> cache(numLines, -1);

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
        int index = blockNumber % numLines;
        int tag = blockNumber / numLines;

        cout << "Address " << addr << " => ";

        if (cache[index] == tag) {
            cout << "Hit" << endl;
            hits++;
        } else {
            cout << "Miss => ";
            if (cache[index] == -1) {
                cout << "Inserted tag " << tag
                     << " into line " << index << endl;
            } else {
                cout << "Replaced tag " << cache[index]
                     << " with tag " << tag
                     << " in line " << index << endl;
            }
            cache[index] = tag;
            misses++;
        }
    }

    cout << "\nTotal Accesses: " << numAddresses << endl;
    cout << "Hits: " << hits << ", Misses: " << misses << endl;
    cout << "Hit Rate: "
         << (hits * 100.0 / numAddresses) << "%" << endl;

    return 0;
}

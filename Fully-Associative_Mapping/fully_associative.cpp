#include <iostream>
#include <vector>
using namespace std;

#define MAX_CACHE_LINES 1000
#define MAX_ADDRESSES 1000

vector<int> cache;   
int size = 0;        

void insertFIFO(int tag, int cacheSize) {
    if (size < cacheSize) {
        cache[size++] = tag;
    } else {
     
        for (int i = 1; i < cacheSize; i++) {
            cache[i - 1] = cache[i];
        }
        cache[cacheSize - 1] = tag;
    }
}

bool isHit(int tag) {
    for (int i = 0; i < size; i++) {
        if (cache[i] == tag)
            return true;
    }
    return false;
}

int main() {
    int cacheSize, blockSize, memorySize;

    cout << "Enter cache size (in bytes): ";
    cin >> cacheSize;

    cout << "Enter block size (in bytes): ";
    cin >> blockSize;

    cout << "Enter main memory size (in bytes): ";
    cin >> memorySize;

    int numLines = cacheSize / blockSize;

    cache.resize(numLines, -1);

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
        int tag = blockNumber; 
        cout << "Address " << addr << " => ";

        if (isHit(tag)) {
            cout << "Hit" << endl;
            hits++;
        } else {
            cout << "Miss => ";
            if (size < numLines) {
                cout << "Inserted tag " << tag << " into cache" << endl;
            } else {
                cout << "Evicted tag " << cache[0]
                     << ", inserted tag " << tag << endl;
            }
            insertFIFO(tag, numLines);
            misses++;
        }
    }

    cout << "\nTotal Accesses: " << numAddresses << endl;
    cout << "Hits: " << hits << ", Misses: " << misses << endl;
    cout << "Hit Rate: "
         << (hits * 100.0 / numAddresses) << "%" << endl;

    return 0;
}

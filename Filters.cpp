#include <iostream>
#include <vector>
#include <limits.h>  // For using INT_MAX in Count-Min Sketch
using namespace std;

const int bloomSize = 10;  // Size of the Bloom Filter array
int bfilter[bloomSize] = {0};  // Initialize Bloom Filter array with all values as 0

// First hash function for Bloom Filter
int h1(string s, int n) {
    int hash = 0;  // Initialize hash to 0
    for (int i = 0; i < s.length(); i++) {
        hash = (hash + int(s[i])) % n;  // Add ASCII value of each character, take modulo n
    }
    return hash;  // Return final hash value
}

// Second hash function for Bloom Filter
int h2(string s, int n) {
    int hash = 1;  // Start with hash = 1
    for (int i = 0; i < s.length(); i++) {
        hash = (hash + int(s[i])) % n;  // Add ASCII values and take modulo n
    }
    return hash;  // Return final hash value
}

// Third hash function for Bloom Filter
int h3(string s, int n) {
    int hash = 2;  // Start with hash = 2
    for (int i = 0; i < s.length(); i++) {
        hash = (hash + int(s[i])) % n;  // Add ASCII values and take modulo n
    }
    return hash;  // Return final hash value
}

// Print Bloom Filter array
void printBloomFilter() {
    cout << "Bloom Filter: ";
    for (int i = 0; i < bloomSize; i++) {
        cout << bfilter[i] << " ";
    }
    cout << endl;
}

// Insert element into Bloom Filter
void insertBloomFilter(string name) {
    int a = h1(name, bloomSize);  // Calculate first hash index
    int b = h2(name, bloomSize);  // Calculate second hash index
    int c = h3(name, bloomSize);  // Calculate third hash index

    // If all three positions already contain 1, element may already be present
    if (bfilter[a] == 1 && bfilter[b] == 1 && bfilter[c] == 1) {
        cout << "Element already exists" << endl;  // Probable duplicate
    } else {
        // Otherwise, insert the element by setting all three positions to 1
        bfilter[a] = 1;
        bfilter[b] = 1;
        bfilter[c] = 1;
        cout << "Element inserted" << endl;
    }
    printBloomFilter();  // Display Bloom Filter after insertion
}

int cfilter1[10];  // First table for Cuckoo Filter
int cfilter2[10];  // Second table for Cuckoo Filter
int cuckooSize = 10;  // Size of each table

// First hash function for Cuckoo Filter
int hash1(int num, int n) {
    return num % n;  // Simple modulo hash
}

// Second hash function for Cuckoo Filter
int hash2(int num, int n) {
    return (num / n) % n;  // A different style of hash function
}

// Print contents of both Cuckoo tables
void printhash() {
    for (int i = 0; i < cuckooSize; i++) {
        cout << cfilter1[i] << " ";  // Print values from table 1
    }
    cout << endl;
    for (int i = 0; i < cuckooSize; i++) {
        cout << cfilter2[i] << " ";  // Print values from table 2
    }
    cout << endl;
}

// Insert value into Cuckoo Filter
void insertCuckooFilter(int num) {
    int a = hash1(num, cuckooSize);  // Get index using first hash function

    if (cfilter1[a] == -1) {  // If slot in first table is empty
        cfilter1[a] = num;  // Insert number
    } else {
        int temp = cfilter1[a];  // Store existing value to relocate
        cfilter1[a] = num;  // Replace with new value

        int b = hash2(temp, cuckooSize);  // Get index in second table for displaced value
        if (cfilter2[b] == -1) {  // If second slot is empty
            cfilter2[b] = temp;  // Place displaced value
        } else {
            insertCuckooFilter(temp);  // Recurse for displaced value (may cause rehash in real implementation)
        }
    }
}

const int d = 4;  // Number of hash functions (rows)
const int w = 10000;  // Width of each row (number of counters per hash function)

// 2D vector for Count-Min Sketch initialized with 0s
vector<vector<int>> countMinSketch(d, vector<int>(w, 0));

// Hash function for Count-Min Sketch, different per row
int hashCMS(string s, int i) {
    int hash = 0;
    int a = 33 + 17 * i;  // Make it different per row
    for (char c : s) {
        hash = (a * hash + c) % w;  // Simple polynomial rolling hash
    }
    return (hash + w) % w;  // Ensure non-negative
}

// Insert an element into Count-Min Sketch
void insertCountMinSketch(string name) {
    cout << "Hash Indices for '" << name << "': ";
    for (int i = 0; i < d; i++) {
        int hash = hashCMS(name, i);  // Compute hash for each row
        countMinSketch[i][hash]++;  // Increment the count at hashed index
        cout << hash << " ";  // Print the actual indices being incremented
    }
    cout << endl;
    cout << "Element Inserted" << endl;

    // Now print counts at those specific indices instead of just first 10 columns
    for (int i = 0; i < d; i++) {
        int hash = hashCMS(name, i);
        cout << "Row " << i + 1 << " [" << hash << "]: " << countMinSketch[i][hash] << endl;
    }
}

// Estimate frequency of an element in Count-Min Sketch
int estimatedCountMinSketch(string name) {
    int minCount = INT_MAX;  // Start with maximum possible value
    for (int i = 0; i < d; i++) {
        int hash = hashCMS(name, i);  // Get hash for each row
        minCount = min(minCount, countMinSketch[i][hash]);  // Find minimum count
    }
    return minCount;  // Return estimated frequency
}


int main() {
    // Initialize cuckoo filter arrays with -1 to indicate empty slots
    for (int i = 0; i < cuckooSize; i++) {
        cfilter1[i] = -1;
        cfilter2[i] = -1;
    }

    int opt;

    do {
        cout << "1. Bloom Filter" << endl;
        cout << "2. Cuckoo Filter" << endl;
        cout << "3. Count-Min Sketch Filter" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> opt;

        switch (opt) {
        case 1: {
            string name;
            cout << "Enter the name to be inserted: ";
            cin >> name;
            insertBloomFilter(name);  // Call Bloom filter insertion
            break;
        }
        case 2: {
            int num;
            cout << "Enter the number to be inserted: ";
            cin >> num;
            insertCuckooFilter(num);  // Call Cuckoo filter insertion
            printhash();  // Print hash tables
            break;
        }
        case 3: {
            string name;
            cout << "Enter the name to be inserted: ";
            cin >> name;
            insertCountMinSketch(name);  // Insert into Count-Min Sketch
            int estFreq = estimatedCountMinSketch(name);  // Estimate frequency
            cout << "Estimated frequency of " << name << ": " << estFreq << endl;
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
        }

    } while (opt != 4);

    return 0;
}

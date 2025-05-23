#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// NOTE: Using this code to recover Test B must have longer lines than Test A
// NOTE: Both test A and Test B must have the same number of lines

string calc_Parity(string& word, string& word1) {
    size_t size = max(word.size(), word1.size());
    string parity;

    // Pad the words to make them equal in size
    string paddedWord = word + string(size - word.size(), 0);
    string paddedWord1 = word1 + string(size - word1.size(), 0);

    // Calculate parity
    for (size_t i = 0; i < size; i++) {
        parity += (paddedWord[i] ^ paddedWord1[i]);
    }
    return parity;
}

int main() {
    // Update paths to match specified locations
    ifstream fileA("/mnt/nfs/data_vm1/a3", ios::binary);
    ifstream fileB("/mnt/nfs/data_vm3/b3", ios::binary);
    if (!fileA.is_open() || !fileB.is_open()) {
        cerr << "Error opening the input files" << endl;
        return 1;
    }

    ofstream fileC("/srv/nfs/data/c3", ios::binary);
    if (!fileC.is_open()) {
        cerr << "Error creating the output file" << endl;
        return 1;
    }

    string lineA, lineB;

    while (true) {
        // Read lines from the input files
        bool hasLineA = static_cast<bool>(getline(fileA, lineA));
        bool hasLineB = static_cast<bool>(getline(fileB, lineB));

        // Exit loop if both files have no more lines
        if (!hasLineA && !hasLineB)
            break;

        cout << "line a: " << lineA << " line b: " << lineB << '\n';

        // Calculate parity and write to output file
        string parityWord = calc_Parity(lineA, lineB);
        fileC << parityWord << '\n';
    }

    // Close all files
    fileA.close();
    fileB.close();
    fileC.close();

    return 0;
}


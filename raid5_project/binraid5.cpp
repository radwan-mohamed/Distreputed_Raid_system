#include <iostream>
#include <fstream>
#include <vector>

// Write data to a file
bool writeToFile(const std::string& filename, const std::vector<char>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }
    file.write(data.data(), data.size());
    file.close();
    return true;
}

// Read data from a file
bool readFromFile(const std::string& filename, std::vector<char>& data) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    data.resize(fileSize);
    file.read(data.data(), fileSize);
    file.close();
    return true;
}

std::vector<char> calculateParity(const std::vector<char>& data1, const std::vector<char>& data2) {
    size_t size = std::min(data1.size(), data2.size());
    std::vector<char> parity(size);

    for (size_t i = 0; i < size; ++i) {
        parity[i] = data1[i] ^ data2[i];
    }
    return parity;
}

std::vector<char> recoverData(const std::vector<char>& data1, const std::vector<char>& parity) {
    size_t size = std::min(data1.size(), parity.size());
    std::vector<char> recoveredData(size);

    for (size_t i = 0; i < size; ++i) {
        recoveredData[i] = data1[i] ^ parity[i];  // Recover the missing data
    }
    return recoveredData;
}

int main() {
    // Original data
    std::vector<char> data1 = {'A', 'B', 'C', 'D', 'E'};
    std::vector<char> data2 = {'1', '2', '3', '4', '5'};

    // Write data to the first two files
    if (writeToFile("dataFile1.bin", data1)) {
        std::cout << "Data written to dataFile1.bin" << std::endl;
    }
    if (writeToFile("dataFile2.bin", data2)) {
        std::cout << "Data written to dataFile2.bin" << std::endl;
    }

    // Calculate the parity
    std::vector<char> parity = calculateParity(data1, data2);
    
    // Write parity to the parity file
    if (writeToFile("parityFile.bin", parity)) {
        std::cout << "Parity written to parityFile.bin" << std::endl;
    }

    // Simulate failure: remove or ignore dataFile2
    // You can delete the file manually or simulate the failure in code.
    std::remove("dataFile2.bin");

    // Read the remaining data
    std::vector<char> recoveredData;
    if (readFromFile("dataFile1.bin", data1) && readFromFile("parityFile.bin", parity)) {
        // Recover the lost data (dataFile2)
        recoveredData = recoverData(data1, parity);
        std::cout << "Recovered data: ";
        for (char c : recoveredData) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

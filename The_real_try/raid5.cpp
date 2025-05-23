#include <iostream>
#include <fstream>
#include <string>

// Write data to a text file
bool writeToFile(const std::string& filename, const std::string& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }
    file << data;
    file.close();
    return true;
}

// Read data from a text file
bool readFromFile(const std::string& filename, std::string& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }
    std::getline(file, data, '\0');  // Read until EOF (null terminator)
    file.close();
    return true;
}

// Calculate parity by XOR-ing ASCII values of corresponding characters
std::string calculateParity(const std::string& data1, const std::string& data2) {
    size_t size = std::min(data1.size(), data2.size());
    std::string parity(size, '\0');

    for (size_t i = 0; i < size; ++i) {
        parity[i] = data1[i] ^ data2[i];  // XOR the ASCII values
    }
    return parity;
}

// Recover the missing data using XOR with the parity
std::string recoverData(const std::string& data1, const std::string& parity) {
    size_t size = std::min(data1.size(), parity.size());
    std::string recoveredData(size, '\0');

    for (size_t i = 0; i < size; ++i) {
        recoveredData[i] = data1[i] ^ parity[i];  // XOR to recover missing data
    }
    return recoveredData;
}

int main() {
    // Original data as strings (for simulation)
    std::string data1, data2, parity, recoveredData;

    // Read data from the text files
    if (readFromFile("data_device_1.txt", data1)) {
        std::cout << "Data read from data_device_1.txt: " << data1 << std::endl;
    }
    if (readFromFile("data_device_2.txt", data2)) {
        std::cout << "Data read from data_device_2.txt: " << data2 << std::endl;
    }

    // Calculate the parity
    parity = calculateParity(data1, data2);
    std::cout << "Parity calculated: " << parity << std::endl;

    // Simulate failure: remove or ignore data_device_2.txt
    std::remove("data_device_2.txt");

    // Recover the lost data (using data_device_1.txt and parity_device.txt)
    recoveredData = recoverData(data1, parity);
    std::cout << "Recovered data: " << recoveredData << std::endl;

    return 0;
}

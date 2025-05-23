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
    std::string data1 = "ABCDE";
    std::string data2 = "12345";

    // Write data to the first two text files
    if (writeToFile("data_device_1.txt", data1)) {
        std::cout << "Data written to data_device_1.txt" << std::endl;
    }
    if (writeToFile("data_device_2.txt", data2)) {
        std::cout << "Data written to data_device_2.txt" << std::endl;
    }

    // Calculate the parity
    std::string parity = calculateParity(data1, data2);
    
    // Write parity to the parity file
    if (writeToFile("parity_device.txt", parity)) {
        std::cout << "Parity written to parity_device.txt" << std::endl;
    }

    // Simulate failure: remove or ignore data_device_2.txt
    std::remove("data_device_2.txt");

    // Read the remaining data
    std::string recoveredData;
    if (readFromFile("data_device_1.txt", data1) && readFromFile("parity_device.txt", parity)) {
        // Recover the lost data (data_device_2.txt)
        recoveredData = recoverData(data1, parity);
        std::cout << "Recovered data: " << recoveredData << std::endl;
    }

    return 0;
}










// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <cstring>


// constexpr int SECTOR_SIZE = 512;


// bool read_from_data_device_1(int sectorIndex, std::byte* buffer) {
//     std::ifstream file("data_device_1.txt", std::ios::binary);
//     if (!file.is_open()) return false;
    
//     file.seekg(sectorIndex * SECTOR_SIZE);
//     file.read(reinterpret_cast<char*>(buffer), SECTOR_SIZE);
//     return file.gcount() == SECTOR_SIZE;
// }

// bool write_to_data_device_1(int sectorIndex, const std::byte* data) {
//     std::ofstream file("data_device_1.txt", std::ios::binary | std::ios::in | std::ios::out);
//     if (!file.is_open()) return false;
    
//     file.seekp(sectorIndex * SECTOR_SIZE);
//     file.write(reinterpret_cast<const char*>(data), SECTOR_SIZE);
//     return true;
// }


// bool read_from_data_device_2(int sectorIndex, std::byte* buffer) {
//     std::ifstream file("data_device_2.txt", std::ios::binary);
//     if (!file.is_open()) return false;
    
//     file.seekg(sectorIndex * SECTOR_SIZE);
//     file.read(reinterpret_cast<char*>(buffer), SECTOR_SIZE);
//     return file.gcount() == SECTOR_SIZE;
// }

// bool write_to_data_device_2(int sectorIndex, const std::byte* data) {
//     std::ofstream file("data_device_2.txt", std::ios::binary | std::ios::in | std::ios::out);
//     if (!file.is_open()) return false;
    
//     file.seekp(sectorIndex * SECTOR_SIZE);
//     file.write(reinterpret_cast<const char*>(data), SECTOR_SIZE);
//     return true;
// }




// bool read_from_parity_device(int sectorIndex, std::byte* buffer) {
//     std::ifstream file("parity_device.txt", std::ios::binary);
//     if (!file.is_open()) return false;
    
//     file.seekg(sectorIndex * SECTOR_SIZE);
//     file.read(reinterpret_cast<char*>(buffer), SECTOR_SIZE);
//     return file.gcount() == SECTOR_SIZE;
// }

// bool write_to_parity_device(int sectorIndex, const std::byte* data) {
//     std::ofstream file("parity_device.txt", std::ios::binary | std::ios::in | std::ios::out);
//     if (!file.is_open()) return false;
    
//     file.seekp(sectorIndex * SECTOR_SIZE);
//     file.write(reinterpret_cast<const char*>(data), SECTOR_SIZE);
//     return true;
// }





// bool read_from_data_device_1(int sectorIndex, std::byte* buffer);
// bool write_to_data_device_1(int sectorIndex, const std::byte* data);

// bool read_from_data_device_2(int sectorIndex, std::byte* buffer);
// bool write_to_data_device_2(int sectorIndex, const std::byte* data);

// bool read_from_parity_device(int sectorIndex, std::byte* buffer);
// bool write_to_parity_device(int sectorIndex, const std::byte* data);

// void xorBuffers(std::byte* buffer1, std::byte* buffer2) {
//     for (int i = 0; i < SECTOR_SIZE; ++i) {
//         buffer1[i] = static_cast<std::byte>(static_cast<uint8_t>(buffer1[i]) ^ static_cast<uint8_t>(buffer2[i]));
//     }
// }

// bool read(int sectorIndex, std::byte* buffer) {
//     std::byte dataBuffer[SECTOR_SIZE];
//     std::byte parityBuffer[SECTOR_SIZE];

//     if (!read_from_data_device_1(sectorIndex, dataBuffer)) {
//         // If data device 1 fails, calculate parity and read from data device 2
//         if (!read_from_parity_device(sectorIndex, parityBuffer)) return false;
//         if (!read_from_data_device_2(sectorIndex, buffer)) return false;

//         xorBuffers(buffer, parityBuffer);  // Recover data
//     } else {
//         std::memcpy(buffer, dataBuffer, SECTOR_SIZE);
//     }

//     return true;
// }

// bool write(int sectorIndex, const std::byte* data) {
//     std::byte dataBuffer[SECTOR_SIZE];
//     std::byte parityBuffer[SECTOR_SIZE];

//     // Write to the first data device
//     if (!write_to_data_device_1(sectorIndex, data)) return false;

//     // Calculate parity and write to the parity device
//     if (!read_from_data_device_2(sectorIndex, dataBuffer)) return false;
//     xorBuffers(dataBuffer, const_cast<std::byte*>(data)); // XOR to create parity

//     if (!write_to_parity_device(sectorIndex, dataBuffer)) return false;

//     // Write the original data to the second data device
//     if (!write_to_data_device_2(sectorIndex, data)) return false;

//     return true;
// }

// int main() {
//     std::byte data[SECTOR_SIZE] = { std::byte(0x01) };  // Sample data to write

//     // Write data
//     if (write(0, data)) {
//         std::cout << "Data written successfully.\n";
//     } else {
//         std::cerr << "Write failed.\n";
//     }

//     std::byte buffer[SECTOR_SIZE];
//     // Read data
//     if (read(0, buffer)) {
//         std::cout << "Data read successfully.\n";
//     } else {
//         std::cerr << "Read failed.\n";
//     }

//     return 0;
// }

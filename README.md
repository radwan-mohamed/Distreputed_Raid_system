# Distreputed_Raid5_system_Data Recovery Project
to retrive data if its lost Special Thanks to Ahemd Aboelrous and Ali and Yehia adawy for their team work as this project is collaboration from all of us 


## Overview

This project demonstrates the implementation of data recovery in a RAID5-like system. The primary purpose is to retrieve lost data using parity calculations. The system utilizes Tailscale for networking and a shared directory mounted across team members' systems to collaborate effectively.

## Project Components

### Directory Structure

```
D:\Github_repos\Distreputed_Raid_system
|
├── another_try
│   ├── data
│   │   ├── testB.txt       # Contains original data or parts of it
│   │   ├── testC.txt       # Contains parity data
│   │   └── reco_A.txt      # Output file with recovered data
│   ├── parity_calculator.cpp
│   ├── raid5
│   └── raid5.cpp
├── raid5_project
├── The_real_try
├── .gitattributes
└── README.md
```

### Key Files

* **parity\_calculator.cpp**: Core logic for parity calculations and data recovery.
* **testB.txt**: Simulated data from one of the drives.
* **testC.txt**: Parity data used for recovery.
* **reco\_A.txt**: Output file where the recovered data is stored.
* **raid5.cpp**: Additional RAID5 functionality and utilities.

## Networking Setup

### Tailscale

Tailscale is used to ensure all team members are on the same virtual network for easy collaboration and file sharing. Each team member has the shared project directory mounted on their system. This enables:

1. Real-time access to updated files.
2. Secure communication over the same virtual network.

### Mounting the Shared Directory

Ensure the shared directory is properly mounted on your local machine. Verify the directory structure matches the one outlined above.

## Purpose

The main objective of this project is to:

1. Simulate a RAID5 environment.
2. Use parity data to recover lost or corrupted data.
3. Demonstrate the feasibility of distributed team collaboration using shared resources.

## How to Run

### Prerequisites

1. **Tailscale**: Installed and configured on all team systems.
2. **C++ Compiler**: Compatible with `parity_calculator.cpp` and `raid5.cpp`.
3. **Directory Setup**: Ensure `data` directory contains:

   * `testB.txt`
   * `testC.txt`

### Steps to Test Data Recovery

1. **Compile the Code**:

   ```bash
   g++ -o parity_calculator parity_calculator.cpp
   ```
2. **Run the Program**:

   ```bash
   ./parity_calculator
   ```
3. **Verify Output**:

   * Check the `data/reco_A.txt` file for the recovered data.
   * Ensure the contents match the expected data from the recovery process.

### Sample Test

1. Populate `testB.txt` and `testC.txt` with the following example:

   * **testB.txt**:

     ```
     Hello
     World
     ```
   * **testC.txt**:

     ```
     XOR1
     XOR2
     ```
2. Run the program and inspect `reco_A.txt`. Expected output:

   ```
   Recovered
   Data
   ```

## Troubleshooting

* **File Not Found**:

  * Ensure the `data` directory contains the required files.
  * Verify file paths are correct relative to the working directory.

* **Compilation Errors**:

  * Check for missing libraries or syntax issues in the code.

* **Incorrect Output**:

  * Confirm the input files (`testB.txt`, `testC.txt`) are correctly formatted.
  * Verify the XOR logic in `parity_calculator.cpp` aligns with the test data.

## Collaboration Notes

* Always sync the shared directory before running the program to ensure you have the latest files.
* Use Tailscale to troubleshoot or discuss issues in real time.

## Future Enhancements

1. Extend functionality for multi-disk RAID5 simulations.
2. Add logging for debugging and performance metrics.
3. Implement a graphical interface for better usability.

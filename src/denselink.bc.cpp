


#include <iostream> // For standard input/output operations
#include <fstream>  // For file input/output operations
#include <string>   // For string manipulation
#include <vector>   // For dynamic arrays
#include <sstream>  // For string streams
#include <iomanip>  // For input/output manipulation
#include <algorithm> // For algorithms like std::transform

// Define a constant for the XOR key
const char XOR_KEY = 0x42;

// Function to encrypt or decrypt a single byte using XOR
unsigned char xorByte(unsigned char byte) {
    return byte ^ XOR_KEY;
}

// Function to encrypt or decrypt a string using XOR
std::string processString(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), xorByte);
    return result;
}

// Function to read and process XML-like data from a file
std::string processXMLFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;

    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
    } else {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return ""; // Return an empty string on error
    }

    std::string fileContents = buffer.str();
    size_t startPos = fileContents.find("<densenlink>");
    size_t endPos = fileContents.find("</densenlink>");

    if (startPos == std::string::npos || endPos == std::string::npos) {
        std::cerr << "Error: Invalid XML format in file: " << filename << std::endl;
        return ""; // Return an empty string on error
    }

    startPos += 13; // Move past the start tag
    std::string dataToProcess = fileContents.substr(startPos, endPos - startPos);

    return processString(dataToProcess);
}

// Function to write processed data to a file
bool writeToFile(const std::string& filename, const std::string& data) {
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        outfile << data;
        outfile.close();
        return true;
    } else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return false;
    }
}

int main() {
    // File names for input and output
    std::string inputFilename = "input.xml"; 
    std::string outputFilename = "output.bin";

    // Process the XML file and get the encrypted/decrypted data
    std::string processedData = processXMLFile(inputFilename);

    // Check if processing was successful
    if (processedData.empty()) {
        return 1; // Return an error code
    }

    // Write the processed data to the output file
    if (writeToFile(outputFilename, processedData)) {
        std::cout << "Data processed and written to: " << outputFilename << std::endl;
    } else {
        return 1; // Return an error code
    }

    return 0; // Return success
}

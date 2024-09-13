#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;

// Function to check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Function to get the current timestamp
std::string getCurrentTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

int main() {
    // ------------------------------------------------------------------------
    // Configuration
    // ------------------------------------------------------------------------

    // Project directory
    const std::string projectDir = "./";

    // Source directory relative to the project directory
    const std::string sourceDir = "src/";

    // Build directory relative to the project directory
    const std::string buildDir = "build/";

    // Output directory relative to the project directory
    const std::string outputDir = "bin/";

    // Compiler to use
    const std::string compiler = "g++";

    // Compiler flags
    const std::vector<std::string> compilerFlags = {
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-std=c++20",
        "-O3",
    };

    // Linker flags
    const std::vector<std::string> linkerFlags = {};

    // ------------------------------------------------------------------------
    // Build process
    // ------------------------------------------------------------------------

    // Create the build directory if it doesn't exist
    if (!fs::exists(buildDir)) {
        fs::create_directory(buildDir);
    }

    // Create the output directory if it doesn't exist
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }

    // Get a list of all source files in the source directory
    std::vector<std::string> sourceFiles;
    for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
            sourceFiles.push_back(entry.path().string());
        }
    }

    // Compile each source file
    for (const auto& sourceFile : sourceFiles) {
        // Get the filename without the extension
        const std::string filename = fs::path(sourceFile).stem().string();

        // Create the object file path
        const std::string objectFile = buildDir + filename + ".o";

        // Build the compiler command
        std::string command = compiler + " -c ";
        for (const auto& flag : compilerFlags) {
            command += flag + " ";
        }
        command += "-o " + objectFile + " " + sourceFile;

        // Execute the compiler command
        const int result = std::system(command.c_str());

        // Check for errors
        if (result != 0) {
            std::cerr << "Error compiling file: " << sourceFile << std::endl;
            return 1;
        }
    }

    // Link the object files into an executable
    {
        // Create the executable file path
        const std::string executableFile = outputDir + "myprogram";

        // Build the linker command
        std::string command = compiler + " ";
        for (const auto& objectFile : sourceFiles) {
            const std::string filename = fs::path(objectFile).stem().string();
            command += buildDir + filename + ".o ";
        }
        for (const auto& flag : linkerFlags) {
            command += flag + " ";
        }
        command += "-o " + executableFile;

        // Execute the linker command
        const int result = std::system(command.c_str());

        // Check for errors
        if (result != 0) {
            std::cerr << "Error linking executable" << std::endl;
            return 1;
        }
    }

    // Print a success message
    std::cout << "Build successful!" << std::endl;

    return 0;
}

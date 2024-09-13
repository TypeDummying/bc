#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

// Structure to represent a file or directory
struct FileEntry {
    std::string name;
    std::filesystem::file_time_type lastWriteTime;
    bool isDirectory;
};

// Function to compare two FileEntry objects by last write time
bool compareByWriteTime(const FileEntry& a, const FileEntry& b) {
    return a.lastWriteTime < b.lastWriteTime;
}

// Function to generate a buildcore (.bc) file
void generateBuildcoreFile(const std::string& sourceDir, const std::string& outputFile) {
    // Create a vector to store file entries
    std::vector<FileEntry> fileEntries;

    // Iterate over the source directory and its subdirectories
    for (const auto& entry : std::filesystem::recursive_directory_iterator(sourceDir)) {
        // Get file or directory information
        FileEntry fileEntry;
        fileEntry.name = entry.path().string();
        fileEntry.lastWriteTime = std::filesystem::last_write_time(entry);
        fileEntry.isDirectory = entry.is_directory();

        // Add file entry to the vector
        fileEntries.push_back(fileEntry);
    }

    // Sort file entries by last write time
    std::sort(fileEntries.begin(), fileEntries.end(), compareByWriteTime);

    // Open the output file for writing
    std::ofstream output(outputFile, std::ios::binary);

    // Write the number of files and directories
    uint32_t numEntries = static_cast<uint32_t>(fileEntries.size());
    output.write(reinterpret_cast<const char*>(&numEntries), sizeof(uint32_t));

    // Write file and directory information to the output file
    for (const auto& entry : fileEntries) {
        // Write file or directory name length
        uint32_t nameLength = static_cast<uint32_t>(entry.name.size());
        output.write(reinterpret_cast<const char*>(&nameLength), sizeof(uint32_t));

        // Write file or directory name
        output.write(entry.name.c_str(), nameLength);

        // Write last write time
        output.write(reinterpret_cast<const char*>(&entry.lastWriteTime), sizeof(std::filesystem::file_time_type));

        // Write directory flag
        bool isDirectory = entry.isDirectory;
        output.write(reinterpret_cast<const char*>(&isDirectory), sizeof(bool));
    }

    // Close the output file
    output.close();
}
int main() {
    // Specify the source directory and output file
    std::string sourceDir = "path/to/source/directory";
    std::string outputFile = "buildcore.bc";

    // Generate the buildcore file
    generateBuildcoreFile(sourceDir, outputFile);

    return 0;
}

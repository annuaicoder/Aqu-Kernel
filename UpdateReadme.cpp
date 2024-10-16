#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// Function to get a list of all .c files in the commands directory
std::vector<std::string> getCommandFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".c") {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

// Function to update the README file
void updateReadme(const std::vector<std::string>& commandFiles) {
    std::string readmeContent;
    std::ifstream readmeFile("README.md");

    // Read the current README content
    if (readmeFile) {
        readmeContent.assign((std::istreambuf_iterator<char>(readmeFile)),
                              std::istreambuf_iterator<char>());
        readmeFile.close();
    }

    // Find the position of the "Starting the Kernel" section
    size_t startPos = readmeContent.find("# Starting the Kernel");
    if (startPos == std::string::npos) {
        std::cerr << "README.md does not contain 'Starting the Kernel' section." << std::endl;
        return;
    }

    // Prepare the new "Starting the Kernel" section content
    std::string newSection = "# Starting the Kernel\n\n";
    newSection += "To start the kernel run the following command:\n\n```\ngcc kernel.c";

    // Add all .c files from the commands folder to the compile command
    for (const auto& file : commandFiles) {
        newSection += " commands/" + file;
    }

    newSection += " -o aqu_kernel\n```\n\n";
    newSection += "And then run the kernel with:\n\n```\n./aqu_kernel\n```\n";

    // Replace the old "Starting the Kernel" section with the new one
    size_t endPos = readmeContent.find("\n#", startPos + 1); // Find the next section
    readmeContent.replace(startPos, endPos - startPos, newSection);

    // Write the updated content back to README.md
    std::ofstream outFile("README.md");
    outFile << readmeContent;
    outFile.close();

    std::cout << "README.md has been updated successfully." << std::endl;
}

int main() {
    // Get the list of .c files from the commands directory
    std::vector<std::string> commandFiles = getCommandFiles("commands");

    // Update the README.md file with the new "Starting the Kernel" section
    updateReadme(commandFiles);

    return 0;
}

#include <iostream>
#include <optional>
#include <filesystem>
#include <fstream>

// TO DO FOR V1.0
// [!] Take in user arguments
// [!] take in only 2 (the program it self and the project name)
// [!] create a folder in the current directory called the project name
// [!] create a main.cpp in the new directory that is a simple hello world
// [!] create a CMakeLists.txt file
const std::string VERSION_ = "060926";

void createCMakeFile(const std::string &folderPath, const std::string &projectName) {
    std::string fileName = folderPath + "/CMakeLists.txt";
    std::cout << fileName << "\n";

    std::ofstream file;
    file.open(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to create CMake file \n";
        return;
    }

    file << "cmake_minimum_required(VERSION 3.22)\n";
    file << "project(" << projectName << ")\n";
    file << "\n";
    file << "set (SOURCES\n";
    file << "   main.cpp\n";
    file << ")\n";
    file << "\n";
    file << "add_executable(" << projectName << " ${SOURCES})\n";
}

void createMain(const std::string &folderPath) {
    std::string fileName = folderPath + "/main.cpp";
    std::cout << fileName << "\n";

    std::ofstream file;
    file.open(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to create main.cpp \n";
        return;
    }

    file << "#include <iostream>\n";
    file << "\n";
    file << "int main() {\n";
    file << "    std::cout << \"Hello World\" << std::endl;\n";
    file << "}\n";
}

std::optional<std::string> createDirectory(const std::string &folderName) {
    bool folder = std::filesystem::create_directories(folderName);
    if (!folder) {
        return std::nullopt;
    }

    std::filesystem::permissions(folderName,
                    std::filesystem::perms::owner_all |
                    std::filesystem::perms::group_all |
                    std::filesystem::perms::others_all,
                    std::filesystem::perm_options::replace);

    std::filesystem::path newDir = folderName;
    std::filesystem::path currentPath = std::filesystem::current_path();
    currentPath /= newDir;
    return currentPath.string();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Build: " << VERSION_ << "\n";
        std::cout << "Usage:\n";
        std::cout << "    " << argv[0] << " <projectName> \n";
        exit(1);
    }

    std::string projectName = argv[1];

    if (std::optional<std::string> dirPath = createDirectory(projectName)) {
        createMain(*dirPath);
        createCMakeFile(*dirPath, projectName);
    } else {
        std::cout << "Failed to make folder for " << projectName << " exiting...\n";
        exit(0);
    }

    return 0;
}
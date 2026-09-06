#include <iostream>
#include <optional>
#include <filesystem>

// TO DO
// [!] Take in user arguments
// [!] take in only 2 (the program it self and the project name)
// [!] create a folder in the current directory called the project name
// [] create a main.cpp in the new directory that is a simple hello world
// [] create a CMakeLists.txt file
// [] auto build the new proejct in a build directory

bool createDirectory(const std::string &folderName) {
    // creates a folder with the passed name
    // returns the folders name if succsefull 
    // return 0 if it failed
    std::string temp = "hello";
    std::cout << folderName << "\n";
    bool folder = std::filesystem::create_directories(folderName);
    std::filesystem::permissions(folderName, 
                    std::filesystem::perms::owner_all | 
                    std::filesystem::perms::group_all | 
                    std::filesystem::perms::others_all,
                    std::filesystem::perm_options::replace);
    return folder;

}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        std::cout << "Usage:\n";
        std::cout << "    " << argv[0] << " <projectName> \n";
        exit(1);
    }
    std::string projectName = argv[1];
    std::cout << projectName << "\n";
    createDirectory(projectName);
    return 0;
}
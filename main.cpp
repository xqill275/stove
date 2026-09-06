#include <iostream>
#include <optional>
#include <filesystem>
#include <fstream>

// TO DO FOR V1.0
// [!] Take in user arguments
// [!] take in only 2 (the program it self and the project name)
// [!] create a folder in the current directory called the project name
// [!] create a main.cpp in the new directory that is a simple hello world
// [] create a CMakeLists.txt file
// [] auto build the new proejct in a build directory
const std::string VERSION_ = "060926"; 
void createMain(const std::string &folderPath) {
    std::string fileNane = folderPath + "/main.cpp";
    std::cout << fileNane << "\n";
    std::ofstream file;
    file.open(fileNane);
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
    // creates a folder with the passed name
    // returns the folder path if succsessfull 
    // return a Nullptr if failed;
    std::string temp = "hello";
    std::cout << folderName << "\n";
    bool folder = std::filesystem::create_directories(folderName);
    if (!folder) {
        return std::nullopt;
    }
    std::filesystem::permissions(folderName, 
                    std::filesystem::perms::owner_all | 
                    std::filesystem::perms::group_all | 
                    std::filesystem::perms::others_all,
                    std::filesystem::perm_options::replace);
    class std::filesystem::__cxx11::path newDir = folderName;
    class std::filesystem::__cxx11::path currentPath = std::filesystem::current_path();
    currentPath /= newDir;
    std::cout << currentPath << "\n";
    return currentPath;

}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        std::cout << "Usage:\n";
        std::cout << "    " << argv[0] << " <projectName> \n";
        exit(1);
    }
    std::string projectName = argv[1];
    std::cout << projectName << "\n";
    if (std::optional<std::string> dirPath = createDirectory(projectName)) {
        createMain(*dirPath);
    } else {
        std::cout << "Failed to make folder for " << projectName << " exiting...\n";
        exit(0);
    }
    return 0;
}
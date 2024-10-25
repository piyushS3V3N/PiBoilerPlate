#include "CMakeGenerator.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void CMakeGenerator::createCMakeLists(const std::string& projectName, const nlohmann::json& dependencies) {
    std::ofstream cmakeFile(projectName + "/CMakeLists.txt");
    if (!cmakeFile) {
        std::cerr << "Error creating CMakeLists.txt" << std::endl;
        return;
    }

    cmakeFile << "cmake_minimum_required(VERSION 3.10)\n\n";
    cmakeFile << "project(" << projectName << ")\n\n";
    cmakeFile << "set(CMAKE_CXX_STANDARD 17)\n\n";
    cmakeFile << "add_executable(" << projectName << " src/main.cpp)\n\n";

    // Adding dependencies
    for (auto& dep : dependencies.items()) {
        cmakeFile << "find_package(" << dep.key() << " CONFIG REQUIRED)\n";
        cmakeFile << "target_link_libraries(" << projectName << " PRIVATE " << dep.key() << ")\n";
    }

    cmakeFile.close();
}

void CMakeGenerator::createProjectStructure(const std::string& projectName, const nlohmann::json& dependencies) {
    fs::create_directory(projectName);
    fs::create_directory(projectName + "/src");
    fs::create_directory(projectName + "/include");

    // Create a sample main.cpp
    std::ofstream mainFile(projectName + "/src/main.cpp");
    mainFile << "#include <iostream>\n\n";
    mainFile << "int main() {\n";
    mainFile << "    std::cout << \"Hello, " << projectName << "!\" << std::endl;\n";
    mainFile << "    return 0;\n";
    mainFile << "}\n";
    mainFile.close();

    createCMakeLists(projectName, dependencies);
}


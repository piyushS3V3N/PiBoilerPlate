#include <iostream>
#include <string>
#include "CMakeGenerator.h"
#include "DependencyManager.h"
#include "ConfigManager.h"
#include <nlohmann/json.hpp> // Include for nlohmann::json

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <project_name> [config_path] | add <library>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string configPath = "CMakeBoilerplateConfig.json"; // Default config path
    DependencyManager depManager; // Create an instance of DependencyManager

    if (command == "add" && argc == 3) {
        std::string library = argv[2];
        depManager.addDependency(library, configPath); // Use the instance to call addDependency
        return 0;
    }

    std::string projectName = command;
    nlohmann::json config = ConfigManager::readConfig(configPath);
    nlohmann::json dependencies = config["dependencies"];

    // Check and install dependencies using the instance
    depManager.checkAndInstallDependencies(dependencies);

    CMakeGenerator::createProjectStructure(projectName, dependencies);
    std::cout << "Project " << projectName << " created successfully!" << std::endl;

    return 0;
}


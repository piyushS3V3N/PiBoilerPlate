#include "ConfigManager.h"
#include <iostream>
#include <fstream>

nlohmann::json ConfigManager::readConfig(const std::string& configPath) {
    std::ifstream configFile(configPath);
    nlohmann::json config;

    if (configFile.is_open()) {
        configFile >> config;
        configFile.close();
    } else {
        std::cerr << "Error reading configuration file: " << configPath << std::endl;
    }

    return config;
}

void ConfigManager::writeConfig(const std::string& configPath, const nlohmann::json& config) {
    std::ofstream configFile(configPath);
    if (configFile.is_open()) {
        configFile << config.dump(4);
        configFile.close();
    } else {
        std::cerr << "Error writing configuration file: " << configPath << std::endl;
    }
}


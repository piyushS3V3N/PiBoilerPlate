#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <nlohmann/json.hpp>

class ConfigManager {
public:
    static nlohmann::json readConfig(const std::string& configPath);
    static void writeConfig(const std::string& configPath, const nlohmann::json& config);
};

#endif // CONFIGMANAGER_H


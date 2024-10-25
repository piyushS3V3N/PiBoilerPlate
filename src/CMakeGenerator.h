#ifndef CMAKEGENERATOR_H
#define CMAKEGENERATOR_H

#include <string>
#include <nlohmann/json.hpp>

class CMakeGenerator {
public:
    static void createCMakeLists(const std::string& projectName, const nlohmann::json& dependencies);
    static void createProjectStructure(const std::string& projectName, const nlohmann::json& dependencies);
};

#endif // CMAKEGENERATOR_H


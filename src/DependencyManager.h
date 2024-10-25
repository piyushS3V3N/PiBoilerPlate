#ifndef DEPENDENCYMANAGER_H
#define DEPENDENCYMANAGER_H

#include <string>
#include <vector>
#include "nlohmann/json.hpp" // Assuming you're using nlohmann::json

enum class PackageManager {
    Homebrew,
    APT,
    DNF,
    Pacman,
    Unknown
};

class DependencyManager {
public:
    void addDependency(const std::string& library, const std::string& configPath);
    void checkAndInstallDependencies(const nlohmann::json& dependencies);
    
private:
    bool isDependencyAvailable(const std::string& dep, PackageManager pm);
    void installDependency(const std::string& dep, PackageManager pm);
    std::vector<std::string> getAvailableDependencies(const std::string& searchTerm, PackageManager pm);
    bool isExactMatch(const std::string& library, const std::vector<std::string>& availablePackages);
    PackageManager detectPackageManager();
};

#endif // DEPENDENCYMANAGER_H


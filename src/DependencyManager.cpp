#include "DependencyManager.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "ConfigManager.h"

PackageManager DependencyManager::detectPackageManager() {
    #ifdef __APPLE__
        return PackageManager::Homebrew; // macOS
    #elif defined(__linux__)
        // Check for APT (Debian/Ubuntu)
        if (std::system("which apt > /dev/null 2>&1") == 0) {
            return PackageManager::APT;
        }
        // Check for DNF (Fedora)
        if (std::system("which dnf > /dev/null 2>&1") == 0) {
            return PackageManager::DNF;
        }
        // Check for Pacman (Arch Linux)
        if (std::system("which pacman > /dev/null 2>&1") == 0) {
            return PackageManager::Pacman;
        }
    #endif
    return PackageManager::Unknown;
}

bool DependencyManager::isDependencyAvailable(const std::string& dep, PackageManager pm) {
    std::string command;
    switch (pm) {
        case PackageManager::Homebrew:
            command = "brew search " + dep + " | grep -E '^\\s*" + dep + "$'";
            break;
        case PackageManager::APT:
            command = "apt-cache search " + dep + " | grep -E '^" + dep + "'";
            break;
        case PackageManager::DNF:
            command = "dnf list available | grep -E '^\\s*" + dep + "'";
            break;
        case PackageManager::Pacman:
            command = "pacman -Ss " + dep + " | grep -E '^\\s*" + dep + "'";
            break;
        default:
            std::cerr << "Unknown package manager." << std::endl;
            return false;
    }
    return (std::system(command.c_str()) == 0);
}

void DependencyManager::installDependency(const std::string& dep, PackageManager pm) {
    std::string command;
    switch (pm) {
        case PackageManager::Homebrew:
            command = "brew install " + dep;
            break;
        case PackageManager::APT:
            command = "sudo apt install -y " + dep;
            break;
        case PackageManager::DNF:
            command = "sudo dnf install -y " + dep;
            break;
        case PackageManager::Pacman:
            command = "sudo pacman -S --noconfirm " + dep;
            break;
        default:
            std::cerr << "Unknown package manager." << std::endl;
            return;
    }

    std::cout << "Installing missing dependency: " << dep << "..." << std::endl;
    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Successfully installed " << dep << std::endl;
    } else {
        std::cerr << "Failed to install " << dep << std::endl;
    }
}

void DependencyManager::addDependency(const std::string& library, const std::string& configPath) {
    PackageManager pm = detectPackageManager();

    // Fetch available dependencies
    auto availablePackages = getAvailableDependencies(library, pm);

    if (!isExactMatch(library, availablePackages)) {
        std::cerr << "Error: The dependency \"" << library << "\" is not available." << std::endl;
        std::cout << "Available packages matching \"" << library << "\":" << std::endl;

        for (const auto& pkg : availablePackages) {
            if (pkg.find(library) != std::string::npos) {
                std::cout << " - " << pkg << std::endl;
            }
        }
        return;
    }

    nlohmann::json config = ConfigManager::readConfig(configPath);

    if (config["dependencies"].contains(library)) {
        std::cout << "Dependency \"" << library << "\" already exists in " << configPath << "." << std::endl;
        return;
    }

    config["dependencies"][library] = "latest";
    ConfigManager::writeConfig(configPath, config);
    std::cout << "Added dependency: " << library << " to " << configPath << std::endl;

    // Install the dependency
    installDependency(library, pm);
}

void DependencyManager::checkAndInstallDependencies(const nlohmann::json& dependencies) {
    PackageManager pm = detectPackageManager();
    
    for (const auto& item : dependencies.items()) {
        const std::string& library = item.key();
        
        if (!isDependencyAvailable(library, pm)) {
            std::cerr << "Dependency \"" << library << "\" is not installed. Installing..." << std::endl;
            installDependency(library, pm);
        } else {
            std::cout << "Dependency \"" << library << "\" is already installed." << std::endl;
        }
    }
}

std::vector<std::string> DependencyManager::getAvailableDependencies(const std::string& searchTerm, PackageManager pm) {
    std::string command;
    switch (pm) {
        case PackageManager::Homebrew:
            command = "brew search " + searchTerm;
            break;
        case PackageManager::APT:
            command = "apt-cache search " + searchTerm;
            break;
        case PackageManager::DNF:
            command = "dnf list available | grep " + searchTerm;
            break;
        case PackageManager::Pacman:
            command = "pacman -Ss " + searchTerm;
            break;
        default:
            std::cerr << "Unknown package manager." << std::endl;
            return {};
    }

    std::vector<std::string> packages;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error: Unable to open pipe." << std::endl;
        return packages;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::string pkg(buffer);
        pkg.erase(0, pkg.find_first_not_of(" \n\r\t")); // Trim leading whitespace
        pkg.erase(pkg.find_last_not_of(" \n\r\t") + 1); // Trim trailing whitespace
        if (!pkg.empty()) {
            packages.push_back(pkg);
        }
    }
    pclose(pipe);
    return packages;
}

// Define isExactMatch function if not already defined
bool DependencyManager::isExactMatch(const std::string& library, const std::vector<std::string>& availablePackages) {
    return std::find(availablePackages.begin(), availablePackages.end(), library) != availablePackages.end();
}


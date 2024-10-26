# PiBoilerplate

PiBoilerplate is a cross-platform C++ project generator designed to simplify the setup of CMake projects. It manages dependencies using popular package managers across different operating systems, including macOS, and Linux.
[![Build and Package](https://github.com/piyushS3V3N/PiBoilerPlate/actions/workflows/build.yml/badge.svg)](https://github.com/piyushS3V3N/PiBoilerPlate/actions/workflows/build.yml)

## Features

- Detects and manages dependencies automatically based on the operating system.
- Supports package managers:
  - **macOS**: Homebrew
  - **Linux**: APT, DNF, Pacman
- Generates a basic CMake project structure.
- Reads and updates project configuration from a JSON file.

## Prerequisites

Before using PiBoilerplate, ensure you have the following installed:

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., g++, clang++).
- **CMake**: Install CMake from [cmake.org](https://cmake.org/download/).
- **Package Managers**:
  - macOS: [Homebrew](https://brew.sh/)
  - Linux: APT, DNF, or Pacman depending on your distribution.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/PiBoilerplate.git
   cd PiBoilerplate
   ```

2. Build the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

## Usage

### Creating a New Project

To create a new CMake project, run the executable with the project name:

```bash
./CMakeBoilerplateGenerator <project_name>
```

### Adding Dependencies

To add a dependency to your project, use the following command:

```bash
./CMakeBoilerplateGenerator add <library>
```

### Configuration File

The configuration file `CMakeBoilerplateConfig.json` will be created or updated in the current directory. You can manually edit this file to manage dependencies.

### Example

```bash
./CMakeBoilerplateGenerator MyProject
./CMakeBoilerplateGenerator add boost
```

## Troubleshooting

- Ensure that the package managers are properly installed and configured.
- Check the permissions if you encounter issues with installing packages on Linux.

## Contributing

Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add new feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For questions or feedback, feel free to reach out:

- **Piyush Parashar**: [piyushparashar2k@gmail.com](mailto:piyushparashar2k@gmail.com)

---

Thank you for using PiBoilerplate!

```

### Key Sections Explained

- **Project Description**: Provides a brief overview of what the project does.
- **Features**: Highlights the main functionalities of the tool.
- **Prerequisites**: Lists the required tools and packages for the setup.
- **Installation Instructions**: Guides users through the process of setting up the project.
- **Usage**: Explains how to create projects and add dependencies.
- **Troubleshooting**: Offers common solutions to potential issues.
- **Contributing**: Invites users to contribute to the project.
- **License**: States the licensing information.
- **Contact Information**: Provides a way for users to reach out for support or questions.

Feel free to modify any section to better match your preferences or project specifics!
```

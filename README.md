# GitHub User Activity CLI

A C++ command-line application to view a GitHub user's recent activity, including:
- Push events (which repositories have been pushed to)
- Number of commits made
- Starred repositories
- 
## Requirements

Before you begin, ensure you have the following installed:

- [CMake](https://cmake.org/download/) (>= 3.15)
- [vcpkg](https://github.com/microsoft/vcpkg) (for managing dependencies)
- A C++ compiler that supports C++17 or higher
- Internet connection (uses HTTP GET requests)

## Dependencies

This project uses:

- [`cpr`](https://github.com/libcpr/cpr) - for HTTP requests
- [`nlohmann/json`](https://github.com/nlohmann/json) - for working with JSON
## Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/github-user-activity-cli.git
cd github-user-activity-cli

## 2. Set Up vcpkg (If You Haven’t Already)

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat   # on Windows
# OR
./bootstrap-vcpkg.sh    # on Unix
```

## 3. Install Required Libraries with vcpkg

```bash
./vcpkg install cpr nlohmann-json
```

## 4. Configure and Build with CMake

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```
*Replace `path/to/vcpkg/` with your actual vcpkg path (e.g. `C:/dev/vcpkg`)*

## 5. Run the Program

```bash
./build/your_executable_name
```

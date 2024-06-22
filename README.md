# Getting started: Windows

Prerequisites:
- Windows
- CMAKE
- VCPKG
- Visual Studio 17 2022
- MSBuild

## Clone repository and setup
```cmd
> git clone https://github.com/venazo/Nazo
> cd Nazo
> mkdir build
```

## Downloading packages and building CMAKE
```cmd
> vcpkg integrate install
> cmake -DCMAKE_TOOLCHAIN_FILE=path/to/toolchainfile -DCMAKE_BUILD_TYPE=Debug -B"Build" -G"Visual Studio 17 2022"
```

## Building
```cmd
> MSBuild build/ALL_BUILD.vcxproj
```

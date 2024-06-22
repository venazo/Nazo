# Getting started: Windows

Prerequisites:
- Windows
- CMAKE
- VCPKG
- Visual Studio 17 2022
- .NET SDK

## Clone repository and setup
```cmd
> git clone https://github.com/venazo/Nazo
> cd Nazo
```

## Downloading packages and building CMAKE
```cmd

> vcpkg integrate install
> cmake -DCMAKE_TOOLCHAIN_FILE=path/to/toolchainfile -DCMAKE_BUILD_TYPE=Debug -B"Build" -G"Visual Studio 17 2022"
```

## Building

```cmd
> dotnet build build/nazo.sln
```

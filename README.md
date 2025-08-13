# Getting started: Windows

Prerequisites:
- Windows
- VCPKG
- CMAKE
- GNU

## Clone repository and setup
```cmd
> git clone https://github.com/venazo/Nazo
> cd Nazo
```

## Downloading packages and building CMAKE
```cmd
> vcpkg integrate install
> cmake -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg -DVCPKG_HOST_TRIPLET=x64-mingw-static -DCMAKE_BUILD_TYPE=Debug -B'Build' -G'MinGW Makefiles'
```

## Build Makefiles
```cmd
> cd Build
> mingw32-make -j8
```




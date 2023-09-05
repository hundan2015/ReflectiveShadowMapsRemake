# Reflective Shadow Maps Remake

Original paper: Reflective shadow maps

The purpose of this project is to reproduce the original paper. And in order to speed up the efficiency, it is optimized by using deferred rendering and point light source shadow map.

## How to build

This project uses Cmake and vcpkg as the submodule. If you hope to build it from source, you need run the command below:

```
git submodule init
git submodule update
mkdir build
cd build 
cmake ..
cmake --build .
```

Then you can use your own way to build this Cmake project. And the CMake would auto download the libraries this project need.

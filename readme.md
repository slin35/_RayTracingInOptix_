# Dependencies
- Cuda 11+ (https://developer.nvidia.com/cuda-downloads)
- OptiX 7+ (https://developer.nvidia.com/designworks/optix/download)
- CMake 2.8+ (https://cmake.org/download/)

# Setup Environment Variables
- CUDA_PATH
- OptiX_INSTALL_DIR (should contain "include" and "SDK" directories)
- OptiX_INCLUDE (should be OptiX_INSTALL_DIR/SDK/CUDA)

# Build Instructions
1. mkdir build
2. cd build
3. cmake ../

# Run Instructions
./rayTraceInOptix.exe [povrayFile] [objectFile]
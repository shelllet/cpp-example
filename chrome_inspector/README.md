# pkg

    vcpkg install qt5-base:x64-windows
    vcpkg.exe install qt5-serialbus:x64-windows
    vcpkg.exe install qt5-websockets:x64-windows
    vcpkg.exe install opencv4[world]:x64-windows
    vcpkg.exe install boost-asio:x64-windows
    vcpkg.exe install boost-log:x64-windows
    vcpkg.exe install boost-beast:x64-windows
    vcpkg.exe install v8:x64-windows
   

# clang
    Using Ninja alongside Visual Studio[https://clang.llvm.org/get_started.html]
    
    1. Check out clang and LLVM 
        `git clone https://github.com/llvm/llvm-project.git`

    2. Open a developer command prompt with the appropriate environment

    3. mkdir build_ninja (or build, or use your own organization)

    4. cd build_ninja

    5. set CXX=cl
    
    6. set CC=cl

    7. cmake -GNinja -DLLVM_ENABLE_PROJECTS=clang ..\llvm
 
    8. ninja clang

# third-party

    git submodule add https://github.com/qt-labs/qthttpserver.git ./third-party/qthttpserver
# v8
    wiki - how to build v8
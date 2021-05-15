
# debug renderer process
1. __debugbreak();
2. HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\AeDebug set Auto(REG_SZ) = 1



# wiki

    git submodule add https://github.com/matcornic/hugo-theme-learn.git wiki/themes/hugo-theme-learn

    git submodule init

    git submodule update --recursive --remote

    cp -rv themes/hugo-theme-learn/exampleSite/. .



# .gitconfig
    git config --global user.name "shelllet"
    git config --global user.email "shelllet@gmail.com"

    git config --global core.autocrlf input
    git config --global core.safecrlf false

# submodule
    git submodule init

    git submodule update --recursive --remote --no-fetch --depth=1


# boost

    git submodule add https://github.com/boostorg/boost.git src/boost

    git submodule update src/boost --recursive --remote --depth=1

    .\bootstrap.bat

    .\b2 --with-program_options --with-coroutine --with-context --with-thread --with-filesystem --with-serialization --with-log --with-random --with-locale link=shared threading=multi address-model=64 runtime-link=shared
    
# juce
    git submodule add https://github.com/WeAreROLI/JUCE.git src/JUCE

    git submodule update src/JUCE --recursive --remote

# inih
    git submodule add https://github.com/benhoyt/inih.git src/inih


# opencv

    git submodule add https://github.com/opencv/opencv.git src/opencv
    
    git submodule update src/opencv --recursive --remote
# opencv_contrib

    git submodule add https://github.com/opencv/opencv_contrib.git src/opencv_contrib

    git submodule update src/opencv_contrib --recursive --remote

# scintilla

    cd scintilla\win32
    
    nmake -f scintilla.mak

    nmake DEBUG=1 -f scintilla.mak
    
    nmake -f scintilla.mak clean

# v8
    wget https://storage.googleapis.com/chrome-infra/depot_tools.zip
    
    gclient

    fetch v8

    git pull origin

    gclient sync

# tinyxml2
    
    git submodule add https://github.com/leethomason/tinyxml2.git src/tinyxml2

    git submodule update src/tinyxml2 --recursive --remote

# json

    git submodule add https://github.com/nlohmann/json.git src/json

    git submodule update src/json --recursive --remote

# depot_tools

    git submodule add https://chromium.googlesource.com/chromium/tools/depot_tools src/depot_tools

    git submodule update src/depot_tools --recursive --remote
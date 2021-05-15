Qt Frameless Titlebar. No cross-system supported, only support window 7++.


# How to use (Method 1) 
    
	auto famelessWindow = std::make_unique<MainWindow>(nullptr, WindowType::AllButton);

	framelessWindow->setCentralWidget(new [YourWidget]);


# How to use (Method 2)

    class MessageBoxDialog : public MainWindow
    {
        MessageBoxDialog(){
            // ....
            setCentralWidget(contentWidget);
        }
    }

# Env
    CMAKE_ROOT # define cmake path, e.g. C:\Program Files\CMake\bin

    VCPKG_ROOT # define vcpkg path, e.g. D:\vcpkg-export-20201126-140522

# vcpkg
	vcpkg install boost:x64-windows-mixed
    vcpkg install pugixml:x64-windows-mixed
    vcpkg install qt5-svg:x64-windows-mixed

#pragma once
#include "framelesswindow_p.h"
namespace shelllet {
    namespace frameless{
        class MainWindowPrivate : public FramelessWindowPrivate {
            Q_DECLARE_PUBLIC(MainWindow)
            public:
                SizePolicyFlags fixedSize;
        };
    }
}
    
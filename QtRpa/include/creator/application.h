#pragma once
#include "common.hpp"
namespace shelllet {
    namespace creator{
        class ApplicationPrivate;
        class Application : public Object {
            Q_DECLARE_PRIVATE(Application)
        public:
          //  Application(Object*parent = nullptr);
			Application(int& argc, char** argv, Object* parent = nullptr);
			void customEvent(QEvent* event);

            void setWindowIcon(const QIcon & icon);
            void setQuitOnLastWindowClosed(bool quit);

            QApplication* toQApplication() const;
        protected:
            Application(ApplicationPrivate& d, int& argc, char** argv, Object*parent = nullptr);
        };
    }
}
    

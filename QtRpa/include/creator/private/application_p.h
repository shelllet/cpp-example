#pragma once
#include "common.hpp"
class QApplication;
namespace shelllet {
    namespace creator{
        class ApplicationPrivate : public ObjectPrivate {
            Q_DECLARE_PUBLIC(Application)
        public:

            class __Application : public QApplication {
            public:

                __Application(Application* self, int& argc, char** argv);

                void customEvent(QEvent* event);
            private:
                Application* self;
            };
            UniquePointer<__Application> app;
        };


	}
}

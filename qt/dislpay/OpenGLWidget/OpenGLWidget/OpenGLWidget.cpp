#include "OpenGLWidget.h"
#include <qopenglfunctions.h>
#include <qpainter.h>
class GLWidget : public QOpenGLWidget, public QOpenGLFunctions {
public:
    GLWidget(QWidget* parent) : QOpenGLWidget(parent) {

    }
protected:
    void initializeGL() override
    {
      //  throw std::logic_error("The method or operation is not implemented.");
        initializeOpenGLFunctions();
    }


    void paintGL() override
    {
        glClearColor(255, 255, 255, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        QPainter painter;

        painter.begin(this);

        painter.drawRect(QRect{ 10, 10, 50, 50 });

        painter.end();


        glColor3b(0, 0, 0);
        glBegin(GL_LINES);

        glVertex2f(0.0, 0.0);

        glVertex2f(0, 0.8);

        glEnd();

    }

};

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    ui.verticalLayout->addWidget(new GLWidget(ui.centralWidget));

}

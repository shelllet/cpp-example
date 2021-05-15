#include "SizeGrip.h"
#include <QtWidgets/QApplication>
#include "QSizeGrip"
#include "QVBoxLayout"
#include "qevent.h"
class MySizeGrip : public QWidget{
public:
    MySizeGrip():QWidget(nullptr, Qt::FramelessWindowHint){


        setLayout(new QVBoxLayout);
        sizegrip = new QSizeGrip(this);

        layout()->addWidget(sizegrip);

    }

    QSizeGrip* sizegrip;

    bool isPressed = false;
    QPointF orgin;
    QPoint windowPos;
protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        isPressed = true;
        orgin = event->screenPos();
        windowPos = pos();
    }


    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (isPressed) {
          //  setGeometry(QRect{ QPoint((windowPos + event->screenPos() - orgin).toPoint()), geometry().size()  });
            move((windowPos + event->screenPos() - orgin).toPoint());
       }

    }


    void mouseReleaseEvent(QMouseEvent* event) override
    {
        isPressed = false;
    }

};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 //   SizeGrip w;
  //  w.show();

    MySizeGrip sizegrip;
    sizegrip.resize(300, 300);
    sizegrip.show();

    return a.exec();
}

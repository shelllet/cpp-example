#include "GrapicsView.h"
#include <QGraphicsScene>
#include <qpixmap.h>
#include <QGraphicsPixmapItem>
#include <QDebug>
GrapicsView::GrapicsView(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QGraphicsScene *scene = new  QGraphicsScene(this);

    qDebug() << ui.graphicsView->rect();

    scene->setSceneRect(QRect(0,0, 793,475));
    ui.graphicsView->setSceneRect(QRect(0, 0, 793, 475));

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    QPixmap pixmap = QPixmap("./231102-151931226201f1.jpg");


    assert(!pixmap.isNull());

    item->setPixmap(pixmap);
    scene->addItem(item);

    scene->addItem(new QGraphicsSimpleTextItem("Hello world"));


    ui.graphicsView->setScene(scene);
}

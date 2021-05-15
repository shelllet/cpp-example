#include "columnview.h"
#include <QtDebug>

ColumnView::ColumnView(QWidget *parent) : QColumnView(parent)
{

}

QAbstractItemView *ColumnView::createColumn(const QModelIndex &rootIndex)
{
    qDebug() <<"col" << rootIndex.column();

//    if (rootIndex.column() == 0)
//        return nullptr;

    return QColumnView::createColumn(rootIndex);
}

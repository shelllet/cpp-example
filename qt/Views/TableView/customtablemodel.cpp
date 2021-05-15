#include "customtablemodel.h"

const int COLUMN_COUNT = 3;
const int ROW_COUNT= 10;

CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    for(auto i = 0; i < ROW_COUNT; i++) {
        QString prifix =QString("%1").arg(i);
        int suffix = 1;

         datas.push_back({prifix+ QString("-%1").arg(suffix++), prifix+ QString("-%1").arg(suffix++), prifix+ QString("-%1").arg(suffix++)});
    }

}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static QList<QString> headers = {"first", " second", "third"};
    if (orientation == Qt::Vertical)
    {
        if (role == Qt::DisplayRole){
            return  QVariant(QString("%1").arg(section) );
        }
    } else{
        if (role == Qt::DisplayRole){
            return headers[section];
        }
    }
    return QVariant();
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ROW_COUNT;
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return COLUMN_COUNT;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        auto row = index.row();
        auto col = index.column();

        return datas[row][col];
    }
    return QVariant();
}

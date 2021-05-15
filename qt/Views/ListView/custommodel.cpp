#include "custommodel.h"
#include <QtDebug>

CustomModel::CustomModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    modelData_.push_back(QStringLiteral("湖北省"));
    modelData_.push_back(QStringLiteral("浙江省"));
    modelData_.push_back(QStringLiteral("河南省"));
    modelData_.push_back(QStringLiteral("四川省"));
}

QVariant CustomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug()<< "header";
    return  QStringLiteral("省份");
}

bool CustomModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

QModelIndex CustomModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex CustomModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int CustomModel::rowCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;


    qDebug() << "row count:" << modelData_.size();
    return modelData_.size();
}

int CustomModel::columnCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;

    return  1;
}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role== Qt::EditRole){

        return modelData_[index.row()];
    }
    return QVariant();
}

bool CustomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole){
            qDebug() << "set";
            modelData_[index.row()] = value.toString();
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const
{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

    return Qt::ItemIsEditable |Qt::ItemIsEnabled;
}

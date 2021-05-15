#include "custommodel.h"
#include <QIcon>
CustomModel::CustomModel(QObject *parent)
    : QStringListModel(parent)
{
}

//QVariant CustomModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//int CustomModel::rowCount(const QModelIndex &parent) const
//{
//    // For list models only the root node (an invalid parent) should return the list's size. For all
//    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    static QStringList list= {":/new/prefix1/image/categories-new-white (1).png", ":/new/prefix1/image/categories-new-white (2).png", ":/new/prefix1/image/categories-new-white3.png"};
    if (role == Qt::DecorationRole){

        QIcon icon(list[index.row()]);

        assert(!icon.isNull());

        return  icon;
    }

    // FIXME: Implement me!
    return QStringListModel::data(index, role);
}

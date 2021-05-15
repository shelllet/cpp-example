#ifndef CUSTOMABSTRACTMODEL_H
#define CUSTOMABSTRACTMODEL_H

#include <QAbstractTableModel>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CustomTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


private:

    QList<QList<QString>> datas;
};

#endif // CUSTOMABSTRACTMODEL_H

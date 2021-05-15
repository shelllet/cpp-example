#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QStringListModel>

class CustomModel : public QStringListModel
{
    Q_OBJECT

public:
    explicit CustomModel(QObject *parent = nullptr);

    // Header:
   // QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    //int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // CUSTOMMODEL_H

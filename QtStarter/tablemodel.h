#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QJsonArray>

enum Column_Type {
    Column_Name,
    Column_Cmd,
    Column_Env
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
signals:
    void reported(const QString& message);

public:
    void save();
    void load();
    void add(const QString& name, const QString&cmd, const QString& env);
    void editCurrent(int row, const QString& name, const QString&cmd, const QString& env);
    void delCurrent(int row);
protected:
   static QString ModelFileName();
private:
    QJsonArray array_;
};

#endif // TABLEMODEL_H

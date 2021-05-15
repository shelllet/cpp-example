#include "tablemodel.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QDir>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


void TableModel::save()
{
    QFile file(ModelFileName());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        emit reported(file.errorString());
        return;
    }

    file.write(QJsonDocument(array_).toJson());
}

void TableModel::load()
{
    QFile file(ModelFileName());
    if (!file.exists())
        return;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        emit reported(file.errorString());
        return;
    }

    QJsonParseError error;

    auto document= QJsonDocument::fromJson(file.readAll(), &error);

    if (error.error != QJsonParseError::NoError){
        emit reported(error.errorString());
        return;
    }
    if (!document.isArray()){
        emit reported("Model root is not array");
        return;
    }

    array_ = document.array();
}

void TableModel::add(const QString &name, const QString &cmd, const QString& env)
{
    QJsonObject object = {
        {"name", name},
        {"cmd", cmd},
        {"env", env}
    };
    int row = array_.size();

    this->beginInsertRows(QModelIndex(), row, row);
    array_.push_back(object);

    this->setData(createIndex(row, Column_Name), name, Qt::DisplayRole);
    this->setData(createIndex(row, Column_Cmd), cmd, Qt::DisplayRole);
    this->setData(createIndex(row, Column_Env), env, Qt::DisplayRole);
    this->endInsertRows();
    this->save();
}

void TableModel::editCurrent(int row, const QString &name, const QString &cmd, const QString& env)
{
    array_[row] = QJsonObject {
    {"name", name},
    {"cmd", cmd},
    {"env", env}
};
    auto index1 = createIndex(row, Column_Name);
    auto index2 = createIndex(row, Column_Cmd);
    auto index3 = createIndex(row, Column_Env);

    this->setData(index1, name, Qt::DisplayRole);
    this->setData(index2, cmd, Qt::DisplayRole);
    this->setData(index3, env, Qt::DisplayRole);

    this->submit();
    this->save();
}

void TableModel::delCurrent(int row)
{
    this->beginRemoveRows(QModelIndex(), row, row);
    array_.removeAt(row);
    this->removeRow(row);
    this->endRemoveRows();
    this->save();
}

QString TableModel::ModelFileName()
{
    return QDir::cleanPath(QDir::homePath() + QDir::separator() + "shelllet.com" + QDir::separator() +"model.json");
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)

    if (section == 0 && role == Qt::DisplayRole){
        return "Name";
    }
    if (section == 1 && role == Qt::DisplayRole){
        return "Cmd";
    }
    if (section == 2 && role == Qt::DisplayRole){
        return "Env";
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return array_.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    int row = index.row();
    if (row >= array_.size()|| row < 0){
        return QVariant();
    }
    if (index.column() == Column_Name) {
        return array_[row].toObject().value("name").toString();
    } else if (index.column() == Column_Cmd) {
        return array_[row].toObject().value("cmd").toString();
    } else if (index.column() == Column_Env) {
        return array_[row].toObject().value("env").toString();
    }
    return QVariant();
}

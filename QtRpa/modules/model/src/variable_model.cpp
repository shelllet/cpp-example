#include "common.hpp"
#include <sstream>
#include "common/variable.h"
#include "model/variable_model.h"


shelllet::model::VariableModel::VariableModel(const YAML::Node& node, QObject* parent)
	: QAbstractTableModel(parent)
	, node_(node)
{
#ifdef _DEBUG
	std::ostringstream ss;
	ss << node;
	LOG_DEBUG("rpa") << "# variables: \n" << ss.str();
#endif // _DEBUG
}

shelllet::model::VariableModel::~VariableModel()
{
}

int shelllet::model::VariableModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return Columns::Count;
}

QVariant shelllet::model::VariableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		//Var var = node_[index.row()].as<Var>();

		switch (index.column()) {
		case Columns::Name:
		case Columns::Type:
		case Columns::Value:
		case Columns::Desc:
		{
			try
			{
				return QString::fromStdString(node_[index.row()][Var::keys[static_cast<Columns>(index.column())]].as<std::string>());
			}
			catch (const std::exception& err)
			{
				LOG_WARNING("rpa") << "# variables error: " << err.what();
			}
			break;
		}
		case Columns::Ref:
			try
			{
				return node_[index.row()][Var::keys[static_cast<Columns>(index.column())]].as<std::int32_t>();
			}
			catch (const std::exception&)
			{
				return 0;
			}
			break;
		default:
			break;
		}
	}
	return QVariant();
}

Qt::ItemFlags shelllet::model::VariableModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if (index.column() == Columns::Ref) {
		return QAbstractTableModel::flags(index);
	}
	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant shelllet::model::VariableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		switch (section) {
		case Columns::Name:
			return tr("Name");
		case Columns::Type:
			return tr("Type");
		case Columns::Value:
			return tr("Value");
		case Columns::Ref:
			return tr("Ref");
		case Columns::Desc:
			return tr("Desc");
		default:
			break;
		}
	}
	return QVariant();
}

int shelllet::model::VariableModel::rowCount(const QModelIndex& parent) const
{
	return node_.size();
}

YAML::Node shelllet::model::VariableModel::node() const
{
	return node_;
}

bool shelllet::model::VariableModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
	if (!index.isValid())
		return false;

	if (role == Qt::EditRole) {
		switch (index.column()) {
		case Columns::Name:
		case Columns::Type:
		case Columns::Value:
		case Columns::Desc:
		{
			node_[index.row()][Var::keys[static_cast<Columns>(index.column())]] = value.toString().toStdString();
			break;
		}
		default:
			break;
		}
#ifdef _DEBUG
		std::ostringstream ss;
		ss << node_;
		LOG_DEBUG("rpa") << "# variables: \n" << ss.str();
#endif // _DEBUG
		emit dataChanged(index, index, { Qt::DisplayRole });
		return true;
	}

	return false;
}

bool shelllet::model::VariableModel::insertRows(int row, int count, const QModelIndex& parent /*= QModelIndex()*/)
{
	std::string name = "name";

	if (rowCount() != 0) {
		name.append(std::to_string(rowCount()).c_str());
	}
	beginInsertRows(parent, row, row);
	node_.push_back(Var{ name, "Auto", "", 0, "" });
	endInsertRows();
	return true;
}

bool shelllet::model::VariableModel::removeRows(int row, int count, const QModelIndex& parent /*= QModelIndex()*/)
{
	beginRemoveRows(parent, row, row);

	node_.remove(node_[row]);

	endRemoveRows();

	return true;
}
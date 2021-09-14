#include "common.hpp"
#include <qmimedata.h>
#include "model/activities_search_model.h"
#include "model/activities_dom_item.h"
#include "qbuffer.h"
#include "model/xmlmimedata.h"



shelllet::model::ActivitiesDomModel::ActivitiesDomModel(const SharedPointer<XmlDocument>& doc, QObject* parent)
	: QAbstractItemModel(parent)
	, rootItem(new ActivitiesDomItem(doc->documentElement(), 0, 0))
{
}

shelllet::model::ActivitiesDomModel::~ActivitiesDomModel()
{
	delete rootItem;
}

int shelllet::model::ActivitiesDomModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 3;
}

QVariant shelllet::model::ActivitiesDomModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	const auto* item = static_cast<ActivitiesDomItem*>(index.internalPointer());

	if (index.column() == 0) {
		{
			if (role == Qt::DisplayRole) {

				return *item->node().attribute(ElementParser::get_const_instance().keyDisplay()).value().toQString();

			}
			else if (role == Qt::DecorationRole) {
				const auto icon_name = item->node().attribute(ElementParser::get_const_instance().keyDecoration()).value();
				if (auto name = item->node().parent().name(); name == ElementParser::get_const_instance().keySystem()) {
					return Environment::getInstance()->getIconByName(icon_name);
				}
				else {
					return Environment::getInstance()->iconMods((boost::format("%1%/%2% ") % name % icon_name).str());
				}
			}

		}
	}



	return QVariant();
}

Qt::ItemFlags shelllet::model::ActivitiesDomModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

	if (index.isValid())
		return Qt::ItemIsDragEnabled | defaultFlags;
	return defaultFlags;
}

QVariant shelllet::model::ActivitiesDomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		switch (section) {
		case 0:
			return tr("Name");
		default:
			break;
		}
	}
	return QVariant();
}

QModelIndex shelllet::model::ActivitiesDomModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	ActivitiesDomItem* parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<ActivitiesDomItem*>(parent.internalPointer());

	ActivitiesDomItem* childItem = parentItem->child(row);

	if (childItem) {
		QModelIndex index = createIndex(row, column, childItem);

		LOG_DEBUG("rpa") << "# child index: " << "(" << row << " - " << column << ")" << index.data(Qt::DisplayRole).toString();

		return index;
	}
	return QModelIndex();
}

QModelIndex shelllet::model::ActivitiesDomModel::parent(const QModelIndex& child) const
{
	if (!child.isValid())
		return QModelIndex();

	auto* childItem = static_cast<ActivitiesDomItem*>(child.internalPointer());
	auto* parentItem = childItem->parent();

	if (!parentItem || parentItem == rootItem)
		return QModelIndex();

	QModelIndex index = createIndex(parentItem->row(), 0, parentItem);


	return index;
}

int shelllet::model::ActivitiesDomModel::rowCount(const QModelIndex& parent) const
{
	//if (parent.column() > 0)
	//	return 0;

	ActivitiesDomItem* parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<ActivitiesDomItem*>(parent.internalPointer());

	const auto& children = parentItem->node().children();

	return std::distance(children.begin(), children.end());
}

QMimeData* shelllet::model::ActivitiesDomModel::mimeData(const QModelIndexList& indexes) const
{
	if (indexes.count() <= 0)
		return nullptr;

	//auto type = common::Environment::getInstance()->getOptions()->mime_data_type;
	auto* item = static_cast<ActivitiesDomItem*>(indexes[0].internalPointer());


	//XmlByteArrayWriter writer;
	//item->node().print(writer);

	//QMimeData* data = new XmlMimeData(item->node());

	//pugi::xml_document doc;
	//doc.append_copy(item->node());

	return new XmlMimeData(item->node());
	//data->setData(type, writer.result);
	//return data;
}
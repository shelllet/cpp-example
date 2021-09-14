#pragma once
#include <pugixml.hpp>
#include <qabstractitemmodel.h>
#include "common/serialization.h"

class QMimeData;
namespace shelllet {
	namespace model {
		class ActivitiesDomItem;
		class ActivitiesDomModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:
			explicit ActivitiesDomModel(const SharedPointer<XmlDocument>& doc, QObject* parent = nullptr);
			~ActivitiesDomModel();

			QVariant data(const QModelIndex& index, int role) const override;
			Qt::ItemFlags flags(const QModelIndex& index) const override;
			QVariant headerData(int section, Qt::Orientation orientation,
				int role = Qt::DisplayRole) const override;
			QModelIndex index(int row, int column,
				const QModelIndex& parent = QModelIndex()) const override;
			QModelIndex parent(const QModelIndex& child) const override;
			int rowCount(const QModelIndex& parent = QModelIndex()) const override;
			int columnCount(const QModelIndex& parent = QModelIndex()) const override;

			QMimeData* mimeData(const QModelIndexList& indexes) const override;

		private:
			ActivitiesDomItem* rootItem;
		};
	}
}

#pragma once
#include <yaml-cpp/yaml.h>
#include <QAbstractTableModel>

namespace shelllet {
	namespace model {
		class VariableModel : public QAbstractTableModel
		{
			Q_OBJECT

		public:

			explicit VariableModel(const YAML::Node& node, QObject* parent = nullptr);
			~VariableModel();

			QVariant data(const QModelIndex& index, int role) const override;
			Qt::ItemFlags flags(const QModelIndex& index) const override;
			QVariant headerData(int section, Qt::Orientation orientation,
				int role = Qt::DisplayRole) const override;

			int rowCount(const QModelIndex& parent = QModelIndex()) const override;
			int columnCount(const QModelIndex& parent = QModelIndex()) const override;

			YAML::Node node() const;

			bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

			bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

			bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

		private:

		private:
			YAML::Node node_;
		};
	}
}

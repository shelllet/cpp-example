#pragma once
#include <filesystem>
#include <QTableView>
#include <QToolBar>
#include <QItemDelegate>
#include "events/listener_manager.h"
#include "common/variable.h"
#include "common/serialization.h"
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "model.hpp"

namespace shelllet::creator {
	class VariableTableComponent : public QWidget, public common::Serialization
	{
		Q_OBJECT
	public:
		VariableTableComponent(QWidget* parent = nullptr);
		~VariableTableComponent();

		void create() override;

		void load(const Path& filename) override;

		void save(const Path& filename) override;

	protected:

	protected:
	private:

		class ComboBoxItemDelegate : public QItemDelegate {
		public:
			ComboBoxItemDelegate(QObject* parent = nullptr);
			QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
		};

	private slots:
		void addRow();
		void removeRow();

	private:
		QTableView* tableView_;
		QToolBar* toolbar_;
		VariableModel* model_;
	};
}

#pragma once
#include <filesystem>
#include <QTabWidget>
#include "common/serialization.h"
#include "activities_search_widget.h"

namespace shelllet::creator {
	class ViewPanel : public QTabWidget, public common::Serialization
	{
	public:
		ViewPanel(QWidget* parent = nullptr);
		~ViewPanel();

		void create() override;

		void load(const Path& filename) override;

		void openTab(const Path& filename);

		void save(const Path& filename) override;

		bool tabOpened(const QString& tab) const;
	protected:
		virtual void customEvent(QEvent* event) override;

	private:

		ActivitiesSearchWidget* searchWidget;
	};
}

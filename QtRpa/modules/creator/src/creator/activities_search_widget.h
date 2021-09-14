#pragma once
#include <qtreewidget.h>
#include "search_input_widget.h"
#include "search_view_widget.h"

namespace shelllet::creator {
	class ActivitiesSearchWidgetPrivate;
	class ActivitiesSearchWidget : public QWidget
	{
		Q_DECLARE_PRIVATE(ActivitiesSearchWidget)
	public:
		ActivitiesSearchWidget(QWidget* parent = nullptr);
		~ActivitiesSearchWidget();

	public slots:
		void itemDoubleClicked(const QModelIndex& index);

	protected:

	private:

	};
}

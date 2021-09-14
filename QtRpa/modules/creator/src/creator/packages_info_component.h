#pragma once
#include <qwidget.h>
#include <qtoolbox.h>
#include <qtreewidget.h>
#include "common/serialization.h"

namespace shelllet::creator {
	class PackagesInfoComponent : public QWidget
	{
	public:
		PackagesInfoComponent(QWidget* parent = nullptr);
		~PackagesInfoComponent();

	public:

		//void create(const juce::File& name);

	protected:

	private:

		QTreeWidget* treeWidget;
	};
}

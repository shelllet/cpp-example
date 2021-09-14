#pragma once
#include <filesystem>
#include <qwidget.h>
#include <qtoolbox.h>
#include "common/serialization.h"

namespace shelllet::creator {
	class LeftPanelPrivate;
	class LeftPanel : public QWidget, public common::Serialization
	{
		Q_DECLARE_PRIVATE(LeftPanel)
	public:
		LeftPanel(QWidget* parent = nullptr);
		~LeftPanel();

		void create() override;

		void load(const Path& filename) override;

		void save(const Path& filename) override;



	public:
		//void create(const juce::File& name);

	protected:
		QSize sizeHint() const override;

	private:

	};
}

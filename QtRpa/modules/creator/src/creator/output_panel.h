#pragma once
#include <filesystem>
#include <qtabwidget.h>
#include "events/listener_manager.h"
#include "common/serialization.h"

namespace shelllet::creator {
	class OutputPanel : public QTabWidget, public common::Serialization {
	public:
		OutputPanel(QWidget* parent = nullptr);
		~OutputPanel();

		void create() override;

		void load(const Path& filename) override;

		void save(const Path& filename) override;



	protected:
		QSize sizeHint() const override;

	private:
	};
}

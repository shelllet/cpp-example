#pragma once
#include <QListWidget>
#include "events/listener_manager.h"

namespace shelllet::creator {
	class OutputComponent : public QListWidget
	{
	public:
		OutputComponent(QWidget* parent = nullptr);
		~OutputComponent();

	protected:

		void customEvent(QEvent* event) override;

	protected:

	private:

	private:
	};
}

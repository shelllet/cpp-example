#pragma once
#include <qwidget.h>
#include <qlistview.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include "framework.h"

namespace shelllet {
	namespace wizard {
		class RencentComponentPrivate;
		class RencentComponent : public QWidget
		{
			Q_DECLARE_PRIVATE(RencentComponent)
		public:
			RencentComponent( QWidget* parent = nullptr);
			~RencentComponent();

		private:

		};
	}
}
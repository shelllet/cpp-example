#pragma once
#include "common.hpp"

namespace shelllet {
	namespace creator {
		class GuiApplicationPrivate;
		class GuiApplication : public Runnable, public Object
		{
			Q_DECLARE_PRIVATE(GuiApplication)
		public:
			GuiApplication();

			void run(QEvent* event) override;


			static GuiApplication* getInstance();
		};
	}
}
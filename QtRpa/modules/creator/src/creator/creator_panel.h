#pragma once
#include "creator.hpp"
#include "qmainwindow.h"

namespace shelllet {
	namespace creator {
		class HideBar;
		class CreatorPanel : public QMainWindow, public creator::Callback
			, private creator::New
			, private creator::Open
			, private creator::Save
			, private creator::Exec
			, private creator::About
		{
			static inline const int kHideBarNum = 3;
		public:
			CreatorPanel(QWidget* parent = nullptr);
			~CreatorPanel();

			void callbk(creator::CallbackMessage*, int num, ...) override;
		public:
			void git();
			void create();
			void open();
		protected:
			void exec();
		private:
			std::array<HideBar*, kHideBarNum> panel;
		};
	}
}

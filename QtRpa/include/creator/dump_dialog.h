#pragma once
#include "qdialog.h"
#include "boost/core/noncopyable.hpp"
namespace shelllet {
	class DumpDialogPrivate;
	namespace creator {
		class DumpDialog : public QDialog, private boost::noncopyable
		{
			Q_DECLARE_PRIVATE(DumpDialog)
		public:
			DumpDialog(QWidget* parent = nullptr);
			~DumpDialog();

		private:
		};
	}
}

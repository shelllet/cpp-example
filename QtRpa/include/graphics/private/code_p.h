#pragma once
#include "elementitem_p.h"
#include "qpushbutton.h"
#include "Qsci/qsciscintilla.h"
#include "qgraphicsproxywidget.h"
#include "Qsci/qscilexerpython.h"
#include "frameless.hpp"
namespace shelllet {
	namespace interpreter {
		class CodeDialog;
		class CodePrivate : public ElementPrivate {
			Q_DECLARE_PUBLIC(Code)

				inline interpreter::Code* pFunc()
			{
				return dynamic_cast<interpreter::Code*>(qGetPtrHelper(prop.get()));
			}

			inline const interpreter::Code* pFunc() const
			{
				return dynamic_cast<interpreter::Code*>(qGetPtrHelper(prop.get()));
			}

		public:

			void setupUi(Code* parent);

			QPushButton* button = nullptr;
			CodeDialog* dialog = nullptr;
			QGraphicsProxyWidget* proxy = nullptr;
			QsciLexerPython* lexer;
		};
	}
}

#pragma once
namespace shelllet {
	namespace interpreter {
		class PyScintillaPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(PyScintilla)
		public:
			UniquePointer<QsciScintilla>scintilla;
			UniquePointer<QGraphicsProxyWidget> proxyWidget;
		};
	}
}

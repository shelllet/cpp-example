#pragma once
#include "common.hpp"

#include "scintilla/scintilla_component.h"

namespace shelllet {
	namespace scintilla {

	
	class ScintillaPage : public scintilla_component
	{
	public:
		ScintillaPage( QWidget* parent = nullptr);
		ScintillaPage(const String& text, QWidget* parent = nullptr);
		~ScintillaPage();

	

	private:
	protected:
	};
}
}

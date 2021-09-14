#include "common.hpp"
//zip_entry::zip_entry(int titleBarHeight) :
//	m_titleBarHeight(titleBarHeight)
//{
//	//m_closeElement
//	//	= juce::parseXML(R"(
//	// <svg x="0" y="0" viewBox="0 0 10.2 10.2" data-radium="true" width="10" height="10">
//	//            <polygon fill="#000000" points="10.2,0.7 9.5,0 5.1,4.4 0.7,0 0,0.7 4.4,5.1 0,9.5 0.7,10.2 5.1,5.8 9.5,10.2 10.2,9.5 5.8,5.1"></polygon>
//	//          </svg>
//	//)");
//}

//juce::Button* nametls::core::LookAndFeel_V5::createDocumentWindowButton(int buttonType)
//{
	// if (buttonType == DocumentWindow::maximiseButton) {
	//   XmlElement * element = XmlDocument::parse(R"(
	 // <svg viewBox="0 0 10.2 10.1" data-radium="true" style="width: 10px; height: 10px;">
	 //            <path fill="#000000" d="M2.1,0v2H0v8.1h8.2v-2h2V0H2.1z M7.2,9.2H1.1V3h6.1V9.2z M9.2,7.1h-1V2H3.1V1h6.1V7.1z" />
	 //</svg>
	 //)");
	//   ;

	//   DrawableButton *button = new DrawableButton("msc", DrawableButton::ImageRaw);

	//   button->setImages(Drawable::createFromSVG(*element));

	//   delete element;

	//   return button;
	// }
	// else if (buttonType == DocumentWindow::minimiseButton) {
	//   XmlElement * element = XmlDocument::parse(R"(
	 //  <svg x="0px" y="0px" viewBox="0 0 10.2 1" data-radium="true" style="width: 10px; height: 10px;">
	 //            <rect fill="#000000" width="10.2" height="1"></rect>
	 //          </svg>
	 //)");
	//   ;

	//   DrawableButton *button = new DrawableButton("min", DrawableButton::ImageRaw);

	//   button->setImages(Drawable::createFromSVG(*element));

	//   delete element;

	//   return button;
	// }

//	return 0;
//}

//juce::Typeface::Ptr nametls::core::LookAndFeel_V5::getTypefaceForFont(const Font&font)
//{
//	juce::String locale = juce::SystemStats::getDisplayLanguage();
//
//	if (locale == "zh-CN") {
//		juce::Font f(font);
//		f.setTypefaceName("MSYH");
//		return juce::Typeface::createSystemTypefaceFor(f);
//	}
//
//	return __super::getTypefaceForFont(font);
//}

//void nametls::core::LookAndFeel_V5::drawDocumentWindowTitleBar(DocumentWindow&, Graphics&g, int, int, int, int, const Image*, bool)
//{
//  g.fillAll(Colour(222, 225, 230));
//}
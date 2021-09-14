#include "common.hpp"
#include "output_panel.h"
#include "output_component.h"
#include "variable_table_component.h"
#include "common/serialization.h"

//
	//tabbed.addTab("Output", juce::Colours::darkorchid, new OutputComponent, true);
////	tabbed.addTab("Variable", juce::Colours::darkorchid, new VariableTableComponent(vs, db), true);
	//addAndMakeVisible(tabbed);

shelllet::creator::OutputPanel::OutputPanel(QWidget* parent /*= nullptr*/)
	:QTabWidget(parent)
{
	addTab(new OutputComponent(), tr("Output"));
	addTab(new VariableTableComponent(), tr("Variable"));
}

shelllet::creator::OutputPanel::~OutputPanel()
{
}

void shelllet::creator::OutputPanel::create()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void shelllet::creator::OutputPanel::load(const Path& filename)
{
	for (auto i = 0; i < count(); ++i)
	{
		auto* w = dynamic_cast<common::Serialization*>(this->widget(i));
		if (w) {
			w->load(filename);
		}
	}
}

void shelllet::creator::OutputPanel::save(const Path& filename)
{
	for (int i = 0; i < count(); ++i)
	{
		auto* serial = dynamic_cast<common::Serialization*>(this->widget(i));

		if (serial) {
			serial->save(filename);
		}
	}
}

QSize shelllet::creator::OutputPanel::sizeHint() const
{
	auto size = __super::sizeHint();

	size.setHeight(size.height() * 0.6);

	return size;

}

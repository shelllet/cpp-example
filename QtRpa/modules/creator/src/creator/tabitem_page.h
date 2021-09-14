#pragma once
#include <filesystem>
#include <pugixml.hpp>
#include <qwidget.h>

#include <QStackedWidget>
#include <qtreewidget.h>
#include <qgraphicsscene.h>
#include <qgraphicsgridlayout.h>
#include "events/listener_manager.h"
#include "common/serialization.h"
#include "graphics_view.h"

namespace shelllet::creator {
	/*	struct Node {
			void operator()(juce::PropertySet* fallbackProperties) const
			{
				std::cout << "Hello, World!" << std::endl;
			}
		};*/
		//class SwitchPage {
		//public:
		//	virtual void switchView() = 0;
		//};
	class TabItemPage : public GraphicsView, public common::Serialization, public common::Property
	{
	public:
		TabItemPage(QWidget* parent = nullptr);
		~TabItemPage();

		void create() override;

		void load(const Path& filename) override;

		void save(const Path& filename) override;

		void add(const std::function<void(const std::string&, int64_t)>& f);

		//void setXml(const std::string& xml);
		//std::string getXml() const;

		std::filesystem::path relative() override;

	private:

	private:

		Path filename_;


	protected:
		void customEvent(QEvent* event) override;
	};
}

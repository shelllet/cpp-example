#pragma once
#include <qwidget.h>

namespace shelllet{
	namespace property { class PropertyBrowser; }
	namespace creator {
	class properties_component : public QWidget
	{
	public:
		properties_component(QWidget* parent = nullptr);
		~properties_component();



	public:
		//void updateProperty(const std::shared_ptr<properties::UniqueNamedProperty>& property);
		void variable_changed(int action, const std::string& old_name, const std::string& new_name);

	protected:

		QSize sizeHint() const override;
		virtual void customEvent(QEvent* event) override;
	private:
		//std::unique_ptr<activities::base::activity_property_component> display_;

		property::PropertyBrowser* browser_;
	};
}
}

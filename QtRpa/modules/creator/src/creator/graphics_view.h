#pragma once
#include <qwidget.h>
#include <qgraphicsview.h>
#include <qgraphicsscene.h>
#include "events/listener_manager.h"
#include "common/serialization.h"
#include "pugixml.hpp"
namespace shelllet {
	namespace creator {
		class DiagramScene;
		class DiagramItem;
	}
	namespace creator {
		/*	struct Node {
				void operator()(juce::PropertySet* fallbackProperties) const
				{
					std::cout << "Hello, World!" << std::endl;
				}
			};*/
		class GraphicsViewPrivate;
		class GraphicsView : public QGraphicsView
		{
			Q_DECLARE_PRIVATE(GraphicsView)
		public:
			GraphicsView(QWidget* parent = nullptr);
			~GraphicsView();

			std::unique_ptr<XmlDocument> getXml() const;
			void setXml(const XmlDocument& doc);
			QString getCode() const;

		protected:

			void mouseDoubleClickEvent(QMouseEvent* event) override;


			void mousePressEvent(QMouseEvent* event) override;

		};
	}
}

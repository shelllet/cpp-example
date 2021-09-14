#pragma once
#include "graphics/containeritem.h"
#include "common.hpp"
#include "properties.hpp"
#include "qgraphicswidget.h"
namespace shelllet {
	namespace interpreter {
		class SequencePrivate;
		class Sequence : public Container {
			Q_OBJECT
				Q_DECLARE_PRIVATE_D(Object::d_ptr, Sequence)
		public:
			//Q_INVOKABLE	Sequence(const std::shared_ptr<CompositeProperty>& property, QGraphicsItem* parent = nullptr);
		protected:


			//void resizeEvent(QGraphicsSceneResizeEvent* event) override;





		};
	}
}
Q_DECLARE_METATYPE(shelllet::interpreter::Sequence*)
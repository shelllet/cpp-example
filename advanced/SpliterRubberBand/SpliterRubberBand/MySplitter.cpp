#include "MySplitter.h"
#include <stdexcept>
#include "QMouseEvent"
MySplitter::MySplitter(QWidget* parent)
	: QSplitter(parent)
{

}/*

void MySplitter::mousePressEvent(QMouseEvent* event)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void MySplitter::mouseReleaseEvent(QMouseEvent* event)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void MySplitter::mouseMoveEvent(QMouseEvent* event)
{
	throw std::logic_error("The method or operation is not implemented.");
}*/

QSplitterHandle* MySplitter::createHandle()
{
	return new MySplitterHandle(this);
}

MySplitter::MySplitterHandle::MySplitterHandle(QSplitter* parent)
	: QSplitterHandle(Qt::Horizontal, parent)
{

}



void MySplitter::MySplitterHandle::mouseReleaseEvent(QMouseEvent* event)
{
	splitter()->setRubberBand(-1);

	//auto* p = parentWidget();

	auto pos =parentWidget()->mapFromGlobal(event->globalPos());
	
	moveSplitter(closestLegalPosition( pos.x()));
}

void MySplitter::MySplitterHandle::mouseMoveEvent(QMouseEvent* event)
{
	auto pos = parentWidget()->mapFromGlobal(event->globalPos());

	splitter()->setRubberBand(closestLegalPosition(pos.x()));
}

MySplitter* MySplitter::MySplitterHandle::splitter()
{
	return dynamic_cast<MySplitter*>(__super::splitter());
}

#include "RubberBand.h"
#include "QMouseEvent"
RubberBand::RubberBand(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


}

void RubberBand::mousePressEvent(QMouseEvent* event)
{
	origin_ = event->pos();
	if (!rubberBand_)
		rubberBand_ = new QRubberBand(QRubberBand::Rectangle, this);
	rubberBand_->setGeometry(QRect(origin_, QSize()));
	rubberBand_->show();
}

void RubberBand::mouseReleaseEvent(QMouseEvent* event)
{
	rubberBand_->hide();
}

void RubberBand::mouseMoveEvent(QMouseEvent* event)
{
	rubberBand_->setGeometry(QRect(origin_, event->pos()).normalized());
}

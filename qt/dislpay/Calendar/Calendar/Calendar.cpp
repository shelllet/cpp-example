#include "Calendar.h"

Calendar::Calendar(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.calendarWidget, &QCalendarWidget::clicked, [this](auto& date) {
        ui.lineEdit->setText(date.toString());
        });
}

#include "wizarddialog.h"
#include <QtWidgets/QApplication>
#include "QWizard"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "qdebug.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // wizarddialog w;
   // w.show();

    QWizard wizard;
    QPixmap pixmap = QPixmap(":/wizarddialog/222");
   // QPixmap pixmap = QPixmap(":/wizarddialog/233");
   // pixmap.scaled({ 200, 400 });
    qDebug() << pixmap.size();
    assert(!pixmap.isNull());
    wizard.setWizardStyle(QWizard::ClassicStyle);
    wizard.setPixmap(QWizard::WatermarkPixmap, pixmap.scaled({ 200, 400 }));
    wizard.addPage(new Page1);
    wizard.addPage(new Page2);
    wizard.addPage(new Page3);
    wizard.show();
    return a.exec();
}

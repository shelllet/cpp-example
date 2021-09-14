#include "wizard/recent_component.h"
#include "wizard/framework.h"
#include "private/qwidget_p.h"
#include "qpushbutton.h"
#include "qdebug.h"
namespace shelllet {
	namespace wizard {
		class Ui_RencentComponent {
		public:
			QLabel* label;
			QListView* listView;
			QVBoxLayout* layout;
			QPushButton *button;
			void setupUi(QWidget* parent) {
				layout = new QVBoxLayout(parent);

				label = new QLabel(parent);
				label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
				layout->addWidget(label);

				listView = new QListView(parent);
				listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
				layout->addWidget(listView);

				button = new QPushButton(parent);

				layout->addWidget(button);

				QObject::connect(button, &QPushButton::clicked, [this]() {
					qDebug() << listView->minimumHeight();
					qDebug() << listView->sizeHint();
					qDebug() << listView->geometry();
					});
			}
		};
		class RencentComponentPrivate : public QWidgetPrivate {
		public:
			Ui_RencentComponent ui;
		};
	}
}
shelllet::wizard::RencentComponent::RencentComponent( QWidget* parent)
	: QWidget(*new RencentComponentPrivate, parent, {})
{
	Q_D(RencentComponent);

	d->ui.setupUi(this);

	d->ui.label->setText(tr("Open Recent"));
}

shelllet::wizard::RencentComponent::~RencentComponent()
{
}
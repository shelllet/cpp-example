#include "ProgressDialog.h"
#include "qprogressdialog.h"
#include "qthread.h"
#include "qdebug.h"

class Thread : public QThread {
	Q_OBJECT
public:
	Thread(QObject* parent) : QThread(parent) {}

signals:

	void reportNumberValue(int n);

protected:
	void run() override
	{
		num = 0;
		while (!isInterruptionRequested()) {
			num++;
			emit reportNumberValue(num);

			if (num == 100) {
				break;
			}

			QThread::msleep(100);
		}

		qDebug() << " thread exit.";
	}

private:
	int num = 0;
};

ProgressDialog::ProgressDialog(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Thread* thread = new Thread(this);

	connect(ui.pushButton, &QPushButton::clicked, [this, thread]() {
		thread->start();
		QProgressDialog dialog("task", "cancel", 0, 100);
		dialog.setAutoClose(true);

		connect(thread, &Thread::reportNumberValue,  [&dialog](int num) {
			//QMetaObject::invokeMethod(&dialog, "setValue", Q_ARG(int, num));
			QMetaObject::invokeMethod(&dialog, "setValue", Qt::BlockingQueuedConnection, Q_ARG(int, num));
			});

		connect(&dialog, &QProgressDialog::canceled, [thread]() {
			thread->requestInterruption();
			});

		dialog.exec();

		qDebug() << "dialog finished";
		});

	
}

#include "ProgressDialog.moc"


//#include "moc_ProgressDialog.cpp"
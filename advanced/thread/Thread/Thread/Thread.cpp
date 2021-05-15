#include "Thread.h"
#include <QThread>
#include <QFile>
#include <QDebug>
#include "WorkerThread.h"


Thread::Thread(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &Thread::save);
	connect(ui.pushButton_set, &QPushButton::clicked, this, &Thread::set);
	connect(ui.pushButton_test, &QPushButton::clicked, this, &Thread::test);
	connect(ui.pushButton_main, &QPushButton::clicked, this, &Thread::mainTest);
	connect(ui.pushButton_move, &QPushButton::clicked, this, &Thread::moveToThread);

	file.open(QIODevice::WriteOnly);
}

void Thread::save()
{
	qDebug() << "Main thread ID: " << QThread::currentThreadId();

	auto* thread = QThread::create([this]() {	
		//mutex.lock();
		//QMutexLocker locker(&mutex);
		locker.lockForWrite();
		if (file.write(ui.lineEdit->text().toUtf8()) > 0) {
			qDebug() << "write ok";
		}
		else {
			qDebug() << "write failed";
		}
		//mutex.unlock();
		locker.unlock();
		qDebug() << "THREAD ID: " << QThread::currentThreadId();
		QThread::sleep(3);
		});

	thread->start();
}

void Thread::set()
{
	QThread::create([this](Thread* thread) {
		for (;;)
		{
			save();
		}

		//QFile file("./setting.txt");
		//file.open(QIODevice::ReadOnly);
		//thread->ui.lineEdit->setText(file.readAll());
		}, this)->start();


	
}

void Thread::test()
{
	//WorkerThread* thread = new WorkerThread(this, this);

	//thread->start();
	file.close();
}

void Thread::mainTest()
{
	WorkerThread* thread = new WorkerThread(this, this);
	thread->run();
}


void Thread::moveToThread()
{
	Worker* worker = new Worker(this, nullptr);

	QThread* thread = new QThread(this);

	worker->moveToThread(thread);

	connect(thread, &QThread::started, worker, &Worker::run);
	connect(worker, &Worker::finished, thread, &QThread::quit);
	connect(thread, &QThread::finished, [=]() {
		thread->deleteLater();
		worker->deleteLater();
		});

	thread->start();

}

QString Thread::text() const
{
	return ui.lineEdit->text();
}

#include "WorkerThread.h"
#include <QtDebug>
WorkerThread::WorkerThread(Thread* thread, QObject *parent)
	: QThread(parent)
	, thread(thread)
{

}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::run()
{
	qDebug() << thread->text();

	sleep(10);

	qDebug() << "exit...";
}

Worker::Worker(Thread* thread, QObject* parent)
	: QObject(parent)
	, thread(thread)
{

}

Worker::~Worker()
{
	qDebug() << "~ worker deleted..";
}

void Worker::run()
{
	qDebug() << thread->text();

	QThread::sleep(10);

	qDebug() << "exit...";
	emit finished();
}

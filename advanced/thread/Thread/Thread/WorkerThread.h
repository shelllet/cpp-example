#pragma once

#include <QThread>
#include "Thread.h"
class WorkerThread : public QThread
{
	Q_OBJECT

public:
	WorkerThread(Thread* thread, QObject *parent);
	~WorkerThread();
public:
	void run() override;

private:
	Thread* thread;
};


class Worker : public QObject
{
	Q_OBJECT

public:
	Worker(Thread* thread, QObject* parent);
	~Worker();
public:
	void run();
signals:
	void finished();
private:
	Thread* thread;
};



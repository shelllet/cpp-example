#pragma once


#include <QThread>

typedef QList<QPair<QString, QString>> ListEnvironment;

class WorkerThread : public QThread {
	Q_OBJECT
public:
	WorkerThread(const QString& src, QObject* object = nullptr);

protected:
	void run();
signals:
	void reported(const QString& info);
private:
	QString program_;
	QString source_dir_;
};

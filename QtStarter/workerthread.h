#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>

typedef QList<QPair<QString, QString>> ListEnvironment;

class WorkerThread : public QThread {
    Q_OBJECT
public:
    WorkerThread(const QString& name, const QString& cmd, const ListEnvironment& env);
    static ListEnvironment StringToListEnvironment(const QString &text);
    static QString ListEnvironmentToString(const ListEnvironment &env);
protected:
    void run();
signals:
    void reported(const QString &info);
private:
    QString name_;
    QString cmd_;
    ListEnvironment env_;
};


#endif // WORKERTHREAD_H

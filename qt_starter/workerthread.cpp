#include "workerthread.h"
#include <QProcess>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include "setting.h"

WorkerThread::WorkerThread(const QString &name, const QString &cmd, const ListEnvironment &env)
    : name_(name)
    , cmd_(cmd)
    , env_(env){

}

ListEnvironment WorkerThread::StringToListEnvironment(const QString &text)
{
    ListEnvironment environment;
    QStringList list = text.split("\n");
    for (const auto &row: list) {
        QStringList keyValue = row.split("=");
        if(keyValue.isEmpty())
            continue;

        environment.push_back(qMakePair(keyValue.first(), keyValue.last()));
    }
    return environment;
}

QString WorkerThread::ListEnvironmentToString(const ListEnvironment &env)
{
    QStringList list;
    for (const auto& e: env){
        list.append(e.first + "=" + e.second);
    }
    return list.join("\n");
}

void WorkerThread::run() {
    QProcess process;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    for(const auto& e: env_){
        env.insert(e.first, e.second);
    }
    process.setProcessEnvironment(env);

    connect(&process, &QProcess::readyReadStandardError, [&](){
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        emit reported(QString("[%1]: %2").arg(name_).arg( codec->toUnicode( process.readAllStandardError())));
    });

    connect(&process, &QProcess::readyReadStandardOutput, [&](){
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString output = codec->toUnicode(process.readAllStandardOutput());
        emit reported(QString("[%1]: %2").arg(name_).arg(output));
    });

    connect(&process, &QProcess::errorOccurred, [&](QProcess::ProcessError error){
        if (error == QProcess::FailedToStart){
            emit reported(QString("[%1]: %2").arg(name_).arg("failed to start"));
        } else if (error == QProcess::Crashed){
            emit reported(QString("[%1]: %2").arg(name_).arg("crash"));
        } else if (error == QProcess::Timedout){
            emit reported(QString("[%1]: %2").arg(name_).arg("timeout"));
        } else if (error == QProcess::ReadError){
            emit reported(QString("[%1]: %2").arg(name_).arg("read error"));
        } else {
            emit reported(QString("[%1]: %2").arg(name_).arg("unknown error"));
        }

    });

    connect(&process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [&](int, QProcess::ExitStatus exitStatus){
        emit reported(QString("[%1]: %2 %3").arg(name_).arg(" exit with").arg(exitStatus));
    });


    QJsonParseError error;
    auto document = QJsonDocument::fromJson(cmd_.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError){
        emit reported(error.errorString());
        return;
    }
    QStringList params;
    auto array = document.array();
    for (int i= 0; i < array.size(); i++){
        auto p = array[i].toString().trimmed();
        params.push_back(p.replace('\\', "\\\\"));
    }

    auto filename = Setting::LetPath();
    auto dir = QFileInfo(filename).absoluteDir().absolutePath();
    process.setWorkingDirectory(dir);

    process.start(filename, params);
    process.waitForFinished(-1);
}

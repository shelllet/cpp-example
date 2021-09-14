#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QProcess>
#include <QtDebug>
#include <QJSEngine>
#include "setting.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::home().mkpath("shelllet.com");

    QProcess process;

    auto filename = Setting::LetPath();
    auto dir = QFileInfo(filename).absoluteDir().absolutePath();
    process.setWorkingDirectory(dir);
    QStringList params;
    params << "run";
    params << qApp->applicationDirPath() + QDir::separator() + "assets" + QDir::separator() + "scripts" + QDir::separator() + "check_process.js";
    process.start(filename, params);

    if (process.waitForFinished()) {
        QByteArray result = process.readAllStandardError();
        QJSEngine myEngine;
        QJSValue three = myEngine.evaluate(QString(result));

        if (three.isBool() && three.toBool()){
            return 0;
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}

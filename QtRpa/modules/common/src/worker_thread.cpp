#include "common.hpp"

#include <QProcess>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include "events/message_output_event.h"

WorkerThread::WorkerThread(const QString& src, QObject* object)
	: QThread(object)
	, source_dir_(src)
{
}

void WorkerThread::run() {
}
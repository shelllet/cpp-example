#include "common/framework.h"
#include "common/logs.h"
#include "common/custom_output_backend.h"
#include "qdebug.h"
void shelllet::common::custom_output_backend::ReceiveLogMessage(g3::LogMessageMover logEntry)
{
	qDebug().noquote() << QString::fromStdString(logEntry.get().toString());
}

void shelllet::common::StdOutBackend::ReceiveLogMessage(g3::LogMessageMover logEntry)
{
	std::cout << logEntry.get().toString() << std::endl;
}

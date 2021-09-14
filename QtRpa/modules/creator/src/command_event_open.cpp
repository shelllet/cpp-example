#include "common.hpp"
#include "creator.hpp"

#include "qwidget.h"
#include <qstring.h>
#include <qfiledialog.h>
#include <yaml-cpp/yaml.h>

void shelllet::creator::Open::messageCallback(Callback* call)
{
	auto* parent = dynamic_cast<QWidget*>(call);
	//auto fmt = boost::format("%1% (*%2%)") % QObject::tr("Project File").toStdString() % common::Environment::getInstance()->getOptions()->pkg_extension.toStdString();
	QString fileName = QFileDialog::getExistingDirectory(parent, QObject::tr("Open File"), QString::fromStdString(common::Environment::getInstance()->storagePath().string()),
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

	if (!fileName.isEmpty())
	{
		Path fullName = String::fromQString(&fileName);

		call->callbk(this, 1, fullName);
	}
}
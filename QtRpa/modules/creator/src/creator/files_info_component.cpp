#include "common.hpp"
#include <QCoreApplication>
#include <qboxlayout.h>
#include <QFileSystemModel>
#include <libzippp/libzippp.h>
#include "files_info_component.h"
#include "events/file_browser_event.h"
#include "events/common_event.h"
#include "private/qwidget_p.h"
#include "qmenu.h"
#include "qdesktopservices.h"
#include "qurl.h"
namespace shelllet {
	enum Role
	{
		FileType = Qt::UserRole + 1
	};
	const int index_column = 0;

	namespace creator {

		class FilesInfoComponentPrivate : public QWidgetPrivate {
		public:
			QTreeWidget* treeWidget = new QTreeWidget;
			QTreeWidgetItem* src_;
			QTreeWidgetItem* res_;

			std::filesystem::path currentPath_;

			QVBoxLayout* layout;

			QMenu* menu;

			QAction* openFolder = nullptr;
		};
	}

}
shelllet::creator::FilesInfoComponent::FilesInfoComponent(QWidget* parent)
	: FilesInfoComponent(*new FilesInfoComponentPrivate, parent)
{

}

shelllet::creator::FilesInfoComponent::FilesInfoComponent(FilesInfoComponentPrivate& d, QWidget* parent /*= nullptr*/)
	: QWidget(d, parent, Qt::WindowFlags())
{
	d.src_ = new QTreeWidgetItem({ tr("src") });
	d.res_ = new QTreeWidgetItem({ tr("res") });
	d.layout = new QVBoxLayout(this);

	d.menu = new QMenu(d.treeWidget);
	d.layout->setContentsMargins({ 0, 0, 0, 0 });

	d.treeWidget->addTopLevelItem(d.src_);
	d.treeWidget->addTopLevelItem(d.res_);

	d.layout->addWidget(d.treeWidget);

	connect(d.treeWidget, &QTreeWidget::itemDoubleClicked, this, &FilesInfoComponent::itemDoubleClicked);

	d.treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
	d.openFolder = new QAction(tr("Open Folder"));

	d.treeWidget->addAction(d.openFolder);
	connect(d.openFolder, &QAction::triggered, this, &FilesInfoComponent::openProjectFolder);
}

shelllet::creator::FilesInfoComponent::~FilesInfoComponent()
{
}

void shelllet::creator::FilesInfoComponent::create()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void shelllet::creator::FilesInfoComponent::load(const Path& filename)
{
	Q_D(FilesInfoComponent);

	libzippp::ZipArchive zf(Environment::getInstance()->getCurrentProjectPath().toString().toStdString());
	zf.open(libzippp::ZipArchive::ReadOnly);

	for (auto& entry : zf.getEntries()) {
		if (entry.isFile() && entry.getName().starts_with(common::Environment::getInstance()->getPkgSrcName().toStdString())) {
			auto* item = new QTreeWidgetItem({ QString::fromStdString(entry.getName()) });
			item->setData(index_column, Role::FileType, QString::fromStdString(entry.getName()));
			d->src_->addChild(item);
		}
		else if (entry.isFile() && entry.getName().starts_with(common::Environment::getInstance()->getOptions()->pkg_res.toStdString())) {
			auto* item = new QTreeWidgetItem({ QString::fromStdString(entry.getName()) });
			item->setData(index_column, Role::FileType, QString::fromStdString(entry.getName()));
			d->res_->addChild(item);
		}
		else if (entry.isFile()) {
			auto* item = new QTreeWidgetItem({ QString::fromStdString(entry.getName()) });
			item->setData(index_column, Role::FileType, QString::fromStdString(entry.getName()));
			d->treeWidget->addTopLevelItem(item);
		}
	}

	d->treeWidget->expandAll();
}

void shelllet::creator::FilesInfoComponent::save(const Path& filename)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void shelllet::creator::FilesInfoComponent::itemDoubleClicked(QTreeWidgetItem* item, int column)
{
	QVariant variant = item->data(index_column, Role::FileType);
	if (variant.isValid())
	{
		QString filename = variant.toString();
		QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::FileBrowserEvent(filename.toStdString(), filename.toStdString()));
	}
}

void shelllet::creator::FilesInfoComponent::openProjectFolder()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(*Environment::getInstance()->getCurrentProjectPath().toString().toQString()));
}

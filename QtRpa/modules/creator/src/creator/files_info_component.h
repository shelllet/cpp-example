#pragma once
#include <filesystem>
#include <qwidget.h>
#include <QTreeView>
#include <qtoolbox.h>
#include <qtreewidget.h>
#include "common/serialization.h"
namespace shelllet {
	class FileSystemModel;
	namespace creator{
		class FilesInfoComponentPrivate;
		class FilesInfoComponent : public QWidget, public common::Serialization
		{
			Q_DECLARE_PRIVATE(FilesInfoComponent)
		public:
			FilesInfoComponent(QWidget* parent = nullptr);
			~FilesInfoComponent();

			void create() override;

			void load(const Path& filename) override;

			void save(const Path& filename) override;

		private slots:

			void itemDoubleClicked(QTreeWidgetItem* item, int column);
			void openProjectFolder();
		protected:
			FilesInfoComponent(FilesInfoComponentPrivate& d, QWidget* parent = nullptr);
		private:
			
		};
	}
}

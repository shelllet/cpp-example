#include "creator.hpp"
#include "common.hpp"
#include "creator/dump_dialog.h"
#include "qlabel.h"
#include "qtablewidget.h"
#include "qboxlayout.h"
#include "qdialogbuttonbox.h"
#include "qpushbutton.h"
#include "qdesktopservices.h"
#include "client/windows/sender/crash_report_sender.h"
#include "private/qdialog_p.h"
namespace shelllet {
	static const wchar_t* kDmpFileExtension = L".dmp";
	using namespace creator;

	class DumpDialogPrivate : public QDialogPrivate {
		Q_DECLARE_PUBLIC(DumpDialog)
	public:
		QLabel* label;
		QTableWidget* tableWidget;
		QDialogButtonBox* buttonBox;
	};
}
shelllet::creator::DumpDialog::DumpDialog(QWidget* parent /*= nullptr*/)
	: QDialog(*new DumpDialogPrivate, parent)
{
	setLayout(new QVBoxLayout);

	Q_D(DumpDialog);

	d->label = new QLabel("The file has been successfully created.\n", this);

	layout()->addWidget(d->label);

	{
		d->tableWidget = new QTableWidget(0, 3, this);
		d->tableWidget->setHorizontalHeaderLabels({ tr("Filename"), tr("Date time"), tr("Size") });
		d->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
		d->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
		d->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		d->tableWidget->setSortingEnabled(false);
		for (auto& it : std::filesystem::directory_iterator(common::Environment::getInstance()->dumpPath()))
		{
			if (!it.is_regular_file())
				continue;

			auto& temp = it.path();

			if (temp.extension().wstring() != kDmpFileExtension) {
				continue;
			}

			auto* item = new QTableWidgetItem(QString::fromStdString(temp.filename().string()));
			item->setFlags(Qt::ItemFlag::ItemIsUserCheckable | Qt::ItemFlag::ItemIsEnabled);
			item->setCheckState(Qt::Unchecked);
			d->tableWidget->insertRow(d->tableWidget->rowCount());

			int row = d->tableWidget->rowCount() - 1;
			d->tableWidget->setItem(row, 0, item);

			time_t t = std::chrono::duration_cast<std::chrono::seconds>(it.last_write_time().time_since_epoch() - 11644473600s).count();
			std::stringstream buf;
			buf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");

			d->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(buf.str())));

			item = new QTableWidgetItem(QString::fromStdString(std::to_string(static_cast<int>(std::ceil(it.file_size() * 1.0 / 1024))) + "KB"));
			item->setTextAlignment(Qt::AlignRight);
			d->tableWidget->setItem(row, 2, item);
		}
		d->tableWidget->setSortingEnabled(true);
		d->tableWidget->resizeColumnsToContents();

		layout()->addWidget(d->tableWidget);
	}


	{

		d->buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Reset | QDialogButtonBox::StandardButton::Ok, this);
		d->buttonBox->button(QDialogButtonBox::Reset)->setText(tr("Browser"));
		connect(d->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, [this](bool) {
			QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(common::Environment::getInstance()->dumpPath().string())));
			});

		d->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Upload"));
		connect(d->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, [d](bool) {
			google_breakpad::CrashReportSender sender(L"crash.checkpoint");
			std::map<std::wstring, std::wstring> files;
			std::map<std::wstring, std::wstring> custom_data;
			for (int i = 0; i < d->tableWidget->rowCount(); ++i)
			{
				auto* item = d->tableWidget->item(i, 0);
				if (item->checkState() == Qt::Checked)
				{
					std::wstring filename = common::Environment::getInstance()->dumpPath().wstring();
					filename += L"\\";
					filename += item->text().toStdWString();

					files.insert(std::make_pair(filename, filename));
				}
			}

			if (!files.empty()) {
				google_breakpad::ReportResult res = sender.SendCrashReport(common::Environment::getInstance()->getOptions()->dump_remote.toStdWString(), custom_data, files, 0);
				LOG_INFO("rpa") << "# upload result: " << (res == google_breakpad::RESULT_SUCCEEDED) << std::endl;
			}

			d->q_func()->accept();
			});

		layout()->addWidget(d->buttonBox);
	}

	setFixedSize(600, 420);
}

shelllet::creator::DumpDialog::~DumpDialog()
{
	LOG_DEBUG("rpa") << "# dump dialog exit." << std::endl;
}
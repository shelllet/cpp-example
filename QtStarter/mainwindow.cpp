#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "workerthread.h"
#include "setting.h"
#include <qt_windows.h>
#include <QtDebug>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	tray_(QIcon(":/new/app/favicon.png"))
{
	ui->setupUi(this);

	connect(&tableModel_, &TableModel::reported, this, &MainWindow::on_Reported);

	ui->tableView->setModel(&tableModel_);

	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	ui->tableView->setColumnWidth(Column_Name, 120);
	ui->tableView->setColumnWidth(Column_Cmd, 380);
	tableModel_.load();

	connect(&tray_, &QSystemTrayIcon::activated, this, &MainWindow::on_IconActivated);
	tray_.show();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_action_new_triggered()
{
	std::unique_ptr<Dialog> dialog = std::make_unique<Dialog>("", "[]", ListEnvironment(), MODE_CREATE, this);

	connect(dialog.get(), &Dialog::created, this, &MainWindow::on_Created);
	dialog->setModal(true);

	dialog->exec();
}

void MainWindow::on_action_edit_triggered()
{
	if (ui->tableView->selectionModel()->hasSelection()) {
		auto indexes = ui->tableView->selectionModel()->selectedRows();

		auto model = ui->tableView->selectionModel()->model();

		auto name = model->data(indexes[0]).toString();
		auto cmd = model->data(model->index(indexes[0].row(), Column_Cmd)).toString();
		auto env = model->data(model->index(indexes[0].row(), Column_Env)).toString();

		std::unique_ptr<Dialog> dialog = std::make_unique<Dialog>(name, cmd, WorkerThread::StringToListEnvironment(env), MODE_EDIT, this);

		connect(dialog.get(), &Dialog::edited, this, &MainWindow::on_Edited);
		dialog->setModal(true);

		dialog->exec();
	}
}

void MainWindow::on_Created(const QString& name, const QString& cmd, const ListEnvironment& env)
{
	tableModel_.add(name, cmd, WorkerThread::ListEnvironmentToString(env));
}

void MainWindow::on_Edited(const QString& name, const QString& cmd, const ListEnvironment& env)
{
	if (ui->tableView->selectionModel()->hasSelection()) {
		auto indexes = ui->tableView->selectionModel()->selectedRows();
		tableModel_.editCurrent(indexes[0].row(), name, cmd, WorkerThread::ListEnvironmentToString(env));
	}
}

void MainWindow::on_Reported(const QString& message)
{
	ui->plainTextEdit->appendPlainText(message);
}

void MainWindow::on_action_del_triggered()
{
	if (ui->tableView->selectionModel()->hasSelection()) {
		auto indexes = ui->tableView->selectionModel()->selectedRows();
		tableModel_.delCurrent(indexes[0].row());
	}
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex& index)
{
	auto model = ui->tableView->model();
	auto name = model->data(model->index(index.row(), Column_Name)).toString();
	auto cmd = model->data(model->index(index.row(), Column_Cmd)).toString();
	auto env = model->data(model->index(index.row(), Column_Env)).toString();

	WorkerThread* workerThread = new WorkerThread(name, cmd, WorkerThread::StringToListEnvironment(env));

	connect(workerThread, SIGNAL(reported(const QString&)), ui->plainTextEdit, SLOT(appendPlainText(const QString&)));

	connect(workerThread, &WorkerThread::finished, workerThread, &WorkerThread::deleteLater);

	workerThread->start();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	hide();
	tray_.showMessage("Tips", "I'm here.");
	event->ignore();
}

bool MainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	if (eventType == "windows_generic_MSG") {
		MSG* msg = static_cast<MSG*>(message);
		if (msg->message == WM_SHOWWINDOW && msg->wParam == TRUE) {
			show();
		}
	}

	return QMainWindow::nativeEvent(eventType, message, result);
}

void MainWindow::on_action_quit_triggered()
{
	qApp->exit();
}

void MainWindow::on_IconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		setWindowState(Qt::WindowActive);
		showNormal();
		break;
	case QSystemTrayIcon::MiddleClick:
	case QSystemTrayIcon::Context:
		qApp->exit();
		break;
	default:
		;
	}
}

void MainWindow::on_action_setting_triggered()
{
	std::unique_ptr<Setting> dialog = std::make_unique<Setting>();
	dialog->setModal(true);
	dialog->exec();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actiontile_triggered()
{

    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actioncascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();

}

void MainWindow::on_actionnext_triggered()
{

    ui->mdiArea->activateNextSubWindow();
}

void MainWindow::on_actionprev_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::on_actiondont_max_triggered()
{
    ui->mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, true);
}

void MainWindow::on_actionno_system_menu_triggered()
{
    ui->mdiArea->currentSubWindow()->setSystemMenu(nullptr);
}

void MainWindow::on_actionshaded_triggered()
{
    ui->mdiArea->currentSubWindow()->showShaded();
}

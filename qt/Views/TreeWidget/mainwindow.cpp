#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto * p1 = new QTreeWidgetItem({"a", "b", "c"});


    p1->addChild(new QTreeWidgetItem({"a"}));


    ui->treeWidget->addTopLevelItems({ p1, new QTreeWidgetItem({"a", "b", "c"})});

    auto * item = ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount() - 1);

    auto *child = new QTreeWidgetItem();
    child->setText(0, "child");
    item->addChild(child);

    ui->treeWidget->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}


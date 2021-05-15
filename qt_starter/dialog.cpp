#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(const QString &name, const QString &cmd, const ListEnvironment &env, Mode mode, QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint),
    ui(new Ui::Dialog),
    mode_(mode)
{
    ui->setupUi(this);

    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(cmd);
    for (const auto& e: env) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(e.first));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(e.second));
    }
    setWindowTitle(mode == MODE_CREATE ? "Create": "Edit");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    if (ui->lineEdit->text().trimmed().isEmpty()){
        return;
    }
    ListEnvironment list;

    for(int i =0; i < ui->tableWidget->rowCount(); i++){
        auto item =  ui->tableWidget->item(i, 0);
        if (!item)
            continue;

        QString name = item->text().trimmed();
        if (name.isEmpty())
            continue;
        item = ui->tableWidget->item(i, 1);
        if (!item)
            continue;

        QString value = item->text().trimmed();
        list.push_back(qMakePair(name, value));
    }
    if (mode_ == MODE_EDIT){
        emit edited(ui->lineEdit->text(), ui->lineEdit_2->text(), list);
    } else if (mode_ == MODE_CREATE){
        emit created(ui->lineEdit->text(), ui->lineEdit_2->text(), list);
    }
}

void Dialog::on_buttonBox_rejected()
{
    this->close();
}

void Dialog::on_toolButton_Add_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void Dialog::on_toolButton_Del_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

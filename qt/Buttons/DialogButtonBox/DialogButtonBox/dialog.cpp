#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPushButton* btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    btn->setText(QStringLiteral("确定"));

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(QStringLiteral("取消"));
}

Dialog::~Dialog()
{
    delete ui;
}

Dialog::Option Dialog::getOption() const
{
    return option_;
}

void Dialog::on_buttonBox_accepted()
{
    option_.math = ui->checkBox_math->isChecked();
    option_.chinese = ui->checkBox_chi->isChecked();
    option_.english = ui->checkBox_eng->isChecked();

    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

#include "setting.h"
#include "ui_setting.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QSettings>

Setting::Setting(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    ui->lineEdit->setText(LetPath());
}

Setting::~Setting()
{
    delete ui;
}

QString Setting::LetPath()
{
    QSettings settings("shelllet.com", "shelllet");

    auto filename = settings.value("let").toString();
    if (filename.isEmpty()){
        filename = QStandardPaths::findExecutable("let.exe", QStringList{ qApp->applicationDirPath() });
        if (filename.isEmpty()){
            filename = QStandardPaths::findExecutable("let.exe");
        }
    }
    return filename;
}

void Setting::on_pushButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, "Select `let.exe` path", ui->lineEdit->text().trimmed(), "*.exe");

    ui->lineEdit->setText(fileName);

}

void Setting::on_buttonBox_accepted()
{
    QSettings settings("shelllet.com", "shelllet");

    settings.setValue("let", ui->lineEdit->text().trimmed());
}

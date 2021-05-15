#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

    static QString LetPath();
private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H

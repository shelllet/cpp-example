#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    struct Option{
        bool chinese;
        bool english;
        bool math;
    };

public:
    Option getOption() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::Dialog *ui;
    Option option_;
};

#endif // DIALOG_H

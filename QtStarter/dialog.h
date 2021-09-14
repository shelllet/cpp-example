#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "workerthread.h"

namespace Ui {
class Dialog;
}

enum Mode{
    MODE_EDIT,
    MODE_CREATE
};



class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(const QString& name, const QString &cmd, const ListEnvironment& env, Mode mode, QWidget *parent = nullptr);
    ~Dialog();
signals:

    void created(const QString& name, const QString& cmd, const ListEnvironment& env);
    void edited(const QString& name, const QString& cmd, const ListEnvironment& env);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_toolButton_Add_clicked();

    void on_toolButton_Del_clicked();

private:
    Ui::Dialog *ui;

    Mode mode_;
};

#endif // DIALOG_H

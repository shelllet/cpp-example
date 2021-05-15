#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
class AbstractEdit {
public:
    virtual void setText(const QString& text) = 0;
};

class Dialog : public QDialog, public AbstractEdit
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

    // AbstractEdit interface
public:
    void setText(const QString &text);
};

#endif // DIALOG_H

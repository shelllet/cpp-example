#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QFrame *frame_;
    QHBoxLayout* layout_;
    QHBoxLayout* layoutCenter_;

    QPushButton *button1_;
    QPushButton *button2_;
    QPushButton *button3_;

    QSpacerItem *spacerItem_;
};

#endif // MAINWINDOW_H

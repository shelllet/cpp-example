#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include "dialog1.h"
#include "dialog2.h"
#include <memory>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<Dialog1> dialog1_;

    std::unique_ptr<Dialog2> dialog2_;

    QStackedLayout * layout_;
};

#endif // MAINWINDOW_H

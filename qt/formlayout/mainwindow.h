#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

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


    QLabel* labelUser_;
    QLabel* labelPassword_;

    QLineEdit* fieldUser_;
    QLineEdit* fieldPassword_;


    QFormLayout* layout_;

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_checkBox_co_stateChanged(int arg1);

    void on_checkBox_chi_stateChanged(int arg1);

    void on_checkBox_eng_stateChanged(int arg1);

    void on_checkBox_jp_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

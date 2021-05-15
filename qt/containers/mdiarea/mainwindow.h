#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actiontile_triggered();

    void on_actioncascade_triggered();

    void on_actionnext_triggered();

    void on_actionprev_triggered();

    void on_actiondont_max_triggered();

    void on_actionno_system_menu_triggered();

    void on_actionshaded_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

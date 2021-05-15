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
    void on_pushButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent*);


    virtual void
    dragEnterEvent(QDragEnterEvent *event);
    virtual void
    dragLeaveEvent(QDragLeaveEvent *event);
    virtual void
    dragMoveEvent(QDragMoveEvent *event);
    virtual void
    dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

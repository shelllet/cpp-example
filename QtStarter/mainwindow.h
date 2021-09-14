#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QStringListModel>
#include <QSystemTrayIcon>
#include "workerthread.h"
#include "tablemodel.h"

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
    void on_action_new_triggered();

    void on_action_edit_triggered();

    void on_Created(const QString &name, const QString& cmd, const ListEnvironment& env);
    void on_Edited(const QString &name, const QString& cmd, const ListEnvironment& env);
    void on_Reported(const QString& message);
    void on_action_del_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_action_quit_triggered();

    void on_IconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_action_setting_triggered();

protected:
    virtual void closeEvent(QCloseEvent *event);
	virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result);
private:
    Ui::MainWindow *ui;

    TableModel tableModel_;
    QSystemTrayIcon tray_;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "pswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_scanbtn_clicked();
    void scan_wpacli();

    void on_wifiList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    PsWindow *pswindow;
};

#endif // MAINWINDOW_H

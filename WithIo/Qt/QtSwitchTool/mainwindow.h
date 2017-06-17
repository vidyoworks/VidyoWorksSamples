#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VsStatus.h"
#include "VsPlugin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
private slots:
    void on_pushButtonVidyoWorks_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

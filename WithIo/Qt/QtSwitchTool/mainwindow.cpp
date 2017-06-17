#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "VidyoWorksUii.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonVidyoWorks_clicked()
{
    QScopedPointer<VidyoWorksUi> vidyoWorks(new VidyoWorksUi(this));
    vidyoWorks->exec();

}

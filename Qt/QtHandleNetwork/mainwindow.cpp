#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VsPlugin.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "vsroomlink.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShowAfterStop();
    vsPlugin = VsPluginPtr(new VsPlugin(this));
    onShowNormalMode();
    onShowConnection();
    m_bInCall = false;
    m_bNoLinkOn = false;



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if(!vsPlugin->VsStart(ui->VideoContent,  ui->VideoContent->geometry()))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("VidyoClientStart");
        msgBox.exec();
        return;

    }
    ShowAfterStart();
}


void MainWindow::ShowAfterStart()
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButton_Stop->setEnabled(true);
    ui->pushButtonRoomLink->setEnabled(true);
    ui->pushButtonEndCall->setEnabled(true);
}

void MainWindow::ShowAfterStop()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButtonRoomLink->setEnabled(false);
    ui->pushButtonEndCall->setEnabled(false);
}


void MainWindow::on_pushButton_Stop_clicked()
{
    if(!vsPlugin->VsStop())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("VidyoClientStop");
        msgBox.exec();
        return;

    }
    ShowAfterStop();
}

void MainWindow::on_pushButtonRoomLink_clicked()
{
    QScopedPointer<VsRoomLink> roomLink(new VsRoomLink(this));
    roomLink->exec();

    if(roomLink->result.isEmpty())
        return;
    if(!vsPlugin->VsRoomLink(roomLink->result))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Room link");
        msgBox.exec();
        return;
    }


}

void MainWindow::on_pushButtonEndCall_clicked()
{
    vsPlugin->VsCallEnd();
}

void MainWindow::InCall()
{
    m_bInCall = true;

    this->bandwidthMonitorTimer = SmartTimer(new QTimer());
   this->bandwidthMonitorTimer->setInterval(10000);
   this->bandwidthMonitorTimer->setSingleShot(false);
   QObject::connect(this->bandwidthMonitorTimer.data(), SIGNAL(timeout()), this, SLOT(OnBandwidthMonitorSlot()));

    this->bandwidthMonitorTimer->start();

}

void MainWindow::NotInCall()
{
    m_bInCall = false;
    this->bandwidthMonitorTimer->stop();
    QTimer::singleShot(2000, this, SLOT(onShowNormalMode()));
    QTimer::singleShot(2000, this, SLOT(onShowConnection()));
}

void MainWindow::VideoMute(bool value)
{

}

void MainWindow::MicMute(bool value)
{
    if(value)
        ui->label_MuteStatusMic->setText("mic muted");
    else
        ui->label_MuteStatusMic->setText("mic unmuted");
}

void MainWindow::onShowLectureMode()
{

    ui->pushButtonLectureMode->setVisible(true);
    ui->VideoContent->setVisible(false);
    //ui->VideoContent->setStyleSheet("background-color:white");
}

void MainWindow::onShowNormalMode()
{
     //ui->VideoContent->setStyleSheet("");
     ui->VideoContent->setVisible(true);
     ui->pushButtonLectureMode->setVisible(false);
     QRect rect(ui->VideoContent->geometry());
     vsPlugin->VsResize(rect);
}

void MainWindow::LectureMode(bool value)
{
    if(value)
    {
         QRect rect(0, 0, 0, 0);
         vsPlugin->VsResize(rect);
         QRect rect2(ui->VideoContent->geometry());
         ui->pushButtonLectureMode->move(rect2.x(), rect2.height() / 2);
         QTimer::singleShot(2000, this, SLOT(onShowLectureMode()));

    }
    else
    {   QTimer::singleShot(2000, this, SLOT(onShowNormalMode()));
    }

}


void MainWindow::onShowNoConnection()
{
    if(!m_bInCall)
    {
        onShowConnection();
        return;
    }
    m_bNoLinkOn = true;
    qDebug() << "...... onShowNoConnection";
    QRect rect2(ui->VideoContent->geometry());
    ui->pushButtonConnectionStatus->move(rect2.x(), rect2.height() / 2);
    ui->pushButtonConnectionStatus->setVisible(true);
    ui->VideoContent->setVisible(false);
}

void MainWindow::onShowConnection()
{

     qDebug() << "...... onShowConnection";
     m_bNoLinkOn = false;
     ui->VideoContent->setVisible(true);
     ui->pushButtonConnectionStatus->setVisible(false);
     QRect rect(ui->VideoContent->geometry());
     vsPlugin->VsResize(rect);
}


void MainWindow::OnBandwidthMonitorSlot()
{

    if((!vsPlugin->VsIsLinkAvailable()) && !m_bNoLinkOn)
        onShowNoConnection();
    else if(vsPlugin->VsIsLinkAvailable() && m_bNoLinkOn)
        onShowConnection();
}


void MainWindow::LinkState(unsigned value)
{
    if(value == 0 && m_bInCall)
    {
        //no connetion
         QRect rect(0, 0, 0, 0);
         vsPlugin->VsResize(rect);

         QTimer::singleShot(2000, this, SLOT(onShowNoConnection()));

    }
    else
    {   QTimer::singleShot(2000, this, SLOT(onShowConnection()));
    }

}


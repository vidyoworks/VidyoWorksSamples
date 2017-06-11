#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VsPlugin.h"
#include <QMessageBox>
#include <QDebug>
#include "vsroomlink.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_bCameraTestOn(false),
    m_bMicTestOn(false),
    m_bSpeakerTestOn(false)
{
    ui->setupUi(this);
    ShowAfterStop();
    vsPlugin = VsPluginPtr(new VsPlugin(this));

    this->pingMicTimer = SmartTimer(new QTimer());
    this->pingMicTimer->setInterval(1000);
    this->pingMicTimer->setSingleShot(false);
    QObject::connect(this->pingMicTimer.data(), SIGNAL(timeout()), this, SLOT(OnQueryEnergy()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if(!vsPlugin->VsStart())
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
    ui->pushCameraTest->setEnabled(true);
    ui->pushButtonMicTest->setEnabled(true);
    ui->pushButtonSpeaker->setEnabled(true);
}

void MainWindow::ShowAfterStop()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButtonRoomLink->setEnabled(false);
    ui->pushButtonEndCall->setEnabled(false);
    ui->pushCameraTest->setEnabled(false);
    ui->pushButtonMicTest->setEnabled(false);
    ui->pushButtonSpeaker->setEnabled(false);
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
    ui->label_CallStatus->setText("In call");
}

void MainWindow::NotInCall()
{
    ui->label_CallStatus->setText("not in In call");
}

void MainWindow::VideoMute(bool value)
{
    if(value)
        ui->label_MuteStatusVideo->setText("video muted");
    else
        ui->label_MuteStatusVideo->setText("video unmuted");
}

void MainWindow::MicMute(bool value)
{
    if(value)
        ui->label_MuteStatusMic->setText("mic muted");
    else
        ui->label_MuteStatusMic->setText("mic unmuted");
}

void MainWindow::on_pushCameraTest_clicked()
{
    PrecallTestType testToRun = TestCameraOff;

    if(!m_bCameraTestOn)
        testToRun = TestCameraOn;
    vsPlugin->PrecallTest(testToRun);
    m_bCameraTestOn = !m_bCameraTestOn;
    if(m_bCameraTestOn)
        ui->pushCameraTest->setText("Stop Camera");
    else
        ui->pushCameraTest->setText("Start Camera");
}

void MainWindow::on_pushButtonMicTest_clicked()
{
    PrecallTestType testToRun = TestMicOff;

    if(!m_bMicTestOn)
        testToRun = TestMicOn;
    vsPlugin->PrecallTest(testToRun);
    m_bMicTestOn = !m_bMicTestOn;
    if(m_bMicTestOn)
    {
        ui->pushButtonMicTest->setText("Stop Mic");
        this->pingMicTimer->start();
    }
    else
    {
        ui->pushButtonMicTest->setText("Start Mic");
        this->pingMicTimer->stop();
    }

}



void MainWindow::OnQueryEnergy()
{
    int volume = vsPlugin->QueryEnergy();
    QString volumeStr(QString("%1").arg(volume));
    ui->label_Energy->setText(volumeStr);
}

void MainWindow::on_pushButtonSpeaker_clicked()
{

    PrecallTestType testToRun = TestSpeakerOff;

    if(!m_bSpeakerTestOn){
        testToRun = TestSpeakerOn;
    }
    vsPlugin->PrecallTest(testToRun);
    m_bSpeakerTestOn = !m_bSpeakerTestOn;
    if(m_bSpeakerTestOn)
    {
        ui->pushButtonSpeaker->setText("Stop Speaker");
    }
    else
    {
        ui->pushButtonSpeaker->setText("Start Speaker");
    }

}

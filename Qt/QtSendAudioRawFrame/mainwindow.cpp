#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VsPlugin.h"
#include <QMessageBox>
#include <QDebug>
#include "vsroomlink.h"

#define SAFE_STRING_CPY(destination, source, limit){\
    size_t sizeToCopy = (limit > 0) ? (limit -1) : 0;\
    strncpy(destination, source, sizeToCopy);\
    }

#define MAX_STREAMS_RENDER  4
#define STREAM_HEIGHT   320
#define STREAM_WIDTH    180

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShowAfterStop();
    vsPlugin = VsPluginPtr(new VsPlugin(this));

    this->playBackTimer = SmartTimer(new QTimer());
    this->playBackTimer->setInterval(20);
    this->playBackTimer->setSingleShot(false);
    QObject::connect(this->playBackTimer.data(), SIGNAL(timeout()), this, SLOT(OnPlayBack()));

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

    m_bIsRawCapturing = false;
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


void MainWindow::OnReceivedFrame(void* )
{

}

void MainWindow::on_pushButtonCaptureRaw_clicked()
{
    m_bIsRawCapturing = !m_bIsRawCapturing;
    if(m_bIsRawCapturing)
    {
        ui->pushButtonCaptureRaw->setText("StopRecord");

        VidyoClientInEventStartAudioSend startAudioSend = {};
        startAudioSend.bps = 16;
        startAudioSend.samplingRate = 32000;
        startAudioSend.frameDuration = 40;
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_AUDIO_SEND, &startAudioSend, sizeof(startAudioSend));
        vsPlugin->VsRecord(true);
    }
    else
    {
        ui->pushButtonCaptureRaw->setText("StartRecord");
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_AUDIO_SEND, NULL, 0);
        vsPlugin->VsRecord(false);
    }
}


void MainWindow::on_pushButtonPlay_clicked()
{
    this->playBackTimer->start();
}

void MainWindow::OnPlayBack()
{
    if(!vsPlugin->VsPlay())
        this->playBackTimer->stop();

}

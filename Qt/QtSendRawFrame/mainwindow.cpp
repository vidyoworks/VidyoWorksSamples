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
    ui->pushButtonRefresh->setEnabled(true);
}

void MainWindow::ShowAfterStop()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButtonRoomLink->setEnabled(false);
    ui->pushButtonEndCall->setEnabled(false);
    ui->pushButtonRefresh->setEnabled(false);
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

void MainWindow::on_pushButtonRefresh_clicked()
{
    QMapIterator<QString, int> iter(uriToWidget);

    while(iter.hasNext())
    {
        iter.next();
        QString uri(iter.key());
        VidyoClientInEventStopWatchVideoSource stopWatch = {0};
        SAFE_STRING_CPY((char *)stopWatch.source.participantURI, uri.toStdString().c_str(), sizeof(stopWatch.source.participantURI));
        stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &stopWatch, sizeof(stopWatch));
    }
    uriToWidget.clear();
    VidyoClientRequestParticipants reqParticipants = {};
    VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants));
    int numOfParticipants = reqParticipants.numberParticipants;
    if(numOfParticipants > MAX_STREAMS_RENDER)
        numOfParticipants = MAX_STREAMS_RENDER;

    for(unsigned index = 0; index < numOfParticipants; ++index)
    {
        VidyoClientInEventStartWatchVideoSource watchSource = {};
        strcpy(watchSource.source.participantURI, reqParticipants.URI[index]);
        watchSource.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
        watchSource.source.sourceId = 0;
        watchSource.frameRate = 15;
        watchSource.height = STREAM_HEIGHT;
        watchSource.width = STREAM_WIDTH;
        watchSource.minFrameInterval = 0;
        watchSource.watchData = NULL;
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource));
        QString uri = QString::fromUtf8((const char *)(reqParticipants.URI[index]));
        uriToWidget.insert(uri,index);
    }


}


QWidget* MainWindow::GetWidgetForUri(QString& uri)
{
    if(!uriToWidget.contains(uri))
    {
        return NULL;
    }
    int index = uriToWidget[uri];
    QWidget* answer = NULL;
    switch(index)
    {
    case 0:
        answer = (QWidget*)ui->openGLWidget1;
        break;
    case 1:
        answer = (QWidget*)ui->openGLWidget2;
        break;
    case 2:
        answer = (QWidget*)ui->openGLWidget3;
        break;
    case 3:
        answer = (QWidget*)ui->openGLWidget4;
        break;
    }
    return answer;

}


void MainWindow::OnReceivedFrame(void* )
{

}

void MainWindow::on_pushButtonCaptureRaw_clicked()
{
    m_bIsRawCapturing = !m_bIsRawCapturing;
    if(m_bIsRawCapturing)
    {
        //make sure to inform plugin to only send frames for first participant
        VidyoClientRequestParticipants reqParticipants = {};
        VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants));
        if(reqParticipants.numberParticipants == 0)
        {
            //there are no participants
            return;
        }

        ui->pushButtonCaptureRaw->setText("StopRawCapture");

        VidyoClientInEventStartVideoSend startVideoSend = {};
        startVideoSend.frameRate = 15;
        startVideoSend.height = STREAM_HEIGHT;
        startVideoSend.width = STREAM_WIDTH;
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_VIDEO_SEND, &startVideoSend, sizeof(startVideoSend));

        {
            QString uriToMonitor = (const char *)(reqParticipants.URI[0]);
            vsPlugin->StartCapture(uriToMonitor);
        }

    }
    else
    {
        ui->pushButtonCaptureRaw->setText("StartRawCapture");
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_VIDEO_SEND, NULL, 0);
        vsPlugin->StartCapture("");
    }
}

void MainWindow::on_pushButtonMuteVideo_clicked()
{
    static bool isMuted = false;
    VidyoClientInEventMute evt = {};
    if(isMuted)
    {
         evt.willMute = VIDYO_FALSE;
    }
    else
    {
        evt.willMute = VIDYO_TRUE;

    }
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO, &evt, sizeof(evt));
    isMuted = !isMuted;
}

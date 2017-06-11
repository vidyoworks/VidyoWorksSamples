#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VsPlugin.h"
#include <QMessageBox>
#include <QDebug>
#include "vsroomlink.h"
#include "VidyoClientPrivate.h"

#define SAFE_STRING_CPY(destination, source, limit){\
    size_t sizeToCopy = (limit > 0) ? (limit -1) : 0;\
    strncpy(destination, source, sizeToCopy);\
    }



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShowAfterStop();
    vsPlugin = VsPluginPtr(new VsPlugin(this));
    m_CurrentParticipantIndex = 0;

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


    VidyoClientRequestParticipants reqParticipants = {};
    VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants));


    QString str = ui->textEditPaticipantIndex->toPlainText();
    if(str.isEmpty())
        str = "0";
    int index = str.toInt();
    if(index >= reqParticipants.numberParticipants)
          return;
    VidyoClientInEventSetParticipantVideoMode pinRequest = {};
    strcpy(pinRequest.uri, reqParticipants.URI[index]);
    pinRequest.videoMode = VIDYO_CLIENT_VIDEO_MODE_PINHIGH;
    pinRequest.actionType = VIDYO_CLIENT_ACTION_TYPE_PIN;
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_PARTICIPANT_VIDEO_MODE, &pinRequest, sizeof(pinRequest));
}


void MainWindow::on_pushButtonMuteCamera_clicked()
{

}



void MainWindow::on_pushButtonStatistics_clicked()
{
    VidyoClientRequestSessionVidyoRouter vidyoRouter;
    VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CURRENT_SESSION_VIDYO_ROUTER,
        &vidyoRouter, sizeof(VidyoClientRequestSessionVidyoRouter));
    QString strRouter(vidyoRouter.routerAddress);
    ui->label_Router->setText("router : " + strRouter);
#ifdef ENABLE_IF_THIS_IS_DEFINED
    VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SHOW_STATISTICS,NULL, 0);
#endif


}

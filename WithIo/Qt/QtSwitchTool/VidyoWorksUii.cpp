#include "VidyoWorksUii.h"
#include "ui_VidyoWorksUi.h"
#include "VsPlugin.h"
#include <QMessageBox>
#include <QDebug>
#include "vsroomlink.h"

VidyoWorksUi::VidyoWorksUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VidyoWorksUi)
{
    ui->setupUi(this);
    VsStatus* statusPtr = static_cast<VsStatus*>(const_cast<VidyoWorksUi*>(this));
    vsPlugin = VsPluginPtr(new VsPlugin(statusPtr, 3));
    ShowAfterStop();
}

VidyoWorksUi::~VidyoWorksUi()
{
    delete ui;
}

void VidyoWorksUi::on_pushButtonStart_clicked()
{
    map<string, string> parameter;
    if(!vsPlugin->VsInit(parameter))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Init");
        msgBox.exec();
        return;

    }

    if(!vsPlugin->VsStart(parameter))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Start");
        msgBox.exec();
        return;

    }
    ShowAfterStart();

}

void VidyoWorksUi::ShowAfterStart()
{
    ui->pushButtonStart->setEnabled(false);
    ui->pushButton_Stop->setEnabled(true);
    ui->pushButtonRoomLink->setEnabled(true);
    ui->pushButtonEndCall->setEnabled(true);
}

void VidyoWorksUi::ShowAfterStop()
{
    ui->pushButtonStart->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButtonRoomLink->setEnabled(false);
    ui->pushButtonEndCall->setEnabled(false);
}


void VidyoWorksUi::on_pushButton_Stop_clicked()
{
    if(!vsPlugin->VsStop())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("VsStop");
        msgBox.exec();
        return;

    }

    if(!vsPlugin->VsUninit())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("VsUninit");
        msgBox.exec();
        return;

    }
    ShowAfterStop();

}

void VidyoWorksUi::on_pushButtonRoomLink_clicked()
{
    QScopedPointer<VsRoomLink> roomLink(new VsRoomLink(this));
    roomLink->exec();


    if(!vsPlugin->VsRoomLink(roomLink->result))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Room link");
        msgBox.exec();
        return;
    }



}

void VidyoWorksUi::on_pushButtonEndCall_clicked()
{
    vsPlugin->VsCallEnd();

}

void VidyoWorksUi::InCall()
{
    ui->label_CallStatus->setText("In call");
}

void VidyoWorksUi::NotInCall()
{
    ui->label_CallStatus->setText("not in In call");
}

void VidyoWorksUi::VideoMute(bool value)
{
    if(value)
        ui->label_MuteStatusVideo->setText("video muted");
    else
        ui->label_MuteStatusVideo->setText("video unmuted");
}

void VidyoWorksUi::MicMute(bool value)
{
    if(value)
        ui->label_MuteStatusMic->setText("mic muted");
    else
        ui->label_MuteStatusMic->setText("mic unmuted");
}


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

#define MAX_STREAMS_RENDER  2
#define STREAM_HEIGHT_STANDARD   320
#define STREAM_WIDTH_STANDARD    180
#define STREAM_HEIGHT_HIGH   1280
#define STREAM_WIDTH_HIGH    720
#define FRAME_RATE_LOW          10
#define FRAME_RATE_HIGH         10

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

    bool isQuality = ui->checkBoxQuality->isChecked();

    int nFrameRate = FRAME_RATE_LOW;
    int nHeight = STREAM_HEIGHT_STANDARD;
    int nWidth = STREAM_WIDTH_STANDARD;
    if(isQuality)
    {
        nFrameRate = FRAME_RATE_HIGH;
        nHeight = STREAM_HEIGHT_HIGH;
        nWidth = STREAM_WIDTH_HIGH;
    }

    ui->openGLWidget1->setVisible(isQuality);
    ui->openGLWidget2->setVisible(!isQuality);
    QString str = ui->textEditPaticipantIndex->toPlainText();
    if(str.isEmpty())
        str = "0";
    int index = str.toInt();
    if(index >= reqParticipants.numberParticipants)
          return;
    VidyoClientInEventStartWatchVideoSource watchSource = {};
    strcpy(watchSource.source.participantURI, reqParticipants.URI[index]);
    watchSource.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
    watchSource.source.sourceId = 0;
    watchSource.frameRate = nFrameRate;
    watchSource.height = nHeight;
    watchSource.width = nWidth;
    watchSource.minFrameInterval = 0;
    watchSource.watchData = NULL;
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource));
    QString uri = QString::fromUtf8((const char *)(reqParticipants.URI[index]));
    uriToWidget.insert(uri,index);
    m_CurrentParticipantIndex = index;
}


void ConvertFrameToOpenCV(void* frameBytes, QImage& m_RGB, int width, int height){
    //if(!m_RGB)  m_RGB = QImage(width, height, QImage::Format_RGB888);


    unsigned char* pData = (unsigned char *) frameBytes;


    for(int i = 0, j=0; i < width * height * 3; i+=6, j+=4)
    {

        unsigned char u = pData[j];
        unsigned char y = pData[j+1];
        unsigned char v = pData[j+2];

        //fprintf(stderr, "%d\n", v);


        m_RGB.bits()[i+2] = 1.0*y + 8 + 1.402*(v-128);               // r
        m_RGB.bits()[i+1] = 1.0*y - 0.34413*(u-128) - 0.71414*(v-128);   // g
        m_RGB.bits()[i] = 1.0*y + 1.772*(u-128) + 0;                            // b

        y = pData[j+3];
        m_RGB.bits()[i+5] = 1.0*y + 8 + 1.402*(v-128);               // r
        m_RGB.bits()[i+4] = 1.0*y - 0.34413*(u-128) - 0.71414*(v-128);   // g
        m_RGB.bits()[i+3] = 1.0*y + 1.772*(u-128) + 0;
    }


}

QWidget* MainWindow::GetWidgetForUri(QString& uri)
{
    if(!uriToWidget.contains(uri))
    {
        return NULL;
    }
    bool isQuality = ui->checkBoxQuality->isChecked();
    if(isQuality)
        return (QWidget*)ui->openGLWidget1;
    return (QWidget*)ui->openGLWidget2;

}

void MainWindow::OnReceivedFrame(void* videoFrameVoid)
{

    VidyoClientOutEventVideoFrameReceived* videoFrame = (VidyoClientOutEventVideoFrameReceived*)videoFrameVoid;

    VidyoClientMediaControlType format = videoFrame->mediaType;
    if(format != VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO)
        return;

    VidyoClientInEventVideoFrame *pFrame = &videoFrame->frame;
    if (pFrame == NULL || pFrame->size <= 0)
        return;
    QString uri = QString::fromUtf8((const char *)(videoFrame->participantURI));
    QWidget* widget = GetWidgetForUri(uri);
    if(!widget)
    {
        return;
    }

    /*int imageWidth = pFrame->width;
    int imageHeight = pFrame->height;
     int bytesPerPixel = 4; // 4 for RGBA, 3 for RGB
    QImage image(pFrame->data, imageWidth, imageHeight, imageWidth * bytesPerPixel, QImage::Format_ARGB32);
    ConvertFrameToOpenCV(pFrame->data, image, imageHeight, imageHeight);*/

   int imageWidth = pFrame->width;
    int imageHeight = pFrame->height;
    QImage image((uchar*)pFrame->data, imageWidth, imageHeight, imageWidth * 4, QImage::Format_RGB32);
    MyGlCanvas *openGLWidget = (MyGlCanvas *)widget;
    openGLWidget->setImage(image);
    openGLWidget->update();
}

void MainWindow::on_checkBoxQuality_clicked(bool checked)
{
   //on_pushButtonRefresh_clicked();
   //return;

        VidyoClientRequestParticipants reqParticipants = {};
        VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants));

        bool isQuality = ui->checkBoxQuality->isChecked();

        int nFrameRate = FRAME_RATE_LOW;
        int nHeight = STREAM_HEIGHT_STANDARD;
        int nWidth = STREAM_WIDTH_STANDARD;
        if(isQuality)
        {
            nFrameRate = FRAME_RATE_HIGH;
            nHeight = STREAM_HEIGHT_HIGH;
            nWidth = STREAM_WIDTH_HIGH;
        }

        ui->openGLWidget1->setVisible(isQuality);
        ui->openGLWidget2->setVisible(!isQuality);

        int index = m_CurrentParticipantIndex;
        if(index >= reqParticipants.numberParticipants)
              return;
        VidyoClientInEventStartWatchVideoSource watchSource = {};
        strcpy(watchSource.source.participantURI, reqParticipants.URI[index]);
        watchSource.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
        watchSource.source.sourceId = 0;
        watchSource.frameRate = nFrameRate;
        watchSource.height = nHeight;
        watchSource.width = nWidth;
        watchSource.minFrameInterval = 0;
        watchSource.watchData = NULL;
        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESTART_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource));
}

void MainWindow::on_pushButtonMuteCamera_clicked()
{
    VidyoClientInEventMute evt = {};

    if(ui->pushButtonMuteCamera->text() == "MuteCamera")
    {
        ui->pushButtonMuteCamera->setText("UnmuteCamera");
        evt.willMute = VIDYO_TRUE;
    }
    else
    {
        ui->pushButtonMuteCamera->setText("MuteCamera");
        evt.willMute = VIDYO_FALSE;
    }
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO, &evt, sizeof(evt));

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

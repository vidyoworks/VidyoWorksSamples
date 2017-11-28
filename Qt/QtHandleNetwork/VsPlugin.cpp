#include "VsPlugin.h"
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include "VsPlugin.h"

VsPlugin * VsPlugin::instance = NULL;

#define SAFE_STRING_CPY(destination, source, limit){\
    size_t sizeToCopy = (limit > 0) ? (limit -1) : 0;\
    strncpy(destination, source, sizeToCopy);\
}

#ifdef Q_WS_WIN
void __stdcall VidyoClientOutCallback
#else
void VidyoClientOutCallback
#endif
(VidyoClientOutEvent event,
              VidyoVoidPtr param, VidyoUint paramSize,
              VidyoVoidPtr data)
{
    if (VsPlugin::getInstance() == NULL)
    {
        return;
    }

    if ((event >= VIDYO_CLIENT_OUT_EVENT_MIN
        && event <= VIDYO_CLIENT_OUT_EVENT_MAX))
    {
        VidyoVoidPtr copyParam = malloc(paramSize);
        memcpy(copyParam, param, paramSize);

        if (copyParam != NULL)
        {
            if ((event >= VIDYO_CLIENT_OUT_EVENT_MIN
                && event <= VIDYO_CLIENT_OUT_EVENT_MAX))
            {
                VsPlugin::getInstance()->EmitOutEvent(event, copyParam, paramSize, data);
            }
        }
    }
    return;

}

void VsPlugin::EmitOutEvent(VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data)
{
    emit(this->OutEvent(event, param, paramSize, data));
}

QByteArray ba;
char *pfolder;


void InitLogParams(VidyoClientLogParams& logParams)
{
    const unsigned int maxLogFileSize = 1000000;
    
#ifdef Q_WS_WIN
    //QString folder("log\\");
    QString folder(QDir::homePath());
    folder += "\\log\\";
    folder.replace("/","\\\\");
#else
    QString folder = QDir::homePath()+ QString("/VsLog/");
#endif
    ba = folder.toLatin1();
    pfolder = ba.data();

    logParams.pathToLogDir= pfolder;
    logParams.pathToDumpDir = pfolder;
    logParams.pathToConfigDir = pfolder;
    
    if(!QDir(folder).exists())
        QDir().mkdir(folder);
    logParams.logBaseFileName = "VidyoSample_";
    logParams.logLevelsAndCategories = "fatal error warning all@AppEvents all@App all@AppVcsoapClient info@AppEmcpClient info@AppEvents all@AppVcsoapClient";
    logParams.logSize = maxLogFileSize;
    
    if(!QDir(logParams.pathToLogDir).exists())
        QDir().mkdir(logParams.pathToLogDir);
    
}

void InitProfileParams(VidyoClientProfileParams& profileParams)
{
#ifdef Q_WS_WIN
    profileParams.PROGFILES_DIR = ".\\";
    profileParams.CONFIG_KEY_PATH = "SOFTWARE\\Vidyo\\Vidyo Desktop\\";

    profileParams.MYDOCS_DIR = ".\\";
    profileParams.VIDYO_DIR = ".\\";
#else
   /*profileParams.PROGFILES_DIR = "./";
    profileParams.CONFIG_KEY_PATH = "./";

    profileParams.MYDOCS_DIR = "./";
    profileParams.VIDYO_DIR = "./";*/

#endif
    profileParams.portNumber = 63460;
    profileParams.PRODUCT_NAME = "VidyoDesktop";

}

VsPlugin * VsPlugin::getInstance()
{
    return instance;
}



VsPlugin::VsPlugin(VsStatus* statusWindow):
    QThread(NULL)
{
    m_Started = false;
    const unsigned int maxLogFileSize = 1000000;
    VidyoClientLogParams logParams = {0};

    InitLogParams(logParams);

    VidyoBool retVal = VidyoClientInitialize((VidyoClientOutEventCallback)VidyoClientOutCallback, NULL, &logParams);

    QObject::connect(this, SIGNAL(started()), SLOT(OnStarted()));
    this->start();
    QObject::moveToThread(this);
    instance = this;

    m_statusWindow = statusWindow;

}

void VsPlugin::OnStarted()
{

   qRegisterMetaType<VidyoClientOutEvent>("VidyoClientOutEvent");
   qRegisterMetaType<VidyoVoidPtr>("VidyoVoidPtr");
   qRegisterMetaType<VidyoUint>("VidyoUint");

    QObject::connect(this,
        SIGNAL(OutEvent(VidyoClientOutEvent,VidyoVoidPtr,VidyoUint,VidyoVoidPtr)),
        this,
        SLOT(OnOutEvent(VidyoClientOutEvent,VidyoVoidPtr,VidyoUint,VidyoVoidPtr)),
        Qt::QueuedConnection);
}

void VsPlugin::OnOutEvent(VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data)
{
    switch (event)
        {
            case VIDYO_CLIENT_OUT_EVENT_SIGN_IN:
                {
                qDebug() << "VIDYO_CLIENT_OUT_EVENT_SIGN_IN";
                VidyoClientOutEventSignIn * eventSignIn = (VidyoClientOutEventSignIn*)param;
                if(eventSignIn)
                {
                    if(!eventSignIn->activeEid)
                    {
                        //we need to consume a license
                        //As VidyoClient just informed that we never consume a license
                        VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0);
                    }
                }
                }
                break;
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
                qDebug() << "conference is active";
                m_statusWindow->InCall();
                break;
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CLEARED:
                qDebug() << "...... conference ended";
                m_statusWindow->NotInCall();
                break;
            case VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN:
                {
                    VidyoClientOutEventMuted * muteData = (VidyoClientOutEventMuted*)param;
                    bool value = (muteData->isMuted == VIDYO_TRUE);
                    m_statusWindow->MicMute(value);
                }
                break;
            case VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO:
                 {
                    VidyoClientOutEventMuted * muteData = (VidyoClientOutEventMuted*)param;
                    bool value = (muteData->isMuted == VIDYO_TRUE);
                    m_statusWindow->VideoMute(value);
                }
                break;
            case VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_STAGE :
            {
                VidyoClientOutEventLectureModeStage * lectureModePara = (VidyoClientOutEventLectureModeStage*)param;
                switch(lectureModePara->stage)
                {
                    case VIDYO_CLIENT_LECTURE_MODE_LISTEN:
                    case VIDYO_CLIENT_LECTURE_MODE_START:
                    {
                       m_statusWindow->LectureMode(true);
                    }
                    break;
                    case VIDYO_CLIENT_LECTURE_MODE_PRESENT:
                    {
                        m_statusWindow->LectureMode(false);
                    }
                    break;
                    case VIDYO_CLIENT_LECTURE_MODE_STOP:
                    {
                        m_statusWindow->LectureMode(false);
                    }
                    break;
                }
            }
            break;
            case VIDYO_CLIENT_OUT_EVENT_SUBSCRIBING:
            {
                    VidyoUint *parm1 = (VidyoUint *)param;
                    unsigned linkedState = *parm1;
                    qDebug() << "......link state = " << linkedState;
                    m_statusWindow->LinkState(linkedState);
            }
            break;
            default:
                    break;
    }
	if (param != NULL)
        free(param);
}

VsPlugin::~VsPlugin()
{

    if(m_Started)
        VsStop();
     VidyoClientUninitialize();
}



bool VsPlugin::VsStart(QWidget * widget, const QRect& rect)
{

    int err;
    const unsigned int maxLogFileSize = 1000000;
    VidyoClientLogParams logParams = {0};
    VidyoClientProfileParams profileParams = {0};
    int keyCode;

    InitLogParams(logParams);
    InitProfileParams(profileParams);

    VidyoWindowId winId = (VidyoWindowId)widget->winId();
    VidyoRect vidyoRect;
    vidyoRect.xPos = 0;
    vidyoRect.yPos = 0;
    vidyoRect.width = rect.width();
    vidyoRect.height = rect.height();
    // startup VidyoClient library
    if (!VidyoClientStart((VidyoClientOutEventCallback)VidyoClientOutCallback,
                          NULL,
                          &logParams,
                          winId,
                          //                      (VidyoWindowId)frame_window,
                          &vidyoRect,
                          NULL,
                          &profileParams,
                          NULL))
    {
        // user already notified by VidyoClientStart()
        return false;
    }

    m_Started = true;
    return true;


}

bool VsPlugin::VsStop()
{
    VidyoClientStop();

    m_Started = false;
    return true;
}

bool VsPlugin::VsRoomLink(QStringList& roomLink)
{
 #define ROOM_LINK_INTERFACE_PORTAL_INDEX   0
 #define ROOM_LINK_INTERFACE_ROOMKEY_INDEX   1
 #define ROOM_LINK_INTERFACE_GUESTNAME_INDEX   2
 #define ROOM_LINK_INTERFACE_PIN_INDEX   3

    QString portalUri(roomLink[ROOM_LINK_INTERFACE_PORTAL_INDEX]);
    QString roomKey(roomLink[ROOM_LINK_INTERFACE_ROOMKEY_INDEX]);
    QString guestName(roomLink[ROOM_LINK_INTERFACE_GUESTNAME_INDEX]);
    QString pin(roomLink[ROOM_LINK_INTERFACE_PIN_INDEX]);

    QScopedPointer<VidyoClientInEventRoomLink> backendReq(new VidyoClientInEventRoomLink());


       SAFE_STRING_CPY((char *)backendReq->portalUri, portalUri.toAscii().data(), sizeof(backendReq->portalUri));

       SAFE_STRING_CPY((char *)backendReq->roomKey, roomKey.toAscii().data(), sizeof(backendReq->roomKey));

       SAFE_STRING_CPY((char *)backendReq->displayName, guestName.toUtf8().data(), sizeof(backendReq->displayName));

       SAFE_STRING_CPY((char *)backendReq->pin, pin.toAscii().data(), sizeof(backendReq->pin));



       backendReq->clientType = VIDYO_CLIENT_CLIENTTYPE_L;



       if(!VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_IN_EVENT_ROOM_LINK, backendReq.data(), sizeof(VidyoClientInEventRoomLink)))

       {

          return false;

       }


    return true;
}

bool VsPlugin::VsCallEnd()
{
       if(!VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE,NULL, 0))

       {

          return false;

       }


    return true;
}

 void VsPlugin::VsResize(const QRect& rect)
 {


     VidyoClientInEventResize inResizeEvent;
     inResizeEvent.x = 0;
     inResizeEvent.y = 0;
     inResizeEvent.width = rect.width();
     inResizeEvent.height = rect.height();

     if (!VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESIZE,
         &inResizeEvent,
         sizeof(VidyoClientInEventResize)))
     {

     }
 }


 bool VsPlugin::VsIsLinkAvailable()
 {
     VidyoClientRequestBandwidthInfo reqBandwidthInfo = {};

     if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_BANDWIDTH_INFO, &reqBandwidthInfo, sizeof(reqBandwidthInfo))
             == VIDYO_CLIENT_ERROR_OK)
     {
         if(reqBandwidthInfo.ActualRecvBwMax < 10)
             return false;
     }
     return true;
 }


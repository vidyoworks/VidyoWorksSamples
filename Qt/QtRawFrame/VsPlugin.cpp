#include "VsPlugin.h"
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <string>
#include "VsPlugin.h"

VsPlugin * VsPlugin::instance = NULL;

#define SAFE_STRING_CPY(destination, source, limit){\
    size_t sizeToCopy = (limit > 0) ? (limit -1) : 0;\
    strncpy(destination, source, sizeToCopy);\
}

#define LmiFourCC(_a, _b, _c, _d) ( ((unsigned int)(_d)<<24) | ((unsigned int)(_c) << 16) | ((unsigned int)(_b) << 8) | ((unsigned int)(_a)) )
#define LMI_MEDIAFORMAT_I420 LmiFourCC('I', '4', '2', '0')
#define LMI_MEDIAFORMAT_YU12 LmiFourCC('Y', 'U', '1', '2')
#define LMI_MEDIAFORMAT_ARGB LmiFourCC('A', 'R', 'G', 'B')
#define LMI_MEDIAFORMAT_BGRA LmiFourCC('B', 'G', 'R', 'A')


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

        if(!copyParam)
            return;
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

void InitLogParams(VidyoClientLogParams& logParams)
{
    const unsigned int maxLogFileSize = 1000000;

#ifdef Q_WS_WIN
    QString folder("log\\");
#else
    //QString folder = QDir::homePath()+ QString("/VsLog/");
    QString folder = QString("/Users/dinesh/VsLog/");
#endif
    logParams.pathToLogDir= folder.toStdString().c_str();
    logParams.pathToDumpDir = folder.toStdString().c_str();
    logParams.pathToConfigDir = folder.toStdString().c_str();

    if(!QDir(folder).exists())
        QDir().mkdir(folder);
    logParams.logBaseFileName = "VidyoSample_";
    logParams.logLevelsAndCategories = "fatal error warning info@App info@AppEmcpClient info@AppEvents all@AppVcsoapClient";
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
    profileParams.PROGFILES_DIR = "./";
    profileParams.CONFIG_KEY_PATH = "./";

    profileParams.MYDOCS_DIR = "./";
    profileParams.VIDYO_DIR = "./";

#endif
    profileParams.portNumber = 63458;
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
            // First event that is received by the client after Login is sent
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
                qDebug() << "conference is active";
                m_statusWindow->InCall();

                {
                        VidyoClientRequestEventSetWatchVideoFormat watch = {};
                        //If VidyoClient version is 3.4.4.0200 or greater use LMI_MEDIAFORMAT_BGRA
                        //unless you use this format, colors wont come correctly
                        //however, this format exists only in 3.4.4.0200
                        //therefore anything LMI_MEDIAFORMAT_BGRA earlier it will fail.
                        watch.format = LMI_MEDIAFORMAT_ARGB;
                        //watch.format = LMI_MEDIAFORMAT_BGRA;
                        VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT, &watch, sizeof(watch));
                }
                break;
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
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED:
                qDebug() << "conference ended";
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
             case VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED:
                {
                VidyoClientOutEventVideoFrameReceived *videoFrame = (VidyoClientOutEventVideoFrameReceived*)param;
                m_statusWindow->OnReceivedFrame((void*)videoFrame);
				queueOfFrames.enqueue((void*)videoFrame);
                while(queueOfFrames.size() >= 100)
                {
                    void *ptr = queueOfFrames.dequeue();
                    if (ptr != NULL)
                        free(ptr);
                }
                //ensure there is return to make sure we dont free this buffer
                return;
                }
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



bool VsPlugin::VsStart()
{

    int err;
    const unsigned int maxLogFileSize = 1000000;
    VidyoClientLogParams logParams = {0};
    VidyoClientProfileParams profileParams = {0};
    int keyCode;
    int window_origin_x = 0;
    int window_origin_y = 0;
    unsigned window_width = 400;
    unsigned window_height = 300;

    InitLogParams(logParams);
    InitProfileParams(profileParams);

    VidyoRect videoRect = {window_origin_x, window_origin_y, window_width, window_height};


    // startup VidyoClient library
    if (!VidyoClientStart((VidyoClientOutEventCallback)VidyoClientOutCallback,
                          NULL,
                          &logParams,
                          NULL,
                          //                      (VidyoWindowId)frame_window,
                          &videoRect,
                          NULL,
                          &profileParams,
                          NULL))
    {
        // user already notified by VidyoClientStart()
        return false;
    }

    m_Started = true;

    //this is a raw frame sample
    //default rendering not required
    VidyoClientInEventMute evt = {};
    evt.willMute = VIDYO_TRUE;
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_DEFAULT_RENDERING, &evt, sizeof(evt));
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


       SAFE_STRING_CPY((char *)backendReq->portalUri, portalUri.toStdString().c_str(), sizeof(backendReq->portalUri));

       SAFE_STRING_CPY((char *)backendReq->roomKey, roomKey.toStdString().c_str(), sizeof(backendReq->roomKey));

       SAFE_STRING_CPY((char *)backendReq->displayName, guestName.toStdString().c_str(), sizeof(backendReq->displayName));

       SAFE_STRING_CPY((char *)backendReq->pin, pin.toStdString().c_str(), sizeof(backendReq->pin));



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


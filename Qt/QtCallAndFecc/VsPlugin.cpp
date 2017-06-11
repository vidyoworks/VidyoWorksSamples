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

void InitLogParams(VidyoClientLogParams& logParams)
{
    const unsigned int maxLogFileSize = 1000000;
    
#ifdef Q_WS_WIN
    QString folder("log\\");
#else
    QString folder = QDir::homePath()+ QString("/VsLog/");
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
            case VIDYO_CLIENT_OUT_EVENT_SIGN_IN_COMPLETE:
                qDebug() << "VIDYO_CLIENT_OUT_EVENT_SIGN_IN_COMPLETEe";
                m_statusWindow->SignedIn();
                break;
            case VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT:
                qDebug() << "VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT";
                m_statusWindow->SignedOut();
                break;
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
                qDebug() << "conference is active";
                m_statusWindow->InCall();
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
    return true;


}

bool VsPlugin::VsStop()
{
    VidyoClientStop();

    m_Started = false;
    return true;
}

bool VsPlugin::VsLogin(QStringList& roomLink)
{
 #define ROOM_LINK_INTERFACE_PORTAL_INDEX   0
 #define ROOM_LINK_INTERFACE_USER_INDEX   1
 #define ROOM_LINK_INTERFACE_PASSWORD_INDEX   2

    QString portalUri(roomLink[ROOM_LINK_INTERFACE_PORTAL_INDEX]);
    QString user(roomLink[ROOM_LINK_INTERFACE_USER_INDEX]);
    QString password(roomLink[ROOM_LINK_INTERFACE_PASSWORD_INDEX]);

    QScopedPointer<VidyoClientInEventLogIn> backendReq(new VidyoClientInEventLogIn());


       SAFE_STRING_CPY((char *)backendReq->portalUri, portalUri.toAscii().data(), sizeof(backendReq->portalUri));

       SAFE_STRING_CPY((char *)backendReq->userName, user.toAscii().data(), sizeof(backendReq->userName));

       SAFE_STRING_CPY((char *)backendReq->userPass, password.toUtf8().data(), sizeof(backendReq->userPass));

       backendReq->clientType = VIDYO_CLIENT_CLIENTTYPE_W;



       backendReq->clientType = VIDYO_CLIENT_CLIENTTYPE_L;



       if(!VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_IN_EVENT_LOGIN, backendReq.data(), sizeof(VidyoClientInEventLogIn)))

       {

          return false;

       }


    return true;
}

void VsPlugin::VsLogout()
{
    VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SIGNOFF, NULL, 0);
}

bool VsPlugin::VsCall(QString& id, bool isLegacy)
{


    QScopedPointer<VidyoClientInEventPortalService> backendReq(new VidyoClientInEventPortalService());

     backendReq->requests.directCall.typeRequest = VIDYO_CLIENT_SERVICE_TYPE_DIRECT_CALL;
     if (isLegacy)
     {
          backendReq->requests.directCall.entityType = VIDYO_CLIENT_ENTITY_TYPE_LEGACY;
         SAFE_STRING_CPY( backendReq->requests.directCall.legacyID, id.toAscii().data(), sizeof(backendReq->requests.directCall.legacyID));
     }
     else
     {
         backendReq->requests.directCall.entityType = VIDYO_CLIENT_ENTITY_TYPE_MEMBER;
         SAFE_STRING_CPY( backendReq->requests.directCall.entityID, id.toAscii().data(), sizeof(backendReq->requests.directCall.entityID) + 1);
     }



       if(!VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE, backendReq.data(), sizeof(VidyoClientInEventPortalService)))

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

QString VsPlugin::VsGetFecc()
{
    QString result("");
    QScopedPointer<VidyoClientRequestFeccList> backendRequest(new VidyoClientRequestFeccList());
     if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_FECC_LIST, backendRequest.data(), sizeof(VidyoClientRequestFeccList)) != VIDYO_CLIENT_ERROR_OK)
     {
         return result;

     }
     if(backendRequest->numberParticipants <= 0)
         return result;
     result = backendRequest->uri[0];
    return result;
}


VidyoClientCameraControlCommand GetFeccCommand(FeccMove direction)
{
    VidyoClientCameraControlCommand result;
    switch(direction)
    {
        case MoveUp:
            result = VIDYO_CLIENT_CAMERA_CONTROL_TILTUP;
            break;
        case MoveDown:
            result = VIDYO_CLIENT_CAMERA_CONTROL_TILTDOWN;
            break;
        case MoveLeft:
            result = VIDYO_CLIENT_CAMERA_CONTROL_PANLEFT;
            break;
       default:
            result = VIDYO_CLIENT_CAMERA_CONTROL_PANRIGHT;
            break;
    }
    return result;
}

void VsPlugin::VsMoveCamera(QString& uri, FeccMove direction)
{
    QScopedPointer<VidyoClientInEventControlCamera> backendRequest(new VidyoClientInEventControlCamera());
    SAFE_STRING_CPY((char *)backendRequest->uri, uri.toAscii().data(), URI_LEN);
    backendRequest->cameraCommand = GetFeccCommand(direction);

     VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, backendRequest.data(),
          sizeof(VidyoClientInEventControlCamera));
}


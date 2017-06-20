#include "VsPlugin.h"
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include "VsPlugin.h"
#include "IVidyoClient.h"
#include "VidyoClientSwitch.h"

VsPlugin * VsPlugin::instance = NULL;

#define SAFE_STRING_CPY(destination, source, limit){\
    size_t sizeToCopy = (limit > 0) ? (limit -1) : 0;\
    strncpy(destination, source, sizeToCopy);\
}


VsPlugin * VsPlugin::getInstance()
{
    return instance;
}


VidyoClientPtr gVidyoClientPtr = NULL;

class VsPluginPrivate : public IVidyoClientCaller
{

public:
    VsPluginPrivate(VsPlugin*)
    {


    }

    virtual void CallComplete(){}
    virtual void CallFailure(VidyoClientSwitchDefs::ErrorCall){}
    virtual void CallEnd(){}


    VsPlugin* m_plugin;


};

VsPlugin::VsPlugin(VsStatus* statusWindow, int typeOfBackend)
{
    impl = QSharedPointer<VsPluginPrivate>(new VsPluginPrivate(this));
    if(typeOfBackend ==3)
        gVidyoClientPtr = VcwGetClient(VidyoClientSwitchDefs::ClientTypeVw);
    else
        gVidyoClientPtr = VcwGetClient(VidyoClientSwitchDefs::ClientTypeIo);

    instance = this;
    m_statusWindow = statusWindow;

}



VsPlugin::~VsPlugin()
{

    if(gVidyoClientPtr){
        delete gVidyoClientPtr;
        gVidyoClientPtr = NULL;
    }
}

bool VsPlugin::VsInit(const char* parameters)
{
    if(!gVidyoClientPtr)
        return false;
    VidyoClientCallerPtr ptrToCallBacks = impl.data();
    if(gVidyoClientPtr->Initialize(parameters, ptrToCallBacks) != VidyoClientSwitchDefs::ErrorSuccess)
        return false;
    return true;
}



bool VsPlugin::VsStart(const char*  parameters)
{
    if(!gVidyoClientPtr)
        return false;
    if(gVidyoClientPtr->Start(parameters) != VidyoClientSwitchDefs::ErrorSuccess)
        return false;
    return true;
}

bool VsPlugin::VsStop()
{
    if(!gVidyoClientPtr)
        return false;
    if(!gVidyoClientPtr->Stop())
        return false;
    return true;
}

bool VsPlugin::VsUninit()
{
    if(!gVidyoClientPtr)
        return false;
    if(!gVidyoClientPtr->Uninitialize())
        return false;
    return true;
}


bool VsPlugin::VsRoomLink(const char*  parameters)
{
    if(!gVidyoClientPtr)
        return false;
    if(gVidyoClientPtr->Join(parameters) != VidyoClientSwitchDefs::ErrorSuccess)
        return false;
    return true;
}

bool VsPlugin::VsCallEnd()
{
    if(!gVidyoClientPtr)
        return false;
    if(!gVidyoClientPtr->Leave())
        return false;
    return true;
}


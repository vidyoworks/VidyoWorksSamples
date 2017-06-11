#ifndef VSSTATUS_H
#define VSSTATUS_H
#include <QSharedPointer>

class VsStatus
{
public:
    VsStatus();
    virtual ~VsStatus();
    virtual void InCall() = 0;
    virtual void NotInCall() = 0;
    virtual void VideoMute(bool value) = 0;
    virtual void MicMute(bool value) = 0;
};
typedef QSharedPointer<VsStatus> VsStatusPtr;

#endif // VSSTATUS_H

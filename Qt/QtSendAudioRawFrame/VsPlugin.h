#ifndef VSPLUGIN_H
#define VSPLUGIN_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QSharedPointer>
#include <QQueue>
#define BUILD_VIDYO_DESKTOP_QMAKE
#include "VidyoClient.h"
#include "VsStatus.h"

typedef struct VsAudioFrame_
{
    int size;
    VidyoUint8 data[1];
} VsAudioFrame;
typedef QSharedPointer<VsAudioFrame> VsAudioFramePtr;

class VsPlugin : public QThread
{
    Q_OBJECT
public:
    explicit VsPlugin(VsStatus* statusWindow);
    virtual ~VsPlugin();
    bool VsStart();
    bool VsStop();
    bool VsRoomLink(QStringList& roomLink);
    void VsRecord(bool start);
    bool VsPlay();
    bool VsCallEnd();
    static VsPlugin* getInstance();
    void EmitOutEvent(VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data);

signals:
    void OutEvent(VidyoClientOutEvent event, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data);

public slots:
    void OnStarted();
    void OnOutEvent(VidyoClientOutEvent event,
                                 VidyoVoidPtr param,
                                 VidyoUint paramSize,
                                 VidyoVoidPtr data);

private:
    bool m_Started;
    static VsPlugin * instance;
    VsStatus* m_statusWindow;
	QQueue<void*> queueOfFrames;
    bool m_Record;

};

typedef QSharedPointer<VsPlugin> VsPluginPtr;

#endif // VSPLUGIN_H

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

enum PrecallTestType { TestCameraOn, TestCameraOff, TestMicOn, TestMicOff, TestSpeakerOn, TestSpeakerOff, MicEnergy };

class VsPlugin : public QThread
{
    Q_OBJECT
public:
    explicit VsPlugin(VsStatus* statusWindow);
    virtual ~VsPlugin();
    bool VsStart();
    bool VsStop();
    bool VsRoomLink(QStringList& roomLink);
    bool VsCallEnd();
    static VsPlugin* getInstance();
    void PrecallTest(PrecallTestType testType);
    int QueryEnergy();
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
    void LoadSoundFile(VidyoClientInEventStartPrecallTestSpeaker &testSpeaker);
};

typedef QSharedPointer<VsPlugin> VsPluginPtr;

#endif // VSPLUGIN_H

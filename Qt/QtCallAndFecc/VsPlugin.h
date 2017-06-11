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


enum FeccMove { MoveUp, MoveDown, MoveLeft, MoveRight};

class VsPlugin : public QThread
{
    Q_OBJECT
public:
    explicit VsPlugin(VsStatus* statusWindow);
    virtual ~VsPlugin();
    bool VsStart();
    bool VsStop();
    bool VsLogin(QStringList& roomLink);
    void VsLogout();
    bool VsCall(QString& id, bool isLegacy);
    bool VsCallEnd();
    QString VsGetFecc();
    void VsMoveCamera(QString& camera, FeccMove direction);
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
};

typedef QSharedPointer<VsPlugin> VsPluginPtr;

#endif // VSPLUGIN_H

#ifndef VSPLUGIN_H
#define VSPLUGIN_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QSharedPointer>
#include <QQueue>
#define BUILD_VIDYO_DESKTOP_QMAKE
#include "VsStatus.h"
#include "IVidyoClient.h"
#include <QSharedPointer>


class VsPluginPrivate;
class VsPlugin : public QObject
{
    Q_OBJECT
public:
    explicit VsPlugin(VsStatus* statusWindow, int typeOfBackend);
    virtual ~VsPlugin();
    bool VsInit(map<string, string> &parameter);
    bool VsStart(map<string, string> &parameter);
    bool VsStop();
    bool VsUninit();
    bool VsRoomLink(map<string, string> &parameter);
    bool VsCallEnd();
    static VsPlugin* getInstance();

public slots:
private:
    static VsPlugin * instance;
    VsStatus* m_statusWindow;
    QSharedPointer<VsPluginPrivate> impl;
};

typedef QSharedPointer<VsPlugin> VsPluginPtr;

#endif // VSPLUGIN_H

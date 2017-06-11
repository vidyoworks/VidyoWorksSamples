#ifndef VDSOUND_H
#define VDSOUND_H
#include <VidyoTypes.h>
#include <QMap>


class VDSound
{
public:
    static VidyoUint8* Load(const QString& name);
    VidyoUint8 *soundData;
    static QMap<QString, int> Init();
private:
    static const QMap<QString, int> mapQtToOs;
};

#endif // VDSOUND_H

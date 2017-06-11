#include "VDSound.h"

const QMap<QString, int> VDSound::mapQtToOs = VDSound::Init();

static QMap<QString, VidyoUint8 *> sounds;


QMap<QString, int> VDSound::Init()
{
    QMap<QString,int> tmp;
    return tmp;
}


VidyoUint8* VDSound::Load(const QString& name)
{
    VidyoUint8 *result = NULL;
    if(sounds.find(name) !=  sounds.end()) {
       result = sounds[name];
       return NULL;
    }
    QFile file(name);
    if(file.open(QIODevice::ReadOnly)) {
        size_t size = file.size();
        if(size) {
            char *buf = new char[size];
            qint64 result = file.read(buf, size);
            if(result == size) {
                result = (VidyoUint8 *)buf;
                sounds[name] = result;
            }
            else
                delete[] buf;
        }
        file.close();
    }

    return  result;
}

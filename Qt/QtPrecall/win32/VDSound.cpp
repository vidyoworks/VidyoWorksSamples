#include "VDSound.h"
#include <QString>
#include <windows.h>
#include "..\resources\win32\resource.h"


const QMap<QString, int> VDSound::mapQtToOs = VDSound::Init();

static QString GetResourcesPath()
{
#ifdef Q_WS_WIN
    return ":/sound";
#elif defined(Q_WS_MACX)
    return QCoreApplication::applicationDirPath() + "/../Resources";
#elif defined(VIDYO_LINUX)
    return "/opt/vidyo/VidyoDesktop/resources";
#else
    return "./";
#endif
}

QMap<QString, int> VDSound::Init()
{
    QMap<QString,int> tmp;
    tmp[GetResourcesPath() + "/testtone.wav"] = IDR_TEST_TONE;
    return tmp;
}


VidyoUint8* VDSound::Load(const QString& name)
{
    VidyoUint8 *result = NULL;

    if(mapQtToOs.find(name) == mapQtToOs.end())
        return result;
    int winResource = mapQtToOs[name];

    HRSRC hResInfo = 0;
    if((hResInfo = ::FindResource(::GetModuleHandle(0), MAKEINTRESOURCE(winResource), TEXT("WAVE"))) == NULL)
        return result;

    HGLOBAL hRes = NULL;
    if((hRes = ::LoadResource(::GetModuleHandle(0), hResInfo)) == NULL)
        return result;

    LPVOID pTheSound = NULL;
    if((pTheSound = ::LockResource(hRes)) == NULL)
        return result;

    result = ((VidyoUint8 *)pTheSound);

    return result;

}

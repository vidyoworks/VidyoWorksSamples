/**
 * This code was taken from AppClient.h in Samples/AppClient.  It has been modified some to work with
 * the Android Client.  Some values are set in the AppDeviceSetup structure that are not yet used.
 */

#ifndef APP_DEVICE_H
#define APP_DEVICE_H
#include "VidyoClient.h"
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Client/LmiLocalParticipant.h>
#include <Lmi/Ui/Client/LmiClientStatisticsDialog.h>
#include <Lmi/Scip/PlugIn/LmiScipSignalingStack.h>

LMI_BEGIN_EXTERN_C

typedef struct AppDeviceSetup_
{
	VidyoUint captureWidth;
	VidyoUint captureHeight;
	VidyoUint croppedWidth;
	VidyoUint croppedHeight;
	VidyoUint captureFrameRate;
	VidyoUint numLayers;

	struct { VidyoUint width, height; } maxTileSingle;
	struct { VidyoUint width, height; } maxTileMultiple;
	VidyoUint maxFpsTile0;
	VidyoUint maxFps;
	VidyoBool multipleTiles;
	VidyoInt temporalSpatialTradeoff;

} AppDeviceSetup;

#define JNI_MEDIA_FORMAT_INVALID        -1
#define JNI_MEDIA_FORMAT_RGBA           1
#define JNI_MEDIA_FORMAT_ARGB           2
#define JNI_MEDIA_FORMAT_BGRA           3

DECLSPEC void AppDeviceSetTemporalSpatialTradeoff(AppDeviceSetup *config, float value);
DECLSPEC VidyoInt AppDeviceGetTemporalSpatialTradeoff(AppDeviceSetup *config);
DECLSPEC VidyoBool AppDeviceProcessorHasNeon(AppDeviceSetup *client);
DECLSPEC VidyoUint AppDeviceGetNumPhysicalCores(AppDeviceSetup *client);
DECLSPEC VidyoUint AppDeviceGetNumLogicalCores(AppDeviceSetup *client);
DECLSPEC VidyoBool AppDeviceSetEncoderConfiguration(AppDeviceSetup* config, VidyoBool directCall, VidyoUint temporalSpatialTradeoff, VidyoUint forcePerf);
DECLSPEC VidyoUint AppDeviceGetEncodedWidth(AppDeviceSetup* config);
DECLSPEC VidyoUint AppDeviceGetEncodedHeight(AppDeviceSetup* config);
DECLSPEC VidyoUint AppDeviceGetEncodedFrameRate(AppDeviceSetup* config);
DECLSPEC VidyoUint VidyoRectangleGetWidth(const VidyoRect *r);
DECLSPEC VidyoUint VidyoRectangleGetHeight(const VidyoRect *r);
DECLSPEC VidyoUint AppDeviceMediaFormat(VidyoUint jniMediaFormat);

LMI_END_EXTERN_C

#endif

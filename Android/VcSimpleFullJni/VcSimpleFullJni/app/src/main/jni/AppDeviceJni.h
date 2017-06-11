/**
 * This code was taken from AppClient.h in Samples/AppClient.  It has been modified some to work with
 * the Android Client.  Some values are set in the AppDeviceSetup structure that are not yet used.
 */

#ifndef APP_DEVICE_H
#define APP_DEVICE_H
#include "VidyoClient.h"
#include "VidyoJniCommon.h"
//#include <Lmi/Utils/LmiTypes.h>
//#include <Lmi/Client/LmiLocalParticipant.h>
//#include <Lmi/Ui/Client/LmiClientStatisticsDialog.h>
//#include <Lmi/Scip/PlugIn/LmiScipSignalingStack.h>

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


void AppDeviceSetTemporalSpatialTradeoff(AppDeviceSetup *config, float value);
VidyoInt AppDeviceGetTemporalSpatialTradeoff(AppDeviceSetup *config);
VidyoBool AppDeviceProcessorHasNeon(AppDeviceSetup *client);
VidyoUint AppDeviceGetNumPhysicalCores(AppDeviceSetup *client);
VidyoUint AppDeviceGetNumLogicalCores(AppDeviceSetup *client);
VidyoBool AppDeviceSetEncoderConfiguration(AppDeviceSetup* config, VidyoBool directCall, VidyoUint temporalSpatialTradeoff, VidyoUint forcePerf);
VidyoUint AppDeviceGetEncodedWidth(AppDeviceSetup* config);
VidyoUint AppDeviceGetEncodedHeight(AppDeviceSetup* config);
VidyoUint AppDeviceGetEncodedFrameRate(AppDeviceSetup* config);

LMI_END_EXTERN_C

#endif

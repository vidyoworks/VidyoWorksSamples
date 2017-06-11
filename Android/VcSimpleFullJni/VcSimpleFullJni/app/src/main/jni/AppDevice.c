/**
 * This code was taken from AppClient.c in Samples/AppClient.  It has been modified some to work with
 * the Android Client.  Some values are set in the AppDeviceSetup structure that are not yet used.
 */
#include "AppDevice.h"
#include <Lmi/Os/LmiOs.h>
#include <Lmi/Os/LmiProcessor.h>
#include <Lmi/Client/LmiClient.h>
#include <Lmi/Ui/LmiUi.h>


void AppDeviceSetTemporalSpatialTradeoff(AppDeviceSetup *config, float value)
{
	config->temporalSpatialTradeoff = (LmiInt) (value * 30);
}

LmiInt AppDeviceGetTemporalSpatialTradeoff(AppDeviceSetup *config)
{
	return config->temporalSpatialTradeoff;
}

LmiBool AppDeviceProcessorHasNeon(AppDeviceSetup *client)
{
	return VidyoClientAndroidProcessorHasNeon();
}

LmiUint AppDeviceGetNumPhysicalCores(AppDeviceSetup *client)
{
	return VidyoClientAndroidProcessorGetNumPhysicalCores();
}

LmiUint AppDeviceGetNumLogicalCores(AppDeviceSetup *client)
{
	return VidyoClientAndroidProcessorGetNumLogicalCores();
}

/**
 * forcePerf value of 0 does NOT force performance, value of 1 forces low and a value of 2 forces high
 */
LmiBool AppDeviceSetEncoderConfiguration(AppDeviceSetup* config, LmiBool directCall, LmiUint temporalSpatialTradeoff, LmiUint forcePerf)
{
	LmiBool tradeoffIsTemporal = (temporalSpatialTradeoff > 15);
	LmiBool hasNeon = VidyoClientAndroidProcessorHasNeon();
	LmiUint numCores = VidyoClientAndroidProcessorGetNumLogicalCores();

	LmiBool bUseHiPerformance;

	// Check if forcing the performance
	if (forcePerf == 1) {		// Force to low performance
		bUseHiPerformance = LMI_FALSE;
	} else if (forcePerf == 2) {	// Force to high performance
		bUseHiPerformance = LMI_TRUE;
	} else { // Default performance
		bUseHiPerformance = (hasNeon && (numCores > 2)) ? LMI_TRUE : LMI_FALSE;
	}
		
	if (directCall) {
		/*
		 * Only support very high performance Android devices
		 */
		if (bUseHiPerformance) {
			/* direct, NEON */
			if (tradeoffIsTemporal) {
				/* direct, NEON, temporal */
				config->captureWidth = 480;
				config->captureHeight = 352;
				config->croppedWidth = 480;
				config->croppedHeight = 352;
				config->captureFrameRate = 30;
				config->numLayers = 1;

				config->maxTileSingle.width    = 480;
				config->maxTileSingle.height   = 352;
				config->maxTileMultiple.width  = 480/2;
				config->maxTileMultiple.height = 352/2;
				config->maxFpsTile0            = 30;
				config->maxFps                 = 30;
			} else {
				/* direct, NEON, spatial */
				config->captureWidth = 640;
				config->captureHeight = 480;
				config->croppedWidth = 640;
				config->croppedHeight = 360;
				config->captureFrameRate = 15;
				config->numLayers = 1;

				config->maxTileSingle.width    = 640;
				config->maxTileSingle.height   = 360;
				config->maxTileMultiple.width  = 640/2;
				config->maxTileMultiple.height = 360/2;
				config->maxFpsTile0            = 15;
				config->maxFps                 = 15;
			}							
		} else {							
			/* direct, no NEON or 1 core */
			if (tradeoffIsTemporal) {
				/* direct, no NEON, temporal */
				config->captureWidth = 320;
				config->captureHeight = 180;
				config->croppedWidth = 320;
				config->croppedHeight = 180;
				config->captureFrameRate = 30;
				config->numLayers = 1;

				config->maxTileSingle.width    = 320;
				config->maxTileSingle.height   = 180;
				config->maxTileMultiple.width  = 320/2;
				config->maxTileMultiple.height = 180/2;
				config->maxFpsTile0            = 30;
				config->maxFps                 = 30;
			} else {
				/* direct, no NEON, spatial */
				config->captureWidth = 320;
				config->captureHeight = 180;
				config->croppedWidth = 320;
				config->croppedHeight = 180;
				config->captureFrameRate = 30;
				config->numLayers = 1;

				config->maxTileSingle.width    = 320;
				config->maxTileSingle.height   = 180;
				config->maxTileMultiple.width  = 320/2;
				config->maxTileMultiple.height = 180/2;
				config->maxFpsTile0            = 30;
				config->maxFps                 = 30;
			}				
		}
	} else {	/* multipoint call */
		if (bUseHiPerformance) {
			if (tradeoffIsTemporal) {
				config->captureWidth = 480;
				config->captureHeight = 352;
				config->croppedWidth = 480;
				config->croppedHeight = 352;
				config->captureFrameRate = 30;
				config->numLayers = 2;

				config->maxTileSingle.width    = 480;
				config->maxTileSingle.height   = 352;
				config->maxTileMultiple.width  = 480/2;
				config->maxTileMultiple.height = 352/2;
				config->maxFpsTile0            = 30;
				config->maxFps                 = 15;
			} else {
				config->captureWidth = 640;
				config->captureHeight = 480;
				config->croppedWidth = 640;
				config->croppedHeight = 360;
				config->captureFrameRate = 15;
				config->numLayers = 2;

				config->maxTileSingle.width    = 640;
				config->maxTileSingle.height   = 360;
				config->maxTileMultiple.width  = 640/2;
				config->maxTileMultiple.height = 360/2;
				config->maxFpsTile0            = 15;
				config->maxFps                 = 8;
			}
		} else {
			if (tradeoffIsTemporal) {
				config->captureWidth = 320;
				config->captureHeight = 180;
				config->croppedWidth = 320;
				config->croppedHeight = 180;
				config->captureFrameRate = 30;
				config->numLayers = 2;
				
				config->maxTileSingle.width    = 320;
				config->maxTileSingle.height   = 180;
				config->maxTileMultiple.width  = 320/2;
				config->maxTileMultiple.height = 180/2;
				config->maxFpsTile0            = 30;
				config->maxFps                 = 15;
			} else {
				config->captureWidth = 320;
				config->captureHeight = 180;
				config->croppedWidth = 320;
				config->croppedHeight = 180;
				config->captureFrameRate = 15;
				config->numLayers = 2;
				
				config->maxTileSingle.width    = 320;
				config->maxTileSingle.height   = 180;
				config->maxTileMultiple.width  = 320/2;
				config->maxTileMultiple.height = 180/2;
				config->maxFpsTile0            = 15;
				config->maxFps                 = 8;
			}
		}
	}
//    AppDeviceManagerResetCameraMode(&client->deviceManager, config);

	return LMI_TRUE;
}

LmiUint AppDeviceGetEncodedWidth(AppDeviceSetup* config)
{
	return 	config->captureWidth;
}

LmiUint AppDeviceGetEncodedHeight(AppDeviceSetup* config)
{
	return 	config->captureHeight;
}

LmiUint AppDeviceGetEncodedFrameRate(AppDeviceSetup* config)
{
	return 	config->captureFrameRate;
}


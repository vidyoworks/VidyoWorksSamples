// VidyoIoWrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Lmi\VidyoClient\VidyoConnector.h>
#include "VidyoIoWrapper.h"

static VidyoConnector vc;
static const LmiUint NUM_REMOTE_PARTICIPANTS = 16;
static VidyoIoWrapperOnSuccess gpOnSuccess;
static VidyoIoWrapperOnFailure gpOnFailure;
static VidyoIoWrapperOnDisconnected gpOnDisconnected;

bool VIoWrapperInitialize(VidyoWindowId parentWindow, VidyoRect *videoRect)
{
	VidyoConnectorInitialize();
	if (!VidyoConnectorConstruct(&vc,
		(const LmiViewId*)&parentWindow,
		VIDYO_CONNECTORVIEWSTYLE_Default,
		NUM_REMOTE_PARTICIPANTS,
		"info@VidyoClient info@VidyoConnector warning",
		"",
		NULL)) 
	{
		return false;
	}
	VidyoConnectorShowViewAt(&vc, NULL, videoRect->xPos, videoRect->yPos, videoRect->width, videoRect->height);

	return true;
}


bool VIoWrapperUninitialize()
{
	VidyoConnectorDestruct(&vc);
	// Uninitialize VidyoConnector
	VidyoConnectorUninitialize();
	return true;
}

void OnConnected(VidyoConnector* c) {
	gpOnSuccess();
}

// Handle attempted connection failure.
void OnConnectionFailed(VidyoConnector *c, VidyoConnectorFailReason reason) {
	gpOnFailure((VidyoIoWrapperFailReason)reason);
}

// Handle an existing session being disconnected.
void OnDisconnected(VidyoConnector *c, VidyoConnectorDisconnectReason reason) {
	gpOnDisconnected((VidyoIoWrapperDisconnectReason)reason);
}


bool VIoWrapperConnect(const char *host, const char * token, const char *displayName, const char* resourceId,
	VidyoIoWrapperOnSuccess onSuccess, VidyoIoWrapperOnFailure onFailure, VidyoIoWrapperOnDisconnected onDisconnected)
{
	gpOnSuccess = onSuccess;
	gpOnFailure = onFailure;
	gpOnDisconnected = onDisconnected;

	// Connect to resource
	LmiBool status = VidyoConnectorConnect(&vc,
		host,
		token,
		displayName,
		resourceId,
		OnConnected,
		OnConnectionFailed,
		OnDisconnected);

	return (status == LMI_TRUE) ? true : false;
}


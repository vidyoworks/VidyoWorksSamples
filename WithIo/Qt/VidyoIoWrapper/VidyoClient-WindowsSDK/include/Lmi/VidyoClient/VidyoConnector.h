/** 
{file:
	{name: VidyoConnector.h}
	{description: High level client library. }
	{copyright:
		(c) 2014-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_CONNECTOR_H_
#define VIDYO_CONNECTOR_H_

#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiMisc.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiUtils.h>
#include <Lmi/Os/LmiMallocAllocator.h>
#include <Lmi/Os/LmiOs.h>
#include <Lmi/Os/LmiLog.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoConnectorImpl_;
typedef struct VidyoConnectorImpl_ VidyoConnectorImpl;
Declare_LmiSharedPtr(VidyoConnectorImpl)
Declare_LmiSharedPtrWrapper(VidyoConnector, VidyoConnectorImpl)
Declare_LmiWeakPtrWrapper(VidyoConnectorHandle, VidyoConnector, VidyoConnectorImpl)

LMI_END_EXTERN_C

#include "VidyoLogger.h"
#include "VidyoLogRecord.h"
#include "VidyoParticipant.h"
#include "VidyoChatMessage.h"
#include "VidyoNetworkInterface.h"

/* devices */
#include "VidyoLocalCamera.h"
#include "VidyoLocalMicrophone.h"
#include "VidyoLocalSpeaker.h"
#include "VidyoLocalWindowShare.h"
#include "VidyoLocalMonitor.h"
#include "VidyoRemoteCamera.h"
#include "VidyoRemoteMicrophone.h"
#include "VidyoRemoteWindowShare.h"

LMI_BEGIN_EXTERN_C

/**
{package:
	{name: Connector}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoConnector.h}
	{description: Package that encapsulates all the APIs required to build a simple videoconferencing application.}
}
*/

/**
 {type apigroup="connector" reference-counted="yes":
	{name: VidyoConnector}
	{parent: Connector}
	{description: The videoconferencing API that handles all aspects of the media (audio/video) connection.}
}
*/

/**
{function apigroup="connector":
	{name: VidyoConnectorInitialize}
	{parent: Connector}
	{description: Initialize the VidyoConnector API.}
	{prototype: LmiBool VidyoConnectorInitialize(void)}
	{return: }
	{note: This function is required: Any application that uses the VidyoConnector API must initialize it first, typically when the application starts.}
}
*/
LmiBool VidyoConnectorInitialize(void);

/**
{function apigroup="connector":
	{name: VidyoConnectorUninitialize}
	{parent: Connector}
	{description: Uninitialize the VidyoConnector API.}
	{prototype: void VidyoConnectorUninitialize(void)}
	{note: This function is required: Any application that uses the VidyoConnector API must uninitialize it once it is no longer needed or before the application exits.}
}
*/
void VidyoConnectorUninitialize(void);

/**
{type apigroup="connector" visibility="private":
	{name: VidyoConnectorHandle}
	{parent: VidyoConnector}
	{description: Weak reference to a VidyoConnector object.}
}
*/

/**
 {type apigroup="connector" visibility="public":
	{name: VidyoConnectorFailReason}
	{parent: VidyoConnector}
	{description: Reasons why a connection attempt failed.}
	{value: {name: VIDYO_CONNECTORFAILREASON_ConnectionFailed}
		{description: The destination could not be reached.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_ConnectionLost}
		{description: The transport connection was lost prior to completing the login procedure.}}
 	{value: {name: VIDYO_CONNECTORFAILREASON_ConnectionTimeout}
		{description: The signaling connection timed-out prior to completing the login procedure.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_NoResponse}
		{description: The service was successfully contacted, but the service ignored the user's
			request to log in or it did not answer in a reasonable amount of time.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_Terminated}
		{description: The service was successfully contacted, but the service closed the connection
			or it refused to continue processing the login request.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_InvalidToken}
		{description: The token that was provided is unknown to the service or unauthorized to log in.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_UnableToCreateResource} {description: The server was unable to create the resource.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_NoResponseFromResource} {description: The server did
		not respond in a reasonable amount of time to the request to connect to the resource.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_InvalidResourceId} {description: The resource ID was invalid.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_ResourceFull} {description: The resource
		is at full capacity, and it cannot accept additional members.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_NotMember} {description: The resource allows
		only certain users to enter, and the current user is not one of them.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_Banned} {description: The user has
		been banned from entering the resource.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_MediaNotEnabled} {description: The client could not enable media.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_MediaFailed} {description: An established media connection failed.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_MiscLocalError} {description: The server
		rejected the user's request to enter the resource, due to a miscellaneous problem with the request.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_MiscRemoteError} {description: The server
		rejected the user's request to enter the resource, due to a miscellaneous problem of its own.}}
	{value: {name: VIDYO_CONNECTORFAILREASON_MiscError}
		{description: The login failed for some other miscellaneous reason.}}
}
*/
typedef enum
{
	VIDYO_CONNECTORFAILREASON_ConnectionFailed,
	VIDYO_CONNECTORFAILREASON_ConnectionLost,
	VIDYO_CONNECTORFAILREASON_ConnectionTimeout,
	VIDYO_CONNECTORFAILREASON_NoResponse,
	VIDYO_CONNECTORFAILREASON_Terminated,
	VIDYO_CONNECTORFAILREASON_InvalidToken,
	VIDYO_CONNECTORFAILREASON_UnableToCreateResource,
	VIDYO_CONNECTORFAILREASON_NoResponseFromResource,
	VIDYO_CONNECTORFAILREASON_InvalidResourceId,
	VIDYO_CONNECTORFAILREASON_ResourceFull,
	VIDYO_CONNECTORFAILREASON_NotMember,
	VIDYO_CONNECTORFAILREASON_Banned,
	VIDYO_CONNECTORFAILREASON_MediaNotEnabled,
	VIDYO_CONNECTORFAILREASON_MediaFailed,
	VIDYO_CONNECTORFAILREASON_MiscLocalError,
	VIDYO_CONNECTORFAILREASON_MiscRemoteError,
	VIDYO_CONNECTORFAILREASON_MiscError
} VidyoConnectorFailReason;

/**
 {type apigroup="connector" visibility="public":
	{name: VidyoConnectorDisconnectReason}
	{parent: VidyoConnector}
	{description: Reasons why an established connection was disconnected.}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_Disconnected}
		{description: The user disconnected gracefully.}}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_ConnectionLost}
		{description: The transport connection was lost.}}
 	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_ConnectionTimeout}
		{description: The signaling connection timed-out.}}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_NoResponse}
		{description: The service did not respond in a reasonable amount of time to a request by the user.}}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_Terminated}
		{description: The service closed the connection or otherwise terminated the login session.}}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_MiscLocalError}
		{description: A miscellaneous problem occurred with this client library.}}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_MiscRemoteError}
		{description: A miscellaneous problem occurred with the conferencing service.}}
	{value: {name: VIDYO_CONNECTORDISCONNECTREASON_MiscError}
		{description: The connection was closed for some other miscellaneous reason.}}
}
*/
typedef enum
{
	VIDYO_CONNECTORDISCONNECTREASON_Disconnected,
	VIDYO_CONNECTORDISCONNECTREASON_ConnectionLost,
	VIDYO_CONNECTORDISCONNECTREASON_ConnectionTimeout,
	VIDYO_CONNECTORDISCONNECTREASON_NoResponse,
	VIDYO_CONNECTORDISCONNECTREASON_Terminated,
	VIDYO_CONNECTORDISCONNECTREASON_MiscLocalError,
	VIDYO_CONNECTORDISCONNECTREASON_MiscRemoteError,
	VIDYO_CONNECTORDISCONNECTREASON_MiscError
} VidyoConnectorDisconnectReason;

/**
 {type apigroup="connector" visibility="public":
	{name: VidyoConnectorState}
	{parent: VidyoConnector}
	{description: States of a connection, mostly representing the progress of a connection attempt.}
	{value: {name: VIDYO_CONNECTORSTATE_Idle}
			{description: Not ready to connect, no devices.}
	}
	{value: {name: VIDYO_CONNECTORSTATE_Ready}
			{description: Ready to connect.}
	}
	{value: {name: VIDYO_CONNECTORSTATE_EstablishingConnection}
			{description: Establishing a connection to the server.}
	}
	{value: {name: VIDYO_CONNECTORSTATE_FindingResource}
			{description: Finding a resource.}
	}
	{value: {name: VIDYO_CONNECTORSTATE_ConnectingToResource}
			{description: Connecting to a resource.}
	}
	{value: {name: VIDYO_CONNECTORSTATE_EnablingMedia}
			{description: Enabling media.}
	}
	{value: {name: VIDYO_CONNECTORSTATE_Connected}
			{description: Sucessfully connected.}
	}
}
*/
typedef enum
{
	VIDYO_CONNECTORSTATE_Idle,
	VIDYO_CONNECTORSTATE_Ready,
	VIDYO_CONNECTORSTATE_EstablishingConnection,
	VIDYO_CONNECTORSTATE_FindingResource,
	VIDYO_CONNECTORSTATE_ConnectingToResource,
	VIDYO_CONNECTORSTATE_EnablingMedia,
	VIDYO_CONNECTORSTATE_Connected
} VidyoConnectorState;

/**
 {type apigroup="connector" visibility="public":
	{name: VidyoConnectorMode}
	{parent: VidyoConnector}
	{description: Operating modes of a VidyoConnector object.}
	{value: {name: VIDYO_CONNECTORMODE_Default}
		{description: The default operating mode.}}
	{value: {name: VIDYO_CONNECTORMODE_Foreground}
		{description: Runs in the foreground.}}
	{value: {name: VIDYO_CONNECTORMODE_Background}
		{description: Runs in the background.}}
	{note: The default is currently VIDYO_CONNECTORMODE_Foreground.}
}
*/
typedef enum
{
	VIDYO_CONNECTORMODE_Default,
	VIDYO_CONNECTORMODE_Foreground,
	VIDYO_CONNECTORMODE_Background
} VidyoConnectorMode;

/**
 {type apigroup="connector" visibility="public":
	{name: VidyoConnectorViewStyle}
	{parent: VidyoConnector}
	{description: Styles of the composite renderer, which apply to its layout and behaviour.}
	{value: {name: VIDYO_CONNECTORVIEWSTYLE_Default}
		{description: The default style.}}
	{value: {name: VIDYO_CONNECTORVIEWSTYLE_Tiles}
		{description: Participants are shown in sizes that best reflect their order of importance.}}
	{note: The default is currently VIDYO_CONNECTORVIEWSTYLE_Tiles.}
}
*/
typedef enum
{
	VIDYO_CONNECTORVIEWSTYLE_Default,
	VIDYO_CONNECTORVIEWSTYLE_Tiles
} VidyoConnectorViewStyle;

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLog}
	{parent: VidyoConnector}
	{description: Callback that is triggered for every log record. }
	{prototype: void (*VidyoConnectorOnLog)(VidyoConnector* c, const VidyoLogRecord* logRecord)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: logRecord}
		{description: The VidyoLogRecord object containing log record data.}
	}
}
*/
typedef void(*VidyoConnectorOnLog)(VidyoConnector* c, const VidyoLogRecord* logRecord);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalCameraAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local camera becomes available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalCameraAdded)(VidyoConnector* c, VidyoLocalCamera* localCamera)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localCamera}
		{description: Local camera that was added to the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalCameraAdded)(VidyoConnector* c, VidyoLocalCamera* localCamera);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalCameraRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local camera is no longer available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalCameraRemoved)(VidyoConnector* c, VidyoLocalCamera* localCamera)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localCamera}
		{description: Local camera that was removed from the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalCameraRemoved)(VidyoConnector* c, VidyoLocalCamera* localCamera);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalCameraSelected}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in which local camera is selected for use.}
	{prototype: void(*VidyoConnectorOnLocalCameraSelected)(VidyoConnector* c, VidyoLocalCamera* localCamera)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localCamera}
		{description: Local camera that was selected. NULL if none of them remain selected.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalCameraSelected)(VidyoConnector* c, VidyoLocalCamera* localCamera);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalCameraStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in the state of the camera such as being suspended or disabled.}
	{prototype: void(*VidyoConnectorOnLocalCameraStateUpdated)(VidyoConnector* c, VidyoLocalCamera* localCamera, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localCamera}
		{description: Local camera that was selected or NULL if nothing was selected.}
	}
	{parameter:
		{name: state}
		{description: New state of the Local camera.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalCameraStateUpdated)(VidyoConnector* c, VidyoLocalCamera* localCamera, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMicrophoneAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local microphone becomes available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalMicrophoneAdded)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMicrophone}
		{description: Local microphone that was added to the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMicrophoneAdded)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMicrophoneRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local microphone is no longer available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalMicrophoneRemoved)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMicrophone}
		{description: Local microphone that was removed from the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMicrophoneRemoved)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMicrophoneSelected}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in which local microphone is selected for use.}
	{prototype: void(*VidyoConnectorOnLocalMicrophoneSelected)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMicrophone}
		{description: Local microphone that was selected. NULL if none of them remain selected.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMicrophoneSelected)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMicrophoneStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in the state of the microphone such as being suspended or disabled.}
	{prototype: void(*VidyoConnectorOnLocalMicrophoneStateUpdated)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMicrophone}
		{description: Local microphone that was selected or NULL if nothing was selected.}
	}
	{parameter:
		{name: state}
		{description: New state of the Local microphone.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMicrophoneStateUpdated)(VidyoConnector* c, VidyoLocalMicrophone* localMicrophone, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalSpeakerAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local speaker becomes available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalSpeakerAdded)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localSpeaker}
		{description: Local speaker that was added to the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalSpeakerAdded)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalSpeakerRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local speaker is no longer available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalSpeakerRemoved)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localSpeaker}
		{description: Local speaker that was removed from the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalSpeakerRemoved)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalSpeakerSelected}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in which local speaker is selected for use.}
	{prototype: void(*VidyoConnectorOnLocalSpeakerSelected)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localSpeaker}
		{description: Local speaker that was selected. NULL if none of them remain selected.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalSpeakerSelected)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalSpeakerStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in the state of the speaker such as being suspended or disabled.}
	{prototype: void(*VidyoConnectorOnLocalSpeakerStateUpdated)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localSpeaker}
		{description: Local speaker that was selected or NULL if nothing was selected.}
	}
	{parameter:
		{name: state}
		{description: New state of the Local speaker.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalSpeakerStateUpdated)(VidyoConnector* c, VidyoLocalSpeaker* localSpeaker, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMonitorAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local monitor becomes available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalMonitorAdded)(VidyoConnector* c, VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMonitor}
		{description: Local monitor that was added to the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMonitorAdded)(VidyoConnector* c, VidyoLocalMonitor* localMonitor);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMonitorRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local monitor is no longer available to a VidyoConnector.}
	{prototype: void(*VidyoConnectorOnLocalMonitorRemoved)(VidyoConnector* c, VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMonitor}
		{description: Local monitor that was removed from the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMonitorRemoved)(VidyoConnector* c, VidyoLocalMonitor* localMonitor);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMonitorSelected}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in which local monitor is selected for sharing.}
	{prototype: void(*VidyoConnectorOnLocalMonitorSelected)(VidyoConnector* c, VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMonitor}
		{description: Local monitor that was selected. NULL if none of them remain selected.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMonitorSelected)(VidyoConnector* c, VidyoLocalMonitor* localMonitor);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalMonitorStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in the state of the monitor such as being suspended or disabled.}
	{prototype: void(*VidyoConnectorOnLocalMonitorStateUpdated)(VidyoConnector* c, VidyoLocalMonitor* localMonitor, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localMonitor}
		{description: Local monitor that was selected or NULL if nothing was selected. }
	}
	{parameter:
		{name: state}
		{description: New state of the Local monitor.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalMonitorStateUpdated)(VidyoConnector* c, VidyoLocalMonitor* localMonitor, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalWindowShareAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local window becomes available for a VidyoConnector to share in a conference.}
	{prototype: void(*VidyoConnectorOnLocalWindowShareAdded)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localWindowShare}
		{description: Local, shareable window that was added to the VidyoConnector.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalWindowShareAdded)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalWindowShareRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a local window is no longer available for a VidyoConnector to share in a conference.}
	{prototype: void(*VidyoConnectorOnLocalWindowShareRemoved)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localWindowShare}
		{description: Local window that was removed from the VidyoConnector. The window is no longer shareable.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalWindowShareRemoved)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalWindowShareSelected}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in which local window is selected for sharing.}
	{prototype: void(*VidyoConnectorOnLocalWindowShareSelected)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localWindowShare}
		{description: Local window that was selected. NULL if none of them remain selected.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalWindowShareSelected)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLocalWindowShareStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in the state of the window such as being suspended or disabled.}
	{prototype: void(*VidyoConnectorOnLocalWindowShareStateUpdated)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: localWindowShare}
		{description: Local window that was selected or NULL if nothing was selected.}
	}
	{parameter:
		{name: state}
		{description: New state of the Local window.}
	}
}
*/
typedef void(*VidyoConnectorOnLocalWindowShareStateUpdated)(VidyoConnector* c, VidyoLocalWindowShare* localWindowShare, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteCameraAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants adds a remote camera into a conference.}
	{prototype: void(*VidyoConnectorOnRemoteCameraAdded)(VidyoConnector* c, VidyoRemoteCamera* remoteCamera, const VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteCamera}
		{description: Remote camera that was added.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote camera.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteCameraAdded)(VidyoConnector* c, VidyoRemoteCamera* remoteCamera, const VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteCameraRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants removes a remote camera from a conference.}
	{prototype: void(*VidyoConnectorOnRemoteCameraRemoved)(VidyoConnector* c, VidyoRemoteCamera* remoteCamera, const VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteCamera}
		{description: Remote camera that was removed.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote camera.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteCameraRemoved)(VidyoConnector* c, VidyoRemoteCamera* remoteCamera, const VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteCameraStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants remote camera changes state in a conference.}
	{prototype: void(*VidyoConnectorOnRemoteCameraStateUpdated)(VidyoConnector* c, VidyoRemoteCamera* remoteCamera, const VidyoParticipant* participant, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteCamera}
		{description: Remote camera that was removed.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote camera.}
	}
	{parameter:
		{name: state}
		{description: The new state of the remote camera.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteCameraStateUpdated)(VidyoConnector* c, VidyoRemoteCamera* remoteCamera, const VidyoParticipant* participant, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteMicrophoneAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants adds a remote microphone into a conference.}
	{prototype: void(*VidyoConnectorOnRemoteMicrophoneAdded)(VidyoConnector* c, VidyoRemoteMicrophone* remoteMicrophone, const VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteMicrophone}
		{description: Remote microphone that was added.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote microphone.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteMicrophoneAdded)(VidyoConnector* c, VidyoRemoteMicrophone* remoteMicrophone, const VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteMicrophoneRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants removes a remote microphone from a conference.}
	{prototype: void(*VidyoConnectorOnRemoteMicrophoneRemoved)(VidyoConnector* c, VidyoRemoteMicrophone* remoteMicrophone, const VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteMicrophone}
		{description: Remote microphone that was removed.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote microphone.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteMicrophoneRemoved)(VidyoConnector* c, VidyoRemoteMicrophone* remoteMicrophone, const VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteMicrophoneStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants remote microphone changes state in a conference.}
	{prototype: void(*VidyoConnectorOnRemoteMicrophoneStateUpdated)(VidyoConnector* c, VidyoRemoteMicrophone* remoteMicrophone, const VidyoParticipant* participant, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteMicrophone}
		{description: Remote microphone that was removed.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote microphone.}
	}
	{parameter:
		{name: state}
		{description: The new state of the remote microphone.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteMicrophoneStateUpdated)(VidyoConnector* c, VidyoRemoteMicrophone* remoteMicrophone, const VidyoParticipant* participant, VidyoDeviceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteWindowShareAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants adds, or shares, a remote window into a conference.}
	{prototype: void(*VidyoConnectorOnRemoteWindowShareAdded)(VidyoConnector* c, VidyoRemoteWindowShare* remoteWindowShare, const VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteWindowShare}
		{description: Remote window that was added, or shared.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote window.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteWindowShareAdded)(VidyoConnector* c, VidyoRemoteWindowShare* remoteWindowShare, const VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteWindowShareRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants removes a remote window from a conference, or stops sharing it.}
	{prototype: void(*VidyoConnectorOnRemoteWindowShareRemoved)(VidyoConnector* c, VidyoRemoteWindowShare* remoteWindowShare, const VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteWindowShare}
		{description: Remote window that was removed, or no longer shared.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote window.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteWindowShareRemoved)(VidyoConnector* c, VidyoRemoteWindowShare* remoteWindowShare, const VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnRemoteWindowShareStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants remote window changes state in a conference.}
	{prototype: void(*VidyoConnectorOnRemoteWindowShareStateUpdated)(VidyoConnector* c, VidyoRemoteWindowShare* remoteWindowShare, const VidyoParticipant* participant, VidyoDeviceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: remoteWindowShare}
		{description: Remote window that was removed, or no longer shared.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who owns the remote window.}
	}
	{parameter:
		{name: state}
		{description: The new state of the remote window.}
	}
}
*/
typedef void(*VidyoConnectorOnRemoteWindowShareStateUpdated)(VidyoConnector* c, VidyoRemoteWindowShare* remoteWindowShare, const VidyoParticipant* participant, VidyoDeviceState state);

/**
{callback apigroup="connector":
	{name: VidyoConnectorOnNetworkInterfaceAdded}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a network interface is available to a VidyoConnector.}
	{prototype: void (*VidyoConnectorOnNetworkInterfaceAdded)(VidyoConnector* c, VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: networkInterface}
		{description: The VidyoNetworkInterface which described the interface.}
	}
}
*/
typedef void(*VidyoConnectorOnNetworkInterfaceAdded)(VidyoConnector* c, VidyoNetworkInterface* networkInterface);

/**
{callback apigroup="connector":
	{name: VidyoConnectorOnNetworkInterfaceRemoved}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a network interface is no longer available to a VidyoConnector.}
	{prototype: void (*VidyoConnectorOnNetworkInterfaceRemoved)(VidyoConnector* c, VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: networkInterface}
		{description: The VidyoNetworkInterface which described the interface.}
	}
}
*/
typedef void(*VidyoConnectorOnNetworkInterfaceRemoved)(VidyoConnector* c, VidyoNetworkInterface* networkInterface);

/**
{callback apigroup="connector":
	{name: VidyoConnectorOnNetworkInterfaceSelected}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in which network interface is selected for use.}
	{prototype: void (*VidyoConnectorOnNetworkInterfaceSelected)(VidyoConnector* c, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceTransportType transportType)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: networkInterface}
		{description: The VidyoNetworkInterface which described the interface.}
	}
	{parameter:
		{name: transportType}
		{description: The Transport type for which this interface was selected.}
	}
}
*/
typedef void(*VidyoConnectorOnNetworkInterfaceSelected)(VidyoConnector* c, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceTransportType transportType);

/**
{callback apigroup="connector":
	{name: VidyoConnectorOnNetworkInterfaceStateUpdated}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time there is a change in the state of the network interface such as being up or down.}
	{prototype: void (*VidyoConnectorOnNetworkInterfaceStateUpdated)(VidyoConnector* c, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceState state)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: networkInterface}
		{description: The VidyoNetworkInterface which described the interface.}
	}
	{parameter:
		{name: state}
		{description: The new state of the interface.}
	}
}
*/
typedef void(*VidyoConnectorOnNetworkInterfaceStateUpdated)(VidyoConnector* c, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceState state);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnSuccess}
	{parent: VidyoConnector}
	{description: Callback that is triggered when the connection is sucessfully established. }
	{prototype: void (*VidyoConnectorOnSuccess)(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
}
*/
typedef void(*VidyoConnectorOnSuccess)(VidyoConnector* c);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnFailure}
	{parent: VidyoConnector}
	{description: Callback that is triggered when the connection attempt has failed. }
	{prototype: void (*VidyoConnectorOnFailure)(VidyoConnector* c, VidyoConnectorFailReason reason)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: reason}
		{description: Reason why the connection could not be established.}
	}
}
*/
typedef void(*VidyoConnectorOnFailure)(VidyoConnector* c, VidyoConnectorFailReason reason);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnDisconnected}
	{parent: VidyoConnector}
	{description: Callback that is triggered when an established connection is disconnected. }
	{prototype: void (*VidyoConnectorOnDisconnected)(VidyoConnector* c, VidyoConnectorDisconnectReason reason)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: reason}
		{description: Reason why the established connection became disconnected.}
	}
}
*/
typedef void(*VidyoConnectorOnDisconnected)(VidyoConnector* c, VidyoConnectorDisconnectReason reason);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnParticipantJoined}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time another participant joins a conference.}
	{prototype: void (*VidyoConnectorOnParticipantJoined)(VidyoConnector* c, VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who joined the conference.}
	}
}
*/
typedef void(*VidyoConnectorOnParticipantJoined)(VidyoConnector* c, VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnParticipantLeft}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time an existing participant leaves a conference.}
	{prototype: void (*VidyoConnectorOnParticipantLeft)(VidyoConnector* c, VidyoParticipant* participant)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who left the conference.}
	}
}
*/
typedef void(*VidyoConnectorOnParticipantLeft)(VidyoConnector* c, VidyoParticipant* participant);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnDynamicParticipantChanged}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time the order of dyanmic participants has changed, based on active speech detection.}
	{prototype: void (*VidyoConnectorOnDynamicParticipantChanged)(VidyoConnector* c, LmiVector(VidyoParticipant)* participants, LmiVector(VidyoRemoteCamera)* remoteCameras)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: participants}
		{description: The vector of participants, listed in their order of importance.}
	}
	{parameter:
		{name: remoteCameras}
		{description: The vector of remote cameras that are being dynamically renderered, listed in the same order as the participants to which they belong, so that they match one-to-one.}
	}
}
*/
typedef void(*VidyoConnectorOnDynamicParticipantChanged)(VidyoConnector* c, LmiVector(VidyoParticipant)* participants, LmiVector(VidyoRemoteCamera)* remoteCameras);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnLoudestParticipantChanged}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time one of the other participants becomes the loudest, based on active speech detection.}
	{prototype: void (*VidyoConnectorOnLoudestParticipantChanged)(VidyoConnector* c, const VidyoParticipant* participant, LmiBool audioOnly)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: participant}
		{description: New loudest participant.}
	}
	{parameter:
		{name: audioOnly}
		{description: LMI_TRUE if the participant does not have video streams.}
	}
}
*/
typedef void(*VidyoConnectorOnLoudestParticipantChanged)(VidyoConnector* c, const VidyoParticipant* participant, LmiBool audioOnly);


/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnChatMessageReceived}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a chat message is received from one of the other participants.}
	{prototype: void (*VidyoConnectorOnChatMessageReceived)(VidyoConnector* c, const VidyoParticipant* participant, VidyoChatMessage* chatMessage)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: participant}
		{description: The VidyoParticipant who sent the chat message.}
	}
	{parameter:
		{name: chatMessage}
		{description: The VidyoChatMessage that was received.}
	}
}
*/
typedef void(*VidyoConnectorOnChatMessageReceived)(VidyoConnector* c, const VidyoParticipant* participant, VidyoChatMessage* chatMessage);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnAvailableResourcesChanged}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time the available local resources change.}
	{prototype: void (*VidyoConnectorOnAvailableResourcesChanged)(VidyoConnector* c, LmiUint cpuEncode, LmiUint cpuDecode, LmiUint bandwidthSend, LmiUint bandwidthReceive)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: cpuEncode}
		{description: Percent of maximum CPU available to encode the streams.}
	}
	{parameter:
		{name: cpuDecode}
		{description: Percent of maximum CPU available to decode the streams.}
	}
	{parameter:
		{name: bandwidthSend}
		{description: Percentage of maximum bandwidth avaialble to transmit the streams.}
	}
	{parameter:
		{name: bandwidthReceive}
		{description: Percentage of maximum bandwidth avaialble to receive the streams.}
	}
}
*/
typedef void(*VidyoConnectorOnAvailableResourcesChanged)(VidyoConnector* c, LmiUint cpuEncode, LmiUint cpuDecode, LmiUint bandwidthSend, LmiUint bandwidthReceive);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorRecorderInCall}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time a recorder joins or leaves the call.}
	{prototype: void (*VidyoConnectorRecorderInCall)(VidyoConnector* c, LmiBool recorderInCall )}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: recorderInCall}
		{description: LMI_TRUE when a recorder joined, LMI_FALSE when no recorder are in the call}
	}
}
*/
typedef void(*VidyoConnectorRecorderInCall)(VidyoConnector* c, LmiBool recorderInCall );

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnMaxRemoteSourcesChanged}
	{parent: VidyoConnector}
	{description: Callback that is triggered each time the local client's maximum decoding capability changes.}
	{prototype: void (*VidyoConnectorOnMaxRemoteSourcesChanged)(VidyoConnector* c, LmiUint maxRemoteSources)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
	{parameter:
		{name: maxRemoteSources}
		{description: Maximum number of remote video sources that can be recived both statically and dynamically.}
	}
	{note: When the application is managing the statically viewed sources through the VidyoConnectorAssign*() API, such as VidyoConnectorAssignViewToRemoteCamera(), the application is responsible for keeping track of the number of these views. When the number of maximum remote participants that can be decoded falls below what the applicaiton has statically viewed, the application must choose which static sources to enable or disable to meet the resource manager constraints.}
}
*/
typedef void(*VidyoConnectorOnMaxRemoteSourcesChanged)(VidyoConnector* c, LmiUint maxRemoteSources);

/**
 {callback apigroup="connector":
	{name: VidyoConnectorOnWebProxyCredentialsRequest}
	{parent: VidyoConnector}
	{description: Callback that is triggered when Web Proxy Server requires password.}
	{prototype: void (*VidyoConnectorOnWebProxyCredentialsRequest)(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector that triggered the callback.}
	}
}
*/
typedef void(*VidyoConnectorOnWebProxyCredentialsRequest)(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorConstruct}
	{parent: VidyoConnector}
	{description: Constructs the VidyoConnector. }
	{prototype: VidyoConnector* VidyoConnectorConstruct(VidyoConnector* c, const LmiViewId* viewId, VidyoConnectorViewStyle viewStyle, LmiUint remoteParticipants, const char* logFileFilter, const char* logFileName, const LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform-specific view ID where the VidyoConnector's rendering window will be added as a child window. It will be used to render the preview and composite remote participants.}
	}
	{parameter:
		{name: viewStyle}
		{description: Type of the composite renderer which represents the visual style and behaviour. }
	}
	{parameter:
		{name: remoteParticipants}
		{description: Number of remote participants to composite into the window. Setting the value to 0 (zero) will render the preview only.}
	}
	{parameter:
		{name: logFileFilter}
		{description:
	   {p: A space-separated (or comma-separated)
		 sequence of names of log levels, each optionally followed by a
		 category.  Categories are
		 separated from levels by the character \'@\'.}
	   {p: Either a level or category may be specified as \'all\' or \'*\'
	     (interchangeably), meaning all levels or categories.  A level specified
		 without a category is equivalent to a level@*.}
	   {p: The levels are: \'fatal\', \'error\', \'warning\', \'info\', \'debug\', 
		 \'sent\', \'received\', \'enter\', and '\leave\'.}
	   {p: The level may be prefixed by \'-\' or \'!\' (interchangeably), meaning to remove
		 the given level (or levels, see below) from the given category.
		 The string \'none\' is equivalent to \'-all\'.}
	   {p: The first level in the list may be prefixed by \'+\'.
	     If the first level begins with a \'+\' or \'-\'/\'!\', the string
		 is used to modify the listener\'s existing levels and categories.
		 Otherwise, unless the {code: add} parameter is true, the levels and categories 
 		 specified in the string replace all existing levels and categories for the listener.  
 		 The leading character \'+\' may be present before other levels, but is ignored.}
	   {p: Unless they are preceded by \'=\', level names imply other levels
		 as well.  In particular, each of the levels \'fatal\', \'error\', \'warning\',
		 \'info\', and \'debug\' implies the levels higher than it, when specified
		 positively; \'sent\' and \'received\' always imply each other; and \'enter\' and
		 \'leave\' always imply each other.}
	   {p: See VidyoConnectorGetLogCategories for determining the names and descriptions of registered categories.}
	   {p: Level names are case-insensitive; category names are case-sensitive.}
	   {p: Example: "all" - all levels, all categories.}
	   {p: Example: "all -enter" - all categories, all levels but enter and leave.}
	   {p: Example: "*@VidyoClient" - all levels for the VidyoClient category.}
	   {p: Example: "-*@VidyoClient" - remove all levels from the VidyoClient category.}
	   {p: Example: "debug" - all categories, fatal, error, warning, info, and debug levels.}
	   {p: Example: "=debug" - all categories, debug level only.}
	   {p: Example: "all -=enter" - all categories, all levels but enter (leave is still included).}
	   {p: Example: "error@VidyoClient" - fatal and error only for the VidyoClient category.}
	   {p: Example: "warning debug@VidyoClient" - fatal, error, and warning for all categories; additionally, info and debug for the VidyoClient category.}
	}}
	{parameter:
		{name: logFileName}
		{description: Full path to the file where the log should be stored; otherwise, NULL or empty string, in order to use the default OS-dependent writable path. }
	}
	{parameter:
		{name: userData}
		{description: Arbitrary user data that can be retrieved later.}
	}
	{return: The constructed object on success. NULL on failure.}
	{note: LmiViewId is HWND on Windows, NSView on Mac OS X, UIView on iOS, window on X11, ViewGroup on Android.}
	{note: The view will not be shown until VidyoConnectorShowViewAt is called with valid parameters.}
}
*/
VidyoConnector* VidyoConnectorConstruct(VidyoConnector* c, const LmiViewId* viewId, VidyoConnectorViewStyle viewStyle, LmiUint remoteParticipants, const char* logFileFilter, const char* logFileName, const LmiVoidPtr userData);

/**
 {function apigroup="connector":
	{name: VidyoConnectorConstructCopy}
	{parent: VidyoConnector}
	{description: Constructs an VidyoConnector object as a copy of another.}
	{prototype: VidyoConnector *VidyoConnectorConstructCopy(VidyoConnector* c, const VidyoConnector *other)}
	{parameter: {name: c} {description: The VidyoConnector object to construct.}}
	{parameter: {name: other} {description: The VidyoConnector object from which to construct a copy.}}
	{return: The constructed object on success. NULL on failure.}
}
*/

/**
 {function apigroup="connector":
	{name: VidyoConnectorDestruct}
	{parent: VidyoConnector}
	{description: Destructs an VidyoConnector object.}
	{prototype: void VidyoConnectorDestruct(VidyoConnector* c)}
	{parameter: {name: c} {description: The VidyoConnector object to destruct.}}
}
*/

/**
 {function apigroup="connector":
	{name: VidyoConnectorAssign}
	{parent: VidyoConnector}
	{description: Assigns one VidyoConnector object the value of another. }
	{prototype: VidyoConnector *VidyoConnectorAssign(VidyoConnector* c, const VidyoConnector *other)}
	{parameter: {name: c} {description: The VidyoConnector object.}}
	{parameter: {name: other} {description: The VidyoConnector object from which to assign.}}
	{return: The destination object on success. NULL on failure.}
}
*/

/**
 {function apigroup="connector" visibility="private":
	{name: VidyoConnectorSetUserData}
	{parent: VidyoConnector}
	{description: Associates user data with a VidyoConnector object, so that such data may be retrieved later.}
	{prototype: void VidyoConnectorSetUserData(VidyoConnector* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: userData}
		{description: Arbitrary data.}
	}
}
*/
void VidyoConnectorSetUserData(VidyoConnector* c, LmiVoidPtr userData);

/**
 {function apigroup="connector" visibility="private":
	{name: VidyoConnectorGetUserData}
	{parent: VidyoConnector}
	{description: Retreives any user data that was associated with a VidyoConnector object.}
	{prototype: LmiVoidPtr VidyoConnectorGetUserData(const VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: User data on success. NULL on failure.}
}
*/
LmiVoidPtr VidyoConnectorGetUserData(const VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetMode}
	{parent: VidyoConnector}
	{description: Sets the operating mode of the VidyoConnector.}
	{prototype: LmiBool VidyoConnectorSetMode(VidyoConnector* c, VidyoConnectorMode mode)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: mode}
		{description: Desired operating mode.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSetMode(VidyoConnector* c, VidyoConnectorMode mode);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetLocation}
	{parent: VidyoConnector}
	{description: Sets the geographic location of the endpoint using the VidyoConnector.}
	{prototype: LmiBool VidyoConnectorSetLocation(VidyoConnector* c, LmiFloat64 latitude, LmiFloat64 longitude)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: latitude}
		{description: Latitude of the geographic coordinate.}
	}
	{parameter:
		{name: longitude}
		{description: Longitude of the geographic coordinate.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: Setting the location manually overrides other proximity detection mechanisms that are used by VidyoConnector to determine the best routing performance. }
}
*/
LmiBool VidyoConnectorSetLocation(VidyoConnector* c, LmiFloat64 latitude, LmiFloat64 longitude);

/**
{function apigroup="connector":
	{name: VidyoConnectorEnableDebug}
	{parent: VidyoConnector}
	{description: Enabled debug mode which will start debug logging and enable statistics.}
	{prototype: LmiBool VidyoConnectorEnableDebug(VidyoConnector* c, LmiUint port, const char *logFilter)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: port}
		{description: Local listening port for debugging.  }
	}
	{parameter:
		{name: logFilter}
		{description: Log filter to use on the debug port. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorEnableDebug(VidyoConnector* c, LmiUint port, const char *logFilter);

/**
{function apigroup="connector":
	{name: VidyoConnectorDisableDebug}
	{parent: VidyoConnector}
	{description: }
	{prototype: void VidyoConnectorDisableDebug(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
}
*/
void VidyoConnectorDisableDebug(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterLogEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about log events.}
	{prototype: LmiBool VidyoConnectorRegisterLogEventListener(VidyoConnector* c, VidyoConnectorOnLog onLog, const char* filter)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onLog}
		{description: Callback that is triggered for every new log record.}
	}
	{parameter:
		{name: filter}
		{description:
	   {p: A space-separated (or comma-separated)
		 sequence of names of log levels, each optionally followed by a
		 category.  Categories are
		 separated from levels by the character \'@\'.}
	   {p: Either a level or category may be specified as \'all\' or \'*\'
	     (interchangeably), meaning all levels or categories.  A level specified
		 without a category is equivalent to a level@*.}
	   {p: The levels are: \'fatal\', \'error\', \'warning\', \'info\', \'debug\', 
		 \'sent\', \'received\', \'enter\', and '\leave\'.}
	   {p: The level may be prefixed by \'-\' or \'!\' (interchangeably), meaning to remove
		 the given level (or levels, see below) from the given category.
		 The string \'none\' is equivalent to \'-all\'.}
	   {p: The first level in the list may be prefixed by \'+\'.
	     If the first level begins with a \'+\' or \'-\'/\'!\', the string
		 is used to modify the listener\'s existing levels and 45categories.
		 Otherwise, unless the {code: add} parameter is true, the levels and categories 
 		 specified in the string replace all existing levels and categories for the listener.  
 		 The leading character \'+\' may be present before other levels, but is ignored.}
	   {p: Unless they are preceded by \'=\', level names imply other levels
		 as well.  In particular, each of the levels \'fatal\', \'error\', \'warning\',
		 \'info\', and \'debug\' implies the levels higher than it, when specified
		 positively; \'sent\' and \'received\' always imply each other; and \'enter\' and
		 \'leave\' always imply each other.}
	   {p: See VidyoConnectorGetLogCategories for determining the names and descriptions of registered categories.}
	   {p: Level names are case-insensitive; category names are case-sensitive.}
	   {p: Example: "all" - all levels, all categories.}
	   {p: Example: "all -enter" - all categories, all levels but enter and leave.}
	   {p: Example: "*@VidyoClient" - all levels for the VidyoClient category.}
	   {p: Example: "-*@VidyoClient" - remove all levels from the VidyoClient category.}
	   {p: Example: "debug" - all categories, fatal, error, warning, info, and debug levels.}
	   {p: Example: "=debug" - all categories, debug level only.}
	   {p: Example: "all -=enter" - all categories, all levels but enter (leave is still included).}
	   {p: Example: "error@VidyoClient" - fatal and error only for the VidyoClient category.}
	   {p: Example: "warning debug@VidyoClient" - fatal, error, and warning for all categories; additionally, info and debug for the VidyoClient category.}
	}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterLogEventListener(VidyoConnector* c, VidyoConnectorOnLog onLog, const char* filter);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterLogEventListener}
	{parent: VidyoConnector}
	{description: Unregisters log event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterLogEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterLogEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterLocalCameraEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about local camera events.}
	{prototype: LmiBool VidyoConnectorRegisterLocalCameraEventListener(VidyoConnector* c, VidyoConnectorOnLocalCameraAdded onAdded, VidyoConnectorOnLocalCameraRemoved onRemoved, VidyoConnectorOnLocalCameraSelected onSelected, VidyoConnectorOnLocalCameraStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing camera added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the camera is removed.}
	}
	{parameter:
		{name: onSelected}
		{description: Callback that is triggered when a camera is selected for use.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when a camera state is updated.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterLocalCameraEventListener(VidyoConnector* c, VidyoConnectorOnLocalCameraAdded onAdded, VidyoConnectorOnLocalCameraRemoved onRemoved, VidyoConnectorOnLocalCameraSelected onSelected, VidyoConnectorOnLocalCameraStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterLocalCameraEventListener}
	{parent: VidyoConnector}
	{description: Unregisters local camera event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterLocalCameraEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterLocalCameraEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectLocalCamera}
	{parent: VidyoConnector}
	{description: Selects the local camera to use.}
	{prototype: LmiBool VidyoConnectorSelectLocalCamera(VidyoConnector* c, const VidyoLocalCamera* localCamera)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: localCamera}
		{description: Local camera to select. NULL if none of them should be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectLocalCamera(VidyoConnector* c, const VidyoLocalCamera* localCamera);

/**
 {function apigroup="connector":
	{name: VidyoConnectorAssignViewToLocalCamera}
	{parent: VidyoConnector}
	{description: Assigns the view in which to show the preview from a local camera.}
	{prototype: LmiBool VidyoConnectorAssignViewToLocalCamera(VidyoConnector* c, const LmiViewId* viewId, VidyoLocalCamera* localCamera, LmiBool displayCropped, LmiBool allowZoom)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID where the participant will be rendered.}
	}
	{parameter:
		{name: localCamera}
		{description: The VidyoLocalCamera that will be shown.}
	}
	{parameter:
		{name: displayCropped}
		{description: Render the image as cropped. Otherwise letterbox.}
	}
	{parameter:
		{name: allowZoom}
		{description: Allow zooming of the image with mouse or touch.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: This API will work only if compositing had been disabled by passing a NULL LmiViewId to VidyoConnectorConstruct.}
	{note: The view will not be shown until VidyoConnectorShowViewAt is called with valid parameters.}
}
*/
LmiBool VidyoConnectorAssignViewToLocalCamera(VidyoConnector* c, const LmiViewId* viewId, VidyoLocalCamera* localCamera, LmiBool displayCropped, LmiBool allowZoom);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterLocalMicrophoneEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about local microphone events.}
	{prototype: LmiBool VidyoConnectorRegisterLocalMicrophoneEventListener(VidyoConnector* c, VidyoConnectorOnLocalMicrophoneAdded onAdded, VidyoConnectorOnLocalMicrophoneRemoved onRemoved, VidyoConnectorOnLocalMicrophoneSelected onSelected, VidyoConnectorOnLocalMicrophoneStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing microphone added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the microphone is removed.}
	}
	{parameter:
		{name: onSelected}
		{description: Callback that is triggered when a microphone is selected for use.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when a microphone state is updated.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterLocalMicrophoneEventListener(VidyoConnector* c, VidyoConnectorOnLocalMicrophoneAdded onAdded, VidyoConnectorOnLocalMicrophoneRemoved onRemoved, VidyoConnectorOnLocalMicrophoneSelected onSelected, VidyoConnectorOnLocalMicrophoneStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterLocalMicrophoneEventListener}
	{parent: VidyoConnector}
	{description: Unregisters local microphone event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterLocalMicrophoneEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterLocalMicrophoneEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectLocalMicrophone}
	{parent: VidyoConnector}
	{description: Selects the local microphone to use.}
	{prototype: LmiBool VidyoConnectorSelectLocalMicrophone(VidyoConnector* c, const VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: localMicrophone}
		{description: Local microphone to select. NULL if none of them should be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectLocalMicrophone(VidyoConnector* c, const VidyoLocalMicrophone* localMicrophone);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterLocalSpeakerEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about local speaker events.}
	{prototype: LmiBool VidyoConnectorRegisterLocalSpeakerEventListener(VidyoConnector* c, VidyoConnectorOnLocalSpeakerAdded onAdded, VidyoConnectorOnLocalSpeakerRemoved onRemoved, VidyoConnectorOnLocalSpeakerSelected onSelected, VidyoConnectorOnLocalSpeakerStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing speaker added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the speaker is removed.}
	}
	{parameter:
		{name: onSelected}
		{description: Callback that is triggered when a speaker is selected for use.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when a speaker state is updated.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterLocalSpeakerEventListener(VidyoConnector* c, VidyoConnectorOnLocalSpeakerAdded onAdded, VidyoConnectorOnLocalSpeakerRemoved onRemoved, VidyoConnectorOnLocalSpeakerSelected onSelected, VidyoConnectorOnLocalSpeakerStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterLocalSpeakerEventListener}
	{parent: VidyoConnector}
	{description: Unregisters local speaker event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterLocalSpeakerEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterLocalSpeakerEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectLocalSpeaker}
	{parent: VidyoConnector}
	{description: Selects the local speaker to use.}
	{prototype: LmiBool VidyoConnectorSelectLocalSpeaker(VidyoConnector* c, const VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: localSpeaker}
		{description: Local speaker to select. NULL if none of them should be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectLocalSpeaker(VidyoConnector* c, const VidyoLocalSpeaker* localSpeaker);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterLocalMonitorEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about local monitor events.}
	{prototype: LmiBool VidyoConnectorRegisterLocalMonitorEventListener(VidyoConnector* c, VidyoConnectorOnLocalMonitorAdded onAdded, VidyoConnectorOnLocalMonitorRemoved onRemoved, VidyoConnectorOnLocalMonitorSelected onSelected, VidyoConnectorOnLocalMonitorStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing monitor added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the monitor is removed.}
	}
	{parameter:
		{name: onSelected}
		{description: Callback that is triggered when a monitor is selected for use.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when a monitor state is updated.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterLocalMonitorEventListener(VidyoConnector* c, VidyoConnectorOnLocalMonitorAdded onAdded, VidyoConnectorOnLocalMonitorRemoved onRemoved, VidyoConnectorOnLocalMonitorSelected onSelected, VidyoConnectorOnLocalMonitorStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterLocalMonitorEventListener}
	{parent: VidyoConnector}
	{description: Unregisters local monitor event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterLocalMonitorEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterLocalMonitorEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectLocalMonitor}
	{parent: VidyoConnector}
	{description: Selects the local monitor to share in a conference.}
	{prototype: LmiBool VidyoConnectorSelectLocalMonitor(VidyoConnector* c, const VidyoLocalMonitor *localMonitor)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: localMonitor}
		{description: Local monitor to share in a conference. NULL if none of them should be shared.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectLocalMonitor(VidyoConnector* c, const VidyoLocalMonitor *localMonitor);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterLocalWindowShareEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about local shareable-window events.}
	{prototype: LmiBool VidyoConnectorRegisterLocalWindowShareEventListener(VidyoConnector* c, VidyoConnectorOnLocalWindowShareAdded onAdded, VidyoConnectorOnLocalWindowShareRemoved onRemoved, VidyoConnectorOnLocalWindowShareSelected onSelected, VidyoConnectorOnLocalWindowShareStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing window added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the window is removed.}
	}
	{parameter:
		{name: onSelected}
		{description: Callback that is triggered when a window is selected for use.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when a window state is updated.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterLocalWindowShareEventListener(VidyoConnector* c, VidyoConnectorOnLocalWindowShareAdded onAdded, VidyoConnectorOnLocalWindowShareRemoved onRemoved, VidyoConnectorOnLocalWindowShareSelected onSelected, VidyoConnectorOnLocalWindowShareStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterLocalWindowShareEventListener}
	{parent: VidyoConnector}
	{description: Unregisters local window share event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterLocalWindowShareEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterLocalWindowShareEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectLocalWindowShare}
	{parent: VidyoConnector}
	{description: Selects the local window to share in a conference.}
	{prototype: LmiBool VidyoConnectorSelectLocalWindowShare(VidyoConnector* c, const VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: localWindowShare}
		{description: Local window to share in a conference. NULL if none of them should be shared.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectLocalWindowShare(VidyoConnector* c, const VidyoLocalWindowShare* localWindowShare);

/**
 {function apigroup="connector" deprecated="yes" replaced-by="VidyoConnectorShowPreview":
	{name: VidyoConnectorSetPreview}
	{parent: VidyoConnector}
	{description: Sets the flag to show/hide the local camera preview.}
	{prototype: LmiBool VidyoConnectorSetPreview(VidyoConnector* c, LmiBool preview)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: preview}
		{description: Flag to show/hide the local camera preview.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSetPreview(VidyoConnector* c, LmiBool preview);

/**
 {function apigroup="connector":
	{name: VidyoConnectorShowPreview}
	{parent: VidyoConnector}
	{description: Sets the flag to show/hide the local camera preview.}
	{prototype: LmiBool VidyoConnectorShowPreview(VidyoConnector* c, LmiBool preview)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: preview}
		{description: Flag to show/hide the local camera preview.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorShowPreview(VidyoConnector* c, LmiBool preview);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetCameraPrivacy}
	{parent: VidyoConnector}
	{description: Sets the flag to show/hide the local camera.}
	{prototype: LmiBool VidyoConnectorSetCameraPrivacy(VidyoConnector* c, LmiBool privacy)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: privacy}
		{description: Flag to show/hide the local camera.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSetCameraPrivacy(VidyoConnector* c, LmiBool privacy);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectDefaultCamera}
	{parent: VidyoConnector}
	{description: Resets the camera selection to pick the Default camera.}
	{prototype: LmiBool VidyoConnectorSelectDefaultCamera(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectDefaultCamera(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorCycleCamera}
	{parent: VidyoConnector}
	{description: Cycles camera selection to the next available camera.}
	{prototype: LmiBool VidyoConnectorCycleCamera(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorCycleCamera(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetMicrophonePrivacy}
	{parent: VidyoConnector}
	{description: Sets the flag to mute/unmute the microphone.}
	{prototype: LmiBool VidyoConnectorSetMicrophonePrivacy(VidyoConnector* c, LmiBool privacy)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: privacy}
		{description: Flag to mute/unmute the microphone.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSetMicrophonePrivacy(VidyoConnector* c, LmiBool privacy);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectDefaultMicrophone}
	{parent: VidyoConnector}
	{description: Resets the microphone selection to pick the Default microphone.}
	{prototype: LmiBool VidyoConnectorSelectDefaultMicrophone(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectDefaultMicrophone(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorCycleMicrophone}
	{parent: VidyoConnector}
	{description: Cycles microphone selection to the next available microphone.}
	{prototype: LmiBool VidyoConnectorCycleMicrophone(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorCycleMicrophone(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetSpeakerPrivacy}
	{parent: VidyoConnector}
	{description: Sets the flag to mute/unmute the speaker.}
	{prototype: LmiBool VidyoConnectorSetSpeakerPrivacy(VidyoConnector* c, LmiBool privacy)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: privacy}
		{description: Flag to mute/unmute the speaker.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSetSpeakerPrivacy(VidyoConnector* c, LmiBool privacy);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectDefaultSpeaker}
	{parent: VidyoConnector}
	{description: Resets the speaker selection to pick the Default speaker.}
	{prototype: LmiBool VidyoConnectorSelectDefaultSpeaker(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectDefaultSpeaker(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorCycleSpeaker}
	{parent: VidyoConnector}
	{description: Cycles speaker selection to the next available speaker.}
	{prototype: LmiBool VidyoConnectorCycleSpeaker(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorCycleSpeaker(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterParticipantEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about participant events.}
	{prototype: LmiBool VidyoConnectorRegisterParticipantEventListener(VidyoConnector* c, VidyoConnectorOnParticipantJoined onJoined, VidyoConnectorOnParticipantLeft onLeft, VidyoConnectorOnDynamicParticipantChanged onDynamicChanged, VidyoConnectorOnLoudestParticipantChanged onLoudestChanged)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onJoined}
		{description: Callback that is triggered when another participant joins a conference.}
	}
	{parameter:
		{name: onLeft}
		{description: Callback that is triggered when an existing participant leaves a conference.}
	}
	{parameter:
		{name: onDynamicChanged}
		{description: Callback that is triggered when the order of participants has changed, based on their importance according to active speech detection.}
	}
	{parameter:
		{name: onLoudestChanged}
		{description: Callback that is triggered when a new participant becomes the loudest, based on active speech detection.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterParticipantEventListener(VidyoConnector* c, VidyoConnectorOnParticipantJoined onJoined, VidyoConnectorOnParticipantLeft onLeft, VidyoConnectorOnDynamicParticipantChanged onDynamicChanged, VidyoConnectorOnLoudestParticipantChanged onLoudestChanged);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterParticipantEventListener}
	{parent: VidyoConnector}
	{description: Unregisters participant event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterParticipantEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterParticipantEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterMessageEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about message events.}
	{prototype: LmiBool VidyoConnectorRegisterMessageEventListener(VidyoConnector* c, VidyoConnectorOnChatMessageReceived onChatMessageReceived)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onChatMessageReceived}
		{description: Callback that is triggered when a chat message is received from a participant.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterMessageEventListener(VidyoConnector* c, VidyoConnectorOnChatMessageReceived onChatMessageReceived);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterMessageEventListener}
	{parent: VidyoConnector}
	{description: Unregisters message event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterMessageEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterMessageEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterRemoteCameraEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about remote camera events.}
	{prototype: LmiBool VidyoConnectorRegisterRemoteCameraEventListener(VidyoConnector* c, VidyoConnectorOnRemoteCameraAdded onAdded, VidyoConnectorOnRemoteCameraRemoved onRemoved, VidyoConnectorOnRemoteCameraStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered each time one of the other participants adds a remote camera into a conference.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered each time one of the other participants removes a remote camera from a conference.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered each time one of the other participants remote camera chagnes state in a conference.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterRemoteCameraEventListener(VidyoConnector* c, VidyoConnectorOnRemoteCameraAdded onAdded, VidyoConnectorOnRemoteCameraRemoved onRemoved, VidyoConnectorOnRemoteCameraStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterRemoteCameraEventListener}
	{parent: VidyoConnector}
	{description: Unregisters remote camera event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterRemoteCameraEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterRemoteCameraEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorAssignViewToRemoteCamera}
	{parent: VidyoConnector}
	{description: Assigns the view in which to show the remote camera of one of the other participants.}
	{prototype: LmiBool VidyoConnectorAssignViewToRemoteCamera(VidyoConnector* c, const LmiViewId* viewId, VidyoRemoteCamera* remoteCamera, LmiBool displayCropped, LmiBool allowZoom)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID where the participant will be rendered.}
	}
	{parameter:
		{name: remoteCamera}
		{description: The VidyoRemoteCamera that will be shown.}
	}
	{parameter:
		{name: displayCropped}
		{description: Render the image as cropped. Otherwise letterbox.}
	}
	{parameter:
		{name: allowZoom}
		{description: Allow zooming of the image with mouse or touch.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: This API will work only if compositing had been disabled by passing a NULL LmiViewId to VidyoConnectorConstruct.}
	{note: The application needs to make sure the sources are hidden when the local CPU and bandwidth are limited, by monitoring the VidyoConnectorOnResourcesChanged callback and showing/hiding sources based on avaialble resources.}
	{note: The view will not be shown until VidyoConnectorShowViewAt is called with valid parameters.}
}
*/
LmiBool VidyoConnectorAssignViewToRemoteCamera(VidyoConnector* c, const LmiViewId* viewId, VidyoRemoteCamera* remoteCamera, LmiBool displayCropped, LmiBool allowZoom);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterRemoteMicrophoneEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about remote microphone events.}
	{prototype: LmiBool VidyoConnectorRegisterRemoteMicrophoneEventListener(VidyoConnector* c, VidyoConnectorOnRemoteMicrophoneAdded onAdded, VidyoConnectorOnRemoteMicrophoneRemoved onRemoved, VidyoConnectorOnRemoteMicrophoneStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered when another participant adds a microphone into a conference.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when another participant removes a microphone from a conference.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when another participant microphone changes state in a conference.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterRemoteMicrophoneEventListener(VidyoConnector* c, VidyoConnectorOnRemoteMicrophoneAdded onAdded, VidyoConnectorOnRemoteMicrophoneRemoved onRemoved, VidyoConnectorOnRemoteMicrophoneStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterRemoteMicrophoneEventListener}
	{parent: VidyoConnector}
	{description: Unregisters remote microphone event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterRemoteMicrophoneEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterRemoteMicrophoneEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterRemoteWindowShareEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about remote shreable-window events.}
	{prototype: LmiBool VidyoConnectorRegisterRemoteWindowShareEventListener(VidyoConnector* c, VidyoConnectorOnRemoteWindowShareAdded onAdded, VidyoConnectorOnRemoteWindowShareRemoved onRemoved, VidyoConnectorOnRemoteWindowShareStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered when another participant adds a window-share into a conference.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when another participant removes a window-share from a conference.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when another participant window-share changes state in a conference.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterRemoteWindowShareEventListener(VidyoConnector* c, VidyoConnectorOnRemoteWindowShareAdded onAdded, VidyoConnectorOnRemoteWindowShareRemoved onRemoved, VidyoConnectorOnRemoteWindowShareStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterRemoteWindowShareEventListener}
	{parent: VidyoConnector}
	{description: Unregisters remote window share event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterRemoteWindowShareEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterRemoteWindowShareEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorAssignViewToRemoteWindowShare}
	{parent: VidyoConnector}
	{description: Shows a participant in a view.}
	{prototype: LmiBool VidyoConnectorAssignViewToRemoteWindowShare(VidyoConnector* c, const LmiViewId* viewId, VidyoRemoteWindowShare* remoteWindowShare, LmiBool displayCropped, LmiBool allowZoom)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID where the participant will be rendered.}
	}
	{parameter:
		{name: remoteWindowShare}
		{description: The VidyoRemoteWindowShare that will be shown.}
	}
	{parameter:
		{name: displayCropped}
		{description: Render the image as cropped. Otherwise letterbox.}
	}
	{parameter:
		{name: allowZoom}
		{description: Allow zooming of the image with mouse or touch.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: This API will work only if compositing had been disabled by passing a NULL LmiViewId to VidyoConnectorConstruct.}
	{note: The view will not be shown until VidyoConnectorShowViewAt is called with valid parameters.}
}
*/
LmiBool VidyoConnectorAssignViewToRemoteWindowShare(VidyoConnector* c, const LmiViewId* viewId, VidyoRemoteWindowShare* remoteWindowShare, LmiBool displayCropped, LmiBool allowZoom);

/**
 {function apigroup="connector":
	{name: VidyoConnectorHideView}
	{parent: VidyoConnector}
	{description: Hides a view which is used for custom layout of sources.}
	{prototype: LmiBool VidyoConnectorHideView(VidyoConnector* c, const LmiViewId* viewId)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: The view ID of the view to hide.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorHideView(VidyoConnector* c, const LmiViewId* viewId);

/**
 {function apigroup="connector":
	{name: VidyoConnectorShowViewAt}
	{parent: VidyoConnector}
	{description: Sets the position of the view every time it's changed on the screen. }
	{prototype: LmiBool VidyoConnectorShowViewAt(VidyoConnector* c, const LmiViewId* viewId, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID to be positioned.}
	}
	{parameter:
		{name: x}
		{description: X coordinate. }
	}
	{parameter:
		{name: y}
		{description: Y coordinate. }
	}
	{parameter:
		{name: width}
		{description: Width of the view. }
	}
	{parameter:
		{name: height}
		{description: Height of the view. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: The view will not be shown until this funciton is called with valid parameters.}
	{note: If viewId is NULL then the composite renderer constructed in VidyoConnectorConstruct will be positioned.}
}
*/
LmiBool VidyoConnectorShowViewAt(VidyoConnector* c, const LmiViewId* viewId, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
 {function apigroup="connector":
	{name: VidyoConnectorShowViewLabel}
	{parent: VidyoConnector}
	{description: Shows or hides the label on the view which displays the participant name or preview. }
	{prototype: LmiBool VidyoConnectorShowViewLabel(VidyoConnector* c, const LmiViewId* viewId, LmiBool showLabel)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID to be positioned.}
	}
	{parameter:
		{name: showLabel}
		{description: Boolean to show or hide the label. }
	}
	{return: }
	{note: If viewId is NULL then the composite renderer constructed in VidyoConnectorConstruct will be assumed.}
}
*/
LmiBool VidyoConnectorShowViewLabel(VidyoConnector* c, const LmiViewId* viewId, LmiBool showLabel);

/**
 {function apigroup="connector":
	{name: VidyoConnectorShowAudioMeters}
	{parent: VidyoConnector}
	{description: Shows or hides the audio meters in the view. }
	{prototype: LmiBool VidyoConnectorShowAudioMeters(VidyoConnector* c, const LmiViewId* viewId, LmiBool showMeters)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID to be positioned.}
	}
	{parameter:
		{name: showMeters}
		{description: Boolean to show or hide the audio meters. }
	}
	{return: }
	{note: If viewId is NULL then the composite renderer constructed in VidyoConnectorConstruct will be assumed.}
}
*/
LmiBool VidyoConnectorShowAudioMeters(VidyoConnector* c, const LmiViewId* viewId, LmiBool showMeters);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetViewBackgroundColor}
	{parent: VidyoConnector}
	{description: Set the background color of the view. }
	{prototype: LmiBool VidyoConnectorSetViewBackgroundColor(VidyoConnector* c, const LmiViewId* viewId, LmiUint8 red, LmiUint8 green, LmiUint8 blue)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID to be positioned.}
	}
	{parameter:
		{name: red}
		{description: Red component of the color 0-255.}
	}
	{parameter:
		{name: green}
		{description: Green component of the color 0-255.}
	}
	{parameter:
		{name: blue}
		{description: Blue component of the color 0-255.}
	}
	{return: }
	{note: If viewId is NULL then the composite renderer constructed in VidyoConnectorConstruct will be assumed.}
}
*/
LmiBool VidyoConnectorSetViewBackgroundColor(VidyoConnector* c, const LmiViewId* viewId, LmiUint8 red, LmiUint8 green, LmiUint8 blue);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetViewAnimationSpeed}
	{parent: VidyoConnector}
	{description: Sets the speed of transition animation for windows moving around inside the view. }
	{prototype: LmiBool VidyoConnectorSetViewAnimationSpeed(VidyoConnector* c, const LmiViewId* viewId, LmiUint speedPercentage)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID to be positioned.}
	}
	{parameter:
		{name: speedPercentage}
		{description: Percentage of animation speed with default of 50, 100 for slowest and 0 for instant. }
	}
	{return: }
	{note: Not supported in WebRTC.}
	{note: If viewId is NULL then the composite renderer constructed in VidyoConnectorConstruct will be assumed.}
}
*/
LmiBool VidyoConnectorSetViewAnimationSpeed(VidyoConnector* c, const LmiViewId* viewId, LmiUint speedPercentage);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterNetworkInterfaceEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about network interface events.}
	{prototype: LmiBool VidyoConnectorRegisterNetworkInterfaceEventListener(VidyoConnector* c, VidyoConnectorOnNetworkInterfaceAdded onAdded, VidyoConnectorOnNetworkInterfaceRemoved onRemoved, VidyoConnectorOnNetworkInterfaceSelected onSelected, VidyoConnectorOnNetworkInterfaceStateUpdated onStateUpdated)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing network interface added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the network interface is removed.}
	}
	{parameter:
		{name: onSelected}
		{description: Callback that is triggered when a network interface is selected for use.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when a network interface state changes.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterNetworkInterfaceEventListener(VidyoConnector* c, VidyoConnectorOnNetworkInterfaceAdded onAdded, VidyoConnectorOnNetworkInterfaceRemoved onRemoved, VidyoConnectorOnNetworkInterfaceSelected onSelected, VidyoConnectorOnNetworkInterfaceStateUpdated onStateUpdated);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterNetworkInterfaceEventListener}
	{parent: VidyoConnector}
	{description: Unregisters network interface event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterNetworkInterfaceEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoConnectorUnregisterNetworkInterfaceEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectNetworkInterfaceForSignaling}
	{parent: VidyoConnector}
	{description: Selects the network interface to be used for Signaling.}
	{prototype: LmiBool VidyoConnectorSelectNetworkInterfaceForSignaling(VidyoConnector* c, const VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: networkInterface}
		{description: Network interface to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectNetworkInterfaceForSignaling(VidyoConnector* c, const VidyoNetworkInterface *networkInterface);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectDefaultNetworkInterfaceForSignaling}
	{parent: VidyoConnector}
	{description: Selects the default "any" network interface to be used for Signaling.}
	{prototype: LmiBool VidyoConnectorSelectDefaultNetworkInterfaceForSignaling(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectDefaultNetworkInterfaceForSignaling(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectNetworkInterfaceForMedia}
	{parent: VidyoConnector}
	{description: Selects the network interface to be used for Media.}
	{prototype: LmiBool VidyoConnectorSelectNetworkInterfaceForMedia(VidyoConnector* c, const VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: networkInterface}
		{description: Network interface to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectNetworkInterfaceForMedia(VidyoConnector* c, const VidyoNetworkInterface *networkInterface);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSelectDefaultNetworkInterfaceForMedia}
	{parent: VidyoConnector}
	{description: Selects the default "any" network interface to be used for Media.}
	{prototype: LmiBool VidyoConnectorSelectDefaultNetworkInterfaceForMedia(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSelectDefaultNetworkInterfaceForMedia(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorConnect}
	{parent: VidyoConnector}
	{description: Connects to a live conference with the specified resourceId.}
	{prototype: LmiBool VidyoConnectorConnect(VidyoConnector* c, const char* host, const char* token, const char* displayName, const char *resourceId, VidyoConnectorOnSuccess onSuccess, VidyoConnectorOnFailure onFailure, VidyoConnectorOnDisconnected onDisconnected)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: host}
		{description: Host to which the connection will be made.}
	}
	{parameter:
		{name: token}
		{description: Token generated by the backend that contains the user ID and other metadata that will be used for authentication.}
	}
	{parameter:
		{name: displayName}
		{description: A display name that will be used in the UI.}
	}
	{parameter:
		{name: resourceId}
		{description: An alphanumeric string. This resourceId does not need to be pre-provisioned but in order to create a connection between multiple participants, the same resourceId has to be specified.}
	}
	{parameter:
		{name: onSuccess}
		{description: Callback that is triggered when the connection is sucessfully established.}
	}
	{parameter:
		{name: onFailure}
		{description: Callback that is triggered when the connection establishemnt failed.}
	}
	{parameter:
		{name: onDisconnected}
		{description: Callback that is triggered when an established connection is disconnected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorConnect(VidyoConnector* c, const char* host, const char* token, const char* displayName, const char *resourceId, VidyoConnectorOnSuccess onSuccess, VidyoConnectorOnFailure onFailure, VidyoConnectorOnDisconnected onDisconnected);

/**
 {function apigroup="connector":
	{name: VidyoConnectorDisconnect}
	{parent: VidyoConnector}
	{description: Disconnects a live conference.}
	{prototype: void VidyoConnectorDisconnect(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
}
*/
void VidyoConnectorDisconnect(VidyoConnector* c);

/**
{function apigroup="connector":
	{name: VidyoConnectorDisable}
	{parent: VidyoConnector}
	{description: Disables connector object, releases all devices as precursor to destruct.}
	{prototype: void VidyoConnectorDisable(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
}
*/
void VidyoConnectorDisable(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSendChatMessage}
	{parent: VidyoConnector}
	{description: Sends a message to all the other participants.}
	{prototype: LmiBool VidyoConnectorSendChatMessage(VidyoConnector* c, const char* message)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: message}
		{description: A message to send to all the other participants.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorSendChatMessage(VidyoConnector* c, const char* message);

/**
 {function apigroup="connector":
	{name: VidyoConnectorGetStatsJson}
	{parent: VidyoConnector}
	{description: Retrieves VidyoConnector statistics in JSON format.}
	{prototype: const LmiString *VidyoConnectorGetStatsJson(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: JSON encoded string on success, NULL on failure.}
}
*/
const LmiString *VidyoConnectorGetStatsJson(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorGetVersion}
	{parent: VidyoConnector}
	{description: Retrieves version of the VidyoConnector library.}
	{prototype: const LmiString *VidyoConnectorGetVersion(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: Version on success, NULL on failure.}
}
*/
const LmiString *VidyoConnectorGetVersion(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorGetState}
	{parent: VidyoConnector}
	{description: Retrieves the state of the VidyoConnector.}
	{prototype: VidyoConnectorState VidyoConnectorGetState(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: The state of the VidyoConnector.}
}
*/
VidyoConnectorState VidyoConnectorGetState(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterResourceManagerEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about resource-management events.}
	{prototype: LmiBool VidyoConnectorRegisterResourceManagerEventListener(VidyoConnector* c, VidyoConnectorOnAvailableResourcesChanged onAvailableResourcesChanged, VidyoConnectorOnMaxRemoteSourcesChanged onMaxRemoteSourcesChanged)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onAvailableResourcesChanged}
		{description: Callback that is triggered when local resource availability changes.}
	}
	{parameter:
		{name: onMaxRemoteSourcesChanged}
		{description: Callback that is triggered when the maximum number of decoded sources changes.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterResourceManagerEventListener(VidyoConnector* c, VidyoConnectorOnAvailableResourcesChanged onAvailableResourcesChanged, VidyoConnectorOnMaxRemoteSourcesChanged onMaxRemoteSourcesChanged);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterResourceManagerEventListener}
	{parent: VidyoConnector}
	{description: Unregisters resource manager event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterResourceManagerEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterResourceManagerEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterRecoderInCallEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified when a recorder joins or leaves the call.}
	{prototype: LmiBool VidyoConnectorRegisterRecoderInCallEventListener(VidyoConnector* c, VidyoConnectorRecorderInCall onRecorderInCallChanged)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onRecorderInCallChanged}
		{description: Callback that is triggered when a recorder joins or leaves the call.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterRecoderInCallEventListener(VidyoConnector* c, VidyoConnectorRecorderInCall onRecorderInCallChanged );

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterRecoderInCallEventListener}
	{parent: VidyoConnector}
	{description: Unregisters recorder in call event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterRecoderInCallEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorUnregisterRecoderInCallEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorRegisterWebProxyEventListener}
	{parent: VidyoConnector}
	{description: Registers to get notified about web proxy events.}
	{prototype: LmiBool VidyoConnectorRegisterWebProxyEventListener(VidyoConnector* c, VidyoConnectorOnWebProxyCredentialsRequest onWebProxyCredentialsRequest)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: onWebProxyCredentialsRequest}
		{description: Callback that is triggered when web proxy credentials are requested.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoConnectorRegisterWebProxyEventListener(VidyoConnector* c, VidyoConnectorOnWebProxyCredentialsRequest onWebProxyCredentialsRequest);

/**
 {function apigroup="connector":
	{name: VidyoConnectorUnregisterWebProxyEventListener}
	{parent: VidyoConnector}
	{description: Unregisters web proxy event notifications.}
	{prototype: LmiBool VidyoConnectorUnregisterWebProxyEventListener(VidyoConnector* c)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoConnectorUnregisterWebProxyEventListener(VidyoConnector* c);

/**
 {function apigroup="connector":
	{name: VidyoConnectorSetWebProxyAddressCredentials}
	{parent: VidyoConnector}
	{description: Sets web proxy server address and credentials.}
	{prototype: void VidyoConnectorSetWebProxyAddressCredentials(VidyoConnector* c, const char* proxyAddress, const char* username, const char* password)}
	{parameter:
		{name: c}
		{description: The VidyoConnector object.}
	}
	{parameter:
		{name: proxyAddress}
		{description: The web proxy server address.}
	}
	{parameter:
		{name: username}
		{description: The web proxy server user name.}
	}
	{parameter:
		{name: password}
		{description: The web proxy server password.}
	}
}
*/
void VidyoConnectorSetWebProxyAddressCredentials(VidyoConnector* c, const char* proxyAddress, const char* username, const char* password);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoConnectorInline.h"
#endif

#endif /* VIDYO_CONNECTOR_H_ */


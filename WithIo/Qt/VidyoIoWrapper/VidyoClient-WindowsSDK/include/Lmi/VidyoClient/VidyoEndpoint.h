/** 
{file:
	{name: VidyoEndpoint.h}
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
#ifndef VIDYO_CLIENT_H_ 
#define VIDYO_CLIENT_H_ 

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

struct VidyoEndpointImpl_;
typedef struct VidyoEndpointImpl_ VidyoEndpointImpl;
Declare_LmiSharedPtr(VidyoEndpointImpl)
Declare_LmiSharedPtrWrapper(VidyoEndpoint, VidyoEndpointImpl)
Declare_LmiWeakPtrWrapper(VidyoEndpointHandle, VidyoEndpoint, VidyoEndpointImpl)

LMI_END_EXTERN_C

#include "VidyoLogRecord.h"
#include "VidyoLogger.h"
#include "VidyoTransport.h"
#include "VidyoNetworkInterface.h"
#include "VidyoCodec.h"
#include "VidyoForwardDecl.h"

#include "VidyoDevice.h"

/* sinks */
#include "VidyoLocalSpeaker.h"
#include "VidyoRemoteSpeaker.h"
#include "VidyoLocalRenderer.h"
#include "VidyoRemoteRenderer.h"

/* sources */
#include "VidyoLocalMicrophone.h"
#include "VidyoRemoteMicrophone.h"
#include "VidyoLocalCamera.h"
#include "VidyoRemoteCamera.h"
#include "VidyoLocalWindowShare.h"
#include "VidyoRemoteWindowShare.h"
#include "VidyoLocalMonitor.h"

#include "VidyoUser.h"
#include "VidyoCall.h"
#include "VidyoRoom.h"
#include "VidyoParticipant.h"

#include "VidyoStatistics.h"

LMI_BEGIN_EXTERN_C

/**
{package:
	{name: VidyoClient}
	{parent: Lmi}
	{include: Lmi/VidyoClient/VidyoEndpoint.h}
	{library: VidyoClient}
	{description: The VidyoClient package encapsulates all APIs required to build a vidyo conferencing application.}
}
*/

/**
{package:
	{name: Endpoint}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoEndpoint.h}
	{description: The VidyoClient package encapsulates all APIs required to build a vidyo conferencing application.}
}
*/


/**
{type apigroup="simple" reference-counted="yes":
	{name: VidyoEndpoint}
	{parent: Endpoint}
	{description: }
}
*/

/**
{type visibility="private":
	{name: VidyoEndpointHandle}
	{parent: VidyoEndpoint}
	{description: }
}
*/

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLog}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered for every log record. }
	{prototype: void (*VidyoEndpointOnLog)(VidyoEndpoint* e, const VidyoLogRecord* logRecord)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: logRecord}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLog)(VidyoEndpoint* e, const VidyoLogRecord* logRecord);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalCameraAdded}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local camera becomes available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalCameraAdded)(VidyoEndpoint* e, VidyoLocalCamera* localCamera)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCamera}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalCameraAdded)(VidyoEndpoint* e, VidyoLocalCamera* localCamera);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalCameraRemoved}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local camera is no longer available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalCameraRemoved)(VidyoEndpoint* e, VidyoLocalCamera* localCamera)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCamera}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalCameraRemoved)(VidyoEndpoint* e, VidyoLocalCamera* localCamera);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalCameraSelected}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in which local camera is selected for use.}
	{prototype: void (*VidyoEndpointOnLocalCameraSelected)(VidyoEndpoint* e, VidyoLocalCamera* localCamera)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCamera}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalCameraSelected)(VidyoEndpoint* e, VidyoLocalCamera* localCamera);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalCameraStateUpdated}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in the state of the camera such as being suspended or disabled.}
	{prototype: void (*VidyoEndpointOnLocalCameraStateUpdated)(VidyoEndpoint* e, VidyoLocalCamera* localCamera, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCamera}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalCameraStateUpdated)(VidyoEndpoint* e, VidyoLocalCamera* localCamera, VidyoDeviceState state);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteCameraAdded}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteCameraAdded)(VidyoEndpoint* e, VidyoRemoteCamera* remoteCamera, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteCamera}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteCameraAdded)(VidyoEndpoint* e, VidyoRemoteCamera* remoteCamera, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteCameraRemoved}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteCameraRemoved)(VidyoEndpoint* e, VidyoRemoteCamera* remoteCamera, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteCamera}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteCameraRemoved)(VidyoEndpoint* e, VidyoRemoteCamera* remoteCamera, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteCameraStateUpdated}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteCameraStateUpdated)(VidyoEndpoint* e, VidyoRemoteCamera* remoteCamera, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteCamera}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteCameraStateUpdated)(VidyoEndpoint* e, VidyoRemoteCamera* remoteCamera, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant, VidyoDeviceState state);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMicrophoneAdded}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local microphone becomes available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalMicrophoneAdded)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophone}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalMicrophoneAdded)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMicrophoneRemoved}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local microphone is no longer available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalMicrophoneRemoved)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophone}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalMicrophoneRemoved)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMicrophoneSelected}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in which local microphone is selected for use.}
	{prototype: void (*VidyoEndpointOnLocalMicrophoneSelected)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophone}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalMicrophoneSelected)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMicrophoneStateUpdated}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in the state of the microphone such as being suspended or disabled.}
	{prototype: void (*VidyoEndpointOnLocalMicrophoneStateUpdated)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophone}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalMicrophoneStateUpdated)(VidyoEndpoint* e, VidyoLocalMicrophone* localMicrophone, VidyoDeviceState state);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteMicrophoneAdded}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteMicrophoneAdded)(VidyoEndpoint* e, VidyoRemoteMicrophone* remoteMicrophone, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteMicrophone}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteMicrophoneAdded)(VidyoEndpoint* e, VidyoRemoteMicrophone* remoteMicrophone, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteMicrophoneRemoved}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteMicrophoneRemoved)(VidyoEndpoint* e, VidyoRemoteMicrophone* remoteMicrophone, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteMicrophone}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteMicrophoneRemoved)(VidyoEndpoint* e, VidyoRemoteMicrophone* remoteMicrophone, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteMicrophoneStateUpdated}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteMicrophoneStateUpdated)(VidyoEndpoint* e, VidyoRemoteMicrophone* remoteMicrophone, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteMicrophone}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteMicrophoneStateUpdated)(VidyoEndpoint* e, VidyoRemoteMicrophone* remoteMicrophone, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant, VidyoDeviceState state);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalSpeakerAdded}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local speaker becomes available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalSpeakerAdded)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeaker}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalSpeakerAdded)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalSpeakerRemoved}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local speaker is no longer available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalSpeakerRemoved)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeaker}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalSpeakerRemoved)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalSpeakerSelected}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in which local speaker is selected for use.}
	{prototype: void (*VidyoEndpointOnLocalSpeakerSelected)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeaker}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalSpeakerSelected)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalSpeakerStateUpdated}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in the state of the speaker such as being suspended or disabled.}
	{prototype: void (*VidyoEndpointOnLocalSpeakerStateUpdated)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeaker}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalSpeakerStateUpdated)(VidyoEndpoint* e, VidyoLocalSpeaker* localSpeaker, VidyoDeviceState state);


/**
{callback:
	{name: VidyoEndpointOnRemoteSpeakerAdded}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteSpeakerAdded)(VidyoEndpoint* e, VidyoRemoteSpeaker* remoteSpeaker, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteSpeaker}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteSpeakerAdded)(VidyoEndpoint* e, VidyoRemoteSpeaker* remoteSpeaker, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room);

/**
{callback:
	{name: VidyoEndpointOnRemoteSpeakerRemoved}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteSpeakerRemoved)(VidyoEndpoint* e, VidyoRemoteSpeaker* remoteSpeaker, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteSpeaker}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteSpeakerRemoved)(VidyoEndpoint* e, VidyoRemoteSpeaker* remoteSpeaker, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room);

/**
{callback:
	{name: VidyoEndpointOnLocalRendererAdded}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnLocalRendererAdded)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalRendererAdded)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer);

/**
{callback:
	{name: VidyoEndpointOnLocalRendererRemoved}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnLocalRendererRemoved)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalRendererRemoved)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer);

/**
{callback:
	{name: VidyoEndpointOnLocalRendererSelected}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnLocalRendererSelected)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalRendererSelected)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer);

/**
{callback:
	{name: VidyoEndpointOnLocalRendererStateUpdated}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnLocalRendererStateUpdated)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalRendererStateUpdated)(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer, VidyoDeviceState state);

/**
{callback:
	{name: VidyoEndpointOnRemoteRendererAdded}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteRendererAdded)(VidyoEndpoint* e, VidyoRemoteRenderer* remoteRenderer, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteRendererAdded)(VidyoEndpoint* e, VidyoRemoteRenderer* remoteRenderer, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room);

/**
{callback:
	{name: VidyoEndpointOnRemoteRendererRemoved}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteRendererRemoved)(VidyoEndpoint* e, VidyoRemoteRenderer* remoteRenderer, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteRenderer}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteRendererRemoved)(VidyoEndpoint* e, VidyoRemoteRenderer* remoteRenderer, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalWindowShareAdded}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local window becomes available for a VidyoEndpoint to share in a conference.}
	{prototype: void (*VidyoEndpointOnLocalWindowShareAdded)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShare}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalWindowShareAdded)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalWindowShareRemoved}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local window is no longer available for a VidyoEndpoint to share in a conference.}
	{prototype: void (*VidyoEndpointOnLocalWindowShareRemoved)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShare}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalWindowShareRemoved)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalWindowShareSelected}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in which local window is selected for sharing.}
	{prototype: void (*VidyoEndpointOnLocalWindowShareSelected)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShare}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalWindowShareSelected)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalWindowShareStateUpdated}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in the state of the window such as being suspended or disabled.}
	{prototype: void (*VidyoEndpointOnLocalWindowShareStateUpdated)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShare}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalWindowShareStateUpdated)(VidyoEndpoint* e, VidyoLocalWindowShare* localWindowShare, VidyoDeviceState state);


/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteWindowShareAdded}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteWindowShareAdded)(VidyoEndpoint* e, VidyoRemoteWindowShare* remoteWindowShare, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteWindowShare}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteWindowShareAdded)(VidyoEndpoint* e, VidyoRemoteWindowShare* remoteWindowShare, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteWindowShareRemoved}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteWindowShareRemoved)(VidyoEndpoint* e, VidyoRemoteWindowShare* remoteWindowShare, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteWindowShare}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteWindowShareRemoved)(VidyoEndpoint* e, VidyoRemoteWindowShare* remoteWindowShare, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnRemoteWindowShareStateUpdated}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void (*VidyoEndpointOnRemoteWindowShareStateUpdated)(VidyoEndpoint* e, VidyoRemoteWindowShare* remoteWindowShare, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: remoteWindowShare}
		{description: }
	}
	{parameter:
		{name: user}
		{description: }
	}
	{parameter:
		{name: call}
		{description: }
	}
	{parameter:
		{name: room}
		{description: }
	}
	{parameter:
		{name: participant}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnRemoteWindowShareStateUpdated)(VidyoEndpoint* e, VidyoRemoteWindowShare* remoteWindowShare, const VidyoUser* user, const VidyoCall* call, const VidyoRoom* room, const VidyoParticipant* participant, VidyoDeviceState state);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMonitorAdded}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local monitor becomes available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalMonitorAdded)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitor}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalMonitorAdded)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMonitorRemoved}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a local monitor is no longer available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnLocalMonitorRemoved)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitor}
		{description: }
	}
}
*/
typedef void (*VidyoEndpointOnLocalMonitorRemoved)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMonitorSelected}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in which local monitor is selected for sharing.}
	{prototype: void (*VidyoEndpointOnLocalMonitorSelected)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitor}
		{description: }
	}
}
*/
typedef void (*VidyoEndpointOnLocalMonitorSelected)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnLocalMonitorStateUpdated}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in the state of the monitor such as being suspended or disabled.}
	{prototype: void (*VidyoEndpointOnLocalMonitorStateUpdated)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor, VidyoDeviceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitor}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnLocalMonitorStateUpdated)(VidyoEndpoint* e, VidyoLocalMonitor* localMonitor, VidyoDeviceState state);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnNetworkInterfaceAdded}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a network interface is available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnNetworkInterfaceAdded)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: networkInterface}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnNetworkInterfaceAdded)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnNetworkInterfaceRemoved}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time a network interface is no longer available to a VidyoEndpoint.}
	{prototype: void (*VidyoEndpointOnNetworkInterfaceRemoved)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: networkInterface}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnNetworkInterfaceRemoved)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnNetworkInterfaceSelected}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in which network interface is selected for use.}
	{prototype: void (*VidyoEndpointOnNetworkInterfaceSelected)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceTransportType transportType)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: networkInterface}
		{description: }
	}
	{parameter:
		{name: transportType}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnNetworkInterfaceSelected)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceTransportType transportType);

/**
{callback apigroup="simple":
	{name: VidyoEndpointOnNetworkInterfaceStateUpdated}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered each time there is a change in the state of the network interface such as being up or down.}
	{prototype: void (*VidyoEndpointOnNetworkInterfaceStateUpdated)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceState state)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: networkInterface}
		{description: }
	}
	{parameter:
		{name: state}
		{description: }
	}
}
*/
typedef void(*VidyoEndpointOnNetworkInterfaceStateUpdated)(VidyoEndpoint* e, VidyoNetworkInterface* networkInterface, VidyoNetworkInterfaceState state);

/**
{type:
	{name: VidyoEndpointMediaState}
	{parent: VidyoEndpoint}
	{description: }
	{value: {name: VIDYO_ENDPOINTMEDIASTATE_Idle} {description: }}
	{value: {name: VIDYO_ENDPOINTMEDIASTATE_GreenRoom} {description: }}
	{value: {name: VIDYO_ENDPOINTMEDIASTATE_Live} {description: }}
}
*/
typedef enum {
	VIDYO_ENDPOINTMEDIASTATE_Idle,
	VIDYO_ENDPOINTMEDIASTATE_GreenRoom,
	VIDYO_ENDPOINTMEDIASTATE_Live
} VidyoEndpointMediaState;

/**
{function apigroup="simple":
	{name: VidyoClientInitialize}
	{parent: Endpoint}
	{description: }
	{prototype: LmiBool VidyoClientInitialize(void)}
	{return: }
}
*/
LmiBool VidyoClientInitialize(void);

/**
{function apigroup="simple":
	{name: VidyoClientUninitialize}
	{parent: Endpoint}
	{description: }
	{prototype: void VidyoClientUninitialize(void)}
}
*/
void VidyoClientUninitialize(void);

/**
{function apigroup="simple":
	{name: VidyoClientGetVersion}
	{parent: Endpoint}
	{description: }
	{prototype: const LmiString *VidyoClientGetVersion(void)}
	{return: Version of the VidyoClient library. }
}
*/
const LmiString *VidyoClientGetVersion(void);

/**
{function apigroup="simple":
	{name: VidyoClientGetBuildTag}
	{parent: Endpoint}
	{description: }
	{prototype: const LmiString *VidyoClientGetBuildTag(void)}
	{return: Build tag of the VidyoClient library. }
}
*/
const LmiString *VidyoClientGetBuildTag(void);

/**
{function apigroup="simple":
	{name: VidyoEndpointConstruct}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: VidyoEndpoint* VidyoEndpointConstruct(VidyoEndpoint* e, const LmiViewId* viewId, VidyoLocalRendererViewStyle viewStyle, LmiUint remoteParticipants, const char* consoleLogFilter, const char* fileLogFilter, const char* fileLogName, LmiAllocator* alloc)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: viewId}
		{description: A platform specific parent view ID where the VidyoEndpoint's rendering window will be added as a child window. It will be used to render preview and composite remote participants. }
	}
	{parameter:
		{name: viewStyle}
		{description: Type of the composite renderer which represents the visual style and behaviour. }
	}
	{parameter:
		{name: remoteParticipants}
		{description: Number of remote participants to composite into the window. Setting the value to 0 will render preview only. }
	}
	{parameter:
		{name: consoleLogFilter}
		{description: }
	}
	{parameter:
		{name: fileLogFilter}
		{description: }
	}
	{parameter:
		{name: fileLogName}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoEndpoint *VidyoEndpointConstruct(VidyoEndpoint *e, const LmiViewId* viewId, VidyoLocalRendererViewStyle viewStyle, LmiUint remoteParticipants, const char *consoleLogFilter, const char *fileLogFilter, const char *fileLogName, LmiAllocator *alloc);

/**
{function apigroup="simple":
	{name: VidyoEndpointConstructCopy}
	{parent: VidyoEndpoint}
	{description: Constructs an VidyoEndpoint object as a copy of another.}
	{prototype: VidyoEndpoint *VidyoEndpointConstructCopy(VidyoEndpoint *obj, const VidyoEndpoint *other)}
	{parameter: {name: obj} {description: The VidyoEndpoint object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="simple":
	{name: VidyoEndpointDestruct}
	{parent: VidyoEndpoint}
	{description: Destructs an VidyoEndpoint object.}
	{prototype: void VidyoEndpointDestruct(VidyoEndpoint *obj)}
	{parameter: {name: obj} {description: The VidyoEndpoint object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoEndpointAssign}
	{parent: VidyoEndpoint}
	{description: Assigns one VidyoEndpoint object the value of another. }
	{prototype: VidyoEndpoint *VidyoEndpointAssign(VidyoEndpoint *obj, const VidyoEndpoint *other)}
	{parameter: {name: obj} {description: The VidyoEndpoint object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoEndpointGetHandle}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: VidyoEndpointHandle* VidyoEndpointGetHandle(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
VidyoEndpointHandle* VidyoEndpointGetHandle(VidyoEndpoint* e);

/**
{function apigroup="simple":
	{name: VidyoEndpointStartDeviceDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointStartDeviceDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointStartDeviceDetection(VidyoEndpoint* e);

/**
{function apigroup="simple":
	{name: VidyoEndpointStopDeviceDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointStopDeviceDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
}
*/
void VidyoEndpointStopDeviceDetection(VidyoEndpoint* e);

/**
{function apigroup="simple":
	{name: VidyoEndpointStartShareDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointStartShareDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointStartShareDetection(VidyoEndpoint* e);

/**
{function apigroup="simple":
	{name: VidyoEndpointStopShareDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointStopShareDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
}
*/
void VidyoEndpointStopShareDetection(VidyoEndpoint* e);

/**
{function visibility="private":
	{name: VidyoEndpointSetUserData}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointSetUserData(VidyoEndpoint* e, LmiVoidPtr userData)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoEndpointSetUserData(VidyoEndpoint* e, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoEndpointGetUserData}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiVoidPtr VidyoEndpointGetUserData(const VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoEndpointGetUserData(const VidyoEndpoint* e);

/**
 {type apigroup="simple":
	{name: VidyoEndpointMode}
	{parent: VidyoEndpoint}
	{description: Operating modes of the VidyoEndpoint.}
	{value: {name: VIDYO_ENDPOINTMODE_Default}
		{description: The default operating mode.}}
	{value: {name: VIDYO_ENDPOINTMODE_Foreground}
		{description: Runs in the foreground.}}
	{value: {name: VIDYO_ENDPOINTMODE_Background}
		{description: Runs in the background.}}
	{note: The default is currently VIDYO_ENDPOINTMODE_Foreground.}
}
*/
typedef enum
{
	VIDYO_ENDPOINTMODE_Default,
	VIDYO_ENDPOINTMODE_Foreground,
	VIDYO_ENDPOINTMODE_Background
} VidyoEndpointMode;

/**
 {function apigroup="simple":
	{name: VidyoEndpointSetMode}
	{parent: VidyoEndpoint}
	{description: Sets the operating mode of the VidyoEndpoint.}
	{prototype: LmiBool VidyoEndpointSetMode(VidyoEndpoint* e, VidyoEndpointMode mode)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: mode}
		{description: Desired operating mode.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSetMode(VidyoEndpoint *e, VidyoEndpointMode mode);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterLogEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about log events.}
	{prototype: LmiBool VidyoEndpointRegisterLogEventListener(VidyoEndpoint* e, VidyoEndpointOnLog onLog, const char* filter)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	   {p: See VidyoEndpointGetLogCategories for determining the names and descriptions of registered categories.}
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
LmiBool VidyoEndpointRegisterLogEventListener(VidyoEndpoint* e, VidyoEndpointOnLog onLog, const char* filter);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLogEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters log event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLogEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLogEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterLocalCameraEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about camera events.}
	{prototype: LmiBool VidyoEndpointRegisterLocalCameraEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalCameraAdded onAdded, VidyoEndpointOnLocalCameraRemoved onRemoved, VidyoEndpointOnLocalCameraSelected onSelected, VidyoEndpointOnLocalCameraStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
LmiBool VidyoEndpointRegisterLocalCameraEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalCameraAdded onAdded, VidyoEndpointOnLocalCameraRemoved onRemoved, VidyoEndpointOnLocalCameraSelected onSelected, VidyoEndpointOnLocalCameraStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLocalCameraEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters local camera event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLocalCameraEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLocalCameraEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectLocalCamera}
	{parent: VidyoEndpoint}
	{description: Selects the camera to be used.}
	{prototype: LmiBool VidyoEndpointSelectLocalCamera(VidyoEndpoint* e, const VidyoLocalCamera* localCamera)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: localCamera}
		{description: Camera to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectLocalCamera(VidyoEndpoint* e, const VidyoLocalCamera* localCamera);

/**
 {function apigroup="simple":
	{name: VidyoEndpointAssignViewToLocalCamera}
	{parent: VidyoEndpoint}
	{description: Shows a preview of a local camera in a view.}
	{prototype: LmiBool VidyoEndpointAssignViewToLocalCamera(VidyoEndpoint* e, const LmiViewId* viewId, VidyoLocalCamera* localCamera, LmiBool displayCropped, LmiBool allowZoom)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{note: This API will work only if compositing had been disabled by passing a NULL LmiViewId to VidyoEndpointConstruct.}
	{note: The view will not be shown until VidyoEndpointShowViewAt is called with valid parameters.}
}
*/
LmiBool VidyoEndpointAssignViewToLocalCamera(VidyoEndpoint* e, const LmiViewId* viewId, VidyoLocalCamera* localCamera, LmiBool displayCropped, LmiBool allowZoom);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterLocalMicrophoneEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about microphone events.}
	{prototype: LmiBool VidyoEndpointRegisterLocalMicrophoneEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalMicrophoneAdded onAdded, VidyoEndpointOnLocalMicrophoneRemoved onRemoved, VidyoEndpointOnLocalMicrophoneSelected onSelected, VidyoEndpointOnLocalMicrophoneStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
LmiBool VidyoEndpointRegisterLocalMicrophoneEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalMicrophoneAdded onAdded, VidyoEndpointOnLocalMicrophoneRemoved onRemoved, VidyoEndpointOnLocalMicrophoneSelected onSelected, VidyoEndpointOnLocalMicrophoneStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLocalMicrophoneEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters local microphone event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLocalMicrophoneEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLocalMicrophoneEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectLocalMicrophone}
	{parent: VidyoEndpoint}
	{description: Selects the microphone to be used.}
	{prototype: LmiBool VidyoEndpointSelectLocalMicrophone(VidyoEndpoint* e, const VidyoLocalMicrophone* localMicrophone)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: localMicrophone}
		{description: Microphone to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectLocalMicrophone(VidyoEndpoint* e, const VidyoLocalMicrophone* localMicrophone);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterLocalSpeakerEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about speaker events.}
	{prototype: LmiBool VidyoEndpointRegisterLocalSpeakerEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalSpeakerAdded onAdded, VidyoEndpointOnLocalSpeakerRemoved onRemoved, VidyoEndpointOnLocalSpeakerSelected onSelected, VidyoEndpointOnLocalSpeakerStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
LmiBool VidyoEndpointRegisterLocalSpeakerEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalSpeakerAdded onAdded, VidyoEndpointOnLocalSpeakerRemoved onRemoved, VidyoEndpointOnLocalSpeakerSelected onSelected, VidyoEndpointOnLocalSpeakerStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLocalSpeakerEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters local speaker event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLocalSpeakerEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLocalSpeakerEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectLocalSpeaker}
	{parent: VidyoEndpoint}
	{description: Selects the speaker to be used.}
	{prototype: LmiBool VidyoEndpointSelectLocalSpeaker(VidyoEndpoint* e, const VidyoLocalSpeaker* localSpeaker)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: localSpeaker}
		{description: Speaker to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectLocalSpeaker(VidyoEndpoint* e, const VidyoLocalSpeaker* localSpeaker);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterLocalMonitorEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about monitor events.}
	{prototype: LmiBool VidyoEndpointRegisterLocalMonitorEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalMonitorAdded onAdded, VidyoEndpointOnLocalMonitorRemoved onRemoved, VidyoEndpointOnLocalMonitorSelected onSelected, VidyoEndpointOnLocalMonitorStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
LmiBool VidyoEndpointRegisterLocalMonitorEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalMonitorAdded onAdded, VidyoEndpointOnLocalMonitorRemoved onRemoved, VidyoEndpointOnLocalMonitorSelected onSelected, VidyoEndpointOnLocalMonitorStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLocalMonitorEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters local monitor event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLocalMonitorEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLocalMonitorEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectLocalMonitor}
	{parent: VidyoEndpoint}
	{description: Selects the monitor to be used.}
	{prototype: LmiBool VidyoEndpointSelectLocalMonitor(VidyoEndpoint* e, const VidyoLocalMonitor* localMonitor)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: localMonitor}
		{description: Monitor to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectLocalMonitor(VidyoEndpoint* e, const VidyoLocalMonitor* localMonitor);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterLocalWindowShareEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about window events.}
	{prototype: LmiBool VidyoEndpointRegisterLocalWindowShareEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalWindowShareAdded onAdded, VidyoEndpointOnLocalWindowShareRemoved onRemoved, VidyoEndpointOnLocalWindowShareSelected onSelected, VidyoEndpointOnLocalWindowShareStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
		{description: Callback that is triggered when a window state changes.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterLocalWindowShareEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalWindowShareAdded onAdded, VidyoEndpointOnLocalWindowShareRemoved onRemoved, VidyoEndpointOnLocalWindowShareSelected onSelected, VidyoEndpointOnLocalWindowShareStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLocalWindowShareEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters local window share event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLocalWindowShareEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLocalWindowShareEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectLocalWindowShare}
	{parent: VidyoEndpoint}
	{description: Selects the window to be used.}
	{prototype: LmiBool VidyoEndpointSelectLocalWindowShare(VidyoEndpoint* e, const VidyoLocalWindowShare* localWindowShare)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: localWindowShare}
		{description: Window to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectLocalWindowShare(VidyoEndpoint *e, const VidyoLocalWindowShare *localWindowShare);

/**
 {function apigroup="simple" deprecated="yes" replaced-by="VidyoEndpointShowPreview":
	{name: VidyoEndpointSetPreview}
	{parent: VidyoEndpoint}
	{description: Sets the flag to show/hide the camera preview.}
	{prototype: LmiBool VidyoEndpointSetPreview(VidyoEndpoint* e, LmiBool preview)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: preview}
		{description: Flag to show/hide the camera preview.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSetPreview(VidyoEndpoint* e, LmiBool preview);

/**
 {function apigroup="simple":
	{name: VidyoEndpointShowPreview}
	{parent: VidyoEndpoint}
	{description: Sets the flag to show/hide the camera preview while in the call.}
	{prototype: LmiBool VidyoEndpointShowPreview(VidyoEndpoint* e, LmiBool preview)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: preview}
		{description: Flag to show/hide the camera preview.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointShowPreview(VidyoEndpoint* e, LmiBool preview);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSetCameraPrivacy}
	{parent: VidyoEndpoint}
	{description: Sets the flag to show/hide the camera.}
	{prototype: LmiBool VidyoEndpointSetCameraPrivacy(VidyoEndpoint* e, LmiBool privacy)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: privacy}
		{description: Flag to show/hide the camera.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSetCameraPrivacy(VidyoEndpoint* e, LmiBool privacy);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectDefaultCamera}
	{parent: VidyoEndpoint}
	{description: Resets the camera selection to pick the Default camera.}
	{prototype: LmiBool VidyoEndpointSelectDefaultCamera(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectDefaultCamera(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointCycleCamera}
	{parent: VidyoEndpoint}
	{description: Cycles camera selection to the next available camera.}
	{prototype: LmiBool VidyoEndpointCycleCamera(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointCycleCamera(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSetMicrophonePrivacy}
	{parent: VidyoEndpoint}
	{description: Sets the flag to mute/unmute the microphone.}
	{prototype: LmiBool VidyoEndpointSetMicrophonePrivacy(VidyoEndpoint* e, LmiBool privacy)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: privacy}
		{description: Flag to mute/unmute the microphone.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSetMicrophonePrivacy(VidyoEndpoint* e, LmiBool privacy);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectDefaultMicrophone}
	{parent: VidyoEndpoint}
	{description: Resets the microphone selection to pick the Default microphone.}
	{prototype: LmiBool VidyoEndpointSelectDefaultMicrophone(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectDefaultMicrophone(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointCycleMicrophone}
	{parent: VidyoEndpoint}
	{description: Cycles microphone selection to the next available microphone.}
	{prototype: LmiBool VidyoEndpointCycleMicrophone(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointCycleMicrophone(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSetSpeakerPrivacy}
	{parent: VidyoEndpoint}
	{description: Sets the flag to mute/unmute the speaker.}
	{prototype: LmiBool VidyoEndpointSetSpeakerPrivacy(VidyoEndpoint* e, LmiBool privacy)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: privacy}
		{description: Flag to mute/unmute the speaker.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSetSpeakerPrivacy(VidyoEndpoint* e, LmiBool privacy);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectDefaultSpeaker}
	{parent: VidyoEndpoint}
	{description: Resets the speaker selection to pick the Default speaker.}
	{prototype: LmiBool VidyoEndpointSelectDefaultSpeaker(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectDefaultSpeaker(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointCycleSpeaker}
	{parent: VidyoEndpoint}
	{description: Cycles speaker selection to the next available speaker.}
	{prototype: LmiBool VidyoEndpointCycleSpeaker(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointCycleSpeaker(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterRemoteCameraEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about camera events from other participants.}
	{prototype: LmiBool VidyoEndpointRegisterRemoteCameraEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteCameraAdded onAdded, VidyoEndpointOnRemoteCameraRemoved onRemoved, VidyoEndpointOnRemoteCameraStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered when another participant adds a camera into a conference.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when another participant removes a camera from a conference.}
	}
	{parameter:
		{name: onStateUpdated}
		{description: Callback that is triggered when another participant updates a camera state in a conference.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterRemoteCameraEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteCameraAdded onAdded, VidyoEndpointOnRemoteCameraRemoved onRemoved, VidyoEndpointOnRemoteCameraStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterRemoteCameraEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters remote camera event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterRemoteCameraEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterRemoteCameraEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointAssignViewToRemoteCamera}
	{parent: VidyoEndpoint}
	{description: Shows a participant in a view.}
	{prototype: LmiBool VidyoEndpointAssignViewToRemoteCamera(VidyoEndpoint* e, const LmiViewId* viewId, VidyoRemoteCamera* camera, LmiBool displayCropped, LmiBool allowZoom)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: viewId}
		{description: A platform specific view ID where the participant will be rendered.}
	}
	{parameter:
		{name: camera}
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
	{note: This API will work only if compositing had been disabled by passing a NULL LmiViewId to VidyoEndpointConstruct.}
	{note: The application needs to make sure the sources are hidden when the local CPU and bandwidth are limited, by monitoring the VidyoEndpointOnResourcesChanged callback and showing/hiding sources based on avaialble resources.}
	{note: The view will not be shown until VidyoEndpointShowViewAt is called with valid parameters.}
}
*/
LmiBool VidyoEndpointAssignViewToRemoteCamera(VidyoEndpoint* e, const LmiViewId* viewId, VidyoRemoteCamera* camera, LmiBool displayCropped, LmiBool allowZoom);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterRemoteMicrophoneEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about microphone events from other participants.}
	{prototype: LmiBool VidyoEndpointRegisterRemoteMicrophoneEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteMicrophoneAdded onAdded, VidyoEndpointOnRemoteMicrophoneRemoved onRemoved, VidyoEndpointOnRemoteMicrophoneStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
		{description: Callback that is triggered when another participant updates a microphone state in a conference.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterRemoteMicrophoneEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteMicrophoneAdded onAdded, VidyoEndpointOnRemoteMicrophoneRemoved onRemoved, VidyoEndpointOnRemoteMicrophoneStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterRemoteMicrophoneEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters remote microphone event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterRemoteMicrophoneEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterRemoteMicrophoneEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterRemoteWindowShareEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about window-shares from other participants.}
	{prototype: LmiBool VidyoEndpointRegisterRemoteWindowShareEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteWindowShareAdded onAdded, VidyoEndpointOnRemoteWindowShareRemoved onRemoved, VidyoEndpointOnRemoteWindowShareStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
		{description: Callback that is triggered when another participant updates a window-share state in a conference.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterRemoteWindowShareEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteWindowShareAdded onAdded, VidyoEndpointOnRemoteWindowShareRemoved onRemoved, VidyoEndpointOnRemoteWindowShareStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterRemoteWindowShareEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters remote window share event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterRemoteWindowShareEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterRemoteWindowShareEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointAssignViewToRemoteWindowShare}
	{parent: VidyoEndpoint}
	{description: Shows a participant in a view.}
	{prototype: LmiBool VidyoEndpointAssignViewToRemoteWindowShare(VidyoEndpoint* e, const LmiViewId* viewId, VidyoRemoteWindowShare* remoteWindowShare, LmiBool displayCropped, LmiBool allowZoom)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{note: This API will work only if compositing had been disabled by passing a NULL LmiViewId to VidyoEndpointConstruct.}
	{note: The view will not be shown until VidyoEndpointShowViewAt is called with valid parameters.}
}
*/
LmiBool VidyoEndpointAssignViewToRemoteWindowShare(VidyoEndpoint* e, const LmiViewId* viewId, VidyoRemoteWindowShare* remoteWindowShare, LmiBool displayCropped, LmiBool allowZoom);

/**
 {function apigroup="simple":
	{name: VidyoEndpointHideView}
	{parent: VidyoEndpoint}
	{description: Hides a view which is used for custom layout of sources.}
	{prototype: LmiBool VidyoEndpointHideView(VidyoEndpoint* e, const LmiViewId* viewId)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: viewId}
		{description: The view ID of the view to hide.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointHideView(VidyoEndpoint* e, const LmiViewId* viewId);

/**
 {function apigroup="simple":
	{name: VidyoEndpointShowViewAt}
	{parent: VidyoEndpoint}
	{description: Sets the position of the view every time it's changed on the screen. }
	{prototype: LmiBool VidyoEndpointShowViewAt(VidyoEndpoint* e, const LmiViewId* viewId, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{return: }
	{note: The view will not be shown until this funciton is called with valid parameters.}
	{note: If viewId is NULL then the composite renderer constructed in VidyoEndpointConstruct will be positioned.}
}
*/
LmiBool VidyoEndpointShowViewAt(VidyoEndpoint* e, const LmiViewId* viewId, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
 {function apigroup="simple":
	{name: VidyoEndpointShowViewLabel}
	{parent: VidyoEndpoint}
	{description: Shows or hides the label on the view which displays the participant name or preview. }
	{prototype: LmiBool VidyoEndpointShowViewLabel(VidyoEndpoint* e, const LmiViewId* viewId, LmiBool showLabel)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{note: If viewId is NULL then the composite renderer constructed in VidyoEndpointConstruct will be assumed.}
}
*/
LmiBool VidyoEndpointShowViewLabel(VidyoEndpoint* e, const LmiViewId* viewId, LmiBool showLabel);

/**
 {function apigroup="simple":
	{name: VidyoEndpointShowAudioMeters}
	{parent: VidyoEndpoint}
	{description: Shows or hides the audio meters in the view. }
	{prototype: LmiBool VidyoEndpointShowAudioMeters(VidyoEndpoint* e, const LmiViewId* viewId, LmiBool showMeters)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{note: If viewId is NULL then the composite renderer constructed in VidyoEndpointConstruct will be assumed.}
}
*/
LmiBool VidyoEndpointShowAudioMeters(VidyoEndpoint* e, const LmiViewId* viewId, LmiBool showMeters);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSetViewBackgroundColor}
	{parent: VidyoEndpoint}
	{description: Shows or hides the label on the view which displays the participant name or preview. }
	{prototype: LmiBool VidyoEndpointSetViewBackgroundColor(VidyoEndpoint* e, const LmiViewId* viewId, LmiUint8 red, LmiUint8 green, LmiUint8 blue)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{note: If viewId is NULL then the composite renderer constructed in VidyoEndpointConstruct will be assumed.}
}
*/
LmiBool VidyoEndpointSetViewBackgroundColor(VidyoEndpoint* e, const LmiViewId* viewId, LmiUint8 red, LmiUint8 green, LmiUint8 blue);


/**
 {function apigroup="simple":
	{name: VidyoEndpointSetViewAnimationSpeed}
	{parent: VidyoEndpoint}
	{description: Sets the speed of transition animaiton for windows moving around inside the view. }
	{prototype: LmiBool VidyoEndpointSetViewAnimationSpeed(VidyoEndpoint* e, const LmiViewId* viewId, LmiUint speedPercentage)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
	{note: If viewId is NULL then the composite renderer constructed in VidyoEndpointConstruct will be assumed.}
}
*/
LmiBool VidyoEndpointSetViewAnimationSpeed(VidyoEndpoint* e, const LmiViewId* viewId, LmiUint speedPercentage);

/**
{function apigroup="simple":
	{name: VidyoEndpointStartLocationDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointStartLocationDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointStartLocationDetection(VidyoEndpoint* e);

/**
{function apigroup="simple":
	{name: VidyoEndpointStopLocationDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointStopLocationDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
}
*/
void VidyoEndpointStopLocationDetection(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointRegisterNetworkInterfaceEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about network interface events.}
	{prototype: LmiBool VidyoEndpointRegisterNetworkInterfaceEventListener(VidyoEndpoint* e, VidyoEndpointOnNetworkInterfaceAdded onAdded, VidyoEndpointOnNetworkInterfaceRemoved onRemoved, VidyoEndpointOnNetworkInterfaceSelected onSelected, VidyoEndpointOnNetworkInterfaceStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
LmiBool VidyoEndpointRegisterNetworkInterfaceEventListener(VidyoEndpoint* e, VidyoEndpointOnNetworkInterfaceAdded onAdded, VidyoEndpointOnNetworkInterfaceRemoved onRemoved, VidyoEndpointOnNetworkInterfaceSelected onSelected, VidyoEndpointOnNetworkInterfaceStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterNetworkInterfaceEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters network interface event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterNetworkInterfaceEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterNetworkInterfaceEventListener(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectDefaultNetworkInterfaceForSignaling}
	{parent: VidyoEndpoint}
	{description: Selects the default "any" network interface to be used for Signaling.}
	{prototype: LmiBool VidyoEndpointSelectDefaultNetworkInterfaceForSignaling(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectDefaultNetworkInterfaceForSignaling(VidyoEndpoint *e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectNetworkInterfaceForSignaling}
	{parent: VidyoEndpoint}
	{description: Selects the network interface to be used for Signaling.}
	{prototype: LmiBool VidyoEndpointSelectNetworkInterfaceForSignaling(VidyoEndpoint* e, const VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: networkInterface}
		{description: Network interface to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectNetworkInterfaceForSignaling(VidyoEndpoint *e, const VidyoNetworkInterface *networkInterface);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectDefaultNetworkInterfaceForMedia}
	{parent: VidyoEndpoint}
	{description: Selects the default "any" network interface to be used for Media.}
	{prototype: LmiBool VidyoEndpointSelectDefaultNetworkInterfaceForMedia(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectDefaultNetworkInterfaceForMedia(VidyoEndpoint* e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointSelectNetworkInterfaceForMedia}
	{parent: VidyoEndpoint}
	{description: Selects the network interface to be used for Media.}
	{prototype: LmiBool VidyoEndpointSelectNetworkInterfaceForMedia(VidyoEndpoint* e, const VidyoNetworkInterface* networkInterface)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: networkInterface}
		{description: Network interface to be selected.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSelectNetworkInterfaceForMedia(VidyoEndpoint *e, const VidyoNetworkInterface *networkInterface);

/**
{function apigroup="simple":
	{name: VidyoEndpointStartNetworkInterfaceDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointStartNetworkInterfaceDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointStartNetworkInterfaceDetection(VidyoEndpoint *e);

/**
{function apigroup="simple":
	{name: VidyoEndpointStopNetworkInterfaceDetection}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointStopNetworkInterfaceDetection(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
}
*/
void VidyoEndpointStopNetworkInterfaceDetection(VidyoEndpoint *e);

/**
{function apigroup="simple":
	{name: VidyoEndpointSetLocation}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetLocation(VidyoEndpoint* e, LmiFloat64 latitude, LmiFloat64 longitude)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: latitude}
		{description: }
	}
	{parameter:
		{name: longitude}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetLocation(VidyoEndpoint* e, LmiFloat64 latitude, LmiFloat64 longitude);

/**
{function:
	{name: VidyoEndpointSetPoolId}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetPoolId(VidyoEndpoint* e, const LmiString* poolId)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: poolId}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetPoolId(VidyoEndpoint* e, const LmiString* poolId);


/**
{function:
	{name: VidyoEndpointGenerateLicenseKey}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGenerateLicenseKey(VidyoEndpoint *e, LmiString *licenseKey)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: licenseKey}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGenerateLicenseKey(VidyoEndpoint *e, LmiString *licenseKey);

/**
{function:
	{name: VidyoEndpointValidateLicenseKey}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointValidateLicenseKey(VidyoEndpoint *e, const LmiString *licenseKey, LmiBool *isValid)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: licenseKey}
		{description: }
	}
	{parameter:
		{name: isValid}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointValidateLicenseKey(VidyoEndpoint *e, const LmiString *licenseKey, LmiBool *isValid);

/**
{function apigroup="simple":
	{name: VidyoEndpointGetId}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: const LmiString* VidyoEndpointGetId(const VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
const LmiString *VidyoEndpointGetId(const VidyoEndpoint *e);

/**
{function:
	{name: VidyoEndpointGetApplicationTag}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: const LmiString* VidyoEndpointGetApplicationTag(const VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: }
	}
	{return: }
}
*/
const LmiString *VidyoEndpointGetApplicationTag(const VidyoEndpoint *e);

/**
{function:
	{name: VidyoEndpointSetApplicationTag}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetApplicationTag(VidyoEndpoint* e, const char* applicationTag)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: applicationTag}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetApplicationTag(VidyoEndpoint *e, const char *applicationTag);

/**
{function apigroup="simple":
	{name: VidyoEndpointIsDebugEnabled}
	{parent: VidyoEndpoint}
	{description: Checks if debug mode is enabled on the endpoint.}
	{prototype: LmiBool VidyoEndpointIsDebugEnabled(VidyoEndpoint *e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE if enabled, LMI_FALSE otherwise.}
}
*/
LmiBool VidyoEndpointIsDebugEnabled(VidyoEndpoint *e);

/**
{function apigroup="simple":
	{name: VidyoEndpointEnableDebug}
	{parent: VidyoEndpoint}
	{description: Enabled debug mode on the endpoint which will start debug logging and enable statistics.}
	{prototype: LmiBool VidyoEndpointEnableDebug(VidyoEndpoint* e, LmiUint port, const char *logFilter)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: port}
		{description: Debug port will output debug logging.  }
	}
	{parameter:
		{name: logFilter}
		{description: Log filter to use on the debug port. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointEnableDebug(VidyoEndpoint *e, LmiUint port, const char *logFilter);

/**
{function apigroup="simple":
	{name: VidyoEndpointDisableDebug}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointDisableDebug(VidyoEndpoint *e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
}
*/
void VidyoEndpointDisableDebug(VidyoEndpoint *e);

/**
{function:
	{name: VidyoEndpointSetDebugFilter}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetDebugFilter(VidyoEndpoint* e, const char* debugLogFilter)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: debugLogFilter}
		{description: Log filter to use on the debug port. }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetDebugFilter(VidyoEndpoint *e, const char *debugLogFilter);

/**
{function apigroup="simple":
	{name: VidyoEndpointSetConsoleLoggerFilter}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetConsoleLoggerFilter(VidyoEndpoint* e, const char* consoleLogFilter)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: consoleLogFilter}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetConsoleLoggerFilter(VidyoEndpoint* e, const char* consoleLogFilter);

/**
{function:
	{name: VidyoEndpointSetConsoleLoggerLevelAndCategory}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetConsoleLoggerLevelAndCategory(VidyoEndpoint* e, const char* levelName, const char* categoryName, LmiBool on)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: levelName}
		{description: }
	}
	{parameter:
		{name: categoryName}
		{description: }
	}
	{parameter:
		{name: on}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetConsoleLoggerLevelAndCategory(VidyoEndpoint* e, const char* levelName, const char* categoryName, LmiBool on);

/**
{function visibility="private":
	{name: VidyoEndpointGetConsoleLoggerCategoryList}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetConsoleLoggerCategoryList(VidyoEndpoint* e, LmiVector(VidyoLoggerCategory)* categories)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: categories}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetConsoleLoggerCategoryList(VidyoEndpoint* e, LmiVector(VidyoLoggerCategory)* categories);

/**
{function apigroup="simple":
	{name: VidyoEndpointEnableFileLogger}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointEnableFileLogger(VidyoEndpoint *e, const char *fileLogName, const char *fileLogFilter)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: fileLogName}
		{description: }
	}
	{parameter:
		{name: fileLogFilter}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointEnableFileLogger(VidyoEndpoint *e, const char *fileLogName, const char *fileLogFilter);

/**
{function apigroup="simple":
	{name: VidyoEndpointSetFileLoggerFilter}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetFileLoggerFilter(VidyoEndpoint* e, const char* fileLogFilter)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: fileLogFilter}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetFileLoggerFilter(VidyoEndpoint* e, const char* fileLogFilter);

/**
{function:
	{name: VidyoEndpointSetFileLoggerLevelAndCategory}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetFileLoggerLevelAndCategory(VidyoEndpoint* e, const char* levelName, const char* categoryName, LmiBool on)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: levelName}
		{description: }
	}
	{parameter:
		{name: categoryName}
		{description: }
	}
	{parameter:
		{name: on}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetFileLoggerLevelAndCategory(VidyoEndpoint* e, const char* levelName, const char* categoryName, LmiBool on);
/**
{function visibility="private":
	{name: VidyoEndpointGetFileLoggerCategoryList}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetFileLoggerCategoryList(VidyoEndpoint* e, LmiVector(VidyoLoggerCategory)* categories)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: categories}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetFileLoggerCategoryList(VidyoEndpoint* e, LmiVector(VidyoLoggerCategory)* categories);

/**
 {type visibility="public":
	{name: VidyoEndpointLogCompressionResult}
	{parent: VidyoEndpoint}
	{description: Result of file log compression.}
	{value: {name: VIDYO_ENDPOINTLOGCOMPRESSIONRESULT_Success}
		{description: File Compressed successfully.}}
	{value: {name: VIDYO_ENDPOINTLOGCOMPRESSIONRESULT_MiscError}
		{description: The compression failed some miscellaneous reason.}}
}
*/
typedef enum
{
	VIDYO_ENDPOINTLOGCOMPRESSIONRESULT_Success,
	VIDYO_ENDPOINTLOGCOMPRESSIONRESULT_MiscError
} VidyoEndpointLogCompressionResult;

/**
 {callback:
	{name: VidyoEndpointOnLogCompressionComplete}
	{parent: VidyoEndpoint}
	{description: Callback that is triggered when the file log compression completes. }
	{prototype: void (*VidyoEndpointOnLogCompressionComplete)(VidyoEndpoint* e, LmiString *compressedFileName, VidyoEndpointLogCompressionResult result)}
	{parameter:
		{name: e}
		{description:}
	}
	{parameter:
		{name: compressedFileName}
		{description: Name if the compression output file.}
	}
	{parameter:
		{name: result}
		{description: Result of the file compression.}
	}
}
*/
typedef void(*VidyoEndpointOnLogCompressionComplete)(VidyoEndpoint* e, LmiString *compressedFileName, VidyoEndpointLogCompressionResult result);

/**
{function:
	{name: VidyoEndpointCompressLogs}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointCompressLogs(VidyoEndpoint *e, LmiString *compressedFileName, VidyoEndpointOnLogCompressionComplete onComplete)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: compressedFileName}
		{description: Name if the compression output file.}
	}
	{parameter:
		{name: onComplete}
		{description: Callback that is triggered when the compression completes.}
	}
	{return: }
}
*/
LmiBool VidyoEndpointCompressLogs(VidyoEndpoint *e, LmiString *compressedFileName, VidyoEndpointOnLogCompressionComplete onComplete);

/**
{function visibility="private":
	{name: VidyoEndpointAddAudioCodec}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointAddAudioCodec(VidyoEndpoint* e, const VidyoCodecAudio* audioCodec)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: audioCodec}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointAddAudioCodec(VidyoEndpoint* e, const VidyoCodecAudio* audioCodec);

/**
{function visibility="private":
	{name: VidyoEndpointAddVideoCodec}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointAddVideoCodec(VidyoEndpoint* e, const VidyoCodecVideo* videoCodec)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: videoCodec}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointAddVideoCodec(VidyoEndpoint* e, const VidyoCodecVideo* videoCodec);

/**
{function visibility="private":
	{name: VidyoEndpointSetAudioVideoCodecPreference}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetAudioVideoCodecPreference(VidyoEndpoint* e, const LmiVector(VidyoCodecVideo)* videoCodecs, const LmiVector(VidyoCodecAudio)* audioCodecs)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: videoCodecs}
		{description: }
	}
	{parameter:
		{name: audioCodecs}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointSetAudioVideoCodecPreference(VidyoEndpoint* e, const LmiVector(VidyoCodecVideo)* videoCodecs, const LmiVector(VidyoCodecAudio)* audioCodecs);

/**
{function visibility="private":
	{name: VidyoEndpointGetAudioVideoCodecPreference}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetAudioVideoCodecPreference(VidyoEndpoint* e, LmiVector(VidyoCodecVideo)* videoCodecs, LmiVector(VidyoCodecAudio)* audioCodecs)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: videoCodecs}
		{description: }
	}
	{parameter:
		{name: audioCodecs}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetAudioVideoCodecPreference(VidyoEndpoint* e, LmiVector(VidyoCodecVideo)* videoCodecs, LmiVector(VidyoCodecAudio)* audioCodecs);

/**
{function visibility="private":
	{name: VidyoEndpointRegisterVidyoTransport}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointRegisterVidyoTransport(VidyoEndpoint* e, const VidyoTransport* transport)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: transport}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointRegisterVidyoTransport(VidyoEndpoint* e, const VidyoTransport* transport);

/**
{function visibility="private":
	{name: VidyoEndpointSetWatermark}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointSetWatermark(VidyoEndpoint *e, const VidyoLmiVideoFrame *watermark)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: watermark}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointSetWatermark(VidyoEndpoint *e, const VidyoLmiVideoFrame *watermark);

/**
{function:
	{name: VidyoEndpointCreateRenderer}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointCreateRenderer(VidyoEndpoint* e, const VidyoLocalMonitor* monitor, LmiUint width, LmiUint height)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: monitor}
		{description: }
	}
	{parameter:
		{name: width}
		{description: }
	}
	{parameter:
		{name: height}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointCreateRenderer(VidyoEndpoint* e, const VidyoLocalMonitor* monitor, LmiUint width, LmiUint height);

/**
{function visibility="private":
	{name: VidyoEndpointCreateRendererFullScreen}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointCreateRendererFullScreen(VidyoEndpoint* e, VidyoLocalMonitor* monitor)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: monitor}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointCreateRendererFullScreen(VidyoEndpoint* e, VidyoLocalMonitor* monitor);

/**
{function visibility="private":
	{name: VidyoEndpointCreateRendererFromConferenceScene}
	{parent: VidyoEndpoint}
	{description: VidyoLocalRenderer object constructed from conference scene should also get notified about stream/slot changes by calling VidyoLocalRendererSetStreamParameters API.}
	{prototype: LmiBool VidyoEndpointCreateRendererFromConferenceScene(VidyoEndpoint* e, VidyoLmiConferenceScene* conferenceScene, LmiAllocator* alloc)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: conferenceScene}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointCreateRendererFromConferenceScene(VidyoEndpoint* e, VidyoLmiConferenceScene* conferenceScene, LmiAllocator* alloc);

/**
{function:
	{name: VidyoEndpointCreateRendererFromViewId}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointCreateRendererFromViewId(VidyoEndpoint* e, const LmiViewId* viewId, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: viewId}
		{description: A platform specific parent view ID where the rendering window will be added as a child window.}
	}
	{parameter:
		{name: x}
		{description: X coordinate of the child window within the parent view ID. }
	}
	{parameter:
		{name: y}
		{description: Y coordinate of the child window within the parent view ID. }
	}
	{parameter:
		{name: width}
		{description: Width of the child window within the parent view ID. }
	}
	{parameter:
		{name: height}
		{description: Height of the child window within the parent view ID. }
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
	{note: LmiViewId is HWND on windows, NSView on mac, UIView on iOS, window on X11, ViewGroup on android.}
}
*/
LmiBool VidyoEndpointCreateRendererFromViewId(VidyoEndpoint* e, const LmiViewId* viewId, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
{function:
	{name: VidyoEndpointRemoveRenderer}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointRemoveRenderer(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
}
*/
void VidyoEndpointRemoveRenderer(VidyoEndpoint* e, VidyoLocalRenderer* localRenderer);

/**
{function visibility="private":
	{name: VidyoEndpointGetLocalCameras}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetLocalCameras(VidyoEndpoint* e, LmiVector(VidyoLocalCamera)* localCameras)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCameras}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetLocalCameras(VidyoEndpoint* e, LmiVector(VidyoLocalCamera)* localCameras);

/**
{function visibility="private":
	{name: VidyoEndpointGetLocalMicrophones}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetLocalMicrophones(VidyoEndpoint* e, LmiVector(VidyoLocalMicrophone)* localMicrophones)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophones}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetLocalMicrophones(VidyoEndpoint* e, LmiVector(VidyoLocalMicrophone)* localMicrophones);

/**
{function visibility="private":
	{name: VidyoEndpointGetLocalSpeakers}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetLocalSpeakers(VidyoEndpoint* e, LmiVector(VidyoLocalSpeaker)* localSpeakers)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeakers}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetLocalSpeakers(VidyoEndpoint* e, LmiVector(VidyoLocalSpeaker)* localSpeakers);

/**
{function visibility="private":
	{name: VidyoEndpointGetLocalRenderers}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetLocalRenderers(VidyoEndpoint* e, LmiVector(VidyoLocalRenderer)* localRenderers)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderers}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetLocalRenderers(VidyoEndpoint* e, LmiVector(VidyoLocalRenderer)* localRenderers);

/**
{function visibility="private":
	{name: VidyoEndpointGetLocalWindowShares}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetLocalWindowShares(VidyoEndpoint* e, LmiVector(VidyoLocalWindowShare)* localWindowShares)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShares}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetLocalWindowShares(VidyoEndpoint* e, LmiVector(VidyoLocalWindowShare)* localWindowShares);

/**
{function visibility="private":
	{name: VidyoEndpointGetLocalMonitors}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: LmiBool VidyoEndpointGetLocalMonitors(VidyoEndpoint* e, LmiVector(VidyoLocalMonitor)* localMonitors)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitors}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoEndpointGetLocalMonitors(VidyoEndpoint* e, LmiVector(VidyoLocalMonitor)* localMonitors);

/**
 {function:
	{name: VidyoEndpointRegisterLocalRendererEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about renderer events.}
	{prototype: LmiBool VidyoEndpointRegisterLocalRendererEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalRendererAdded onAdded, VidyoEndpointOnLocalRendererRemoved onRemoved, VidyoEndpointOnLocalRendererSelected onSelected, VidyoEndpointOnLocalRendererStateUpdated onStateUpdated)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
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
		{description: Callback that is triggered when a window state changes.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterLocalRendererEventListener(VidyoEndpoint* e, VidyoEndpointOnLocalRendererAdded onAdded, VidyoEndpointOnLocalRendererRemoved onRemoved, VidyoEndpointOnLocalRendererSelected onSelected, VidyoEndpointOnLocalRendererStateUpdated onStateUpdated);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterLocalRendererEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters local renderer event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterLocalRendererEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterLocalRendererEventListener(VidyoEndpoint* e);

/**
 {function:
	{name: VidyoEndpointRegisterRemoteRendererEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about renderer events.}
	{prototype: LmiBool VidyoEndpointRegisterRemoteRendererEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteRendererAdded onAdded, VidyoEndpointOnRemoteRendererRemoved onRemoved)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing window added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the window is removed.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterRemoteRendererEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteRendererAdded onAdded, VidyoEndpointOnRemoteRendererRemoved onRemoved);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterRemoteRendererEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters remote renderer event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterRemoteRendererEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterRemoteRendererEventListener(VidyoEndpoint* e);

/**
 {function:
	{name: VidyoEndpointRegisterRemoteSpeakerEventListener}
	{parent: VidyoEndpoint}
	{description: Registers to get notified about speaker events.}
	{prototype: LmiBool VidyoEndpointRegisterRemoteSpeakerEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteSpeakerAdded onAdded, VidyoEndpointOnRemoteSpeakerRemoved onRemoved)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{parameter:
		{name: onAdded}
		{description: Callback that is triggered for every new or existing window added.}
	}
	{parameter:
		{name: onRemoved}
		{description: Callback that is triggered when the window is removed.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoEndpointRegisterRemoteSpeakerEventListener(VidyoEndpoint* e, VidyoEndpointOnRemoteSpeakerAdded onAdded, VidyoEndpointOnRemoteSpeakerRemoved onRemoved);

/**
 {function apigroup="simple":
	{name: VidyoEndpointUnregisterRemoteSpeakerEventListener}
	{parent: VidyoEndpoint}
	{description: Unregisters remote speaker event notifications.}
	{prototype: LmiBool VidyoEndpointUnregisterRemoteSpeakerEventListener(VidyoEndpoint* e)}
	{parameter:
		{name: e}
		{description: The VidyoEndpoint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
 }
 */
LmiBool VidyoEndpointUnregisterRemoteSpeakerEventListener(VidyoEndpoint* e);

/**
{function:
	{name: VidyoEndpointLocalCameraSelectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalCameraSelectAdvanced(VidyoEndpoint *e, const VidyoLocalCamera *localCamera)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCamera}
		{description: }
	}
}
*/
void VidyoEndpointLocalCameraSelectAdvanced(VidyoEndpoint *e, const VidyoLocalCamera *localCamera);

/**
{function:
	{name: VidyoEndpointLocalCameraUnselectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalCameraUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalCamera *localCamera)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localCamera}
		{description: }
	}
}
*/
void VidyoEndpointLocalCameraUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalCamera *localCamera);

/**
{function:
	{name: VidyoEndpointLocalMicrophoneSelectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalMicrophoneSelectAdvanced(VidyoEndpoint *e, const VidyoLocalMicrophone *localMicrophone, LmiBool previewedPreCall)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophone}
		{description: }
	}
	{parameter:
		{name: previewedPreCall}
		{description: }
	}
}
*/
void VidyoEndpointLocalMicrophoneSelectAdvanced(VidyoEndpoint *e, const VidyoLocalMicrophone *localMicrophone, LmiBool previewedPreCall);

/**
{function:
	{name: VidyoEndpointLocalMicrophoneUnselectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalMicrophoneUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalMicrophone *localMicrophone)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMicrophone}
		{description: }
	}
}
*/
void VidyoEndpointLocalMicrophoneUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalMicrophone *localMicrophone);

/**
{function:
	{name: VidyoEndpointLocalSpeakerSelectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalSpeakerSelectAdvanced(VidyoEndpoint *e, const VidyoLocalSpeaker *localSpeaker)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeaker}
		{description: }
	}
}
*/
void VidyoEndpointLocalSpeakerSelectAdvanced(VidyoEndpoint *e, const VidyoLocalSpeaker *localSpeaker);

/**
{function:
	{name: VidyoEndpointLocalSpeakerUnselectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalSpeakerUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalSpeaker *localSpeaker)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localSpeaker}
		{description: }
	}
}
*/
void VidyoEndpointLocalSpeakerUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalSpeaker *localSpeaker);

/**
{function:
	{name: VidyoEndpointLocalWindowShareSelectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalWindowShareSelectAdvanced(VidyoEndpoint *e, const VidyoLocalWindowShare *localWindowShare)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShare}
		{description: }
	}
}
*/
void VidyoEndpointLocalWindowShareSelectAdvanced(VidyoEndpoint *e, const VidyoLocalWindowShare *localWindowShare);

/**
{function:
	{name: VidyoEndpointLocalWindowShareUnselectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalWindowShareUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalWindowShare *localWindowShare)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localWindowShare}
		{description: }
	}
}
*/
void VidyoEndpointLocalWindowShareUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalWindowShare *localWindowShare);

/**
{function:
	{name: VidyoEndpointLocalMonitorSelectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalMonitorSelectAdvanced(VidyoEndpoint *e, const VidyoLocalMonitor *localMonitor)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitor}
		{description: }
	}
}
*/
void VidyoEndpointLocalMonitorSelectAdvanced(VidyoEndpoint *e, const VidyoLocalMonitor *localMonitor);

/**
{function:
	{name: VidyoEndpointLocalMonitorUnselectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalMonitorUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalMonitor *localMonitor)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localMonitor}
		{description: }
	}
}
*/
void VidyoEndpointLocalMonitorUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalMonitor *localMonitor);

/**
{function:
	{name: VidyoEndpointLocalRendererSelectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalRendererSelectAdvanced(VidyoEndpoint *e, const VidyoLocalRenderer *localRenderer)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
}
*/
void VidyoEndpointLocalRendererSelectAdvanced(VidyoEndpoint *e, const VidyoLocalRenderer *localRenderer);

/**
{function:
	{name: VidyoEndpointLocalRendererUnselectAdvanced}
	{parent: VidyoEndpoint}
	{description: }
	{prototype: void VidyoEndpointLocalRendererUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalRenderer *localRenderer)}
	{parameter:
		{name: e}
		{description: }
	}
	{parameter:
		{name: localRenderer}
		{description: }
	}
}
*/
void VidyoEndpointLocalRendererUnselectAdvanced(VidyoEndpoint *e, const VidyoLocalRenderer *localRenderer);

/**
{type:
	{name: VidyoEndpointTone}
	{parent: VidyoEndpoint}
	{description: }
	{value: {name: VIDYO_ENDPOINTTONE_Join} {description: }}
	{value: {name: VIDYO_ENDPOINTTONE_Leave} {description: }}
	{value: {name: VIDYO_ENDPOINTTONE_MsgRecv} {description: }}
    {value: {name: VIDYO_ENDPOINTTONE_MsgSend} {description: }}
    {value: {name: VIDYO_ENDPOINTTONE_Ring} {description: }}
    {value: {name: VIDYO_ENDPOINTTONE_Max} {description: }}
}
*/
typedef enum {
	VIDYO_ENDPOINTTONE_Join,
	VIDYO_ENDPOINTTONE_Leave,
	VIDYO_ENDPOINTTONE_MsgRecv,
    VIDYO_ENDPOINTTONE_MsgSend,
    VIDYO_ENDPOINTTONE_Ring,
    VIDYO_ENDPOINTTONE_Max
} VidyoEndpointTone;

LmiBool LmiVidyoEndpointSetTone(VidyoEndpoint* e, VidyoEndpointTone tone, const LmiString* filePath);
VidyoLmiAudioFrame* LmiVidyoEndpointGetTone(VidyoEndpoint* e, VidyoEndpointTone tone);

struct LmiResourceManager_;
struct LmiResourceManager_* VidyoEndpointGetResourceManager(VidyoEndpoint *e);

/**
{function apigroup="simple":
	{name: VidyoEndpointGetStats}
	{parent: VidyoEndpoint}
	{description: Fill in data in VidyoEndpointStats from an endpoint.}
	{prototype: VidyoEndpointStats *VidyoEndpointGetStats(VidyoEndpoint *e)}
	{parameter: {name: e} {description: The endpoint object to extract stats.}}
	{return: Pointer to the endpoint stats on Success or NULL on failure.}
}
*/
VidyoEndpointStats *VidyoEndpointGetStats(VidyoEndpoint *e);

/**
{function apigroup="simple":
	{name: VidyoEndpointGetStatsJson}
	{parent: VidyoEndpoint}
	{description: Fill in data in VidyoEndpointStats from an endpoint.}
	{prototype: LmiString *VidyoEndpointGetStatsJson(VidyoEndpoint *e)}
	{parameter: {name: e} {description: The endpoint object to extract stats.}}
	{return: Pointer to the json encoded string containing the stats on Success or NULL on failure.}
}
*/
LmiString *VidyoEndpointGetStatsJson(VidyoEndpoint *e);

/**
 {function apigroup="simple":
	{name: VidyoEndpointDisable}
	{parent: VidyoEndpoint}
	{description: Stop background tasks associated with an endpoint.}
	{prototype: void VidyoEndpointDisable(VidyoEndpoint *e)}
	{parameter: {name: e} {description: The endpoint object to disable.}}
 }
 */
void VidyoEndpointDisable(VidyoEndpoint *e);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoEndpointInline.h"
#endif

#endif /* VIDYO_CLIENT_H_ */


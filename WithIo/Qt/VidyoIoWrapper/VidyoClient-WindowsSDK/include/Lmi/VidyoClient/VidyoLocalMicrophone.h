/** 
{file:
	{name: VidyoLocalMicrophone.h}
	{description: Microphone device. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
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
#ifndef VIDYO_LOCALMICROPHONE_H_ 
#define VIDYO_LOCALMICROPHONE_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoLocalMicrophoneImpl_;
typedef struct VidyoLocalMicrophoneImpl_ VidyoLocalMicrophoneImpl;
Declare_LmiSharedPtr(VidyoLocalMicrophoneImpl)
Declare_LmiSharedPtrWrapper(VidyoLocalMicrophone, VidyoLocalMicrophoneImpl)
Declare_LmiWeakPtrWrapper(VidyoLocalMicrophoneHandle, VidyoLocalMicrophone, VidyoLocalMicrophoneImpl)
Declare_LmiVector(VidyoLocalMicrophone)
Declare_LmiList(VidyoLocalMicrophone)

LMI_END_EXTERN_C

#include "VidyoEndpoint.h"
#include "VidyoLocalSpeaker.h"
#include "VidyoRemoteSpeaker.h"
#include "VidyoAudioCapability.h"
#include "VidyoForwardDecl.h"
#include "VidyoDevice.h"

LMI_BEGIN_EXTERN_C

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoLocalMicrophone}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoLocalMicrophone.h}
	{description: This object represents a microphone on the local endpoint.}
	{member:
		{name: id}
		{type: LmiString}
		{description: Unique ID.}
	}
	{member:
		{name: name}
		{type: LmiString}
		{description: Name.}
	}
}
*/

/**
{type apigroup="connector simple" visibility="private":
	{name: VidyoLocalMicrophoneHandle}
	{parent: VidyoLocalMicrophone}
	{description: }
}
*/

/**
{callback visibility="private":
	{name: VidyoLocalMicrophoneCallback}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void (*VidyoLocalMicrophoneCallback)(const VidyoLocalMicrophone* m, const VidyoLmiAudioFrame* audioFrame)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: audioFrame}
		{description: }
	}
}
*/
typedef void (*VidyoLocalMicrophoneCallback)(const VidyoLocalMicrophone* m, const VidyoLmiAudioFrame* audioFrame);

/**
{callback visibility="private":
	{name: VidyoLocalMicrophoneStartCallback}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void (*VidyoLocalMicrophoneStartCallback)(const VidyoLocalMicrophone* m, LmiUint sampleRate, LmiUint numberOfChannels, const LmiMediaFormat *mediaFormat, LmiTime frameInterval, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: sampleRate}
		{description: }
	}
	{parameter:
		{name: numberOfChannels}
		{description: }
	}
	{parameter:
		{name: mediaFormat}
		{description: }
	}
	{parameter:
		{name: frameInterval}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalMicrophoneStartCallback)(const VidyoLocalMicrophone* m, LmiUint sampleRate, LmiUint numberOfChannels, const LmiMediaFormat *mediaFormat, LmiTime frameInterval, LmiVoidPtr userData);

/**
{callback visibility="private":
	{name: VidyoLocalMicrophoneStopCallback}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void (*VidyoLocalMicrophoneStopCallback)(const VidyoLocalMicrophone* m, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
typedef void (*VidyoLocalMicrophoneStopCallback)(const VidyoLocalMicrophone* m, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneConstruct}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: VidyoLocalMicrophone* VidyoLocalMicrophoneConstruct(VidyoLocalMicrophone* m, VidyoEndpoint *endpoint, VidyoLmiAudioCapturer* audioCapturer, LmiAllocator* alloc)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: audioCapturer}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalMicrophone* VidyoLocalMicrophoneConstruct(VidyoLocalMicrophone* m, VidyoEndpoint *endpoint, VidyoLmiAudioCapturer* audioCapturer, LmiAllocator* alloc);


/**
{function visibility="private":
	{name: VidyoLocalMicrophoneConstructVirtual}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: VidyoLocalMicrophone *VidyoLocalMicrophoneConstructVirtual(VidyoLocalMicrophone *m, VidyoEndpoint *endpoint, LmiString *id, LmiString *name, VidyoLocalMicrophoneStartCallback onStart, VidyoLocalMicrophoneStopCallback onStop, LmiVoidPtr virtualUserData, LmiAllocator *alloc)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: endpoint}
		{description: }
	}
	{parameter:
		{name: id}
		{description: }
	}
	{parameter:
		{name: name}
		{description: }
	}
	{parameter:
		{name: onStart}
		{description: }
	}
	{parameter:
		{name: onStop}
		{description: }
	}
	{parameter:
		{name: virtualUserData}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalMicrophone *VidyoLocalMicrophoneConstructVirtual(VidyoLocalMicrophone *m, VidyoEndpoint *endpoint, LmiString *id, LmiString *name, VidyoLocalMicrophoneStartCallback onStart, VidyoLocalMicrophoneStopCallback onStop, LmiVoidPtr virtualUserData, LmiAllocator *alloc);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMicrophoneConstructCopy}
	{parent: VidyoLocalMicrophone}
	{description: Constructs an VidyoLocalMicrophone object as a copy of another.}
	{prototype: VidyoLocalMicrophone *VidyoLocalMicrophoneConstructCopy(VidyoLocalMicrophone *obj, const VidyoLocalMicrophone *other)}
	{parameter: {name: obj} {description: The VidyoLocalMicrophone object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple":
	{name: VidyoLocalMicrophoneDestruct}
	{parent: VidyoLocalMicrophone}
	{description: Destructs an VidyoLocalMicrophone object.}
	{prototype: void VidyoLocalMicrophoneDestruct(VidyoLocalMicrophone *obj)}
	{parameter: {name: obj} {description: The VidyoLocalMicrophone object to destruct.}}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMicrophoneAssign}
	{parent: VidyoLocalMicrophone}
	{description: Assigns one VidyoLocalMicrophone object the value of another. }
	{prototype: VidyoLocalMicrophone *VidyoLocalMicrophoneAssign(VidyoLocalMicrophone *obj, const VidyoLocalMicrophone *other)}
	{parameter: {name: obj} {description: The VidyoLocalMicrophone object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMicrophoneGetHandle}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: VidyoLocalMicrophoneHandle* VidyoLocalMicrophoneGetHandle(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
VidyoLocalMicrophoneHandle* VidyoLocalMicrophoneGetHandle(VidyoLocalMicrophone* m);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMicrophoneGetName}
	{parent: VidyoLocalMicrophone}
	{description: Gets the name of the microphone. }
	{prototype: const LmiString* VidyoLocalMicrophoneGetName(const VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: Name of the microphone.}
}
*/
const LmiString* VidyoLocalMicrophoneGetName(const VidyoLocalMicrophone* m);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMicrophoneGetId}
	{parent: VidyoLocalMicrophone}
	{description: Gets the unique ID of the microphone.}
	{prototype: const LmiString* VidyoLocalMicrophoneGetId(const VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: Unique ID of the microphone. }
}
*/
const LmiString* VidyoLocalMicrophoneGetId(const VidyoLocalMicrophone* m);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMicrophoneSetUserData}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void VidyoLocalMicrophoneSetUserData(VidyoLocalMicrophone* m, LmiVoidPtr userData)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoLocalMicrophoneSetUserData(VidyoLocalMicrophone* m, LmiVoidPtr userData);

/**
{function apigroup="connector simple" visibility="private":
	{name: VidyoLocalMicrophoneGetUserData}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiVoidPtr VidyoLocalMicrophoneGetUserData(const VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiVoidPtr VidyoLocalMicrophoneGetUserData(const VidyoLocalMicrophone* m);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneSetCallback}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void VidyoLocalMicrophoneSetCallback(VidyoLocalMicrophone* m, VidyoLocalMicrophoneCallback callback)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: callback}
		{description: }
	}
}
*/
void VidyoLocalMicrophoneSetCallback(VidyoLocalMicrophone* m, VidyoLocalMicrophoneCallback callback);

/**
{function:
	{name: VidyoLocalMicrophoneIsPaused}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneIsPaused(const VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneIsPaused(const VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophonePause}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void VidyoLocalMicrophonePause(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
}
*/
void VidyoLocalMicrophonePause(VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophoneResume}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void VidyoLocalMicrophoneResume(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
}
*/
void VidyoLocalMicrophoneResume(VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophonePlayTone}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void VidyoLocalMicrophonePlayTone(VidyoLocalMicrophone* m, char dtmfTone)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: dtmfTone}
		{description: }
	}
}
*/
void VidyoLocalMicrophonePlayTone(VidyoLocalMicrophone* m, char dtmfTone);

/**
{function:
	{name: VidyoLocalMicrophoneGetVolume}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiUint VidyoLocalMicrophoneGetVolume(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiUint VidyoLocalMicrophoneGetVolume(VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophoneSetVolume}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: void VidyoLocalMicrophoneSetVolume(VidyoLocalMicrophone* m, LmiUint volumePercent)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: volumePercent}
		{description: }
	}
}
*/
void VidyoLocalMicrophoneSetVolume(VidyoLocalMicrophone* m, LmiUint volumePercent);

/**
{function:
	{name: VidyoLocalMicrophoneGetAutoGain}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneGetAutoGain(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneGetAutoGain(VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophoneSetAutoGain}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneSetAutoGain(VidyoLocalMicrophone* m, LmiBool autoGain)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: autoGain}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneSetAutoGain(VidyoLocalMicrophone* m, LmiBool autoGain);

/**
{function:
	{name: VidyoLocalMicrophoneGetVoiceProcessing}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneGetVoiceProcessing(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneGetVoiceProcessing(VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophoneSetVoiceProcessing}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneSetVoiceProcessing(VidyoLocalMicrophone* m, LmiBool voiceProcessing)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: voiceProcessing}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneSetVoiceProcessing(VidyoLocalMicrophone* m, LmiBool voiceProcessing);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMicrophoneGetSignalType}
	{parent: VidyoLocalMicrophone}
	{description: Gets signal type of the microphone, which affects how the audio is processed.}
	{prototype: VidyoDeviceAudioSignalType VidyoLocalMicrophoneGetSignalType(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: The signal type of the microphone.}
	{note: The default signal type is Voice.}
}
*/
VidyoDeviceAudioSignalType VidyoLocalMicrophoneGetSignalType(VidyoLocalMicrophone* m);

/**
{function apigroup="connector simple":
	{name: VidyoLocalMicrophoneSetSignalType}
	{parent: VidyoLocalMicrophone}
	{description: Sets the signal type of the microhone which changes how the auido is processed. }
	{prototype: LmiBool VidyoLocalMicrophoneSetSignalType(VidyoLocalMicrophone* m, VidyoDeviceAudioSignalType signalType)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: signalType}
		{description: The signal type of the microphone.}
	}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalMicrophoneSetSignalType(VidyoLocalMicrophone* m, VidyoDeviceAudioSignalType signalType);

/**
{function:
	{name: VidyoLocalMicrophoneAddToRemoteSpeaker}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneAddToRemoteSpeaker(VidyoLocalMicrophone* m, const VidyoRemoteSpeaker* remoteSpeaker)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: remoteSpeaker}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneAddToRemoteSpeaker(VidyoLocalMicrophone* m, const VidyoRemoteSpeaker* remoteSpeaker);

/**
{function:
	{name: VidyoLocalMicrophoneRemoveFromRemoteSpeaker}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneRemoveFromRemoteSpeaker(VidyoLocalMicrophone* m, const VidyoRemoteSpeaker* remoteSpeaker)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: remoteSpeaker}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneRemoveFromRemoteSpeaker(VidyoLocalMicrophone* m, const VidyoRemoteSpeaker* remoteSpeaker);

/**
{function:
	{name: VidyoLocalMicrophoneAddToLocalSpeaker}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneAddToLocalSpeaker(VidyoLocalMicrophone* m, const VidyoLocalSpeaker* speaker)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: speaker}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneAddToLocalSpeaker(VidyoLocalMicrophone* m, const VidyoLocalSpeaker* speaker);

/**
{function:
	{name: VidyoLocalMicrophoneRemoveFromLocalSpeaker}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneRemoveFromLocalSpeaker(VidyoLocalMicrophone* m, const VidyoLocalSpeaker* speaker)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: speaker}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneRemoveFromLocalSpeaker(VidyoLocalMicrophone* m, const VidyoLocalSpeaker* speaker);

/**
{function:
	{name: VidyoLocalMicrophoneSetEchoCancellation}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneSetEchoCancellation(VidyoLocalMicrophone* m, const VidyoLocalSpeaker* speaker, LmiBool isEnable)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: speaker}
		{description: }
	}
	{parameter:
		{name: isEnable}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneSetEchoCancellation(VidyoLocalMicrophone* m, const VidyoLocalSpeaker* speaker, LmiBool isEnable);

/**
{function:
	{name: VidyoLocalMicrophoneEnableDebugRecording}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneEnableDebugRecording(VidyoLocalMicrophone* m, const LmiString* dir)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: dir}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneEnableDebugRecording(VidyoLocalMicrophone* m, const LmiString* dir);

/**
{function:
	{name: VidyoLocalMicrophoneDisableDebugRecording}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneDisableDebugRecording(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneDisableDebugRecording(VidyoLocalMicrophone* m);

/**
{function:
	{name: VidyoLocalMicrophoneIsDebugRecordingEnabled}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneIsDebugRecordingEnabled(VidyoLocalMicrophone* m)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneIsDebugRecordingEnabled(VidyoLocalMicrophone* m);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneGetStats}
	{parent: VidyoLocalMicrophone}
	{description: Fill in data in VidyoLocalMicrophoneStats from a local microphone.}
	{prototype: LmiBool VidyoLocalMicrophoneGetStats(VidyoLocalMicrophone *microphone, VidyoLocalMicrophoneStats *stats)}
	{parameter: {name: microphone} {description: The local microphone object to extract stats.}}
	{parameter: {name: stats} {description: The stats object to fill.}}
	{return: LMI_TRUE on success.}
}
*/
LmiBool VidyoLocalMicrophoneGetStats(VidyoLocalMicrophone *microphone, VidyoLocalMicrophoneStats *stats);

/**
{function:
	{name: VidyoLocalMicrophoneShowDebugDialog}
	{parent: VidyoLocalMicrophone}
	{description: Shows an audio debug dialog for the local microphone.}
	{prototype: void VidyoLocalMicrophoneShowDebugDialog(VidyoLocalMicrophone *microphone)}
	{parameter: {name: microphone} {description: The local microphone object to extract stats.}}
	{note: The dialog is a platform-specific native window that will pop up outside of the application.}
}
*/
void VidyoLocalMicrophoneShowDebugDialog(VidyoLocalMicrophone *microphone);

/**
{function:
	{name: VidyoLocalMicrophoneHideDebugDialog}
	{parent: VidyoLocalMicrophone}
	{description: Hides an audio debug dialog for the local microphone.}
	{prototype: void VidyoLocalMicrophoneHideDebugDialog(VidyoLocalMicrophone *microphone)}
	{parameter: {name: microphone} {description: The local microphone object to extract stats.}}
}
*/
void VidyoLocalMicrophoneHideDebugDialog(VidyoLocalMicrophone *microphone);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneAddAudioFrame}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: LmiBool VidyoLocalMicrophoneAddAudioFrame(VidyoLocalMicrophone *m, const VidyoLmiAudioFrame *audioFrame)}
	{parameter:
		{name: m}
		{description: The VidyoLocalMicrophone object. }
	}
	{parameter:
		{name: audioFrame}
		{description: }
	}
	{return: }
}
*/
LmiBool VidyoLocalMicrophoneAddAudioFrame(VidyoLocalMicrophone *m, const VidyoLmiAudioFrame *audioFrame);

/**
{function visibility="private":
	{name: VidyoLocalMicrophoneConstructFromDevice}
	{parent: VidyoLocalMicrophone}
	{description: }
	{prototype: VidyoLocalMicrophone *VidyoLocalMicrophoneConstructFromDevice(VidyoLocalMicrophone* vidyoLocalMicrophone, VidyoDevice *device, LmiAllocator* alloc)}
	{parameter:
		{name: vidyoLocalMicrophone}
		{description: }
	}
	{parameter:
		{name: device}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoLocalMicrophone *VidyoLocalMicrophoneConstructFromDevice(VidyoLocalMicrophone* vidyoLocalMicrophone, VidyoDevice *device, LmiAllocator* alloc);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoLocalMicrophoneInline.h"
#endif

#endif /* VIDYO_LOCALMICROPHONE_H_ */

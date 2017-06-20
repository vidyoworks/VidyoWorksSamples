/**
{file:
	{name: VidyoGateway.h}
	{description: Gateway base class. }
	{copyright:
		(c) 2013-2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.

		All rights reserved.

		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
		                  ***** CONFIDENTIAL *****
	}
}
*/
#ifndef VIDYO_GATEWAY_H_
#define VIDYO_GATEWAY_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiSharedPtr.h>

LMI_BEGIN_EXTERN_C

struct VidyoGatewayImpl_;
typedef struct VidyoGatewayImpl_ VidyoGatewayImpl;
Declare_LmiSharedPtr(VidyoGatewayImpl)
Declare_LmiSharedPtrWrapper(VidyoGateway, VidyoGatewayImpl)
Declare_LmiWeakPtrWrapper(VidyoGatewayHandle, VidyoGateway, VidyoGatewayImpl)

/**
{type reference-counted="yes":
	{name: VidyoGateway}
	{parent: Connector}
	{include: Lmi/VidyoClient/VidyoGateway.h}
	{description: A wrapper for Vidyo gateways. }
}
*/

/**
{function:
	{name: VidyoGatewayInitialize}
	{parent: VidyoGateway}
	{description: Initialize the VidyoGateway library.}
	{prototype: LmiBool VidyoGatewayInitialize(void)}
	{return: }
	{note: The library must be Initialized once the application starts, before any other VidyoGateway APIs. It must also be Uninitialized before exiting the application or after the library is no loger needed. }
}
*/
LmiBool VidyoGatewayInitialize(void);

/**
{function:
	{name: VidyoGatewayUninitialize}
	{parent: VidyoGateway}
	{description: Uninitialize the VidyoGateway library.}
	{prototype: void VidyoGatewayUninitialize(void)}
}
*/
void VidyoGatewayUninitialize(void);

/**
 {type:
	{name: VidyoGatewayFailReason}
	{parent: VidyoGateway}
	{description: Reasons why a connection attempt failed.}
	{value: {name: VIDYO_GATEWAYFAILREASON_ConnectionFailed}
		{description: The destination could not be reached.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_ConnectionLost}
		{description: The transport connection was lost prior to completing the login procedure.}}
 	{value: {name: VIDYO_GATEWAYFAILREASON_ConnectionTimeout}
		{description: The signaling connection timed-out prior to completing the login procedure.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_NoResponse}
		{description: The service was successfully contacted, but the service ignored the user's
			request to log in or it did not answer in a reasonable amount of time.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_Terminated}
		{description: The service was successfully contacted, but the service closed the connection
			or it refused to continue processing the login request.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_InvalidToken}
		{description: The token that was provided is unknown to the service or unauthorized to log in.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_UnableToCreateResource} {description: The server was unable to create the resource.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_NoResponseFromResource} {description: The server did
		not respond in a reasonable amount of time to the request to connect to the resource.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_InvalidResourceId} {description: The resource ID was invalid.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_ResourceFull} {description: The resource
		is at full capacity, and it cannot accept additional members.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_NotMember} {description: The resource allows
		only certain users to enter, and the current user is not one of them.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_Banned} {description: The user has
		been banned from entering the resource.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_MediaNotEnabled} {description: The client could not enable media.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_MediaFailed} {description: An established media connection failed.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_MiscLocalError} {description: The server
		rejected the user's request to enter the resource, due to a miscellaneous problem with the request.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_MiscRemoteError} {description: The server
		rejected the user's request to enter the resource, due to a miscellaneous problem of its own.}}
	{value: {name: VIDYO_GATEWAYFAILREASON_MiscError}
		{description: The login failed for some other miscellaneous reason.}}
}
*/
typedef enum
{
	VIDYO_GATEWAYFAILREASON_ConnectionFailed,
	VIDYO_GATEWAYFAILREASON_ConnectionLost,
	VIDYO_GATEWAYFAILREASON_ConnectionTimeout,
	VIDYO_GATEWAYFAILREASON_NoResponse,
	VIDYO_GATEWAYFAILREASON_Terminated,
	VIDYO_GATEWAYFAILREASON_InvalidToken,
	VIDYO_GATEWAYFAILREASON_UnableToCreateResource,
	VIDYO_GATEWAYFAILREASON_NoResponseFromResource,
	VIDYO_GATEWAYFAILREASON_InvalidResourceId,
	VIDYO_GATEWAYFAILREASON_ResourceFull,
	VIDYO_GATEWAYFAILREASON_NotMember,
	VIDYO_GATEWAYFAILREASON_Banned,
	VIDYO_GATEWAYFAILREASON_MediaNotEnabled,
	VIDYO_GATEWAYFAILREASON_MediaFailed,
	VIDYO_GATEWAYFAILREASON_MiscLocalError,
	VIDYO_GATEWAYFAILREASON_MiscRemoteError,
	VIDYO_GATEWAYFAILREASON_MiscError
} VidyoGatewayFailReason;

/**
 {type:
	{name: VidyoGatewayDisconnectReason}
	{parent: VidyoGateway}
	{description: Reasons why an established connection was disconnected.}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_Disconnected}
		{description: The user disconnected gracefully.}}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_ConnectionLost}
		{description: The transport connection was lost.}}
 	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_ConnectionTimeout}
		{description: The signaling connection timed-out.}}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_NoResponse}
		{description: The service did not respond in a reasonable amount of time to a request by the user.}}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_Terminated}
		{description: The service closed the connection or otherwise terminated the login session.}}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_MiscLocalError}
		{description: A miscellaneous problem occurred with this client library.}}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_MiscRemoteError}
		{description: A miscellaneous problem occurred with the conferencing service.}}
	{value: {name: VIDYO_GATEWAYDISCONNECTREASON_MiscError}
		{description: The connection was closed for some other miscellaneous reason.}}
}
*/
typedef enum
{
	VIDYO_GATEWAYDISCONNECTREASON_Disconnected,
	VIDYO_GATEWAYDISCONNECTREASON_ConnectionLost,
	VIDYO_GATEWAYDISCONNECTREASON_ConnectionTimeout,
	VIDYO_GATEWAYDISCONNECTREASON_NoResponse,
	VIDYO_GATEWAYDISCONNECTREASON_Terminated,
	VIDYO_GATEWAYDISCONNECTREASON_MiscLocalError,
	VIDYO_GATEWAYDISCONNECTREASON_MiscRemoteError,
	VIDYO_GATEWAYDISCONNECTREASON_MiscError
} VidyoGatewayDisconnectReason;

/**
 {type:
	{name: VidyoGatewayState}
	{parent: VidyoGateway}
	{description: States of the VidyoGateway.}
	{value: {name: VIDYO_GATEWAYSTATE_Idle}
			{description: Ready to connect.}
	}
	{value: {name: VIDYO_GATEWAYSTATE_EstablishingConnection}
			{description: Establishing a connection to the server.}
	}
	{value: {name: VIDYO_GATEWAYSTATE_FindingResource}
			{description: Finding a resource.}
	}
	{value: {name: VIDYO_GATEWAYSTATE_ConnectingToResource}
			{description: Connecting to a resource.}
	}
	{value: {name: VIDYO_GATEWAYSTATE_EnablingMedia}
			{description: Enabling media.}
	}
	{value: {name: VIDYO_GATEWAYSTATE_Connected}
			{description: Sucessfully connected.}
	}
}
*/
typedef enum
{
	VIDYO_GATEWAYSTATE_Idle,
	VIDYO_GATEWAYSTATE_EstablishingConnection,
	VIDYO_GATEWAYSTATE_FindingResource,
	VIDYO_GATEWAYSTATE_ConnectingToResource,
	VIDYO_GATEWAYSTATE_EnablingMedia,
	VIDYO_GATEWAYSTATE_Connected
} VidyoGatewayState;

/**
 {callback:
	{name: VidyoGatewayOnSuccess}
	{parent: VidyoGateway}
	{description: Callback that is triggered when the connection is sucessfully established. }
	{prototype: void (*VidyoGatewayOnSuccess)(VidyoGateway* gateway)}
	{parameter:
		{name: gateway}
		{description: The VidyoGateway that triggered the callback.}
	}
}
*/
typedef void(*VidyoGatewayOnSuccess)(VidyoGateway* gateway);

/**
 {callback:
	{name: VidyoGatewayOnFailure}
	{parent: VidyoGateway}
	{description: Callback that is triggered when the connection establishemnt failed. }
	{prototype: void (*VidyoGatewayOnFailure)(VidyoGateway* gateway, VidyoGatewayFailReason reason)}
	{parameter:
		{name: gateway}
		{description: The VidyoGateway that triggered the callback.}
	}
	{parameter:
		{name: reason}
		{description: Reason why the connection could not be established.}
	}
}
*/
typedef void(*VidyoGatewayOnFailure)(VidyoGateway* gateway, VidyoGatewayFailReason reason);

/**
 {callback:
	{name: VidyoGatewayOnDisconnected}
	{parent: VidyoGateway}
	{description: Callback that is triggered when an established connection is disconnected. }
	{prototype: void (*VidyoGatewayOnDisconnected)(VidyoGateway* gateway, VidyoGatewayDisconnectReason reason)}
	{parameter:
		{name: gateway}
		{description: The VidyoGateway that triggered the callback.}
	}
	{parameter:
		{name: reason}
		{description: Reason why the connection could not be established.}
	}
}
*/
typedef void(*VidyoGatewayOnDisconnected)(VidyoGateway* gateway, VidyoGatewayDisconnectReason reason);

/**
{function visibility="private":
	{name: VidyoGatewayConstruct}
	{parent: VidyoGateway}
	{description: Initialize an instance of VidyoGateway}
	{prototype: VidyoGateway* VidyoGatewayConstruct(VidyoGateway* gateway, LmiAllocator* alloc)}
	{parameter: {name: gateway} {description: Pointer to the VidyoGateway object to construct.}}
	{parameter: {name: alloc} {description: allocator}}
	{return: Properly initialized object or NULL on failure.}
}
*/
VidyoGateway* VidyoGatewayConstruct(VidyoGateway* gateway, LmiAllocator* alloc);

/**
{function:
	{name: VidyoGatewayConstructCopy}
	{parent: VidyoGateway}
	{description: Constructs an VidyoGateway object as a copy of another.}
	{prototype: VidyoGateway *VidyoGatewayConstructCopy(VidyoGateway *obj, const VidyoGateway *other)}
	{parameter: {name: obj} {description: The VidyoGateway object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoGateway *VidyoGatewayConstructCopy(VidyoGateway *obj, const VidyoGateway *other);

/**
{function:
	{name: VidyoGatewayDestruct}
	{parent: VidyoGateway}
	{description: Destruct an instance of VidyoGateway. This may block until there are no more threads running.}
	{prototype: void VidyoGatewayDestruct(VidyoGateway* gateway)}
	{parameter: {name: gateway} {description: Pointer to the VidyoGateway object to destruct.}}
}
*/
void VidyoGatewayDestruct(VidyoGateway* gateway);

/**
{function:
	{name: VidyoGatewayAssign}
	{parent: VidyoGateway}
	{description: Assigns one VidyoGateway object the value of another. }
	{prototype: VidyoGateway *VidyoGatewayAssign(VidyoGateway *obj, const VidyoGateway *other)}
	{parameter: {name: obj} {description: The VidyoGateway object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/
VidyoGateway *VidyoGatewayAssign(VidyoGateway *obj, const VidyoGateway *other);

/**
{function visibility="private":
	{name: VidyoGatewaySetUserData}
	{parent: VidyoGateway}
	{description: }
	{prototype: void VidyoGatewaySetUserData(VidyoGateway* d, LmiVoidPtr userData)}
	{parameter:
		{name: d}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoGatewaySetUserData(VidyoGateway *d, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoGatewayGetUserData}
	{parent: VidyoGateway}
	{description: }
	{prototype: LmiVoidPtr VidyoGatewayGetUserData(const VidyoGateway* d)}
	{parameter:
		{name: d}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoGatewayGetUserData(const VidyoGateway *d);

/**
 {function:
	{name: VidyoGatewayConnect}
	{parent: VidyoGateway}
	{description: Connects to a gateway to a live conference with the specified resourceId.}
	{prototype: LmiBool VidyoGatewayConnect(VidyoGateway* gateway, const char* host, const char* token, const char* displayName, const char *resourceId, VidyoGatewayOnSuccess onSuccess, VidyoGatewayOnFailure onFailure, VidyoGatewayOnDisconnected onDisconnected)}
	{parameter:
		{name: gateway}
		{description: The VidyoGateway object.}
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
		{description: An alphanumeric string. This resourceId does does not need to be pre-provisioned but in order to create a connection between multiple participants, the same resource ID has to be specified.}
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
LmiBool VidyoGatewayConnect(VidyoGateway* gateway, const char* host, const char* token, const char* displayName, const char *resourceId, VidyoGatewayOnSuccess onSuccess, VidyoGatewayOnFailure onFailure, VidyoGatewayOnDisconnected onDisconnected);

/**
 {function:
	{name: VidyoGatewayDisconnect}
	{parent: VidyoGateway}
	{description: Disconnects a live gateway call.}
	{prototype: void VidyoGatewayDisconnect(VidyoGateway* gateway)}
	{parameter:
		{name: gateway}
		{description: The VidyoGateway object.}
	}
}
*/
void VidyoGatewayDisconnect(VidyoGateway* gateway);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoGatewayInline.h"
#endif

#endif /* VIDYO_GATEWAY_H_ */

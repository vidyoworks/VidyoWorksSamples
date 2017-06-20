/** 
{file:
	{name:  VidyoNetworkInterface.h}
	{description: Vidyo Network Interface. }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_NETWORKINTERFACE_H_
#define VIDYO_NETWORKINTERFACE_H_

#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiVector.h>

LMI_BEGIN_EXTERN_C

struct VidyoNetworkInterfaceImpl_;
typedef struct VidyoNetworkInterfaceImpl_ VidyoNetworkInterfaceImpl;
Declare_LmiSharedPtr(VidyoNetworkInterfaceImpl)
Declare_LmiSharedPtrWrapper(VidyoNetworkInterface, VidyoNetworkInterfaceImpl)
Declare_LmiWeakPtrWrapper(VidyoNetworkInterfaceHandle, VidyoNetworkInterface, VidyoNetworkInterfaceImpl)
Declare_LmiVector(VidyoNetworkInterface)
Declare_LmiVectorEqual(VidyoNetworkInterface)
Declare_LmiList(VidyoNetworkInterface)

/**
{type  apigroup="connector simple" visibility="public":
	{name: VidyoNetworkInterfaceType}
	{parent: VidyoNetworkInterface}
	{description: The connection type of a network interface.}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_Wired}
		{description: A wired interface.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_WiFi}
		{description: A Wi-Fi (802.11) interface.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_Wwan}
		{description: A WWAN (cellular data) interface.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_Loopback}
		{description: A loopback interface.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_Tunneled}
		{description: A tunneled interface.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_Other}
		{description: Some other type of interface, not one of the above.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETYPE_NotApplicable}
		{description: Network interface type is not applicable in this context.}}
}
*/
typedef enum {
	VIDYO_NETWORKINTERFACETYPE_Other = 0,
	VIDYO_NETWORKINTERFACETYPE_Wired,
	VIDYO_NETWORKINTERFACETYPE_WiFi,
	VIDYO_NETWORKINTERFACETYPE_Wwan,
	VIDYO_NETWORKINTERFACETYPE_Loopback,
	VIDYO_NETWORKINTERFACETYPE_Tunneled,
	VIDYO_NETWORKINTERFACETYPE_NotApplicable,
} VidyoNetworkInterfaceType;

/**
{type  apigroup="connector simple" visibility="public":
	{name: VidyoNetworkInterfaceState}
	{parent: VidyoNetworkInterface}
	{description: The state of a network interface.}
	{value:
		{name: VIDYO_NETWORKINTERFACESTATE_Unknown}
		{description: The interface state is unknown.}}
	{value:
		{name: VIDYO_NETWORKINTERFACESTATE_Up}
		{description: The interface is up.}}
	{value:
		{name: VIDYO_NETWORKINTERFACESTATE_Down}
		{description: The interface is down.}}
}
*/
typedef enum {
	VIDYO_NETWORKINTERFACESTATE_Unknown = 0,
	VIDYO_NETWORKINTERFACESTATE_Up,
	VIDYO_NETWORKINTERFACESTATE_Down
} VidyoNetworkInterfaceState;

/**
{type  apigroup="connector simple" visibility="public":
	{name: VidyoNetworkInterfaceFamily}
	{parent: VidyoNetworkInterface}
	{description: The family of a network interface.}
	{value:
		{name: VIDYO_NETWORKINTERFACEFAMILY_Unspecified}
		{description: The interface state is unknown.}}
	{value:
		{name: VIDYO_NETWORKINTERFACEFAMILY_IPV4}
		{description: The interface IPV4.}}
	{value:
		{name: VIDYO_NETWORKINTERFACEFAMILY_IPV6}
		{description: The interface is IPV6.}}
}
*/
typedef enum {
	VIDYO_NETWORKINTERFACEFAMILY_Unspecified = 0,
	VIDYO_NETWORKINTERFACEFAMILY_IPV4,
	VIDYO_NETWORKINTERFACEFAMILY_IPV6
} VidyoNetworkInterfaceFamily;

/**
{type  apigroup="connector simple" visibility="public":
	{name: VidyoNetworkInterfaceTransportType}
	{parent: VidyoNetworkInterface}
	{description: The trasport type used over the network interface.}
	{value:
		{name: VIDYO_NETWORKINTERFACETRANSPORTTYPE_Signaling}
		{description: The interface is used for signaling.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETRANSPORTTYPE_Media}
		{description: The interface is used fro Media.}}
	{value:
		{name: VIDYO_NETWORKINTERFACETRANSPORTTYPE_Data}
		{description: The interface is used fro Data.}}
}
*/
typedef enum {
	VIDYO_NETWORKINTERFACETRANSPORTTYPE_Signaling = 0,
	VIDYO_NETWORKINTERFACETRANSPORTTYPE_Media,
	VIDYO_NETWORKINTERFACETRANSPORTTYPE_Data
} VidyoNetworkInterfaceTransportType;

/**
{type apigroup="connector simple" reference-counted="yes":
	{name: VidyoNetworkInterface}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoNetworkInterface.h}
	{description: Stores network interface information.}
	{member:
		{name: name}
		{type: LmiString}
		{description: The name of the interface.}
	}
	{member:
		{name: type}
		{type: VidyoNetworkInterfaceType}
		{description: The type of the interface.}
	}
	{member:
		{name: address}
		{type: LmiString}
		{description: The address of the interface.}
	}
	{member:
		{name: state}
		{type: VidyoNetworkInterfaceState}
		{description: The state of the interface.}
	}
	{member:
		{name: family}
		{type: VidyoNetworkInterfaceFamily}
		{description: The family of the interface.}
	}
}
*/

/**
{function:
	{name: VidyoNetworkInterfaceConstructCopy}
	{parent: VidyoNetworkInterface}
	{description: Constructs an VidyoNetworkInterface object as a copy of an existing object.}
	{prototype: VidyoNetworkInterface *VidyoNetworkInterfaceConstructCopy(VidyoNetworkInterface *d, const VidyoNetworkInterface *s)}
	{parameter: {name: d} {description: The VidyoNetworkInterface object to construct.}}
	{parameter: {name: s} {description: The existing VidyoNetworkInterface object to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function:
	{name: VidyoNetworkInterfaceDestruct}
	{parent: VidyoNetworkInterface}
	{description: Destructs an VidyoNetworkInterface object.}
	{prototype: void VidyoNetworkInterfaceDestruct(VidyoNetworkInterface *n)}
	{parameter: {name: n} {description: The VidyoNetworkInterface object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceAssign}
	{parent: VidyoNetworkInterface}
	{description: Assign the contents of one VidyoNetworkInterface to another.}
	{prototype: VidyoNetworkInterface *VidyoNetworkInterfaceAssign(VidyoNetworkInterface *d, const VidyoNetworkInterface *s)}
	{parameter: {name: d} {description: The object to assign to.}}
	{parameter: {name: s} {description: The object to copy.}}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceEqual}
	{parent: VidyoNetworkInterface}
	{description: Check the equality of VidyoNetworkInterface object.}
	{prototype: LmiBool VidyoNetworkInterfaceEqual(const VidyoNetworkInterface *a, const VidyoNetworkInterface *b)}
	{parameter: {name: a} {description: The VidyoNetworkInterface object to compare.}}
	{parameter: {name: b} {description: The VidyoNetworkInterface object to compare.}}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceGetUserData}
	{parent: VidyoNetworkInterface}
	{description: Gets the user data pointer of the network interface.}
	{prototype: LmiVoidPtr VidyoNetworkInterfaceGetUserData(const VidyoNetworkInterface* n)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{return: Name of the network interface. }
}
*/
LmiVoidPtr VidyoNetworkInterfaceGetUserData(const VidyoNetworkInterface* n);

/**
{function visibility="private":
	{name: VidyoNetworkInterfaceSetUserData}
	{parent: VidyoNetworkInterface}
	{description: Sets the user data pointer of the network interface.}
	{prototype: void VidyoNetworkInterfaceSetUserData(VidyoNetworkInterface* n, LmiVoidPtr userData)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoNetworkInterfaceSetUserData(VidyoNetworkInterface* n, LmiVoidPtr userData);

/**
{function apigroup="connector simple":
	{name: VidyoNetworkInterfaceGetName}
	{parent: VidyoNetworkInterface}
	{description: Gets the name of the network interface.}
	{prototype: const LmiString* VidyoNetworkInterfaceGetName(const VidyoNetworkInterface* n)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{return: Name of the network interface. }
}
*/
const LmiString* VidyoNetworkInterfaceGetName(const VidyoNetworkInterface* n);

/**
{function apigroup="connector simple":
	{name: VidyoNetworkInterfaceGetType}
	{parent: VidyoNetworkInterface}
	{description: Gets the type of the network interface.}
	{prototype: VidyoNetworkInterfaceType VidyoNetworkInterfaceGetType(const VidyoNetworkInterface* n)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{return: Type of the network interface. }
}
*/
VidyoNetworkInterfaceType VidyoNetworkInterfaceGetType(const VidyoNetworkInterface* n);

/**
{function apigroup="connector simple":
	{name: VidyoNetworkInterfaceGetAddress}
	{parent: VidyoNetworkInterface}
	{description: Gets the address of the network interface.}
	{prototype: const LmiString* VidyoNetworkInterfaceGetAddress(const VidyoNetworkInterface* n)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{return: Address of the network interface. }
}
*/
const LmiString* VidyoNetworkInterfaceGetAddress(const VidyoNetworkInterface* n);

/**
{function apigroup="connector simple":
	{name: VidyoNetworkInterfaceGetState}
	{parent: VidyoNetworkInterface}
	{description: Gets the state of the network interface.}
	{prototype: VidyoNetworkInterfaceState VidyoNetworkInterfaceGetState(const VidyoNetworkInterface* n)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{return: State of the network interface. }
}
*/
VidyoNetworkInterfaceState VidyoNetworkInterfaceGetState(const VidyoNetworkInterface* n);

/**
{function apigroup="connector simple":
	{name: VidyoNetworkInterfaceGetFamily}
	{parent: VidyoNetworkInterface}
	{description: Gets the family of the network interface.}
	{prototype: VidyoNetworkInterfaceFamily VidyoNetworkInterfaceGetFamily(const VidyoNetworkInterface* n)}
	{parameter:
		{name: n}
		{description: The VidyoNetworkInterface object.}
	}
	{return: Family of the network interface. }
}
*/
VidyoNetworkInterfaceFamily VidyoNetworkInterfaceGetFamily(const VidyoNetworkInterface* n);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoNetworkInterfaceInline.h"
#endif

#endif /* VIDYO_NETWORKINTERFACE_H_ */

/**
{file:
	{name: VidyoTransport.h}
	{description: High level client library. }
	{copyright:
		(c) 2013-2015 Vidyo, Inc.,
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
#ifndef VIDYO_TRANSPORT_H
#define VIDYO_TRANSPORT_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUri.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Os/LmiTimerLoop.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Os/LmiProperties.h>
#include "VidyoForwardDecl.h"

LMI_BEGIN_EXTERN_C

struct VidyoTransportImpl_;
typedef struct VidyoTransportImpl_ VidyoTransportImpl;
Declare_LmiSharedPtr(VidyoTransportImpl)
Declare_LmiSharedPtrWrapper(VidyoTransport, VidyoTransportImpl)

/**
{type visibility="private":
	{name: VidyoTlsConfig}
	{parent: VidyoTransport}
	{description: }
}
*/
typedef struct
{
	LmiAllocator *alloc;
	LmiBool caValidation;
	LmiBool peerNameValidation;
	
	LmiString cert1; /* Public certificate file if OpenSSL, certificate store if SChannel (Windows). */
	LmiString cert2; /* Private certificate file if OpenSSL, certificate subject if SChannel (Windows). */
	LmiString certpw;/* Ignored for SChannel */
	LmiString cafile;/* Ignored for SChannel */
	LmiString cadir; /* Ignored for SChannel */
	LmiString caString;
	LmiVoidPtr userData;
} VidyoTlsConfig;

struct VidyoTransportWebProxy_;

typedef struct VidyoTransportWebProxy_ VidyoTransportWebProxy;

/**
{function visibility="private":
	{name: VidyoTlsConfigConstruct}
	{parent: VidyoTlsConfig}
	{description: }
	{prototype: VidyoTlsConfig* VidyoTlsConfigConstruct(VidyoTlsConfig* c, const char* cert1, const char* cert2, const char* certPassword, const char* ca, const char* caFilePath, const char* caDir, const char* caString, LmiAllocator* alloc)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: cert1}
		{description: }
	}
	{parameter:
		{name: cert2}
		{description: }
	}
	{parameter:
		{name: certPassword}
		{description: }
	}
	{parameter:
		{name: ca}
		{description: }
	}
	{parameter:
		{name: caFilePath}
		{description: }
	}
	{parameter:
		{name: caDir}
		{description: }
	}
	{parameter:
		{name: caString}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoTlsConfig* VidyoTlsConfigConstruct(VidyoTlsConfig* c, const char* cert1, const char* cert2, const char* certPassword, const char* ca, const char* caFilePath, const char* caDir, const char* caString, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoTlsConfigConstructCopy}
	{parent: VidyoTlsConfig}
	{description: }
	{prototype: VidyoTlsConfig* VidyoTlsConfigConstructCopy(VidyoTlsConfig* a, const VidyoTlsConfig* b)}
	{parameter:
		{name: a}
		{description: }
	}
	{parameter:
		{name: b}
		{description: }
	}
	{return: }
}
*/
VidyoTlsConfig *VidyoTlsConfigConstructCopy(VidyoTlsConfig *a, const VidyoTlsConfig *b);

/**
{function visibility="private":
	{name: VidyoTlsConfigConstructDefault}
	{parent: VidyoTlsConfig}
	{description: }
	{prototype: VidyoTlsConfig* VidyoTlsConfigConstructDefault(VidyoTlsConfig* c, LmiAllocator* alloc)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoTlsConfig* VidyoTlsConfigConstructDefault(VidyoTlsConfig* c, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoTlsConfigDestruct}
	{parent: VidyoTlsConfig}
	{description: }
	{prototype: void VidyoTlsConfigDestruct(VidyoTlsConfig* c)}
	{parameter:
		{name: c}
		{description: }
	}
}
*/
void VidyoTlsConfigDestruct(VidyoTlsConfig* c);
/**
{function visibility="private":
	{name: VidyoTlsConfigSetUserData}
	{parent: VidyoTlsConfig}
	{description: }
	{prototype: void VidyoTlsConfigSetUserData(VidyoTlsConfig* c, LmiVoidPtr userData)}
	{parameter:
		{name: c}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoTlsConfigSetUserData(VidyoTlsConfig* c, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoTlsConfigGetUserData}
	{parent: VidyoTlsConfig}
	{description: }
	{prototype: LmiVoidPtr VidyoTlsConfigGetUserData(const VidyoTlsConfig* c)}
	{parameter:
		{name: c}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoTlsConfigGetUserData(const VidyoTlsConfig* c);


void VidyoTlsConfigSetCAValidation(VidyoTlsConfig* c, LmiBool validation);
LmiBool VidyoTlsConfigGetCAValidation(const VidyoTlsConfig* c);
void VidyoTlsConfigSetPeerNameValidation(VidyoTlsConfig* c, LmiBool validation);
LmiBool VidyoTlsConfigGetPeerNameValidation(const VidyoTlsConfig* c);

void VidyoTlsConfigSetCa(VidyoTlsConfig* c, const char* ca);
void VidyoTlsConfigSetCaFilePath(VidyoTlsConfig* c, const char* caFilePath);
void VidyoTlsConfigSetCaDir(VidyoTlsConfig* c, const char* caDir);
const LmiString *VidyoTlsConfigGetCert1(const VidyoTlsConfig* c);
const char *VidyoTlsConfigGetCert1CStr(const VidyoTlsConfig* c);
const LmiString *VidyoTlsConfigGetCert2(const VidyoTlsConfig* c);
const char *VidyoTlsConfigGetCert2CStr(const VidyoTlsConfig* c);
const LmiString *VidyoTlsConfigGetCertPw(const VidyoTlsConfig* c);
const char *VidyoTlsConfigGetCertPwCStr(const VidyoTlsConfig* c);
const LmiString *VidyoTlsConfigGetCaFile(const VidyoTlsConfig* c);
const char *VidyoTlsConfigGetCaFileCStr(const VidyoTlsConfig* c);
const LmiString *VidyoTlsConfigGetCaDir(const VidyoTlsConfig* c);
const char *VidyoTlsConfigGetCaDirCStr(const VidyoTlsConfig* c);
const LmiString *VidyoTlsConfigGetCaString(const VidyoTlsConfig* c);

/**
{callback visibility="private":
	{name: VidyoTransportTlsTransportCallback}
	{parent: VidyoTransport}
	{description: }
	{prototype: LmiBool (*VidyoTransportTlsTransportCallback)(VidyoTransport* t, VidyoLmiTransportAddress* address, const VidyoTlsConfig* tlsConfig, const LmiString* domain, LmiBool startSecure, void* userData)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: address}
		{description: }
	}
	{parameter:
		{name: tlsConfig}
		{description: }
	}
	{parameter:
		{name: domain}
		{description: }
	}
	{parameter:
		{name: startSecure}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
	{return: }
}
*/
typedef LmiBool (*VidyoTransportTlsTransportCallback)(VidyoTransport* t, VidyoLmiTransportAddress* address, const VidyoTlsConfig* tlsConfig, const LmiString* domain, LmiBool startSecure, void* userData);


/**
{type visibility="private":
	{name: VidyoTransport}
	{parent: VidyoClient}
	{include: Lmi/VidyoClient/VidyoTransport.h}
	{description: }
}
*/

/**
{function visibility="private":
	{name: VidyoTransportInitialize}
	{parent: VidyoTransport}
	{description: }
	{prototype: LmiBool VidyoTransportInitialize(void)}
	{return: }
}
*/
LmiBool VidyoTransportInitialize(void);

/**
{function visibility="private":
	{name: VidyoTransportUninitialize}
	{parent: VidyoTransport}
	{description: }
	{prototype: void VidyoTransportUninitialize(void)}
}
*/
void VidyoTransportUninitialize(void);

/**
{function visibility="private":
	{name: VidyoTransportConstruct}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoTransport* VidyoTransportConstruct(VidyoTransport* t, LmiUint socketThreads, LmiUint timerThreads, LmiAllocator* alloc)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: socketThreads}
		{description: }
	}
	{parameter:
		{name: timerThreads}
		{description: }
	}
	{parameter:
		{name: alloc}
		{description: }
	}
	{return: }
}
*/
VidyoTransport* VidyoTransportConstruct(VidyoTransport* t, LmiUint socketThreads, LmiUint timerThreads, LmiAllocator* alloc);

/**
{function visibility="private":
	{name: VidyoTransportConstructCopy}
	{parent: VidyoTransport}
	{description: Constructs an VidyoTransport object as a copy of another.}
	{prototype: VidyoTransport *VidyoTransportConstructCopy(VidyoTransport *obj, const VidyoTransport *other)}
	{parameter: {name: obj} {description: The VidyoTransport object to construct.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoTransportDestruct}
	{parent: VidyoTransport}
	{description: Destructs an VidyoTransport object.}
	{prototype: void VidyoTransportDestruct(VidyoTransport *obj)}
	{parameter: {name: obj} {description: The VidyoTransport object to destruct.}}
}
*/

/**
{function visibility="private":
	{name: VidyoTransportAssign}
	{parent: VidyoTransport}
	{description: Assigns one VidyoTransport object the value of another. }
	{prototype: VidyoTransport *VidyoTransportAssign(VidyoTransport *obj, const VidyoTransport *other)}
	{parameter: {name: obj} {description: The VidyoTransport object.}}
	{parameter: {name: other} {description: The call object to make a copy of.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/

/**
{function visibility="private":
	{name: VidyoTransportSetUserData}
	{parent: VidyoTransport}
	{description: }
	{prototype: void VidyoTransportSetUserData(VidyoTransport* t, LmiVoidPtr userData)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: userData}
		{description: }
	}
}
*/
void VidyoTransportSetUserData(VidyoTransport* t, LmiVoidPtr userData);

/**
{function visibility="private":
	{name: VidyoTransportGetUserData}
	{parent: VidyoTransport}
	{description: }
	{prototype: LmiVoidPtr VidyoTransportGetUserData(const VidyoTransport* t)}
	{parameter:
		{name: t}
		{description: }
	}
	{return: }
}
*/
LmiVoidPtr VidyoTransportGetUserData(const VidyoTransport* t);



/**
{function visibility="private":
	{name: VidyoTransportGetTimerManager}
	{parent: VidyoTransport}
	{description: }
	{prototype: LmiTimerManager* VidyoTransportGetTimerManager(VidyoTransport* t)}
	{parameter:
		{name: t}
		{description: }
	}
	{return: }
}
*/
LmiTimerManager* VidyoTransportGetTimerManager(VidyoTransport* t);

LmiBool VidyoTransportStopTimerLoop(VidyoTransport* t);

VidyoLmiTransport* VidyoTransportCreateProxyTransport(VidyoTransport *t, LmiString* addr, LmiInt port, LmiBool onTls, LmiBool onTls12, VidyoLmiTransport* inTransport, LmiAllocator* alloc);

void VidyoTransportDeleteProxyTransport(VidyoLmiTransport* proxyTransport, LmiAllocator* alloc);

VidyoLmiTransport* VidyoTransportCreateWebProxyTransport(const LmiString* addr, LmiInt port, LmiString* auth, LmiBool onTls, LmiBool onTls12, VidyoLmiTransport* inTransport, LmiAllocator* alloc);

void VidyoTransportDeleteWebProxyTransport(VidyoLmiTransport* webProxyTransport, LmiAllocator* alloc);

void VidyoTransportProcessTurnServer(VidyoTransport* t, const LmiString* turnUriStr);
VidyoLmiTransport* VidyoTransportGetTurnTransport(VidyoTransport* t, const LmiString* turnServer);

VidyoLmiTransport* VidyoTransportWebProxyGetInnerTransport(const VidyoTransportWebProxy* webProxy);
VidyoLmiTransport* VidyoTransportWebProxyGetWebProxyTransport(const VidyoTransportWebProxy* webProxy);
VidyoLmiTransport* VidyoTransportWebProxyGetTlsTransport(const VidyoTransportWebProxy* webProxy);
LmiBool VidyoTransportWebProxyServerDiscovered(const VidyoTransportWebProxy* webProxy);

void VidyoTransportCreateWebSocketWebProxy(VidyoTransport* t, const LmiUri* websocketUri);
VidyoTransportWebProxy* VidyoTransportGetWebSocketWebProxy(VidyoTransport* t, const LmiUri* websocketUri);

VidyoTransportWebProxy* VidyoTransportWebProxyConstruct(VidyoTransportWebProxy* webProxy, VidyoTransport* t, const LmiUri* targetUri, LmiAllocator* alloc);
void VidyoTransportWebProxyDestruct(VidyoTransportWebProxy* webProxy);
VidyoTransportWebProxy* VidyoTransportWebProxyConstructCopy(VidyoTransportWebProxy* webProxy, const VidyoTransportWebProxy* srcWebProxy);
VidyoTransportWebProxy* VidyoTransportWebProxyAssign(VidyoTransportWebProxy* webProxy, const VidyoTransportWebProxy* srcWebProxy);

void VidyoTransportSetWebProxyAddressCredentials(VidyoTransport* t, const LmiString* proxyAddress, const LmiString* username, const LmiString* password);

/**
{function visibility="private":
	{name: VidyoTransportGetTcpTransport}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransport* VidyoTransportGetTcpTransport(VidyoTransport* t)}
	{parameter:
		{name: t}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransport* VidyoTransportGetTcpTransport(VidyoTransport* t);

/**
{function visibility="private":
	{name: VidyoTransportGetUdpTransport}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransport* VidyoTransportGetUdpTransport(VidyoTransport* t)}
	{parameter:
		{name: t}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransport* VidyoTransportGetUdpTransport(VidyoTransport* t);

/**
{function visibility="private":
	{name: VidyoTransportGetTlsTransport}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransport* VidyoTransportGetTlsTransport(VidyoTransport* t)}
	{parameter:
		{name: t}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransport* VidyoTransportGetTlsTransport(VidyoTransport* t);

/**
 {function visibility="private":
	{name: VidyoTransportGetWebsocketTransport}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransport* VidyoTransportGetWebsocketTransport(VidyoTransport* t)}
	{parameter:
 {name: t}
 {description: }
	}
	{return: }
 }
 */
VidyoLmiTransport* VidyoTransportGetWebsocketTransport(VidyoTransport* t);

/**
{function visibility="private":
	{name: VidyoTransportBuildLocalSignalingAddressFromString}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddressFromString(VidyoTransport* t, VidyoLmiTransportAddress* address, const LmiString* domain, const LmiString* hostname, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: address}
		{description: }
	}
	{parameter:
		{name: domain}
		{description: }
	}
	{parameter:
		{name: hostname}
		{description: }
	}
	{parameter:
		{name: tls}
		{description: }
	}
	{parameter:
		{name: tlsConfig}
		{description: }
	}
	{parameter:
		{name: startSecure}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddressFromString(VidyoTransport* t, VidyoLmiTransportAddress* address, const LmiString* domain, const LmiString* hostname, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure);

/**
{function visibility="private":
	{name: VidyoTransportBuildLocalSignalingAddress}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddress(VidyoTransport* t, VidyoLmiTransportAddress* address, const VidyoLmiIpAddress* ipAddress, LmiUint port, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: address}
		{description: }
	}
	{parameter:
		{name: ipAddress}
		{description: }
	}
	{parameter:
		{name: port}
		{description: }
	}
	{parameter:
		{name: tls}
		{description: }
	}
	{parameter:
		{name: tlsConfig}
		{description: }
	}
	{parameter:
		{name: startSecure}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddress(VidyoTransport* t, VidyoLmiTransportAddress* address, const VidyoLmiIpAddress* ipAddress, LmiUint port, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure);

/**
 {function visibility="private":
	{name: VidyoTransportSetWebsocketAddressLocalAddr}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransportAddress* VidyoTransportSetWebsocketAddressLocalAddr(VidyoLmiTransportAddress* address, const VidyoLmiTransportAddress* localAddr)}
	{parameter:
		{name: address}
		{description: Websocket local address}
	}
	{parameter:
		{name: localAddr}
		{description: Local transport address to set in Websocket Address Data}
	}
	{return: }
 }
 */
VidyoLmiTransportAddress* VidyoTransportSetWebsocketAddressLocalAddr(VidyoLmiTransportAddress* address, const VidyoLmiTransportAddress* localAddr);

/**
{function visibility="private":
	{name: VidyoTransportBuildLocalSignalingAddressAnyV4}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddressAnyV4(VidyoTransport* t, VidyoLmiTransportAddress* address, LmiUint port, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: address}
		{description: }
	}
	{parameter:
		{name: port}
		{description: }
	}
	{parameter:
		{name: tls}
		{description: }
	}
	{parameter:
		{name: tlsConfig}
		{description: }
	}
	{parameter:
		{name: startSecure}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddressAnyV4(VidyoTransport* t, VidyoLmiTransportAddress* address, LmiUint port, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure);

/**
{function visibility="private":
	{name: VidyoTransportBuildLocalSignalingAddressAnyV6}
	{parent: VidyoTransport}
	{description: }
	{prototype: VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddressAnyV6(VidyoTransport* t, VidyoLmiTransportAddress* address, LmiUint port, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure)}
	{parameter:
		{name: t}
		{description: }
	}
	{parameter:
		{name: address}
		{description: }
	}
	{parameter:
		{name: port}
		{description: }
	}
	{parameter:
		{name: tls}
		{description: }
	}
	{parameter:
		{name: tlsConfig}
		{description: }
	}
	{parameter:
		{name: startSecure}
		{description: }
	}
	{return: }
}
*/
VidyoLmiTransportAddress* VidyoTransportBuildLocalSignalingAddressAnyV6(VidyoTransport* t, VidyoLmiTransportAddress* address, LmiUint port, LmiBool tls, const VidyoTlsConfig* tlsConfig, LmiBool startSecure);

VidyoLmiTransportAddress *VidyoTransportBuildLocalTransportAddress(VidyoTransport* t, VidyoLmiTransportAddress* address, VidyoLmiTransport* tlsTransport, const VidyoTlsConfig *tlsConfig, LmiBool startSecure);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoTransportInline.h"
#endif

#endif

/**
{file:
	{name: LmiUriInline.h}
	{description: Object for Universal Resource Identifiers.}
	{copyright:
		(c) 2008-2015 Vidyo, Inc.,
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
LMI_INLINE LmiUri *LmiUriConstructStr(LmiUri *uri, const LmiString *str, LmiAllocator *alloc)
{
	return LmiUriConstructCStr(uri, LmiStringCStr(str), alloc);
}

LMI_INLINE const char* LmiUriGetScheme(const LmiUri *uri)
{
	return LmiStringCStr(&uri->scheme);
}

LMI_INLINE const LmiString* LmiUriGetSchemeStr(const LmiUri *uri)
{
	return &uri->scheme;
}

LMI_INLINE void LmiUriSetScheme(LmiUri *uri, const char *scheme)
{
	if(scheme != NULL)
		LmiStringAssignCStr(&uri->scheme, scheme);
	else
		LmiStringClear(&uri->scheme);
	LmiUriSerialize_(uri, &uri->serialized, LMI_FALSE);
}

LMI_INLINE LmiBool LmiUriEmpty(const LmiUri *uri)
{
	return LmiStringEmpty(&uri->scheme);
}

LMI_INLINE void LmiUriClearAuthorityParameters(LmiUri *uri)
{
	LmiVectorClear(LmiUriParam)(&uri->authParams);
	LmiUriSerialize_(uri, &uri->serialized, LMI_FALSE);
}

LMI_INLINE const char *LmiUriGetName(const LmiUri *uri)
{
	return LmiStringEmpty(&uri->name) ? NULL : LmiStringCStr(&uri->name);
}

LMI_INLINE const LmiString *LmiUriGetNameStr(const LmiUri *uri)
{
	return LmiStringEmpty(&uri->name) ? NULL : &uri->name;
}

LMI_INLINE void LmiUriSetName(LmiUri *uri, const char *name)
{
	if(name != NULL)
		LmiStringAssignCStr(&uri->name, name);
	else
		LmiStringClear(&uri->name);
	LmiUriSerialize_(uri, &uri->serialized, LMI_FALSE);
}

LMI_INLINE const char *LmiUriGetHost(const LmiUri *uri)
{
	return LmiStringCStr(&uri->host);
}

LMI_INLINE const LmiString *LmiUriGetHostStr(const LmiUri *uri)
{
	return &uri->host;
}

LMI_INLINE void LmiUriSetHost(LmiUri *uri, const char *host)
{
	LmiStringAssignCStr(&uri->host, host);
	uri->addressStringValid = LMI_FALSE;
	LmiUriSerialize_(uri, &uri->serialized, LMI_FALSE);
}

LMI_INLINE LmiUint LmiUriGetPort(const LmiUri *uri)
{
	return uri->port;
}

LMI_INLINE void LmiUriSetPort(LmiUri *uri, LmiUint port)
{
	uri->port = port;
	uri->addressStringValid = LMI_FALSE;
	LmiUriSerialize_(uri, &uri->serialized, LMI_FALSE);
}

LMI_INLINE const char *LmiUriGetAddress(const LmiUri *uri)
{
	return LmiStringCStr(LmiUriGetAddressStr(uri));
}

LMI_INLINE const char *LmiUriGetFragment(const LmiUri *uri)
{
	return LmiStringEmpty(&uri->fragment) ? NULL : LmiStringCStr(&uri->fragment);
}

LMI_INLINE const LmiString *LmiUriGetFragmentStr(const LmiUri *uri)
{
	return LmiStringEmpty(&uri->fragment) ? NULL : &uri->fragment;
}

LMI_INLINE void LmiUriSetFragment(LmiUri *uri, const char *fragment)
{
	if(fragment != NULL)
		LmiStringAssignCStr(&uri->fragment, fragment);
	else
		LmiStringClear(&uri->fragment);
	LmiUriSerialize_(uri, &uri->serialized, LMI_FALSE);
}


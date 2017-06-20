/**
{file:
	{name: LmiUri.h}
	{description: Object for Universal Resource Identifiers.}
	{copyright:
		(c) 2007-2015 Vidyo, Inc.,
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
#ifndef LMI_URI_H_
#define LMI_URI_H_

#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiStdCLib.h>

LMI_BEGIN_EXTERN_C

/* An LMI URI is of the following format

     cmcp://bala@example.com:8042/user/home?foo=bar&foo2=bar2#foo3
     \__/   \___________________/\________/ \_______________/ \__/
       |           |                 |             |            |
    scheme     authority           path          query       fragment

     cmcp:bala@example.com:8042;transport=tcp
     \__/ \___________________/ \___________/
       |           |                 |
    scheme        path           path_param

  This definition is compliant to the Generic URI 
  syntax defined in RFC3986.
*/

typedef struct
{
	LmiString name;
	LmiString value;
} LmiUriParam;

LmiUriParam *LmiUriParamConstruct(LmiUriParam *p, const char *name, const char *value, LmiAllocator *alloc);
LmiUriParam* LmiUriParamConstructCopy(LmiUriParam *d, const LmiUriParam *s);
void LmiUriParamDestruct(LmiUriParam *p);
LmiUriParam *LmiUriParamAssign(LmiUriParam *d, const LmiUriParam *s);
LmiBool LmiUriParamEqual(const LmiUriParam *a, const LmiUriParam *b);
LmiBool LmiUriParamLess(const LmiUriParam *a, const LmiUriParam *b);

Declare_LmiVector(LmiUriParam)
Declare_LmiVectorEqual(LmiUriParam)

typedef struct
{
	LmiAllocator* alloc;
	LmiString name;
	LmiVector(LmiUriParam) params;
} LmiUriPath;

LmiUriPath *LmiUriPathConstruct(LmiUriPath *p, const char *str, LmiAllocator *alloc);
LmiUriPath* LmiUriPathConstructCopy(LmiUriPath *d, const LmiUriPath *s);
void LmiUriPathDestruct(LmiUriPath *p);
LmiUriPath *LmiUriPathAssign(LmiUriPath *d, const LmiUriPath *s);
LmiBool LmiUriPathEqual(const LmiUriPath *a, const LmiUriPath *b);
LmiBool LmiUriPathLess(const LmiUriPath *a, const LmiUriPath *b);

Declare_LmiVector(LmiUriPath)
Declare_LmiVectorEqual(LmiUriPath)

const char *LmiUriPathGetParameter(const LmiUriPath *p, const char *name);
const LmiString *LmiUriPathGetParameterStr(const LmiUriPath *p, const char *name);
LmiBool LmiUriPathAddParameter(LmiUriPath *p, const char *name, const char *value);

/**
{type:
	{name: LmiUri}
	{parent: Utils}
	{include: Lmi/Utils/LmiUri.h}
	{description: Universal Resource Identifiers.}
}
*/

typedef struct {
	LmiString scheme;
	LmiString name;
	LmiString host;
	LmiUint port;
	LmiString address;
	LmiBool addressStringValid;
	LmiVector(LmiUriPath) paths;
	LmiVector(LmiUriParam) authParams;
	LmiVector(LmiUriParam) querys;
	LmiString fragment;
	LmiString serialized;
	LmiAllocator* alloc;
} LmiUri;



/**
{function:
	{name: LmiUriConstructDefault}
	{parent: LmiUri}
	{description: Constructs a default LmiUri object.}
	{prototype: LmiUri *LmiUriConstructDefault(LmiUri *uri, LmiAllocator *alloc)}
	{parameter:
		{name: uri}
		{description: The URI object to construct.}
	}
	{parameter:
		{name: alloc}
		{description: An allocator to be used for memory}
	}
	{return: A pointer to an URI on success or NULL on failure}
}
*/
LmiUri* LmiUriConstructDefault(LmiUri *uri, LmiAllocator *alloc);

/**
{function:
	{name: LmiUriConstruct}
	{parent: LmiUri}
	{description: Constructs a URI object.}
	{prototype: LmiUri* LmiUriConstruct(LmiUri* uri, const char* scheme, const char* name, const char* host, LmiUint port, const char *authParams, const char *path, const char *query, const char *fragment, LmiAllocator* alloc)}
	{parameter: 
		{name: uri}
		{description: The URI object to construct.}
	}
	{parameter: 
		{name: scheme}
		{description: URI Scheme.}
	}
	{parameter: 
		{name: name}
		{description: An optional NULL terminated C string containing the name field of authority.
		Set this parameter to NULL if no name is desired.}
	}
	{parameter: 
		{name: host}
		{description: A NULL terminated C string containing the host name. Acceptable formats 
			for this string are "IpV4Address", "[IpAddress]" and "DnsName".}
	}
	{parameter: 
		{name: port}
		{description: An optional port number. Set this parameter to 0 to leave the port unspecified.}
	}
	{parameter: 
		{name: authParams}
		{description: A NULL terminated C string containing the auth params part of the URI. Between the // and /.}
	}
	{parameter: 
		{name: path}
		{description: A NULL terminated C string containing the path part of the URI. From end of auth params to the ?. }
	}
	{parameter: 
		{name: query}
		{description: A NULL terminated C string containing the path part of the URI. From end of path to the #.}
	}
	{parameter: 
		{name: fragment}
		{description: A NULL terminated C string containing the path part of the URI. From end of query to end of string.}
	}
	{parameter:
		{name: alloc}
		{description: An allocator to be used for memory.}
	}
	{return: A pointer to an URI on success, NULL on failure including parse error}
}
*/
LmiUri *LmiUriConstruct(LmiUri *uri, const char* scheme, const char *name, const char *host, LmiUint port, const char *authParams, const char *path, const char *query, const char *fragment, LmiAllocator *alloc);

/**
{function:
	{name: LmiUriConstructCStr}
	{parent: LmiUri}
	{description: Constructs a URI object from a NULL-terminated C string representation of that URI.}
	{prototype: LmiUri* LmiUriConstructCStr(LmiUri* uri, const char* str, LmiAllocator* alloc)}
	{parameter:
		{name: uri}
		{description: The URI object to construct.}
	}
	{parameter:
		{name: str}
		{description: A NULL-terminated string representation of an URI}
	}
	{parameter:
		{name: alloc}
		{description: An allocator to be used for memory}
	}
	{return: A pointer to an URI on success or NULL on failure including parse error}
}
*/
LmiUri* LmiUriConstructCStr(LmiUri* uri, const char* str, LmiAllocator* alloc);

/**
{function:
	{name: LmiUriConstructStr}
	{parent: LmiUri}
	{description: Constructs a URI object based on a LMI string representation of that URI.}
	{prototype: LmiUri* LmiUriConstructStr(LmiUri* uri, const LmiString* str, LmiAllocator* alloc)}
	{parameter:
		{name: uri}
		{description: The URI object to construct.}
	}
	{parameter:
		{name: str}
		{description: An LmiString object containing the URI.}
	}
	{parameter:
		{name: alloc}
		{description: An allocator to be used for memory.}
	}
	{return: A pointer to an URI on success, NULL on failure including parse error.}
}
*/
LMI_INLINE_DECLARATION LmiUri* LmiUriConstructStr(LmiUri* uri, const LmiString* str, LmiAllocator* alloc);

/**
{function:
	{name: LmiUriConstructCopy}
	{parent: LmiUri}
	{description: Constructs a URI object as a copy of an existing URI object.}
	{prototype: LmiUri* LmiUriConstructCopy(LmiUri* uri, const LmiUri* other)}
	{parameter:
		{name: uri}
		{description: The URI object to construct.}
	}
	{parameter:
		{name: other}
		{description: The existing URI to be copied.}
	}
	{return: A pointer to a URI on success or NULL on failure.}
}
*/
LmiUri* LmiUriConstructCopy(LmiUri* uri, const LmiUri* other);

/**
{function:
	{name: LmiUriDestruct}
	{parent: LmiUri}
	{description: Destructs a URI object}
	{prototype: void LmiUriDestruct(LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI to be destructed.}
	}
}
*/
void LmiUriDestruct(LmiUri* uri);

/**
{function:
	{name: LmiUriAssign}
	{parent: LmiUri}
	{description: Assigns the value of one URI object to another}
	{prototype: LmiUri* LmiUriAssign(LmiUri* uri, const LmiUri* other)}
	{parameter:
		{name: uri}
		{description: The URI object to assign to.}
	}
	{parameter:
		{name: other}
		{description: The existing URI to be copied.}
	}
	{return: A pointer to a URI on success, or NULL on failure}
}
*/
LmiUri* LmiUriAssign(LmiUri* uri, const LmiUri* other);

/**
{function:
	{name: LmiUriEqual}
	{parent: LmiUri}
	{description: Compares two URI objects for equality }
	{prototype: LmiBool LmiUriEqual(const LmiUri* a, const LmiUri* b)}
	{parameter:
		{name: a}
		{description: A pointer to the first URI to be compared}
	}
	{parameter:
		{name: b}
		{description: A pointer to the second URI to be compared}
	}
	{return: LMI_TRUE if the URIs are equal, otherwise LMI_FALSE.}
}
*/
LmiBool LmiUriEqual(const LmiUri* a, const LmiUri* b);

LmiBool LmiUriLess(const LmiUri *a, const LmiUri *b);
LmiSizeT LmiUriHash(const LmiUri *uri);
LmiBool LmiUriSerialize_(const LmiUri *uri, LmiString *s, LmiBool encode);

/**
{function:
	{name: LmiUriGetScheme}
	{parent: LmiUri}
	{description: Gets the scheme of a URI.}
	{prototype: const char* LmiUriGetScheme(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: The URI Scheme}
}
*/
LMI_INLINE_DECLARATION const char* LmiUriGetScheme(const LmiUri* uri);

/**
{function:
	{name: LmiUriGetSchemeStr}
	{parent: LmiUri}
	{description: Gets the scheme of a URI as an LmiString.}
	{prototype: const LmiString* LmiUriGetSchemeStr(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: The URI Scheme}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiUriGetSchemeStr(const LmiUri* uri);

/**
{function:
	{name: LmiUriSetScheme}
	{parent: LmiUri}
	{description: Sets the scheme field in a URI object.}
	{prototype: void LmiUriSetScheme(LmiUri *uri, const char *scheme)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: scheme} {description: The new scheme field.}}
}
*/
LMI_INLINE_DECLARATION void LmiUriSetScheme(LmiUri *uri, const char *scheme);

LMI_INLINE_DECLARATION LmiBool LmiUriEmpty(const LmiUri *uri);

/**
{function:
	{name: LmiUriGetAuthority}
	{parent: LmiUri}
	{description: Gets the authority of a URI in a buffer.}
	{prototype: LmiSizeT LmiUriGetAuthority(const LmiUri* uri, char *buf, LmiSizeT buflen)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{parameter:
		{name: buf}
		{description: The buffer to encode the URI into.}
	}
	{parameter:
		{name: buflen}
		{description: The length of the buffer. No more than buflen bytes will be
			written to buf, including the final NUL. The resulting string will
			always be NUL-terminated unless buflen == 0}
	}
	{return: The number of characters that would be printed if buflen were
		unlimited (not counting the final NUL.) If this is greater than
		or equal to buflen, the formatted string was truncated.}
}
*/
LmiSizeT LmiUriGetAuthority(const LmiUri* uri, char *buf, LmiSizeT buflen);

/**
{function:
	{name: LmiUriGetAuthorityStr}
	{parent: LmiUri}
	{description: Gets the authority of a URI as an LmiString.}
	{prototype: LmiString* LmiUriGetAuthorityStr(const LmiUri* uri, LmiString* str)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{parameter: 
		{name: str}
		{description: The LmiString object.}
	}
	{return: The URI Authority as an LmiString on success; NULL on failure.}
}
*/
LmiString* LmiUriGetAuthorityStr(const LmiUri* uri, LmiString* str);

/**
{function:
	{name: LmiUriGetAuthorityParameter}
	{parent: LmiUri}
	{description: Gets an authority parameter from a URI by name.}
	{prototype: const char *LmiUriGetAuthorityParameter(const LmiUri *uri, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: The value of the parameter, or NULL if this parameter is not contained in the given URI.}
}
*/
const char *LmiUriGetAuthorityParameter(const LmiUri *uri, const char *name);

/**
{function:
	{name: LmiUriGetAuthorityParameterStr}
	{parent: LmiUri}
	{description: Gets an authority parameter from a URI by name.}
	{prototype: const LmiString *LmiUriGetAuthorityParameterStr(const LmiUri *uri, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: The value of the parameter, or NULL if this parameter is not contained in the given URI.}
}
*/
const LmiString *LmiUriGetAuthorityParameterStr(const LmiUri *uri, const char *name);

/**
{function:
	{name: LmiUriAddAuthorityParameter}
	{parent: LmiUri}
	{description: Gets an authority parameter from a URI by name.}
	{prototype: LmiBool LmiUriAddAuthorityParameter(LmiUri *uri, const char *name, const char *value)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{parameter: {name: value} {description: The optional value of the parameter.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiUriAddAuthorityParameter(LmiUri *uri, const char *name, const char *value);

/**
{function:
	{name: LmiUriClearAuthorityParameters}
	{parent: LmiUri}
	{description: Removes all parameters from a URI.}
	{prototype: void LmiUriClearAuthorityParameters(LmiUri *uri)}
	{parameter: {name: uri} {description: The URI object.}}
}
*/
LMI_INLINE_DECLARATION void LmiUriClearAuthorityParameters(LmiUri *uri);

/**
{function:
	{name: LmiUriGetName}
	{parent: LmiUri}
	{description: Gets the name field from a URI object.}
	{prototype: const char* LmiUriGetName(const LmiUri* uri)}
	{parameter:
	{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to a NULL-terminated C String with the name
		on success, or NULL on failure}
}
*/
LMI_INLINE_DECLARATION const char* LmiUriGetName(const LmiUri* uri);

/**
{function:
	{name: LmiUriGetNameStr}
	{parent: LmiUri}
	{description: Gets the name field from a URI object as an LmiString.}
	{prototype: const LmiString* LmiUriGetNameStr(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to the LmiString object with the name on
		success, or NULL on failure}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiUriGetNameStr(const LmiUri* uri);

/**
{function:
	{name: LmiUriSetName}
	{parent: LmiUri}
	{description: Sets the name field in a URI object.}
	{prototype: void LmiUriSetName(LmiUri *uri, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The new name field.}}
}
*/
LMI_INLINE_DECLARATION void LmiUriSetName(LmiUri *uri, const char *name);

/**
{function:
	{name: LmiUriGetHost}
	{parent: LmiUri}
	{description: Gets the host name from a URI.}
	{prototype: const char* LmiUriGetHost(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to a NULL-terminated C String with the host name
		on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION const char* LmiUriGetHost(const LmiUri* uri);

/**
{function:
	{name: LmiUriGetHostStr}
	{parent: LmiUri}
	{description: Gets the host name from a URI as an LmiString.}
	{prototype: const LmiString* LmiUriGetHostStr(const LmiUri* uri)}
	{parameter: 
		{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to the LmiString object with the host name on 
		success, or NULL on failure}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiUriGetHostStr(const LmiUri* uri);

/**
{function:
	{name: LmiUriSetHost}
	{parent: LmiUri}
	{description: Sets the host name in a URI.}
	{prototype: void LmiUriSetHost(LmiUri *uri, const char *host)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: host} {description: The new host name.}}
}
*/
LMI_INLINE_DECLARATION void LmiUriSetHost(LmiUri *uri, const char *host);

/**
{function:
	{name: LmiUriGetPort}
	{parent: LmiUri}
	{description: Gets the port number from a URI.}
	{prototype: LmiUint LmiUriGetPort(const LmiUri* uri)}
	{parameter: 
		{name: uri}
		{description: The URI object.}
	}
	{return: The port number. If the URI does not contain a port number, 0 is returned.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiUriGetPort(const LmiUri* uri);

/**
{function:
	{name: LmiUriSetPort}
	{parent: LmiUri}
	{description: Sets the port number in a URI.}
	{prototype: void LmiUriSetPort(LmiUri *uri, LmiUint port)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: port} {description: The new port number.}}
}
*/
LMI_INLINE_DECLARATION void LmiUriSetPort(LmiUri *uri, LmiUint port);

/**
{function:
	{name: LmiUriGetAddress}
	{parent: LmiUri}
	{description: Gets the address portion of a URI.}
	{prototype: const char* LmiUriGetAddress(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: A Pointer to a NULL-terminated C String with the address string
		on success, or NULL on failure}
}
*/
LMI_INLINE_DECLARATION const char* LmiUriGetAddress(const LmiUri* uri);

/**
{function:
	{name: LmiUriGetAddressStr}
	{parent: LmiUri}
	{description: Gets the address portion of a URI as an LmiString.}
	{prototype: const LmiString* LmiUriGetAddressStr(const LmiUri* uri)}
	{parameter: 
		{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to an LmiString object with the address on 
		success, or NULL on failure}
}
*/
const LmiString* LmiUriGetAddressStr(const LmiUri* uri);

/**
{function:
	{name: LmiUriGetPathCount}
	{parent: LmiUri}
	{description: Gets the number of paths in a URI.}
	{prototype: LmiSizeT LmiUriGetPathCount(const LmiUri *uri)}
	{parameter: {name: uri} {description: The URI object.}}
	{return: Number of paths in the Uri.}
}
*/
LmiSizeT LmiUriGetPathCount(const LmiUri *uri);

/**
{function:
	{name: LmiUriGetPathName}
	{parent: LmiUri}
	{description: Gets the name of a path in a URI by index.}
	{prototype: const char* LmiUriGetPathName(const LmiUri* uri, LmiSizeT index)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The index.}}
	{return: A Pointer to a NULL-terminated C String with the name string
		on success, or NULL on failure}
}
*/
const char* LmiUriGetPathName(const LmiUri *uri, LmiSizeT index);

/**
{function:
	{name: LmiUriGetPathNameStr}
	{parent: LmiUri}
	{description: Gets the name of a path in a URI by index.}
	{prototype: const LmiString *LmiUriGetPathNameStr(const LmiUri* uri, LmiSizeT index)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The index.}}
	{return: A name string on success, or NULL on failure}
}
*/
const LmiString *LmiUriGetPathNameStr(const LmiUri *uri, LmiSizeT index);

/**
{function:
	{name: LmiUriAddPath}
	{parent: LmiUri}
	{description: Adds a path to a URI.}
	{prototype: LmiSizeT LmiUriAddPath(LmiUri *uri, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: Index of the path just added which can be used to add path parameters.}
}
*/
LmiSizeT LmiUriAddPath(LmiUri *uri, const char *name);

/**
{function:
	{name: LmiUriGetPathParameter}
	{parent: LmiUri}
	{description: Gets a parameter of a path with the position index and a name from a URI.}
	{prototype: const char *LmiUriGetPathParameter(const LmiUri *uri, LmiSizeT index, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The position index.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: The value of the path parameter, or NULL if this path parameter is not contained in the given index of the URI.}
}
*/
const char* LmiUriGetPathParameter(const LmiUri *uri, LmiSizeT index, const char *name);

/**
{function:
	{name: LmiUriGetPathParameterStr}
	{parent: LmiUri}
	{description: Gets a parameter of a path with the position index and a name from a URI.}
	{prototype: const LmiString *LmiUriGetPathParameterStr(const LmiUri *uri, LmiSizeT index, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The position index.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: The value of the path parameter, or NULL if this path parameter is not contained in the given index of the URI.}
}
*/
const LmiString *LmiUriGetPathParameterStr(const LmiUri *uri, LmiSizeT index, const char *name);

/**
{function:
	{name: LmiUriAddPathParameter}
	{parent: LmiUri}
	{description: Adds a parameter into a given path index of a URI.}
	{prototype: LmiBool LmiUriAddPathParameter(LmiUri *uri, LmiSizeT index, const char *name, const char *value)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The position index.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{parameter: {name: value} {description: The value of the parameter.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiUriAddPathParameter(LmiUri *uri, LmiSizeT index, const char *name, const char *value);

/**
{function:
	{name: LmiUriGetQueryCount}
	{parent: LmiUri}
	{description: Gets the number of queries in a URI.}
	{prototype: LmiSizeT LmiUriGetQueryCount(const LmiUri *uri)}
	{parameter: {name: uri} {description: The URI object.}}
	{return: Number of queries in the Uri.}
}
*/
LmiSizeT LmiUriGetQueryCount(const LmiUri *uri);

/**
{function:
	{name: LmiUriGetQueryName}
	{parent: LmiUri}
	{description: Gets the name of a query in a URI by index.}
	{prototype: const char* LmiUriGetQueryName(const LmiUri* uri, LmiSizeT index)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The index.}}
	{return: A Pointer to a NULL-terminated C String with the name string
		on success, or NULL on failure}
}
*/
const char *LmiUriGetQueryName(const LmiUri *uri, LmiSizeT index);

/**
{function:
	{name: LmiUriGetQueryNameStr}
	{parent: LmiUri}
	{description: Gets the name of a query in a URI by index.}
	{prototype: const LmiString *LmiUriGetQueryNameStr(const LmiUri* uri, LmiSizeT index)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The index.}}
	{return: A name string on success, or NULL on failure}
}
*/
const LmiString *LmiUriGetQueryNameStr(const LmiUri *uri, LmiSizeT index);

/**
{function:
	{name: LmiUriGetQueryParameter}
	{parent: LmiUri}
	{description: Gets a parameter from a query in a URI by name.}
	{prototype: const char *LmiUriGetQueryParameter(const LmiUri *uri, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: The value of the query parameter, or NULL if this query parameter is not contained in the given URI.}
}
*/
const char *LmiUriGetQueryParameter(const LmiUri *uri, const char *name);

/**
{function:
	{name: LmiUriGetQueryParameterStr}
	{parent: LmiUri}
	{description: Gets a parameter from a query in a URI by name.}
	{prototype: const LmiString *LmiUriGetQueryParameterStr(const LmiUri *uri, const char *name)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{return: The value of the query parameter, or NULL if this query parameter is not contained in the given URI.}
}
*/
const LmiString *LmiUriGetQueryParameterStr(const LmiUri *uri, const char *name);

/**
{function:
	{name: LmiUriAddQueryParameter}
	{parent: LmiUri}
	{description: Adds a query parameter into a given URI.}
	{prototype: LmiBool LmiUriAddQueryParameter(LmiUri *uri, const char *name, const char *value)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: name} {description: The name of the parameter.}}
	{parameter: {name: value} {description: The value of the parameter.}}
	{return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool LmiUriAddQueryParameter(LmiUri *uri, const char *name, const char *value);

/**
{function:
	{name: LmiUriGetFragment}
	{parent: LmiUri}
	{description: Gets the fragment field from a URI object.}
	{prototype: const char* LmiUriGetFragment(const LmiUri* uri)}
	{parameter:
	{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to a NULL-terminated C String with the fragment
		on success, or NULL on failure}
}
*/
LMI_INLINE_DECLARATION const char* LmiUriGetFragment(const LmiUri* uri);

/**
{function:
	{name: LmiUriGetFragmentStr}
	{parent: LmiUri}
	{description: Gets the fragment field from a URI object as an LmiString.}
	{prototype: const LmiString* LmiUriGetFragmentStr(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: A pointer to the LmiString object with the fragment on
		success, or NULL on failure}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiUriGetFragmentStr(const LmiUri* uri);

/**
{function:
	{name: LmiUriSetFragment}
	{parent: LmiUri}
	{description: Sets the fragment field in a URI object.}
	{prototype: void LmiUriSetFragment(LmiUri *uri, const char *fragment)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: fragment} {description: The new fragment field.}}
}
*/
LMI_INLINE_DECLARATION void LmiUriSetFragment(LmiUri *uri, const char *fragment);

/**
{function:
	{name: LmiUriAsString}
	{parent: LmiUri}
	{description: Encodes a URI to an LmiString.}
	{prototype: LmiString* LmiUriAsString(const LmiUri* uri, LmiString* buf, LmiBool percentEncode)}
	{parameter: 
		{name: uri}
		{description: The URI object.}
	}
	{parameter: 
		{name: buf}
		{description: The LmiString object.}
	}
	{parameter:
		{name: percentEncode}
		{description: Flag to percent encode the output.}
	}
	{return: The URI as an LmiString on success; NULL on failure.}
}
*/
LmiString* LmiUriAsString(const LmiUri* uri, LmiString* buf, LmiBool percentEncode);

/**
{function:
	{name: LmiUriAppendPathToString}
	{parent: LmiUri}
	{description: Appends the full path of a URI without parameters or a leading slash to the LmiString.}
	{prototype: void LmiUriAppendPathToString(const LmiUri *uri, LmiString *s, LmiBool percentEncode)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: s} {description: The LmiString to which the path will be appended.}}
	{parameter:
		{name: percentEncode}
		{description: Flag to percent encode the output.}
	}
}
*/
void LmiUriAppendPathToString(const LmiUri *uri, LmiString *s, LmiBool percentEncode);

/**
{function:
	{name: LmiUriAppendPathQueryFragmentToString}
	{parent: LmiUri}
	{description: Appends the path query and fragment components of a URI to the LmiString.}
	{prototype: void LmiUriAppendPathQueryFragmentToString(const LmiUri *uri, LmiSizeT index, LmiString *s, LmiBool percentEncode)}
	{parameter: {name: uri} {description: The URI object.}}
	{parameter: {name: index} {description: The index of the path from which to start.}}
	{parameter: {name: s} {description: The LmiString to which the path will be appended.}}
 	{parameter:
		{name: percentEncode}
		{description: Flag to percent encode the output.}
	}
}
*/
void LmiUriAppendPathQueryFragmentToString(const LmiUri *uri, LmiSizeT index, LmiString *s, LmiBool percentEncode);

/**
{function:
	{name: LmiUriAppendToString}
	{parent: LmiUri}
	{description: Appends the encoding of a URI to an LmiString.}
	{prototype: LmiBool LmiUriAppendToString(const LmiUri* uri, LmiString* str, LmiBool percentEncode)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{parameter:
		{name: str}
		{description: The string to append the encoding to.}
	}
  	{parameter:
		{name: percentEncode}
		{description: Flag to percent encode the output.}
	}
	{return: LMI_TRUE on success, LMI_FALSE on failure}
}
*/
LmiBool LmiUriAppendToString(const LmiUri* uri, LmiString* str, LmiBool percentEncode);

/**
{function:
	{name: LmiUriAsStr}
	{parent: LmiUri}
	{description: Encodes a URI to a buffer.}
	{prototype: LmiSizeT LmiUriAsStr(const LmiUri* uri, char* buf, LmiSizeT buflen, LmiBool percentEncode)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{parameter:
		{name: buf}
		{description: The buffer to encode the URI into.}
	}
	{parameter:
		{name: buflen}
		{description: The length of the buffer. No more than buflen bytes will be
			written to buf, including the final NUL. The resulting string will
			always be NUL-terminated unless buflen == 0.}
	}
  	{parameter:
		{name: percentEncode}
		{description: Flag to percent encode the output.}
	}
	{return: The number of characters that would be printed if buflen were
		unlimited (not counting the final NUL.) If this is greater than
		or equal to buflen, the formatted string was truncated.}
}
*/
LmiSizeT LmiUriAsStr(const LmiUri* uri, char* buf, LmiSizeT buflen, LmiBool percentEncode);

/**
{function:
	{name: LmiUriCStr}
	{parent: LmiUri}
	{description: Gets the URI as an CStr.}
	{prototype: const char *LmiUriCStr(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: The URI on success; NULL on failure.}
	{note: Use with caution. The returned const char * will only be valid until the next non-const operation on LmiUri.}
}
*/
const char *LmiUriCStr(const LmiUri* uri);

/**
{function:
	{name: LmiUriString}
	{parent: LmiUri}
	{description: Gets the URI as an LmiString.}
	{prototype: const LmiString *LmiUriString(const LmiUri* uri)}
	{parameter:
		{name: uri}
		{description: The URI object.}
	}
	{return: The URI on success; NULL on failure.}
	{note: Use with caution. The returned const LmiString * will only be valid until the next non-const operation on LmiUri.}
}
*/
const LmiString *LmiUriString(const LmiUri *uri);


void LmiUriAppendEncodedString(LmiString *s, const LmiString *decodedString);
void LmiUriAppendDecodedStringCStr(LmiString *s, const char *encodedString);

Declare_LmiVector(LmiUri)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiUriInline.h>
#endif

#endif

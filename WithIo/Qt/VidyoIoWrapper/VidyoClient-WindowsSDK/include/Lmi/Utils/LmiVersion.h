/**
{file:
	{name: LmiVersion.h}
	{description: The interface to the LmiVersion class.}
	{copyright:
		(c) 2009-2015 Vidyo, Inc.,
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
#if !defined(LMI_VERSION_H_)
#define LMI_VERSION_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: LmiVersion}
	{parent: Utils}
	{include: Lmi/Utils/LmiVersion.h}
	{description: A data type that describes a version.}
}
*/
typedef LmiUint32 LmiVersion;

/**
{function visibility="private":
	{name: LmiVersionConstruct}
	{parent: LmiVersion}
	{description: Constructs a version from its component revisions. }
	{prototype: LmiVersion* LmiVersionConstruct(LmiVersion* x, LmiUint major, LmiUint minor, LmiUint engineering, LmiUint patch)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: major}
		{description: The major revision number.}
	}
	{parameter:
		{name: minor}
		{description: The minor revision number.}
	}
	{parameter:
		{name: engineering}
		{description: The engineering revision number.}
	}
	{parameter:
		{name: patch}
		{description: The patch revision number.}
	}
	{return: Returns the version or NULL on error. }
}
*/
LMI_INLINE_DECLARATION LmiVersion* LmiVersionConstruct(LmiVersion* x, LmiUint major, LmiUint minor, LmiUint engineering, LmiUint patch);

/**
{function visibility="private":
	{name: LmiVersionConstructFromTag}
	{parent: LmiVersion}
	{description: Constructs a version from a build tag. }
	{prototype: LmiVersion* LmiVersionConstructFromTag(LmiVersion* x, char* tag)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: tag}
		{description:
			A build tag of the form [word_[major_[minor_[patch_[engineering]]]]] where {italic: word}
			is [^_]*, and {italic:major}, {italic:minor}, {italic:patch} and {italic: engineering} are [0-9]*.
		}
	}
	{return: Returns the version or NULL on error. }
}
*/
LmiVersion* LmiVersionConstructFromTag(LmiVersion* x, char* tag);

/**
{function visibility="private":
	{name: LmiVersionConstructCopy}
	{parent: LmiVersion}
	{description: Constructs a version from another version. }
	{prototype: LmiVersion* LmiVersionConstructCopy(LmiVersion* x, const LmiVersion* y)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: y}
		{description: A version object to be copied.}
	}
	{return: Returns the version or NULL on error. }
}
*/
LMI_INLINE_DECLARATION LmiVersion* LmiVersionConstructCopy(LmiVersion* x, const LmiVersion* y);

/**
{function visibility="private":
	{name: LmiVersionDestruct}
	{parent: LmiVersion}
	{description: Constructs a version from a build tag. }
	{prototype: void LmiVersionDestruct(LmiVersion* x)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
}
*/
void LmiVersionDestruct(LmiVersion* x);

/**
{function visibility="private":
	{name: LmiVersionAssign}
	{parent: LmiVersion}
	{description: Assign one version to another version. }
	{prototype: LmiVersion* LmiVersionAssign(LmiVersion* x, const LmiVersion* y)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: y}
		{description: A version object to be copied.}
	}
	{return: Returns the version or NULL on error. }
}
*/
LMI_INLINE_DECLARATION LmiVersion* LmiVersionAssign(LmiVersion* x, const LmiVersion* y);

/**
{function visibility="private":
	{name: LmiVersionEqual}
	{parent: LmiVersion}
	{description: Compares two versions for equality.}
	{prototype: LmiBool LmiVersionEqual(const LmiVersion* x, const LmiVersion* y)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: y}
		{description: Another version object.}
	}
	{return: Returns the version or NULL on error. }
}
*/
LMI_INLINE_DECLARATION LmiBool LmiVersionEqual(const LmiVersion* x, const LmiVersion* y);

/**
{function visibility="private":
	{name: LmiVersionLess}
	{parent: LmiVersion}
	{description: Compares two versions for less-than ordering. }
	{prototype: LmiBool LmiVersionLess(const LmiVersion* x, const LmiVersion* y)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: y}
		{description: Another version object.}
	}
	{return: Returns the version or NULL on error. }
}
*/
LMI_INLINE_DECLARATION LmiBool LmiVersionLess(const LmiVersion* x, const LmiVersion* y);

/**
{function:
	{name: LmiVersionGetMajor}
	{parent: LmiVersion}
	{description: Gets the major revision field of a version. }
	{prototype: LmiUint LmiVersionGetMajor(const LmiVersion* x)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{return: Returns the major revision field of a version. }
}
*/
LMI_INLINE_DECLARATION LmiUint LmiVersionGetMajor(const LmiVersion* x);

/**
{function:
	{name: LmiVersionGetMinor}
	{parent: LmiVersion}
	{description: Gets the minor revision field of a version. }
	{prototype: LmiUint LmiVersionGetMinor(const LmiVersion* x)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{return: Returns the minor revision field of a version. }
}
*/
LMI_INLINE_DECLARATION LmiUint LmiVersionGetMinor(const LmiVersion* x);

/**
{function:
	{name: LmiVersionGetEngineering}
	{parent: LmiVersion}
	{description: Gets the engineering revision field of a version. }
	{prototype: LmiUint LmiVersionGetEngineering(const LmiVersion* x)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{return: Returns the engineering revision field of a version. }
}
*/
LMI_INLINE_DECLARATION LmiUint LmiVersionGetEngineering(const LmiVersion* x);

/**
{function:
	{name: LmiVersionGetPatch}
	{parent: LmiVersion}
	{description: Gets the patch revision field of a version. }
	{prototype: LmiUint LmiVersionGetPatch(const LmiVersion* x)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{return: Returns the patch revision field of a version. }
}
*/
LMI_INLINE_DECLARATION LmiUint LmiVersionGetPatch(const LmiVersion* x);

/**
{function:
	{name: LmiVersionAsString}
	{parent: LmiVersion}
	{description: Gets the version as a human readable string. }
	{prototype: LmiString* LmiVersionAsString(const LmiVersion* x, LmiString* s)}
	{parameter:
		{name: x}
		{description: A version object.}
	}
	{parameter:
		{name: s}
		{description: A constructed string into which the human readable version is written. }
	}
	{return: Returns a pointer to the string on success or NULL on error. }
}
*/
LmiString* LmiVersionAsString(const LmiVersion* x, LmiString* s);

const char *LmiVersionAsString_(const LmiVersion* x, char *buf, LmiSizeT size);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiVersionInline.h>
#endif

#endif /* LMI_VERSION_H_ */

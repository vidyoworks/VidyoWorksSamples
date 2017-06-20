/** {file:
      {name: LmiOs.h}
      {description: Top-level interface to LmiOs package.}
      {copyright:
      	(c) 2006-2016 Vidyo, Inc.,
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
#ifndef LMI_OS_H_
#define LMI_OS_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>

LMI_BEGIN_EXTERN_C

/**
   {package:
     {name: Os}
     {parent: Lmi}
     {include: Lmi/Os/LmiOs.h}
	 {library: LmiOs}
     {description: The LmiOs package encapsulates all
       operating-system-dependent aspects of the Vidyo SDK.}
   }
*/

/**
   {function:
     {name: LmiOsInitialize}
     {parent: Os}
     {description: Initialize all operating-system-dependent
       components of the Vidyo SDK.}
     {prototype: LmiBool LmiOsInitialize(void)}
     {return: LMI_TRUE on success, LMI_FALSE on failure.}
     {note: This function is not reentrant.}
     {note: This function may be called multiple times as long as its corresponding LmiOsUninitialize function is called the same number of times.}
   }
*/
LmiBool LmiOsInitialize(void);

/**
   {function:
     {name: LmiOsUninitialize}
     {parent: Os}
     {description: Uninitialize all operating-system-dependent
       components of the Vidyo SDK.}
     {prototype: void LmiOsUninitialize(void)}
	 {note: This function is not reentrant.}
	 {note: This function must be called the same number of times as LmiOsInitialize was called.}
   }
*/
void LmiOsUninitialize(void);

/**
   {function:
     {name: LmiOsGetName}
     {parent: Os}
     {description: Get the name of underlying operating system as a human readable string; appropriate for display, bug reporting, etc.}
     {prototype: LmiString* LmiOsGetName(LmiString* s)}
     {parameter: {name: s} {description: A string into which the operating system name will be written.}}
     {return: Returns a point to the string containing the operating system name or NULL on error.}
   }
*/
LmiString* LmiOsGetName(LmiString* s);

/**
   {function:
     {name: LmiOsGetVersionAsString}
     {parent: Os}
     {description: Get the underlying operating system version as a human readable string; appropriate for display, bug reporting, etc.; not appropriate for parsing. }
     {prototype: LmiString* LmiOsGetVersionAsString(LmiString* s)}
     {parameter: {name: s} {description: A string into which the version will be written.}}
     {return: Returns a point to the string containing the version or NULL on error.}
   }
*/
LmiString* LmiOsGetVersionAsString(LmiString* s);

/**
   {function:
     {name: LmiOsGetMajorVersion}
     {parent: Os}
     {description: Get the major version of the underlying operating system.}
     {prototype: LmiInt LmiOsGetMajorVersion(void)}
     {return: Returns the major version number.}
   }
*/
LmiInt LmiOsGetMajorVersion(void);

/**
   {function:
     {name: LmiOsGetMinorVersion}
     {parent: Os}
     {description: Get the minor version of the underlying operating system.}
     {prototype: LmiInt LmiOsGetMinorVersion(void)}
     {return: Returns the minor version number.}
   }
*/
LmiInt LmiOsGetMinorVersion(void);

/**
   {function:
     {name: LmiOsGetPatchVersion}
     {parent: Os}
     {description: Get the patch version of the underlying operating system.}
     {prototype: LmiInt LmiOsGetPatchVersion(void)}
     {return: Returns the patch version number.}
   }
*/
LmiInt LmiOsGetPatchVersion(void);


/* OS dependent interface */
LmiString* LmiOsGetName_(LmiString* s);
LmiString* LmiOsGetVersionAsString_(LmiString* s);
LmiInt LmiOsGetMajorVersion_(void);
LmiInt LmiOsGetMinorVersion_(void);
LmiInt LmiOsGetPatchVersion_(void);

LMI_END_EXTERN_C

#endif /* LMI_OS_H_ */

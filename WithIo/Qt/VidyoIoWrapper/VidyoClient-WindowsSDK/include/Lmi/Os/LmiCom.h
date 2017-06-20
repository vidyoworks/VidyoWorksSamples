/** {file:
	  {name: LmiCom.h}
	  {description: Interface for wrapper around Microsoft COM functions.}
	  {copyright:
	  	(c) 2013-2014 Vidyo, Inc.,
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

#ifndef LMI_COM_H
#define LMI_COM_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiLog.h>

typedef enum {
	LMI_COMAPARTMENTMODE_Single,
	LMI_COMAPARTMENTMODE_Multi
} LmiComApartmentMode;

LMI_BEGIN_EXTERN_C
LmiBool LmiComInitialize(void);
void LmiComUninitialize(void);
LmiBool LmiComEnter(LmiComApartmentMode mode);
void LmiComLeave(void);
LmiBool LmiComIsThreadInitialized(void);

typedef enum {
	LMI_COMGUARDMODE_Single,
	LMI_COMGUARDMODE_Multi,
	LMI_COMGUARDMODE_Any
} LmiComGuardMode;

typedef struct {
	LmiBool any;
} LmiComGuard;

LmiComGuard* LmiComGuardConstructWithMode(LmiComGuard* x, LmiComGuardMode mode);
LmiComGuard* LmiComGuardConstruct(LmiComGuard* x);
void LmiComGuardDestruct(LmiComGuard* x);

LMI_END_EXTERN_C

#endif


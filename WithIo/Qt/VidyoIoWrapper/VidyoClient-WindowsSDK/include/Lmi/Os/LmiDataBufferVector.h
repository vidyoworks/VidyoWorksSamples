/**
{file:
	{name: LmiDataBufferVector.h}
	{description: Centralizes definition of a vector of data buffers.}
	{copyright:
		(c) 2007 Vidyo, Inc.,
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

#ifndef LMI_DATA_BUFFER_VECTOR_H_
#define LMI_DATA_BUFFER_VECTOR_H_

#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Os/LmiDataBuffer.h>

LMI_BEGIN_EXTERN_C

Declare_LmiVector(LmiDataBuffer)

LMI_END_EXTERN_C

#endif /* LMI_DATA_BUFFER_VECTOR_H_ */

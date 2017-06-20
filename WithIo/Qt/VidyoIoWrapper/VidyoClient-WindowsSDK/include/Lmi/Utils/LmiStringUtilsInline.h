/**
{file:
	{name: LmiStringUtilsInline.h}
	{description: Miscellaneous string utilities}
	{copyright:
		(c) 2005-2008 Vidyo, Inc.,
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
LMI_INLINE LmiPrintfBuffer *LmiPrintfBufferConstruct(LmiPrintfBuffer *pb, char *buffer, LmiSizeT bufferLength)
{
	pb->buffer = buffer;
	pb->bufferLength = bufferLength;
	pb->stringLength = 0;
	return pb;
}

LMI_INLINE void LmiPrintfBufferDestruct(LmiPrintfBuffer *pb)
{
}

LMI_INLINE LmiSizeT LmiPrintfBufferGetStringLength(const LmiPrintfBuffer *pb)
{
	return pb->stringLength;
}

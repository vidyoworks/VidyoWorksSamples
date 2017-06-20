/** 
{file:
	{name: VidyoRemoteRendererInline.h}
	{description: RemoteRenderer to which local Sources can be sent. }
	{copyright:
		(c) 2013 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/

Define_LmiSharedPtrWrapper_NoCompare(VidyoRemoteRenderer, VidyoRemoteRendererImpl)
Define_LmiWeakPtrWrapper(VidyoRemoteRendererHandle, VidyoRemoteRenderer, VidyoRemoteRendererImpl)

Define_LmiSharedPtrWrapper_NoCompare(VidyoRemoteRendererStream, VidyoRemoteRendererStreamImpl)
Define_LmiWeakPtrWrapper(VidyoRemoteRendererStreamHandle, VidyoRemoteRendererStream, VidyoRemoteRendererStreamImpl)

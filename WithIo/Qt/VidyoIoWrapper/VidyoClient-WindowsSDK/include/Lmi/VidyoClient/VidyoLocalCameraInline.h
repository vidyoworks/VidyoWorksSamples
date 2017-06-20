/** 
{file:
	{name: VidyoLocalCameraInline.h}
	{description: Camera device. }
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

Define_LmiSharedPtrWrapper_NoCompare(VidyoVideoFrameNormalizationData, VidyoVideoFrameNormalizationDataImpl)
Define_LmiWeakPtrWrapper(VidyoVideoFrameNormalizationDataHandle, VidyoVideoFrameNormalizationData, VidyoVideoFrameNormalizationDataImpl)

Define_LmiSharedPtrWrapper_NoCompare(VidyoLocalCamera, VidyoLocalCameraImpl)
Define_LmiWeakPtrWrapper(VidyoLocalCameraHandle, VidyoLocalCamera, VidyoLocalCameraImpl)


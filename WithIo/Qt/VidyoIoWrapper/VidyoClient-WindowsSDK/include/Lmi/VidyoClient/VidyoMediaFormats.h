/**
{file:
	{name: VidyoVideoCapability.h}
	{description: Video Capability. }
	{copyright:
		(c) 2015 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/
#ifndef VIDYO_MEDIAFORMATS_H_
#define VIDYO_MEDIAFORMATS_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiMediaFormat.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="public":
	{name: VidyoMediaFormat}
	{parent: Endpoint}
	{include: Lmi/VidyoClient/VidyoMediaFormats.h}
	{description: Represents the media format.}
	{value: {name: VIDYO_MEDIAFORMAT_IN16}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_FL32}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_NULL}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_WPCM}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_I420}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_YU12}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_YUYV}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_YUY2}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_yuvs}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_2vuy}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_UYVY}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_HDYC}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_yuv2}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_yuvu}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_NV12}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_NV21}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_24BG}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_raw}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_BGRA}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_RGBA}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_ARGB}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_BYR1}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_BYR2}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_JPEG}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_MJPG}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dmb1}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dvsd}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dvhd}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dvsl}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dv25}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dv50}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dvh1}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_dv}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_M420}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_420f}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_420v}
			{description:}
	}
	{value: {name: VIDYO_MEDIAFORMAT_Y8}
			{description:}
	}
}
*/
typedef enum
{
	VIDYO_MEDIAFORMAT_IN16,
	VIDYO_MEDIAFORMAT_FL32,
	VIDYO_MEDIAFORMAT_NULL,
	VIDYO_MEDIAFORMAT_WPCM,
	VIDYO_MEDIAFORMAT_I420,
	VIDYO_MEDIAFORMAT_YU12,
	VIDYO_MEDIAFORMAT_YUYV,
	VIDYO_MEDIAFORMAT_YUY2,
	VIDYO_MEDIAFORMAT_yuvs,
	VIDYO_MEDIAFORMAT_2vuy,
	VIDYO_MEDIAFORMAT_UYVY,
	VIDYO_MEDIAFORMAT_HDYC,
	VIDYO_MEDIAFORMAT_yuv2,
	VIDYO_MEDIAFORMAT_yuvu,
	VIDYO_MEDIAFORMAT_NV12,
	VIDYO_MEDIAFORMAT_NV21,
	VIDYO_MEDIAFORMAT_24BG,
	VIDYO_MEDIAFORMAT_raw,
	VIDYO_MEDIAFORMAT_BGRA,
	VIDYO_MEDIAFORMAT_RGBA,
	VIDYO_MEDIAFORMAT_ARGB,
	VIDYO_MEDIAFORMAT_BYR1,
	VIDYO_MEDIAFORMAT_BYR2,
	VIDYO_MEDIAFORMAT_JPEG,
	VIDYO_MEDIAFORMAT_MJPG,
	VIDYO_MEDIAFORMAT_dmb1,
	VIDYO_MEDIAFORMAT_dvsd,
	VIDYO_MEDIAFORMAT_dvhd,
	VIDYO_MEDIAFORMAT_dvsl,
	VIDYO_MEDIAFORMAT_dv25,
	VIDYO_MEDIAFORMAT_dv50,
	VIDYO_MEDIAFORMAT_dvh1,
	VIDYO_MEDIAFORMAT_dv,
	VIDYO_MEDIAFORMAT_M420,
	VIDYO_MEDIAFORMAT_420f,
	VIDYO_MEDIAFORMAT_420v,
	VIDYO_MEDIAFORMAT_Y8
} VidyoMediaFormat;

LmiBool VidyoMediaFormatLess(const VidyoMediaFormat* x, const VidyoMediaFormat* y);
LmiBool VidyoMediaFormatEqual(const VidyoMediaFormat* x, const VidyoMediaFormat* y);
VidyoMediaFormat* VidyoMediaFormatConstructCopy(VidyoMediaFormat* x, const VidyoMediaFormat* y);
void VidyoMediaFormatDestruct(VidyoMediaFormat* x);
VidyoMediaFormat* VidyoMediaFormatAssign(VidyoMediaFormat* x, const VidyoMediaFormat* y);
VidyoMediaFormat VidyoMediaFormatConvertLmiMediaFormat(LmiMediaFormat format);
LmiMediaFormat VidyoMediaFormatConvertToLmiMediaFormat(VidyoMediaFormat format);

Declare_LmiVector(VidyoMediaFormat)
Declare_LmiVectorEqual(VidyoMediaFormat)

LMI_END_EXTERN_C

#endif /* VIDYO_MEDIAFORMATS_H_ */

/**
{file:
	{name: LmiMediaFormat.h}
	{description: Media formats.}
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
#ifndef LMI_MEDIAFORMAT_H
#define LMI_MEDIAFORMAT_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>

LMI_BEGIN_EXTERN_C

#define LmiFourCC(_a, _b, _c, _d) ( ((LmiUint32)(_d)<<24) | ((LmiUint32)(_c) << 16) | ((LmiUint32)(_b) << 8) | ((LmiUint32)(_a)) )

/* Use LmiMediaFormatConstruct to create an LmiMediaFormat from these constants */
/* Note: the last component of the constant's name is a mapped from the FourCC value by preserving case and stripping ending whitespace */
#define LMI_MEDIAFORMAT_NULL LmiFourCC('N', 'U', 'L', 'L')
#define LMI_MEDIAFORMAT_WPCM LmiFourCC('W', 'P', 'C', 'M')
#define LMI_MEDIAFORMAT_I420 LmiFourCC('I', '4', '2', '0')
#define LMI_MEDIAFORMAT_YU12 LmiFourCC('Y', 'U', '1', '2')
#define LMI_MEDIAFORMAT_YUYV LmiFourCC('Y', 'U', 'Y', 'V')
#define LMI_MEDIAFORMAT_YUY2 LmiFourCC('Y', 'U', 'Y', '2')
#define LMI_MEDIAFORMAT_yuvs LmiFourCC('y', 'u', 'v', 's')
#define LMI_MEDIAFORMAT_2vuy LmiFourCC('2', 'v', 'u', 'y')
#define LMI_MEDIAFORMAT_UYVY LmiFourCC('U', 'Y', 'V', 'Y')
#define LMI_MEDIAFORMAT_HDYC LmiFourCC('H', 'D', 'Y', 'C')
#define LMI_MEDIAFORMAT_yuv2 LmiFourCC('y', 'u', 'v', '2')
#define LMI_MEDIAFORMAT_yuvu LmiFourCC('y', 'u', 'v', 'u')
#define LMI_MEDIAFORMAT_NV12 LmiFourCC('N', 'V', '1', '2')
#define LMI_MEDIAFORMAT_NV21 LmiFourCC('N', 'V', '2', '1')
#define LMI_MEDIAFORMAT_24BG LmiFourCC('2', '4', 'B', 'G')
#define LMI_MEDIAFORMAT_raw  LmiFourCC('r', 'a', 'w', ' ')
#define LMI_MEDIAFORMAT_BGRA LmiFourCC('B', 'G', 'R', 'A')
#define LMI_MEDIAFORMAT_RGBA LmiFourCC('R', 'G', 'B', 'A')
#define LMI_MEDIAFORMAT_ARGB LmiFourCC('A', 'R', 'G', 'B')
#define LMI_MEDIAFORMAT_BYR1 LmiFourCC('B', 'Y', 'R', '1')
#define LMI_MEDIAFORMAT_BYR2 LmiFourCC('B', 'Y', 'R', '2')
#define LMI_MEDIAFORMAT_JPEG LmiFourCC('J', 'P', 'E', 'G')
#define LMI_MEDIAFORMAT_MJPG LmiFourCC('M', 'J', 'P', 'G')
#define LMI_MEDIAFORMAT_dmb1 LmiFourCC('d', 'm', 'b', '1')
#define LMI_MEDIAFORMAT_dvsd LmiFourCC('d', 'v', 's', 'd')
#define LMI_MEDIAFORMAT_dvhd LmiFourCC('d', 'v', 'h', 'd')
#define LMI_MEDIAFORMAT_dvsl LmiFourCC('d', 'v', 's', 'l')
#define LMI_MEDIAFORMAT_dv25 LmiFourCC('d', 'v', '2', '5')
#define LMI_MEDIAFORMAT_dv50 LmiFourCC('d', 'v', '5', '0')
#define LMI_MEDIAFORMAT_dvh1 LmiFourCC('d', 'v', 'h', '1')
#define LMI_MEDIAFORMAT_dv   LmiFourCC('d', 'v', ' ', ' ')
#define LMI_MEDIAFORMAT_M420 LmiFourCC('M', '4', '2', '0')
#define LMI_MEDIAFORMAT_420f LmiFourCC('4', '2', '0', 'f')
#define LMI_MEDIAFORMAT_420v LmiFourCC('4', '2', '0', 'v')
#define LMI_MEDIAFORMAT_Y8   LmiFourCC('Y', '8', ' ', ' ')
#define LMI_MEDIAFORMAT_in16 LmiFourCC('i', 'n', '1', '6')
#define LMI_MEDIAFORMAT_fl32 LmiFourCC('f', 'l', '3', '2')

/* Deprecated.  Replaced by LMI_MEDIAFORMAT_xxxx */
#define MEDIA_FORMAT_WPCM LMI_MEDIAFORMAT_WPCM
#define MEDIA_FORMAT_I420 LMI_MEDIAFORMAT_I420
#define MEDIA_FORMAT_YU12 LMI_MEDIAFORMAT_YU12
#define MEDIA_FORMAT_YUYV LMI_MEDIAFORMAT_YUYV
#define MEDIA_FORMAT_YUY2 LMI_MEDIAFORMAT_YUY2
#define MEDIA_FORMAT_YUVS LMI_MEDIAFORMAT_yuvs
#define MEDIA_FORMAT_2VUY LMI_MEDIAFORMAT_2vuy
#define MEDIA_FORMAT_UYVY LMI_MEDIAFORMAT_UYVY
#define MEDIA_FORMAT_HDYC LMI_MEDIAFORMAT_HDYC
#define MEDIA_FORMAT_YUV2 LMI_MEDIAFORMAT_yuv2
#define MEDIA_FORMAT_YUVU LMI_MEDIAFORMAT_yuvu
#define MEDIA_FORMAT_NV12 LMI_MEDIAFORMAT_NV12
#define MEDIA_FORMAT_NV21 LMI_MEDIAFORMAT_NV21
#define MEDIA_FORMAT_24BG LMI_MEDIAFORMAT_24BG
#define MEDIA_FORMAT_RAW  LMI_MEDIAFORMAT_raw
#define MEDIA_FORMAT_BGRA LMI_MEDIAFORMAT_BGRA
#define MEDIA_FORMAT_RGBA LMI_MEDIAFORMAT_RGBA
#define MEDIA_FORMAT_ARGB LMI_MEDIAFORMAT_ARGB
#define MEDIA_FORMAT_BYR1 LMI_MEDIAFORMAT_BYR1
#define MEDIA_FORMAT_BYR2 LMI_MEDIAFORMAT_BYR2
#define MEDIA_FORMAT_MJPG LMI_MEDIAFORMAT_MJPG
#define MEDIA_FORMAT_DVSD LMI_MEDIAFORMAT_dvsd
#define MEDIA_FORMAT_DVHD LMI_MEDIAFORMAT_dvhd
#define MEDIA_FORMAT_DVSL LMI_MEDIAFORMAT_dvsl
#define MEDIA_FORMAT_DV25 LMI_MEDIAFORMAT_dv25
#define MEDIA_FORMAT_DV50 LMI_MEDIAFORMAT_dv50
#define MEDIA_FORMAT_DVH1 LMI_MEDIAFORMAT_dvh1
#define MEDIA_FORMAT_DV   LMI_MEDIAFORMAT_dv
#define MEDIA_FORMAT_M420 LMI_MEDIAFORMAT_M420
#define MEDIA_FORMAT_420F LMI_MEDIAFORMAT_420f
#define MEDIA_FORMAT_420V LMI_MEDIAFORMAT_420v

/**
{type: 
	{name: LmiMediaFormat}
	{parent: Utils}
	{include: Lmi/Utils/LmiMediaFormat.h}
	{description: Uniquely identifies a media format.}
	{constant: {name: LMI_MEDIAFORMAT_NULL} {type: LmiMediaFormat} {description: Media format for null (empty) objects.}}
 	{constant: {name: LMI_MEDIAFORMAT_WPCM} {type: LmiMediaFormat} {description: Media Format for FourCC 'WPCM' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_I420} {type: LmiMediaFormat} {description: Media Format for FourCC 'I420' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_YU12} {type: LmiMediaFormat} {description: Media Format for FourCC 'YU12' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_YUYV} {type: LmiMediaFormat} {description: Media Format for FourCC 'YUYV' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_YUY2} {type: LmiMediaFormat} {description: Media Format for FourCC 'YUY2' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_yuvs} {type: LmiMediaFormat} {description: Media Format for FourCC 'YUY2' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_2vuy} {type: LmiMediaFormat} {description: Media Format for FourCC 'yuvs' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_UYVY} {type: LmiMediaFormat} {description: Media Format for FourCC '2vuy' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_HDYC} {type: LmiMediaFormat} {description: Media Format for FourCC 'HDYC' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_yuv2} {type: LmiMediaFormat} {description: Media Format for FourCC 'yuv2' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_yuvu} {type: LmiMediaFormat} {description: Media Format for FourCC 'yuvu' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_NV12} {type: LmiMediaFormat} {description: Media Format for FourCC 'NV12' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_NV21} {type: LmiMediaFormat} {description: Media Format for FourCC 'NV21' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_24BG} {type: LmiMediaFormat} {description: Media Format for FourCC '24BG' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_raw} {type: LmiMediaFormat} {description: Media Format for FourCC 'raw ' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_BGRA} {type: LmiMediaFormat} {description: Media Format for FourCC 'BGRA' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_RGBA} {type: LmiMediaFormat} {description: Media Format for FourCC 'RGBA' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_ARGB} {type: LmiMediaFormat} {description: Media Format for FourCC 'ARGB' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_BYR1} {type: LmiMediaFormat} {description: Media Format for FourCC 'BYR1' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_BYR2} {type: LmiMediaFormat} {description: Media Format for FourCC 'BYR2' data.}}
	{constant: {name: LMI_MEDIAFORMAT_JPEG} {type: LmiMediaFormat} {description: Media Format for FourCC 'JPEG' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_MJPG} {type: LmiMediaFormat} {description: Media Format for FourCC 'MJPG' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dmb1} {type: LmiMediaFormat} {description: Media Format for FourCC 'dmb1' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dvsd} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvsd' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dvhd} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvhd' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dvsl} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvsl' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dv25} {type: LmiMediaFormat} {description: Media Format for FourCC 'dv25' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dv50} {type: LmiMediaFormat} {description: Media Format for FourCC 'dv50' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dvh1} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvh1' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_dv} {type: LmiMediaFormat} {description: Media Format for FourCC 'dv  ' data.}}
 	{constant: {name: LMI_MEDIAFORMAT_M420} {type: LmiMediaFormat} {description: Media Format for FourCC 'M420' data.}}
  	{constant: {name: LMI_MEDIAFORMAT_420f} {type: LmiMediaFormat} {description: Media Format for FourCC '420f' data.}}
  	{constant: {name: LMI_MEDIAFORMAT_420v} {type: LmiMediaFormat} {description: Media Format for FourCC '420v' data.}}
  	{constant: {name: LMI_MEDIAFORMAT_Y8} {type: LmiMediaFormat} {description: Media Format for FourCC 'Y8  ' data.}}
  	{constant: {name: LMI_MEDIAFORMAT_in16} {type: LmiMediaFormat} {description: Media Format for FourCC 'in16' data: PCM audio in 16-bit signed integer in native byte order.}}
  	{constant: {name: LMI_MEDIAFORMAT_fl32} {type: LmiMediaFormat} {description: Media Format for FourCC 'fl32' data: PCM audio in 32-bit native single-precision floating-point.}}
	{constant symbolic="no": {name: lmiMediaFormat_NULL} {type: LmiMediaFormat} {description: Media format for null (empty) objects.}}
 	{constant symbolic="no": {name: lmiMediaFormat_WPCM} {type: LmiMediaFormat} {description: Media Format for FourCC 'WPCM' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_I420} {type: LmiMediaFormat} {description: Media Format for FourCC 'I420' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_YU12} {type: LmiMediaFormat} {description: Media Format for FourCC 'YU12' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_YUYV} {type: LmiMediaFormat} {description: Media Format for FourCC 'YUYV' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_YUY2} {type: LmiMediaFormat} {description: Media Format for FourCC 'YUY2' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_yuvs} {type: LmiMediaFormat} {description: Media Format for FourCC 'YUY2' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_2vuy} {type: LmiMediaFormat} {description: Media Format for FourCC 'yuvs' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_UYVY} {type: LmiMediaFormat} {description: Media Format for FourCC '2vuy' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_HDYC} {type: LmiMediaFormat} {description: Media Format for FourCC 'HDYC' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_yuv2} {type: LmiMediaFormat} {description: Media Format for FourCC 'yuv2' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_yuvu} {type: LmiMediaFormat} {description: Media Format for FourCC 'yuvu' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_NV12} {type: LmiMediaFormat} {description: Media Format for FourCC 'NV12' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_NV21} {type: LmiMediaFormat} {description: Media Format for FourCC 'NV21' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_24BG} {type: LmiMediaFormat} {description: Media Format for FourCC '24BG' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_raw} {type: LmiMediaFormat} {description: Media Format for FourCC 'raw ' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_BGRA} {type: LmiMediaFormat} {description: Media Format for FourCC 'BGRA' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_RGBA} {type: LmiMediaFormat} {description: Media Format for FourCC 'RGBA' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_ARGB} {type: LmiMediaFormat} {description: Media Format for FourCC 'ARGB' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_BYR1} {type: LmiMediaFormat} {description: Media Format for FourCC 'BYR1' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_BYR2} {type: LmiMediaFormat} {description: Media Format for FourCC 'BYR2' data.}}
    {constant symbolic="no": {name: lmiMediaFormat_JPEG} {type: LmiMediaFormat} {description: Media Format for FourCC 'JPEG' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_MJPG} {type: LmiMediaFormat} {description: Media Format for FourCC 'MJPG' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dmb1} {type: LmiMediaFormat} {description: Media Format for FourCC 'dmb1' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dvsd} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvsd' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dvhd} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvhd' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dvsl} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvsl' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dv25} {type: LmiMediaFormat} {description: Media Format for FourCC 'dv25' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dv50} {type: LmiMediaFormat} {description: Media Format for FourCC 'dv50' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dvh1} {type: LmiMediaFormat} {description: Media Format for FourCC 'dvh1' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_dv} {type: LmiMediaFormat} {description: Media Format for FourCC 'dv  ' data.}}
 	{constant symbolic="no": {name: lmiMediaFormat_M420} {type: LmiMediaFormat} {description: Media Format for FourCC 'M420' data.}}
  	{constant symbolic="no": {name: lmiMediaFormat_420f} {type: LmiMediaFormat} {description: Media Format for FourCC '420f' data.}}
  	{constant symbolic="no": {name: lmiMediaFormat_420v} {type: LmiMediaFormat} {description: Media Format for FourCC '420v' data.}}
  	{constant symbolic="no": {name: lmiMediaFormat_Y8} {type: LmiMediaFormat} {description: Media Format for FourCC 'Y8  ' data.}}
  	{constant symbolic="no": {name: lmiMediaFormat_in16} {type: LmiMediaFormat} {description: Media Format for FourCC 'in16' data: PCM audio in 16-bit signed integer in native byte order.}}
  	{constant symbolic="no": {name: lmiMediaFormat_fl32} {type: LmiMediaFormat} {description: Media Format for FourCC 'fl32' data: PCM audio in 32-bit native single-precision floating-point.}}
	{note: The "LMI_MEDIAFORMAT_" constants are compile-time symbolic constants (suitable for initializers); the "lmiMediaFormat_" constants are constant objects (so pointers to them can be passed to functions).}

}
*/
typedef LmiUint32 LmiMediaFormat;

extern const LmiMediaFormat lmiMediaFormat_NULL;
extern const LmiMediaFormat lmiMediaFormat_WPCM;
extern const LmiMediaFormat lmiMediaFormat_I420;
extern const LmiMediaFormat lmiMediaFormat_YU12;
extern const LmiMediaFormat lmiMediaFormat_YUYV;
extern const LmiMediaFormat lmiMediaFormat_YUY2;
extern const LmiMediaFormat lmiMediaFormat_yuvs;
extern const LmiMediaFormat lmiMediaFormat_2vuy;
extern const LmiMediaFormat lmiMediaFormat_UYVY;
extern const LmiMediaFormat lmiMediaFormat_HDYC;
extern const LmiMediaFormat lmiMediaFormat_yuv2;
extern const LmiMediaFormat lmiMediaFormat_yuvu;
extern const LmiMediaFormat lmiMediaFormat_NV12;
extern const LmiMediaFormat lmiMediaFormat_NV21;
extern const LmiMediaFormat lmiMediaFormat_24BG;
extern const LmiMediaFormat lmiMediaFormat_raw;
extern const LmiMediaFormat lmiMediaFormat_BGRA;
extern const LmiMediaFormat lmiMediaFormat_RGBA;
extern const LmiMediaFormat lmiMediaFormat_ARGB;
extern const LmiMediaFormat lmiMediaFormat_BYR1;
extern const LmiMediaFormat lmiMediaFormat_BYR2;
extern const LmiMediaFormat lmiMediaFormat_JPEG;
extern const LmiMediaFormat lmiMediaFormat_MJPG;
extern const LmiMediaFormat lmiMediaFormat_dmb1;
extern const LmiMediaFormat lmiMediaFormat_dvsd;
extern const LmiMediaFormat lmiMediaFormat_dvhd;
extern const LmiMediaFormat lmiMediaFormat_dvsl;
extern const LmiMediaFormat lmiMediaFormat_dv25;
extern const LmiMediaFormat lmiMediaFormat_dv50;
extern const LmiMediaFormat lmiMediaFormat_dvh1;
extern const LmiMediaFormat lmiMediaFormat_dv;
extern const LmiMediaFormat lmiMediaFormat_M420;
extern const LmiMediaFormat lmiMediaFormat_420f;
extern const LmiMediaFormat lmiMediaFormat_420v;
extern const LmiMediaFormat lmiMediaFormat_Y8;
/*audio related*/
extern const LmiMediaFormat lmiMediaFormat_in16;
extern const LmiMediaFormat lmiMediaFormat_fl32;

/**
{function:
	{name: LmiMediaFormatConstruct}
	{parent: LmiMediaFormat}
	{description: Constructs a media format object and initializes it from a FourCC value.}
	{prototype: LmiMediaFormat* LmiMediaFormatConstruct(LmiMediaFormat* x, LmiUint32 fourcc)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: fourcc}
		{description: The ???? byte-order FourCC value to initialize the media format from. }
	}
	{return: The constructed object or NULL on error.}
	{note: See also LmiMediaFormatConstructFromNative to construct media formats from FourCC codes in native byte order (as are typically used on Apple platforms).}
}
*/
LmiMediaFormat* LmiMediaFormatConstruct(LmiMediaFormat* x, LmiUint32 fourcc);

/**
{function:
	{name: LmiMediaFormatConstructFromNative}
	{parent: LmiMediaFormat}
	{description: Constructs a media format object and initializes it from a native-format FourCC value.}
	{prototype: LmiMediaFormat* LmiMediaFormatConstructFromNative(LmiMediaFormat* x, LmiUint32 fourcc)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: fourcc}
		{description: The native-format FourCC value to initialize the media format from. }
	}
	{return: The constructed object or NULL on error.}
    {note: The endiannesses of FourCC values are different on different little-endian platforms.  On Apple platforms, they are typically forward in an unsigned 32-bit integer (reversed in memory), whereas on Windows and Linux they are reversed in a 32-bit integer (forward in memory).  (Big-endian platforms, generally, are consistently forward both in memory and in the integer.)}
}
*/
LmiMediaFormat* LmiMediaFormatConstructFromNative(LmiMediaFormat* x, LmiUint32 fourcc);



/**
{function:
	{name: LmiMediaFormatConstructFromCStr}
	{parent: LmiMediaFormat}
	{description: Constructs a media format object from a C string representation of a FourCC value.}
	{prototype: LmiMediaFormat* LmiMediaFormatConstructFromCStr(LmiMediaFormat* x, const char* fourcc)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: fourcc}
		{description: A C string representation of the FourCC value to initialize the media format with. }
	}
	{return: The constructed object or NULL on error.}
}
*/
LmiMediaFormat* LmiMediaFormatConstructFromCStr(LmiMediaFormat* x, const char* fourcc);

/**
{function:
	{name: LmiMediaFormatConstructCopy}
	{parent: LmiMediaFormat}
	{description: Construct a media format object from another media format instance.}
	{prototype: LmiMediaFormat* LmiMediaFormatConstructCopy(LmiMediaFormat* x, const LmiMediaFormat* y)}
	{parameter: 
		{name: x}
		{description: The media object. }
	}
	{parameter: 
		{name: y}
		{description: The media object to initialize from.}
	}
	{return: The constructed object or NULL on error.}
}
*/
LmiMediaFormat* LmiMediaFormatConstructCopy(LmiMediaFormat* x, const LmiMediaFormat* y);

/**
{function:
	{name: LmiMediaFormatDestruct}
	{parent: LmiMediaFormat}
	{description: Destructs a media format object.}
	{prototype: void LmiMediaFormatDestruct(LmiMediaFormat* x)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
}
*/
void LmiMediaFormatDestruct(LmiMediaFormat* x);

/**
{function:
	{name: LmiMediaFormatAssign}
	{parent: LmiMediaFormat}
	{description: Copy the content of one media format object to another.}
	{prototype: LmiMediaFormat* LmiMediaFormatAssign(LmiMediaFormat* x, const LmiMediaFormat* y)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: y}
		{description: The media format object to copy from.}
	}
	{return: The object assigned to or NULL on error.}
}
*/
LmiMediaFormat* LmiMediaFormatAssign(LmiMediaFormat* x, const LmiMediaFormat* y);

/**
{function:
	{name: LmiMediaFormatSwap}
	{parent: LmiMediaFormat}
	{description: Swap the content of one media format object with another.}
	{prototype: LmiBool LmiMediaFormatSwap(LmiMediaFormat* x, LmiMediaFormat* y)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: y}
		{description: The media format object to copy from.}
	}
	{return: Returns LMI_TRUE on success or LMI_FALSE otherwise.}
}
*/
LmiBool LmiMediaFormatSwap(LmiMediaFormat* x, LmiMediaFormat* y);

/**
{function:
	{name: LmiMediaFormatEqual}
	{parent: LmiMediaFormat}
	{description: Compares two media format objects for equality.}
	{prototype: LmiBool LmiMediaFormatEqual(const LmiMediaFormat* x, const LmiMediaFormat* y)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: y}
		{description: The other media format object.}
	}
	{return: LMI_TRUE if the media format objects are equal and LMI_FALSE otherwise. }
}
*/
LmiBool LmiMediaFormatEqual(const LmiMediaFormat* x, const LmiMediaFormat* y);

/**
{function:
	{name: LmiMediaFormatLess}
	{parent: LmiMediaFormat}
	{description: Checks if the media format x is less than media format y}
	{prototype: LmiBool LmiMediaFormatLess(const LmiMediaFormat* x, const LmiMediaFormat* y)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: y}
		{description: The media format object to check with.}
	}
	{return: LMI_TRUE if x is less than y and LMI_FALSE otherwise.}
}
*/
LmiBool LmiMediaFormatLess(const LmiMediaFormat* x, const LmiMediaFormat* y);

/**
{function:
	{name: LmiMediaFormatToFourCC}
	{parent: LmiMediaFormat}
	{description: Converts a media format object to a FourCC value.}
	{prototype: LmiUint32 LmiMediaFormatToFourCC(const LmiMediaFormat* x)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{return: A FourCC value.}
    {note: See also LmiMediaFormatToNativeFourCC.}
}
*/
LmiUint32 LmiMediaFormatToFourCC(const LmiMediaFormat* x);

/**
{function:
	{name: LmiMediaFormatToNativeFourCC}
	{parent: LmiMediaFormat}
	{description: Converts a media format object to a native-format FourCC value.}
	{prototype: LmiUint32 LmiMediaFormatToNativeFourCC(const LmiMediaFormat* x)}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{return: A native-format FourCC value.}
    {note: The endiannesses of FourCC values are different on different little-endian platforms.  On Apple platforms, they are typically forward in an unsigned 32-bit integer (reversed in memory), whereas on Windows and Linux they are reversed in a 32-bit integer (forward in memory).  (Big-endian platforms, generally, are consistently forward both in memory and in the integer.)}
}
*/
LmiUint32 LmiMediaFormatToNativeFourCC(const LmiMediaFormat* x);


/**
{function:
	{name: LmiMediaFormatToCStr}
	{parent: LmiMediaFormat}
	{description: Converts a media format object to a C string representation of a FourCC value.}
	{prototype: char* LmiMediaFormatToCStr(const LmiMediaFormat* x, char buf[5])}
	{parameter: 
		{name: x}
		{description: The media format object.}
	}
	{parameter: 
		{name: buf}
		{description: The buffer to hold the result.}
	}
	{return: A pointer to the FourCC buffer.}
}
*/
char* LmiMediaFormatToCStr(const LmiMediaFormat* x, char buf[5]);

Declare_LmiVector(LmiMediaFormat)
Declare_LmiVectorEqual(LmiMediaFormat)

LMI_END_EXTERN_C

#endif

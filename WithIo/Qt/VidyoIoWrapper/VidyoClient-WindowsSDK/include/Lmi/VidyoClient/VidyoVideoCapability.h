/** 
{file:
	{name: VidyoVideoCapability.h}
	{description: Video Capability. }
	{copyright:
		(c) 2014-2016 Vidyo, Inc.,
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
#ifndef VIDYO_VIDEOCAPABILITY_H_
#define VIDYO_VIDEOCAPABILITY_H_

#include <Lmi/Utils/LmiBase64Encoding.h>
#include <Lmi/Os/LmiDataBuffer.h>
#include "VidyoMediaFormats.h"
#include "VidyoForwardDecl.h"

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: VidyoTimeRange}
	{parent: VidyoVideoFrameIntervalRange}
	{description: A time range class used to represent a range of time intervals.}
	{member: 
 		{name: begin}
		{type: LmiTime}
 		{description: The first time interval of the range.}}
 	{member: 
 		{name: end}
		{type: LmiTime}
 		{description: The last time interval of the range.}
	}
}
*/
typedef struct
{
	LmiTime begin;
	LmiTime end;
} VidyoTimeRange;

/**
{function visibility="private":
	{name: VidyoTimeRangeConstruct}
	{parent: VidyoTimeRange}
	{description: Constructs an VidyoTimeRange object.}
	{prototype: VidyoTimeRange* VidyoTimeRangeConstruct(VidyoTimeRange *x, LmiTime begin, LmiTime end)}
		{parameter:
		{name: x}
		{description: The VidyoTimeRange object to construct.}}
	{parameter:
		{name: begin}
		{description: The first interval of the time range.}}
	{parameter:
		{name: end}
		{description: The last interval of the time range.}}
	{return: Returns a pointer to the constructed object or NULL on failure.}
}
*/
VidyoTimeRange* VidyoTimeRangeConstruct(VidyoTimeRange *x, LmiTime begin, LmiTime end);

/**
{function visibility="private":
	{name: VidyoTimeRangeDestruct}
	{parent: VidyoTimeRange}
	{description: Destructs an VidyoTimeRange object.}
	{prototype: void VidyoTimeRangeDestruct(VidyoTimeRange *x)}
		{parameter:
		{name: x}
		{description: The VidyoTimeRange object to destruct.}
	}
}
*/
void VidyoTimeRangeDestruct(VidyoTimeRange *x);

/**
{function visibility="private":
	{name: VidyoTimeRangeConstructCopy}
	{parent: VidyoTimeRange}
	{description: Constructs an VidyoTimeRange object as a copy of another object.}
	{prototype: VidyoTimeRange* VidyoTimeRangeConstructCopy(VidyoTimeRange *x, const VidyoTimeRange *y)}
	{parameter:
		{name: x}
		{description: The VidyoTimeRange object to construct.}}
	{parameter:
		{name: y}
		{description: The VidyoTimeRange object from which the object need to be constructed.}}
	{return: Returns a pointer to the constructed object or NULL on failure.}
}
*/
VidyoTimeRange* VidyoTimeRangeConstructCopy(VidyoTimeRange *x, const VidyoTimeRange *y);

/**
{function visibility="private":
	{name: VidyoTimeRangeAssign}
	{parent: VidyoTimeRange}
	{description: Assigns an VidyoTimeRange object from another object.}
	{prototype: VidyoTimeRange* VidyoTimeRangeAssign(VidyoTimeRange *x, const VidyoTimeRange *y)}
	{parameter:
		{name: x}
		{description: The VidyoTimeRange object to assign.}}
	{parameter:
		{name: y}
		{description: The VidyoTimeRange object from which the object need to be assigned.}}
	{return: Returns a pointer to the assigned object or NULL on failure.}
}
*/
VidyoTimeRange* VidyoTimeRangeAssign(VidyoTimeRange *x, const VidyoTimeRange *y);

/**
{function visibility="private":
	{name: VidyoTimeRangeSwap}
	{parent: VidyoTimeRange}
	{description: Swaps an VidyoTimeRange object with another VidyoTimeRange object.}
	{prototype: void VidyoTimeRangeSwap(VidyoTimeRange *x, VidyoTimeRange *y)}
	{parameter:
		{name: x}
		{description: A VidyoTimeRange object to swap.}}
	{parameter:
		{name: y}
		{description: A VidyoTimeRange object to swap.}}
}
*/
void VidyoTimeRangeSwap(VidyoTimeRange *x, VidyoTimeRange *y);

/**
{function visibility="private":
	{name: VidyoTimeRangeEqual}
	{parent: VidyoTimeRange}
	{description: Determines the equality of two VidyoTimeRange objects.}
	{prototype: LmiBool VidyoTimeRangeEqual(const VidyoTimeRange *x, const VidyoTimeRange *y)}
	{parameter:
		{name: x}
		{description: The VidyoTimeRange object.}}
	{parameter:
		{name: y}
		{description: The VidyoTimeRange object.}}
	{return: Returns LMI_TRUE if equal or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoTimeRangeEqual(const VidyoTimeRange *x, const VidyoTimeRange *y);

/**
{function visibility="private":
	{name: VidyoTimeRangeLess}
	{parent: VidyoTimeRange}
	{description: Determines whether an VidyoTimeRange object is less than another VidyoTimeRange object.}
	{prototype: LmiBool VidyoTimeRangeLess(const VidyoTimeRange *x, const VidyoTimeRange *y)}
	{parameter:
		{name: x}
		{description: The VidyoTimeRange object.}}
	{parameter:
		{name: y}
		{description: The VidyoTimeRange object.}}
	{return: Returns LMI_TRUE if less or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoTimeRangeLess(const VidyoTimeRange *x, const VidyoTimeRange *y);


/**
{function visibility="private":
	{name: VidyoTimeRangeBegin}
	{parent: VidyoTimeRange}
	{description: Gets the first value of the time range.}
	{prototype: LmiTime VidyoTimeRangeBegin(const VidyoTimeRange *x)}
	{parameter:
		{name: x}
		{description: The VidyoTimeRange object.}}
	{return: Returns the first value of the time range.}
}
*/
LmiTime VidyoTimeRangeBegin(const VidyoTimeRange *x);

/**
{function visibility="private":
	{name: VidyoTimeRangeEnd}
	{parent: VidyoTimeRange}
	{description: Gets the last value of the time range.}
	{prototype: LmiTime VidyoTimeRangeEnd(const VidyoTimeRange *x)}
	{parameter:
		{name: x}
		{description: The VidyoTimeRange object.}}
	{return: Returns the last value of the time range.}
}
*/
LmiTime VidyoTimeRangeEnd(const VidyoTimeRange *x);


/**
{callback visibility="private":
	{name: VidyoMediaFormatLessCallback}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Compare two media formats for less than equality.}
	{prototype: LmiBool (*VidyoMediaFormatLessCallback)(const VidyoMediaFormat* x, const VidyoMediaFormat* y)}
	{parameter:
		{name: x}
		{description: A pointer to a VidyoMediaFormat object to compare for less than inequality.}
	}
	{parameter:
		{name: y}
		{description: A pointer to a VidyoMediaFormat object to compare for less than inequality.}
	}
	{return: Returns LMI_TRUE if {code:x} is less then {code:y} or LMI_FALSE otherwise.}
}
*/
typedef LmiBool(*VidyoMediaFormatLessCallback)(const VidyoMediaFormat* x, const VidyoMediaFormat* y);


/**
{type:
	{name: VidyoVideoFrameIntervalRange}
	{parent: VidyoVideoCapability}
	{description: Represents frame interval range and media formats supported by that range.}
	{member:
		{name: range}
		{type: VidyoTimeRange}
		{description: }
	}
	{member:
		{name: step}
		{type: LmiTime}
		{description: }
	}
	{member:
		{name: formats}
		{type: LmiVector(VidyoMediaFormat)}
		{description: }
	}
}
*/
typedef struct{
	LmiAllocator* a;
	VidyoTimeRange range;
	LmiTime step;
	LmiVector(VidyoMediaFormat) formats;
}VidyoVideoFrameIntervalRange;


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeConstructDefault}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Constructs an empty frame interval range.}
	{prototype: VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeConstructDefault(VidyoVideoFrameIntervalRange* x, LmiAllocator* a)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: a}
		{description: An allocator.}
	}
	{return: Returns {code:x} on success or NULL on failure.}
}
*/
VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeConstructDefault(VidyoVideoFrameIntervalRange* x, LmiAllocator* a);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeConstruct}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Constructs a frame interval range.}
	{prototype: VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeConstruct(VidyoVideoFrameIntervalRange* x, LmiTime maxInterval, LmiTime minInterval, LmiTime step, const LmiVector(VidyoMediaFormat)* formats, LmiAllocator* a)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: maxInterval}
		{description: The maximum interval (lowest frame rate) of the frame interval range.}
	}
	{parameter:
		{name: minInterval}
		{description: The minimum interval (highest frame rate) of the frame interval range.}
	}
	{parameter:
		{name: step}
		{description: The granualarity of the steps between the maximum and minimum interval.}
	}
	{parameter:
		{name: formats}
		{description: The list of formats supported by the frame interval range.}
	}
	{parameter:
		{name: a}
		{description: An allocator.}
	}
	{return: Returns {code:x} on success or NULL on failure.}
}
*/
VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeConstruct(VidyoVideoFrameIntervalRange* x, LmiTime maxInterval, LmiTime minInterval, LmiTime step, const LmiVector(VidyoMediaFormat)* formats, LmiAllocator* a);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeConstructCopy}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Construct a frame interval range from another frame interval range.}
	{prototype: VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeConstructCopy(VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: y}
		{description: The other frame interval range.}
	}
	{return: Returns {code:x} on success or NULL on failure.}
}
*/
VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeConstructCopy(VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeDestruct}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Destructs a frame interval range.}
	{prototype: void VidyoVideoFrameIntervalRangeDestruct(VidyoVideoFrameIntervalRange* x)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
}
*/
void VidyoVideoFrameIntervalRangeDestruct(VidyoVideoFrameIntervalRange* x);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeAssign}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Assigns one frame interval range to another frame interval range.}
	{prototype: VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeAssign(VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: y}
		{description: The other frame interval range.}
	}
	{return: Returns {code:x} on success or NULL on failure.}
}
*/
VidyoVideoFrameIntervalRange* VidyoVideoFrameIntervalRangeAssign(VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeEqual}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Compares two frame interval ranges for equality.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeEqual(const VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y)}
	{parameter:
		{name: x}
		{description: A frame interval range.}
	}
	{parameter:
		{name: y}
		{description: A frame interval range.}
	}
	{return: Returns LMI_TRUE if the frame interval ranges are equal or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoFrameIntervalRangeEqual(const VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeLess}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Compares two frame interval ranges for less-than equality.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeLess(const VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y)}
	{parameter:
		{name: x}
		{description: A frame interval range.}
	}
	{parameter:
		{name: y}
		{description: A frame interval range.}
	}
	{return: Returns LMI_TRUE if the first frame interval range is less than the second or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoFrameIntervalRangeLess(const VidyoVideoFrameIntervalRange* x, const VidyoVideoFrameIntervalRange* y);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeSwap}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Swap two frame interval ranges.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeSwap(VidyoVideoFrameIntervalRange* x, VidyoVideoFrameIntervalRange* y)}
	{parameter:
		{name: x}
		{description: A frame interval range.}
	}
	{parameter:
		{name: y}
		{description: A frame interval range.}
	}
	{return: Returns LMI_TRUE if the successful or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoFrameIntervalRangeSwap(VidyoVideoFrameIntervalRange* x, VidyoVideoFrameIntervalRange* y);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeGetMinimum}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Gets the minimum interval (highest frame rate) of the frame interval range.}
	{prototype: LmiTime VidyoVideoFrameIntervalRangeGetMinimum(const VidyoVideoFrameIntervalRange* x)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{return: Returns the minimum interval (highest frame rate) of the frame interval range.}
}
*/
LmiTime VidyoVideoFrameIntervalRangeGetMinimum(const VidyoVideoFrameIntervalRange* x);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeGetMaximum}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Gets the maximum interval (lowest frame rate) of the frame interval range.}
	{prototype: LmiTime VidyoVideoFrameIntervalRangeGetMaximum(const VidyoVideoFrameIntervalRange* x)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{return: Returns the maximum interval (lowest frame rate) of the frame interval range.}
}
*/
LmiTime VidyoVideoFrameIntervalRangeGetMaximum(const VidyoVideoFrameIntervalRange* x);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeGetTimeRange}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Gets the time range of the frame interval range.}
	{prototype: const VidyoTimeRange* VidyoVideoFrameIntervalRangeGetTimeRange(const VidyoVideoFrameIntervalRange* x)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{return: Returns apointer to the time range of the frame interval range.}
}
*/
const VidyoTimeRange* VidyoVideoFrameIntervalRangeGetTimeRange(const VidyoVideoFrameIntervalRange* x);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeGetStep}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Gets the granularity of the steps between the minimum and maximum of the frame interval range.}
	{prototype: LmiTime VidyoVideoFrameIntervalRangeGetStep(const VidyoVideoFrameIntervalRange* x)}
		{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{return: Returns the granularity of the steps between the minimum and maximum of the frame interval range.}
}
*/
LmiTime VidyoVideoFrameIntervalRangeGetStep(const VidyoVideoFrameIntervalRange* x);


/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeGetFormats}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Gets the list of formats supported by the frame interval range.}
	{prototype: const LmiVector(VidyoMediaFormat)* VidyoVideoFrameIntervalRangeGetFormats(const VidyoVideoFrameIntervalRange* x)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{return: Returns a pointer to a vector of formats supported by the frame interval range.}
}
*/
const LmiVector(VidyoMediaFormat)* VidyoVideoFrameIntervalRangeGetFormats(const VidyoVideoFrameIntervalRange* x);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeIsFormatSupported}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Determines whether a given format is supported by the frame interval range.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeIsFormatSupported(const VidyoVideoFrameIntervalRange* x, const VidyoMediaFormat* format)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: format}
		{description: A format.}
	}
	{return: Returns LMI_TRUE if the format is supported by the frame interval range or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoFrameIntervalRangeIsFormatSupported(const VidyoVideoFrameIntervalRange* x, const VidyoMediaFormat* format);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeIsSupported}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Determines whether a given frame interval and format are supported by the frame interval range. Note that the step is not considered; only that the frame interval is in range and the format is in the list of formats the frame interval supports.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeIsSupported(const VidyoVideoFrameIntervalRange* x, LmiTime frameInterval, const VidyoMediaFormat* format)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: frameInterval}
		{description: A frame interval. If this parameter is 0.0, then the frame interval matches.}
	}
	{parameter:
		{name: format}
		{description: A format. If this parameter is NULL, then the format matches.}
	}
	{return: Returns LMI_TRUE if the frame interval and format are supported by the frame interval range or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoFrameIntervalRangeIsSupported(const VidyoVideoFrameIntervalRange* x, LmiTime frameInterval, const VidyoMediaFormat* format);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeIsSupportedWithFrameRate}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Determines whether a given frame rate and format are supported by the frame interval range. Note that the step is not considered; only that the frame rate is in range and the format is in the list of formats the frame interval supports.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeIsSupportedWithFrameRate(const VidyoVideoFrameIntervalRange* x, LmiFloat64 frameRate, const VidyoMediaFormat* format)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: frameRate}
		{description: A frame rate. If this parameter is 0.0, then the frame rate matches.}
	}
	{parameter:
		{name: format}
		{description: A format. If this parameter is NULL, then the format matches.}
	}
	{return: Returns LMI_TRUE if the frame rate and format are supported by the frame interval range or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoFrameIntervalRangeIsSupportedWithFrameRate(const VidyoVideoFrameIntervalRange* x, LmiFloat64 frameRate, const VidyoMediaFormat* format);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeAddFormat}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Adds a media format to the frame interval range and orders the resulting set by {code:less}.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeAddFormat(VidyoVideoFrameIntervalRange* x, const VidyoMediaFormat* format, VidyoMediaFormatLessCallback less)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: format}
		{description: The format to add.}
	}
	{parameter:
		{name: less}
		{description: A function pointer to order the resulting formats by.}
	}
	{return: }
}
*/
LmiBool VidyoVideoFrameIntervalRangeAddFormat(VidyoVideoFrameIntervalRange* x, const VidyoMediaFormat* format, VidyoMediaFormatLessCallback less);

/**
{function visibility="private":
	{name: VidyoVideoFrameIntervalRangeAddFormats}
	{parent: VidyoVideoFrameIntervalRange}
	{description: Adds a set of media formats to the frame interval range and orders the resulting set by {code:less}.}
	{prototype: LmiBool VidyoVideoFrameIntervalRangeAddFormats(VidyoVideoFrameIntervalRange* x, const LmiVector(VidyoMediaFormat)* formats, VidyoMediaFormatLessCallback less)}
	{parameter:
		{name: x}
		{description: The frame interval range.}
	}
	{parameter:
		{name: formats}
		{description: The formats to add.}
	}
	{parameter:
		{name: less}
		{description: A function pointer to order the resulting formats by.}
	}
	{return: }
}
*/
LmiBool VidyoVideoFrameIntervalRangeAddFormats(VidyoVideoFrameIntervalRange* x, const LmiVector(VidyoMediaFormat)* formats, VidyoMediaFormatLessCallback less);

Declare_LmiVector(VidyoVideoFrameIntervalRange)
Declare_LmiVectorEqual(VidyoVideoFrameIntervalRange)


/**
{type:
	{name: VidyoVideoCapability}
	{parent: Device}
	{include: Lmi/VidyoClient/VidyoVideoCapability.h}
	{description: Represents the capability of a Video Source.}
	{member:
		{name: width}
		{type: LmiSizeT}
		{description:}
	}
	{member:
		{name: height}
		{type: LmiSizeT}
		{description:}
	}
	{member:
		{name: ranges}
		{type: LmiVector(VidyoVideoFrameIntervalRange)}
		{description:}
	}
}
*/
typedef struct {
	LmiAllocator* a;
	LmiSizeT width;
	LmiSizeT height;
	LmiVector(VidyoVideoFrameIntervalRange) ranges;
} VidyoVideoCapability;


/**
{function visibility="private":
	{name: VidyoVideoCapabilityConstructDefault}
	{parent: VidyoVideoCapability}
	{description: Constructs a default video source capability.}
	{prototype: VidyoVideoCapability* VidyoVideoCapabilityConstructDefault(VidyoVideoCapability* cap, LmiAllocator* a)}
	{parameter: 
		{name: cap}
		{description: The video source capability object to be constructed.}
	}
  	{parameter: 
		{name: a}
		{description: An allocator.}
	}
	{return: A pointer to the constructed video source capability object.}
}
*/
VidyoVideoCapability* VidyoVideoCapabilityConstructDefault(VidyoVideoCapability* cap, LmiAllocator* a);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityConstruct}
	{parent: VidyoVideoCapability}
	{description: Constructs a video source capability with the given parameters.}
	{prototype: VidyoVideoCapability* VidyoVideoCapabilityConstruct(VidyoVideoCapability* cap, LmiSizeT width, LmiSizeT height, const LmiVector(VidyoVideoFrameIntervalRange)* ranges, LmiAllocator* a)}
	{parameter: 
		{name: cap}
		{description: The video source capability object to be constructed.}
	}
	{parameter: 
		{name: width}
		{description: The width supported by this video source capability.}
	}
	{parameter: 
		{name: height}
		{description: The height supported by this video source capability.}
	}
	{parameter: 
		{name: ranges}
		{description: The frame interval ranges supported by this video source capability.
			The ranges should be non-overlapping and sorted.}
	}
  	{parameter: 
		{name: a}
		{description: An allocator.}
	}
	{return: A pointer to the constructed video source capability object.}
}
*/
VidyoVideoCapability* VidyoVideoCapabilityConstruct(VidyoVideoCapability* cap, LmiSizeT width, LmiSizeT height, const LmiVector(VidyoVideoFrameIntervalRange)* ranges, LmiAllocator* a);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityConstructCopy}
	{parent: VidyoVideoCapability}
	{description: Constructs a new VidyoVideoCapability as a copy of an existing one.}
	{prototype: VidyoVideoCapability* VidyoVideoCapabilityConstructCopy(VidyoVideoCapability* cap, const VidyoVideoCapability* y)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object to initialize as a copy.}
	}
	{parameter: 
		{name: y}
		{description: An existing VidyoVideoCapability object.}
	}
	{return: A pointer to the constructed object on full successful completion, otherwise {code: NULL}.}
}
*/
VidyoVideoCapability* VidyoVideoCapabilityConstructCopy(VidyoVideoCapability* cap, const VidyoVideoCapability* y);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityDestruct}
	{parent: VidyoVideoCapability}
	{description: Destructs a VidyoVideoCapability.}
	{prototype: void VidyoVideoCapabilityDestruct(VidyoVideoCapability* cap)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object to destruct.}
	}
}
*/
void VidyoVideoCapabilityDestruct(VidyoVideoCapability* cap);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityAssign}
	{parent: VidyoVideoCapability}
	{description: Assign the value of one VidyoVideoCapability to another.}
	{prototype: VidyoVideoCapability* VidyoVideoCapabilityAssign(VidyoVideoCapability* cap, const VidyoVideoCapability* y)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object to be assigned. This object
			is assumed to be already initialized.}
	}
	{parameter: 
		{name: y}
		{description: A pointer to an existing VidyoVideoCapability object.}
	}
	{return: A pointer to cap, or {code: NULL} on failure.}
}
*/
VidyoVideoCapability* VidyoVideoCapabilityAssign(VidyoVideoCapability* cap, const VidyoVideoCapability* y);

/**
{function visibility="private":
	{name: VidyoVideoCapabilitySwap}
	{parent: VidyoVideoCapability}
	{description: Swap the values of two VidyoVideoCapability objects.}
	{prototype: LmiBool VidyoVideoCapabilitySwap(VidyoVideoCapability* cap, VidyoVideoCapability* y)}
	{parameter: 
		{name: cap}
		{description: A pointer an initialized VidyoVideoCapability object.}
	}
	{parameter: 
		{name: y}
		{description: A pointer an initialized VidyoVideoCapability object.}
	}
    {return: LMI_TRUE on success, LMI_FALSE on failure.}
}
*/
LmiBool VidyoVideoCapabilitySwap(VidyoVideoCapability* cap, VidyoVideoCapability* y);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityEqual}
	{parent: VidyoVideoCapability}
	{description: Compares the values of two VidyoVideoCapability objects for equality.}
	{prototype: LmiBool VidyoVideoCapabilityEqual(const VidyoVideoCapability* cap, const VidyoVideoCapability* y)}
	{parameter: 
		{name: cap}
		{description: A pointer to the first VidyoVideoCapability object to be compared.}
	}
	{parameter: 
		{name: y}
		{description: A pointer to the second VidyoVideoCapability object to be compared.}
	}
	{return: LMI_TRUE if the objects pointed to are equal, otherwise LMI_FALSE.}
}
*/
LmiBool VidyoVideoCapabilityEqual(const VidyoVideoCapability* cap, const VidyoVideoCapability* y);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityLess}
	{parent: VidyoVideoCapability}
	{description: Finds out if the given VidyoVideoCapability object is less than the other object.}
	{prototype: LmiBool VidyoVideoCapabilityLess(const VidyoVideoCapability* cap, const VidyoVideoCapability* y)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{parameter: 
		{name: y}
		{description: A pointer to the VidyoVideoCapability object to be checked against.}
	}
	{return: Returns LMI_TRUE if the object is less, otherwise LMI_FALSE.}
}
*/
LmiBool VidyoVideoCapabilityLess(const VidyoVideoCapability* cap, const VidyoVideoCapability* y);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityGetWidth}
	{parent: VidyoVideoCapability}
	{description: Gets the width of the given VidyoVideoCapability.}
	{prototype: LmiSizeT VidyoVideoCapabilityGetWidth(const VidyoVideoCapability* cap)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{return: The width.}
}
*/
LmiSizeT VidyoVideoCapabilityGetWidth(const VidyoVideoCapability* cap);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityGetHeight}
	{parent: VidyoVideoCapability}
	{description: Get the height of the given VidyoVideoCapability.}
	{prototype: LmiSizeT VidyoVideoCapabilityGetHeight(const VidyoVideoCapability* cap)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{return: The height.}
}
*/
LmiSizeT VidyoVideoCapabilityGetHeight(const VidyoVideoCapability* cap);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityFindFrameIntervalRange}
	{parent: VidyoVideoCapability}
	{description: Find the frame interval range that supports the given frame interval and format.}
	{prototype: const VidyoVideoFrameIntervalRange* VidyoVideoCapabilityFindFrameIntervalRange(const VidyoVideoCapability* x, LmiTime frameInterval, const VidyoMediaFormat* format)}
	{parameter:
		{name: x}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{parameter:
		{name: frameInterval}
		{description: A frame rate to test. If this parameter is 0, then it matches all frame interval ranges. }
	}
	{parameter:
		{name: format}
		{description: A format to test. If this parameter is NULL, then it matches all frame interval ranges.}
	}
	{return: Returns the first matching frame interval range, or NULL if no frame interval range of the capability matches.}
}
*/
const VidyoVideoFrameIntervalRange* VidyoVideoCapabilityFindFrameIntervalRange(const VidyoVideoCapability* x, LmiTime frameInterval, const VidyoMediaFormat* format);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityFindFrameIntervalRangeWithFrameRate}
	{parent: VidyoVideoCapability}
	{description: Find the frame interval range that supports the given frame rate and format.}
	{prototype: const VidyoVideoFrameIntervalRange* VidyoVideoCapabilityFindFrameIntervalRangeWithFrameRate(const VidyoVideoCapability* x, LmiFloat64 frameRate, const VidyoMediaFormat* format)}
	{parameter:
		{name: x}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{parameter:
		{name: frameRate}
		{description: A frame rate to test. If this parameter is 0.0, then it matches all frame interval ranges. }
	}
	{parameter:
		{name: format}
		{description: A format to test. If this parameter is NULL, then it matches all frame interval ranges.}
	}
	{return: Returns the first matching frame interval range, or NULL if no frame interval range of the capability matches.}
}
*/
const VidyoVideoFrameIntervalRange* VidyoVideoCapabilityFindFrameIntervalRangeWithFrameRate(const VidyoVideoCapability* x, LmiFloat64 frameRate, const VidyoMediaFormat* format);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityIsSupported}
	{parent: VidyoVideoCapability}
	{description: Determines whether a given configuration (width, height, frame interval and format) is supported by a given VidyoVideoCapability.}
	{prototype: LmiBool VidyoVideoCapabilityIsSupported(const VidyoVideoCapability* x, LmiSizeT width, LmiSizeT height, LmiTime frameInterval, const VidyoMediaFormat* format)}
	{parameter:
		{name: x}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{parameter:
		{name: width}
		{description: The width to test.}
	}
	{parameter:
		{name: height}
		{description: The height to test.}
	}
	{parameter:
		{name: frameInterval}
		{description: A frame interval to test.}
	}
	{parameter:
		{name: format}
		{description: A format to test.}
	}
	{return: Returns LMI_TRUE if {code:frameInterval} and {code: format} is supported, or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoCapabilityIsSupported(const VidyoVideoCapability* x, LmiSizeT width, LmiSizeT height, LmiTime frameInterval, const VidyoMediaFormat* format);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityGetMinFrameInterval}
	{parent: VidyoVideoCapability}
	{description: Get the minimum frame interval of the given VidyoVideoCapability.}
	{prototype: LmiTime VidyoVideoCapabilityGetMinFrameInterval(const VidyoVideoCapability* cap)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{return: Returns the minimum frame interval.}
}
*/
LmiTime VidyoVideoCapabilityGetMinFrameInterval(const VidyoVideoCapability* cap);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityGetMaxFrameInterval}
	{parent: VidyoVideoCapability}
	{description: Get the maximum frame interval of the given VidyoVideoCapability.}
	{prototype: LmiTime VidyoVideoCapabilityGetMaxFrameInterval(const VidyoVideoCapability* cap)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{return: Returns the maximum frame interval.}
}
*/
LmiTime VidyoVideoCapabilityGetMaxFrameInterval(const VidyoVideoCapability* cap);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityGetFrameIntervalRanges}
	{parent: VidyoVideoCapability}
	{description: Get a vector of frame interval ranges supported by a given VidyoVideoCapability.  Each range is defined by a pair of frame intervals, in nanoseconds, specifying the range [{code:first}, {code:second}] of supported frame intervals.  The list is ordered by {code:first} (longest to shortest) then by {code:second} (longest to shortest).}
 	{prototype: const LmiVector(VidyoVideoFrameIntervalRange)* VidyoVideoCapabilityGetFrameIntervalRanges(const VidyoVideoCapability* cap)}
	{parameter: 
		{name: cap}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{return: Returns a pointer to vector containing a list of supported frame interval ranges.}
	{note: The range is closed. Thus, [33333333, 33333333] represents a single frame rate (~30 FPS). }
	{note: The range values are frame intervals, not frames per second. Thus, (perhaps counter-intuitively) the value of {code: first} will be greater than or equal to {code: second}. }
}
*/
const LmiVector(VidyoVideoFrameIntervalRange)* VidyoVideoCapabilityGetFrameIntervalRanges(const VidyoVideoCapability* cap);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityAddFrameIntervalRange}
	{parent: VidyoVideoCapability}
	{description: Add a frame interval range to a VidyoVideoCapability.}
	{prototype: LmiBool VidyoVideoCapabilityAddFrameIntervalRange(VidyoVideoCapability* x, const VidyoVideoFrameIntervalRange* range)}
	{parameter:
		{name: x}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{parameter:
		{name: range}
		{description: A frame interval range to add to the VidyoVideoCapability object.}
	}
	{return: Returns LMI_TRUE on success or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoCapabilityAddFrameIntervalRange(VidyoVideoCapability* x, const VidyoVideoFrameIntervalRange* range);

/**
{function visibility="private":
	{name: VidyoVideoCapabilityAddFrameIntervalRanges}
	{parent: VidyoVideoCapability}
	{description: Add frame interval ranges to a VidyoVideoCapability.}
	{prototype: LmiBool VidyoVideoCapabilityAddFrameIntervalRanges(VidyoVideoCapability* x, const LmiVector(VidyoVideoFrameIntervalRange)* ranges)}
	{parameter:
		{name: x}
		{description: A pointer to the VidyoVideoCapability object.}
	}
	{parameter:
		{name: ranges}
		{description: A vector of frame interval ranges to add to the VidyoVideoCapability object.}
	}
	{return: Returns LMI_TRUE on success or LMI_FALSE otherwise.}
}
*/
LmiBool VidyoVideoCapabilityAddFrameIntervalRanges(VidyoVideoCapability* x, const LmiVector(VidyoVideoFrameIntervalRange)* ranges);

Declare_LmiVector(VidyoVideoCapability)


LMI_END_EXTERN_C

#endif /* VIDYO_VIDEOCAPABILITY_H_ */

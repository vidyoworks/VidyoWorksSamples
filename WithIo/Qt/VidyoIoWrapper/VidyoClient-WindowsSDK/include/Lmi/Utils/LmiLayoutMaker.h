/**
{file:
	{name: LmiLayoutMaker.h}
	{description: Class for partitioning a rectangle into rectangular tiles.}
	{copyright:
		(c) 2010-2014 Vidyo, Inc.,
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
#ifndef LMI_LAYOUTMAKER_H
#define LMI_LAYOUTMAKER_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiRectangle.h>

LMI_BEGIN_EXTERN_C

#define LMI_LAYOUTMAKER_MAXTILES 32
#define LMI_LAYOUTMAKER_NUMSNAPINDICES_ ((LMI_LAYOUTMAKER_MAXTILES * (LMI_LAYOUTMAKER_MAXTILES + 1)) / 2)

struct LmiAspectRange_;

/**
{type visibility="private":
	{name: LmiLayoutMaker}
	{parent: Utils}
	{include: Lmi/Utils/LmiLayoutMaker.h}
	{description: Class for partitioning a rectangle into rectangular tiles.}
}
*/
typedef struct
{
	LmiUint aspectW;
	LmiUint aspectH;
	LmiUint minVisiblePctX;
	LmiUint minVisiblePctY;
	LmiBool equalSizes;
	LmiBool strict;
	LmiBool fill;
	LmiAllocator *alloc;
	struct LmiAspectRange_ *snapRanges[LMI_LAYOUTMAKER_NUMSNAPINDICES_];
	LmiUint numRanges[LMI_LAYOUTMAKER_NUMSNAPINDICES_];
} LmiLayoutMaker;

/**
{function visibility="private":
	{name: LmiLayoutMakerConstruct}
	{parent: LmiLayoutMaker}
	{description: Constructs an LmiLayoutMaker object. This object is used to partition a rectangle into
		smaller tiles.}
	{prototype: LmiLayoutMaker *LmiLayoutMakerConstruct(LmiLayoutMaker *layoutMaker,
		LmiUint aspectW, LmiUint aspectH, LmiUint maxCropPctX, LmiUint maxCropPctY,
		LmiBool equalSizes, LmiBool strict, LmiBool fill, LmiAllocator *alloc)}
	{parameter: {name: layoutMaker} {description: The LmiLayoutMaker object to construct.}}
	{parameter: {name: aspectW} {description: The preferred aspect ratio of the rectangular tiles that
		will be created. Specify the width component here.}}
	{parameter: {name: aspectH} {description: The preferred aspect ratio of the rectangular tiles that
		will be created. Specify the height component here.}}
	{parameter: {name: maxCropPctX} {description: Modifying the aspect ratio of the tiles may achieve
		a better fit. Specify here the maximum allowable horizontal cropping of the tiles, expressed as a
		percentage of the tile width.}}
	{parameter: {name: maxCropPctY} {description: Modifying the aspect ratio of the tiles may achieve
		a better fit. Specify here the maximum allowable vertical cropping of the tiles, expressed as a
		percentage of the tile height.}}
	{parameter: {name: equalSizes} {description: Specifies whether to prefer layouts where all preferred
		tiles are the same size and all nonpreferred tiles are the same size and the preferred tiles are
		larger than the nonpreferred tiles.}}
	{parameter: {name: strict} {description: Specifies whether to only use layouts that meet a higher
		aesthetic standard. If set to LMI_FALSE, more unusual layouts may be utilized to make better
		use of the available area.}}
	{parameter: {name: fill} {description: Specifies whether to prefer layouts that completely
		fill the input rectangle.}}
	{parameter: {name: alloc} {description: An allocator to use for miscellaneous objects.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiLayoutMaker *LmiLayoutMakerConstruct(LmiLayoutMaker *layoutMaker,
	LmiUint aspectW, LmiUint aspectH, LmiUint maxCropPctX, LmiUint maxCropPctY,
	LmiBool equalSizes, LmiBool strict, LmiBool fill, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: LmiLayoutMakerDestruct}
	{parent: LmiLayoutMaker}
	{description: Destructs an LmiLayoutMaker object.}
	{prototype: void LmiLayoutMakerDestruct(LmiLayoutMaker *layoutMaker)}
	{parameter: {name: layoutMaker} {description: The LmiLayoutMaker object to destruct.}}
}
*/
void LmiLayoutMakerDestruct(LmiLayoutMaker *layoutMaker);

/**
{function visibility="private":
	{name: LmiLayoutMakerGetLayout}
	{parent: LmiLayoutMaker}
	{description: Calculate the optimum layout for a given rectangle.}
	{prototype: LmiBool LmiLayoutMakerGetLayout(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
		LmiUint width, LmiUint height, LmiRectangle *rects, LmiUint *groupRank)}
	{parameter: {name: layoutMaker} {description: The LmiLayoutMaker object.}}
	{parameter: {name: numRects} {description: The number of rectangular partitions to create. This number
		should be no greater than LMI_LAYOUTMAKER_MAXTILES.}}
	{parameter: {name: numPreferred} {description: The number of preferred partitions. This parameter controls
		how evenly the rectangle area is divided among the different partitions. The layout maker will
		attempt to make the preferred partitions larger and the nonpreferred ones smaller.}}
	{parameter: {name: width} {description: The width of the rectangle to partition.}}
	{parameter: {name: height} {description: The height of the rectangle to partition.}}
	{parameter: {name: rects} {description: An array of rectangles. The dimensions of the rectangular
		partitions will be written into these objects. The array must contain at least numRects rectangles.}}
	{parameter: {name: groupRank} {description: An array of integers. A value will be written into this
		array for each rectangular partition such that partitions of the same size are given the same value.
		The array must contain at least numRects elements. This parameter can be NULL if group
		information is not desired.}}
	{return: A boolean indicating whether a layout was found matching the given constraints.}
}
*/
LmiBool LmiLayoutMakerGetLayout(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
	LmiUint width, LmiUint height, LmiRectangle *rects, LmiUint *groupRank);

/**
{function visibility="private":
	{name: LmiLayoutMakerGetLayoutEx}
	{parent: LmiLayoutMaker}
	{description: Calculate the optimum layout for a given rectangle.}
	{prototype: LmiBool LmiLayoutMakerGetLayoutEx(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
		const LmiRectangle *inRect, LmiBool yUp, LmiRectangle *rects, LmiUint *groupRank)}
	{parameter: {name: layoutMaker} {description: The LmiLayoutMaker object.}}
	{parameter: {name: numRects} {description: The number of rectangular partitions to create. This number
		should be no greater than LMI_LAYOUTMAKER_MAXTILES.}}
	{parameter: {name: numPreferred} {description: The number of preferred partitions. This parameter controls
		how evenly the rectangle area is divided among the different partitions. The layout maker will
		attempt to make the preferred partitions larger and the nonpreferred ones smaller.}}
	{parameter: {name: inRect} {description: The rectangle to partition.}}
	{parameter: {name: yUp} {description: Indicates whether the positive y-axis of the coordinate system in use
		points upward.}}
	{parameter: {name: rects} {description: An array of rectangles. The dimensions of the rectangular
		partitions will be written into these objects. The array must contain at least numRects rectangles.}}
	{parameter: {name: groupRank} {description: An array of integers. A value will be written into this
		array for each rectangular partition such that partitions of the same size are given the same value.
		The array must contain at least numRects elements. This parameter can be NULL if group
		information is not desired.}}
	{return: A boolean indicating whether a layout was found matching the given constraints.}
}
*/
LmiBool LmiLayoutMakerGetLayoutEx(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
	const LmiRectangle *inRect, LmiBool yUp, LmiRectangle *rects, LmiUint *groupRank);

#define LMI_LAYOUTMAKER_MAXMIXEDTILES 4

/**
{function visibility="private":
	{name: LmiLayoutMakerGetMixedLayout}
	{parent: LmiLayoutMaker}
	{description: Calculate a layout with partitions of different aspect ratios.}
	{prototype: void LmiLayoutMakerGetMixedLayout(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
		LmiUint width, LmiUint height, const LmiFloat64 *aspects, const LmiRectangle *curPos, LmiRectangle *rects)}
	{parameter: {name: layoutMaker} {description: The LmiLayoutMaker object.}}
	{parameter: {name: numRects} {description: The number of rectangular partitions to create. This number
		should be no greater than LMI_LAYOUTMAKER_MAXMIXEDTILES.}}
	{parameter: {name: numPreferred} {description: The number of preferred partitions. This parameter controls
		how evenly the rectangle area is divided among the different partitions. The layout maker will
		attempt to make the preferred partitions larger and the nonpreferred ones smaller.}}
	{parameter: {name: width} {description: The width of the rectangle to partition.}}
	{parameter: {name: height} {description: The height of the rectangle to partition.}}
	{parameter: {name: aspects} {description: An array containing the desired aspect ratios for the partitions. This
		array must contain at least numRects elements.}}
	{parameter: {name: curPos} {description: An array containing the current positions of the partitions.
		This will be used to preserve the relative positioning of the partitions when possible, to prevent
		partitions from swapping places unnecessarily. This parameter is optional. Pass NULL to ignore the current
		positions of the partitions when creating the layout.}}
	{parameter: {name: rects} {description: An array of rectangles. The dimensions of the rectangular
		partitions will be written into these objects. The array must contain at least numRects rectangles.}}
}
*/
void LmiLayoutMakerGetMixedLayout(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
	LmiUint width, LmiUint height, const LmiFloat64 *aspects, const LmiRectangle *curPos, LmiRectangle *rects);

/**
{function visibility="private":
	{name: LmiLayoutMakerSnapResize}
	{parent: LmiLayoutMaker}
	{description: This function can be used to modify prospective window sizes such that
		the resulting size will generate layouts with no background exposed.}
	{prototype: void LmiLayoutMakerSnapResize(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
		LmiUint *width, LmiUint *height, LmiUint curWidth, LmiUint curHeight,
		LmiUint minWidth, LmiUint minHeight, LmiUint maxWidth, LmiUint maxHeight,
		LmiBool keepWidth, LmiBool keepHeight)}
	{parameter: {name: layoutMaker} {description: The LmiLayoutMaker object.}}
	{parameter: {name: numRects} {description: The current number of partitions in the window.}}
	{parameter: {name: numPreferred} {description: The current number of preferred participants.}}
	{parameter: {name: width} {description: The width the user is trying to resize the window to.
		This variable will be modified to contain the width that the window should actually be resized to.}}
	{parameter: {name: height} {description: The height the user is trying to resize the window to.
		This variable will be modified to contain the height that the window should actually be resized to.}}
	{parameter: {name: curWidth} {description: The current width of the window.}}
	{parameter: {name: curHeight} {description: The current height of the window.}}
	{parameter: {name: minWidth} {description: The minimum width that the window can be resized to.}}
	{parameter: {name: minHeight} {description: The minimum height that the window can be resized to.}}
	{parameter: {name: maxWidth} {description: The maximum width that the window can be resized to.}}
	{parameter: {name: maxHeight} {description: The maximum height that the window can be resized to.}}
	{parameter: {name: keepWidth} {description: Maintain the prospective width if possible, and modify the height.
		This would typically be set to LMI_TRUE when the window is being resized horizontally.}}
	{parameter: {name: keepHeight} {description: Maintain the prospective height if possible, and modify the width.
		This would typically be set to LMI_TRUE when the window is being resized vertically. This parameter is
		ignored if keepWidth is LMI_TRUE.}}
}
*/
void LmiLayoutMakerSnapResize(LmiLayoutMaker *layoutMaker, LmiUint numRects, LmiUint numPreferred,
	LmiUint *width, LmiUint *height, LmiUint curWidth, LmiUint curHeight,
	LmiUint minWidth, LmiUint minHeight, LmiUint maxWidth, LmiUint maxHeight,
	LmiBool keepWidth, LmiBool keepHeight);

LMI_END_EXTERN_C

#endif

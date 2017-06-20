/**
{file:
	{name: LmiRectangle.h}
	{description: Rectangular region on an integer grid.}
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
#ifndef LMI_RECTANGLE_H
#define LMI_RECTANGLE_H

#include <Lmi/Utils/LmiTypes.h>

#if defined(LMI_HAVE_CREATEWINDOWEXA)
#	if defined(LMI_HAVE_WINSOCK2_H)
#		include <winsock2.h>
#	elif defined(LMI_HAVE_WINDOWS_H)
#		include <windows.h>
#	endif
#endif

LMI_BEGIN_EXTERN_C

/**
{type:
	{name: LmiRectangle}
	{parent: Utils}
	{include: Lmi/Utils/LmiRectangle.h}
	{description: Defines a rectangular region on an integer grid. This is useful
		for representing rectangular regions of pixels on a screen.}
}
*/
typedef struct
{
	LmiInt x0, y0, x1, y1;
} LmiRectangle;

/**
{function:
	{name: LmiRectangleConstructDefault}
	{parent: LmiRectangle}
	{description: Constructs a rectangle.}
	{prototype: LmiRectangle* LmiRectangleConstructDefault(LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object to construct.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleConstructDefault(LmiRectangle *r);

/**
{function:
	{name: LmiRectangleConstruct}
	{parent: LmiRectangle}
	{description: Constructs a rectangle by specifying the minimum values for each coordinate, and also the rectangle's width and height.}
	{prototype: LmiRectangle* LmiRectangleConstruct(LmiRectangle* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object to construct.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
	{parameter: {name: width} {description: The width.}}
	{parameter: {name: height} {description: The height.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
	{note: equivalent to LmiRectangleConstructMinAndSize}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleConstruct(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
{function:
	{name: LmiRectangleConstructMinAndMax}
	{parent: LmiRectangle}
	{description: Constructs a rectangle by specifying the minimum and maximum values for each coordinate.}
	{prototype: LmiRectangle* LmiRectangleConstructMinAndMax(LmiRectangle* r, LmiInt xMin, LmiInt yMin, LmiInt xMax, LmiInt yMax)}
	{parameter: {name: r} {description: The rectangle object to construct.}}
	{parameter: {name: xMin} {description: The minimum x coordinate.}}
	{parameter: {name: yMin} {description: The minimum y coordinate.}}
	{parameter: {name: xMax} {description: The maximum x coordinate.}}
	{parameter: {name: yMax} {description: The maximum y coordinate.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleConstructMinAndMax(LmiRectangle *r, LmiInt xMin, LmiInt yMin, LmiInt xMax, LmiInt yMax);

/**
{function:
	{name: LmiRectangleConstructMinAndSize}
	{parent: LmiRectangle}
	{description: Constructs a rectangle by specifying the minimum values for each coordinate, and also the rectangle's width and height.}
	{prototype: LmiRectangle* LmiRectangleConstructMinAndSize(LmiRectangle* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object to construct.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
	{parameter: {name: width} {description: The width.}}
	{parameter: {name: height} {description: The height.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleConstructMinAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
{function:
	{name: LmiRectangleConstructMaxAndSize}
	{parent: LmiRectangle}
	{description: Constructs a rectangle by specifying the maximum values for each coordinate, and also the rectangle's width and height.}
	{prototype: LmiRectangle* LmiRectangleConstructMaxAndSize(LmiRectangle* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object to construct.}}
	{parameter: {name: x} {description: The maximum x coordinate.}}
	{parameter: {name: y} {description: The maximum y coordinate.}}
	{parameter: {name: width} {description: The width.}}
	{parameter: {name: height} {description: The height.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleConstructMaxAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
{function:
	{name: LmiRectangleConstructCopy}
	{parent: LmiRectangle}
	{description: Constructs an LmiRectangle object as a copy of another.}
	{prototype: LmiRectangle* LmiRectangleConstructCopy(LmiRectangle* d, const LmiRectangle* s)}
	{parameter: {name: d} {description: The rectangle to construct.}}
	{parameter: {name: s} {description: The rectangle to copy.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleConstructCopy(LmiRectangle *d, const LmiRectangle *s);

/**
{function:
	{name: LmiRectangleDestruct}
	{parent: LmiRectangle}
	{description: Destructs an LmiRectangle object.}
	{prototype: void LmiRectangleDestruct(LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleDestruct(LmiRectangle *r);

/**
{function:
	{name: LmiRectangleAssign}
	{parent: LmiRectangle}
	{description: Assigns one LmiRectangle object the value of another.}
	{prototype: LmiRectangle* LmiRectangleAssign(LmiRectangle* d, const LmiRectangle* s)}
	{parameter: {name: d} {description: The destination object.}}
	{parameter: {name: s} {description: The source object.}}
	{return: A pointer to the destination object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiRectangle *LmiRectangleAssign(LmiRectangle *d, const LmiRectangle *s);

/**
{function:
	{name: LmiRectangleEqual}
	{parent: LmiRectangle}
	{description: Checks whether two rectangles are equivalent, meaning they
		have the same size and location.}
	{prototype: LmiBool LmiRectangleEqual(const LmiRectangle* a, const LmiRectangle* b)}
	{parameter: {name: a} {description: The first rectangle object.}}
	{parameter: {name: b} {description: The second rectangle object.}}
	{return: A boolean indicating whether the rectangles are equivalent.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiRectangleEqual(const LmiRectangle *a, const LmiRectangle *b);

LMI_INLINE_DECLARATION void LmiRectangleSetMinX(LmiRectangle *r, LmiInt x);
LMI_INLINE_DECLARATION void LmiRectangleSetMinY(LmiRectangle *r, LmiInt y);

/**
{function:
	{name: LmiRectangleSetMin}
	{parent: LmiRectangle}
	{description: Changes the minimum values for each coordinate. The maximum values are left unchanged.
		If new minimum values are provided, the size of the rectangle will change.}
	{prototype: void LmiRectangleSetMin(LmiRectangle* r, LmiInt x, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetMin(LmiRectangle *r, LmiInt x, LmiInt y);

LMI_INLINE_DECLARATION void LmiRectangleSetMaxX(LmiRectangle *r, LmiInt x);
LMI_INLINE_DECLARATION void LmiRectangleSetMaxY(LmiRectangle *r, LmiInt y);

/**
{function:
	{name: LmiRectangleSetMax}
	{parent: LmiRectangle}
	{description: Changes the maximum values for each coordinate. The minimum values are left unchanged.
		If new maximum values are provided, the size of the rectangle will change.}
	{prototype: void LmiRectangleSetMax(LmiRectangle* r, LmiInt x, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The maximum x coordinate.}}
	{parameter: {name: y} {description: The maximum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetMax(LmiRectangle *r, LmiInt x, LmiInt y);

LMI_INLINE_DECLARATION void LmiRectangleMoveToMinX(LmiRectangle *r, LmiInt x);
LMI_INLINE_DECLARATION void LmiRectangleMoveToMinY(LmiRectangle *r, LmiInt y);

/**
{function:
	{name: LmiRectangleMoveToMin}
	{parent: LmiRectangle}
	{description: Moves a rectangle without changing its size. Specify the new minimum values for each coordinate.}
	{prototype: void LmiRectangleMoveToMin(LmiRectangle* r, LmiInt x, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleMoveToMin(LmiRectangle *r, LmiInt x, LmiInt y);

LMI_INLINE_DECLARATION void LmiRectangleMoveToMaxX(LmiRectangle *r, LmiInt x);
LMI_INLINE_DECLARATION void LmiRectangleMoveToMaxY(LmiRectangle *r, LmiInt y);

/**
{function:
	{name: LmiRectangleMoveToMax}
	{parent: LmiRectangle}
	{description: Moves a rectangle without changing its size. Specify the new maximum values for each coordinate.}
	{prototype: void LmiRectangleMoveToMax(LmiRectangle* r, LmiInt x, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The maximum x coordinate.}}
	{parameter: {name: y} {description: The maximum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleMoveToMax(LmiRectangle *r, LmiInt x, LmiInt y);

/**
{function:
	{name: LmiRectangleMoveTo}
	{parent: LmiRectangle}
	{description: Moves a rectangle without changing its size. Specify the new minimum values for each coordinate.}
	{prototype: void LmiRectangleMoveTo(LmiRectangle *r, LmiInt x, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
	{note: equivalent to LmiRectangleMoveToMin}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleMoveTo(LmiRectangle *r, LmiInt x, LmiInt y);

LMI_INLINE_DECLARATION void LmiRectangleResizeFromMinX(LmiRectangle *r, LmiUint width);
LMI_INLINE_DECLARATION void LmiRectangleResizeFromMinY(LmiRectangle *r, LmiUint height);

/**
{function:
	{name: LmiRectangleResizeFromMin}
	{parent: LmiRectangle}
	{description: Resizes a rectangle, keeping the minimum values for each coordinate unchanged.
		The maximum values are adjusted as necessary.}
	{prototype: void LmiRectangleResizeFromMin(LmiRectangle* r, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: width} {description: The new width.}}
	{parameter: {name: height} {description: The new height.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleResizeFromMin(LmiRectangle *r, LmiUint width, LmiUint height);

LMI_INLINE_DECLARATION void LmiRectangleResizeFromMaxX(LmiRectangle *r, LmiUint width);
LMI_INLINE_DECLARATION void LmiRectangleResizeFromMaxY(LmiRectangle *r, LmiUint height);

/**
{function:
	{name: LmiRectangleResizeFromMax}
	{parent: LmiRectangle}
	{description: Resizes a rectangle, keeping the maximum values for each coordinate unchanged.
		The minimum values are adjusted as necessary.}
	{prototype: void LmiRectangleResizeFromMax(LmiRectangle* r, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: width} {description: The new width.}}
	{parameter: {name: height} {description: The new height.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleResizeFromMax(LmiRectangle *r, LmiUint width, LmiUint height);

LMI_INLINE_DECLARATION void LmiRectangleSetMinAndMaxX(LmiRectangle *r, LmiInt xMin, LmiInt xMax);
LMI_INLINE_DECLARATION void LmiRectangleSetMinAndMaxY(LmiRectangle *r, LmiInt yMin, LmiInt yMax);

/**
{function:
	{name: LmiRectangleSetMinAndMax}
	{parent: LmiRectangle}
	{description: Modifies a rectangle by specifying the minimum and maximum values for each coordinate.}
	{prototype: void LmiRectangleSetMinAndMax(LmiRectangle* r, LmiInt xMin, LmiInt yMin, LmiInt xMax, LmiInt yMax)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: xMin} {description: The minimum x coordinate.}}
	{parameter: {name: yMin} {description: The minimum y coordinate.}}
	{parameter: {name: xMax} {description: The maximum x coordinate.}}
	{parameter: {name: yMax} {description: The maximum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetMinAndMax(LmiRectangle *r, LmiInt xMin, LmiInt yMin, LmiInt xMax, LmiInt yMax);

LMI_INLINE_DECLARATION void LmiRectangleSetMinAndSizeX(LmiRectangle *r, LmiInt x, LmiUint width);
LMI_INLINE_DECLARATION void LmiRectangleSetMinAndSizeY(LmiRectangle *r, LmiInt y, LmiUint height);

/**
{function:
	{name: LmiRectangleSetMinAndSize}
	{parent: LmiRectangle}
	{description: Modifies a rectangle by specifying the minimum values for each coordinate, and also the rectangle's width and height.}
	{prototype: void LmiRectangleSetMinAndSize(LmiRectangle* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
	{parameter: {name: width} {description: The width.}}
	{parameter: {name: height} {description: The height.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetMinAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

LMI_INLINE_DECLARATION void LmiRectangleSetMaxAndSizeX(LmiRectangle *r, LmiInt x, LmiUint width);
LMI_INLINE_DECLARATION void LmiRectangleSetMaxAndSizeY(LmiRectangle *r, LmiInt y, LmiUint height);

/**
{function:
	{name: LmiRectangleSetMaxAndSize}
	{parent: LmiRectangle}
	{description: Modifies a rectangle by specifying the maximum values for each coordinate, and also the rectangle's width and height.}
	{prototype: void LmiRectangleSetMaxAndSize(LmiRectangle* r, LmiInt x, LmiInt y, LmiUint width, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The maximum x coordinate.}}
	{parameter: {name: y} {description: The maximum y coordinate.}}
	{parameter: {name: width} {description: The width.}}
	{parameter: {name: height} {description: The height.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetMaxAndSize(LmiRectangle *r, LmiInt x, LmiInt y, LmiUint width, LmiUint height);

/**
{function:
	{name: LmiRectangleGetMinX}
	{parent: LmiRectangle}
	{description: Gets the minimum x coordinate for a rectangle.}
	{prototype: LmiInt LmiRectangleGetMinX(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The minimum x coordinate.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetMinX(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetMinY}
	{parent: LmiRectangle}
	{description: Gets the minimum y coordinate for a rectangle.}
	{prototype: LmiInt LmiRectangleGetMinY(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The minimum y coordinate.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetMinY(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetMaxX}
	{parent: LmiRectangle}
	{description: Gets the maximum x coordinate for a rectangle.}
	{prototype: LmiInt LmiRectangleGetMaxX(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The maximum x coordinate.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetMaxX(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetMaxY}
	{parent: LmiRectangle}
	{description: Gets the maximum y coordinate for a rectangle.}
	{prototype: LmiInt LmiRectangleGetMaxY(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The maximum y coordinate.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetMaxY(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetLeft}
	{parent: LmiRectangle}
	{description: Gets the x coordinate of the left edge of a rectangle.}
	{prototype: LmiInt LmiRectangleGetLeft(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The x coordinate of the left edge.}
	{note: equivalent to LmiRectangleGetMinX}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetLeft(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetTop}
	{parent: LmiRectangle}
	{description: Gets the minimum y coordinate for a rectangle.
		When the rectangle represents a region in a coordinate system whose y values increase
		as you move downward, this value corresponds to the top edge of the rectangle.}
	{prototype: LmiInt LmiRectangleGetTop(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The minimum y coordinate.}
	{note: equivalent to LmiRectangleGetMinY}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetTop(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetRight}
	{parent: LmiRectangle}
	{description: Gets the x coordinate of the right edge of a rectangle.}
	{prototype: LmiInt LmiRectangleGetRight(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The x coordinate of the right edge.}
	{note: equivalent to LmiRectangleGetMaxX}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetRight(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetBottom}
	{parent: LmiRectangle}
	{description: Gets the maximum y coordinate for a rectangle.
		When the rectangle represents a region in a coordinate system whose y values increase
		as you move downward, this value corresponds to the bottom edge of the rectangle.}
	{prototype: LmiInt LmiRectangleGetBottom(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The maximum y coordinate.}
	{note: equivalent to LmiRectangleGetMaxY}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiRectangleGetBottom(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleSetLeft}
	{parent: LmiRectangle}
	{description: Changes the minimum x coordinate. The maximum x coordinate is left unchanged.
		If a new value is provided, the width of the rectangle will change.}
	{prototype: void  LmiRectangleSetLeft(LmiRectangle* r, LmiInt x)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The minimum x coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetLeft(LmiRectangle *r, LmiInt x);

/**
{function:
	{name: LmiRectangleSetTop}
	{parent: LmiRectangle}
	{description: Changes the minimum y coordinate. The maximum y coordinate is left unchanged.
		If a new value is provided, the height of the rectangle will change.}
	{prototype: void LmiRectangleSetTop(LmiRectangle* r, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: y} {description: The minimum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetTop(LmiRectangle *r, LmiInt y);

/**
{function:
	{name: LmiRectangleSetRight}
	{parent: LmiRectangle}
	{description: Changes the maximum x coordinate. The minimum x coordinate is left unchanged.
		If a new value is provided, the width of the rectangle will change.}
	{prototype: void LmiRectangleSetRight(LmiRectangle* r, LmiInt x)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The maximum x coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetRight(LmiRectangle *r, LmiInt x);

/**
{function:
	{name: LmiRectangleSetBottom}
	{parent: LmiRectangle}
	{description: Changes the maximum y coordinate. The minimum y coordinate is left unchanged.
		If a new value is provided, the height of the rectangle will change.}
	{prototype: void LmiRectangleSetBottom(LmiRectangle* r, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: y} {description: The maximum y coordinate.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetBottom(LmiRectangle *r, LmiInt y);

/**
{function:
	{name: LmiRectangleGetWidth}
	{parent: LmiRectangle}
	{description: Gets the width of a rectangle.}
	{prototype: LmiUint LmiRectangleGetWidth(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The width.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiRectangleGetWidth(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleGetHeight}
	{parent: LmiRectangle}
	{description: Gets the height of a rectangle.}
	{prototype: LmiUint LmiRectangleGetHeight(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The height.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiRectangleGetHeight(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleSetWidth}
	{parent: LmiRectangle}
	{description: Changes the width of a rectangle, keeping the minimum x coordinate unchanged.
		The maximum x coordinate is adjusted as necessary.}
	{prototype: void LmiRectangleSetWidth(LmiRectangle* r, LmiUint width)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: width} {description: The new width.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetWidth(LmiRectangle *r, LmiUint width);

/**
{function:
	{name: LmiRectangleSetHeight}
	{parent: LmiRectangle}
	{description: Changes the height of a rectangle, keeping the minimum y coordinate unchanged.
		The maximum y coordinate is adjusted as necessary.}
	{prototype: void LmiRectangleSetHeight(LmiRectangle* r, LmiUint height)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: height} {description: The new height.}}
}
*/
LMI_INLINE_DECLARATION void LmiRectangleSetHeight(LmiRectangle *r, LmiUint height);

/**
{function:
	{name: LmiRectangleGetArea}
	{parent: LmiRectangle}
	{description: Gets the area of a rectangle.}
	{prototype: LmiUint LmiRectangleGetArea(const LmiRectangle* r)}
	{parameter: {name: r} {description: The rectangle object.}}
	{return: The area.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiRectangleGetArea(const LmiRectangle *r);

/**
{function:
	{name: LmiRectangleContains}
	{parent: LmiRectangle}
	{description: Determine if a point is located within a rectangle. Note that points lying on the
		rectangle's maximum x and y coordinates will be considered outside the rectangle. When the
		rectangle is used to represent a grid of pixels, this convention ensures that the proper number
		of pixels are determined to lie within the rectangle.}
	{prototype: LmiBool LmiRectangleContains(const LmiRectangle *r, LmiInt x, LmiInt y)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: x} {description: The x coordinate of the point.}}
	{parameter: {name: y} {description: The y coordinate of the point.}}
	{return: A boolean indicating if the point is within the rectangle.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiRectangleContains(const LmiRectangle *r, LmiInt x, LmiInt y);

/**
{function:
	{name: LmiRectangleIntersect}
	{parent: LmiRectangle}
	{description: Finds the intersection between two rectangles.}
	{prototype: void LmiRectangleIntersect(const LmiRectangle *a, const LmiRectangle *b, LmiRectangle *r)}
	{parameter: {name: a} {description: The first rectangle.}}
	{parameter: {name: b} {description: The second rectangle.}}
	{parameter: {name: r} {description: The intersection between the first and second rectangles will be written
		into this rectangle. If there is no intersection, the width or height of this rectangle will be zero.}}
}
*/
void LmiRectangleIntersect(const LmiRectangle *a, const LmiRectangle *b, LmiRectangle *r);

/**
{function:
	{name: LmiRectangleIntersects}
	{parent: LmiRectangle}
	{description: Determines if two rectangles intersect. Rectangles are considered intersecting if they have
		nonzero common area. Two rectangles sharing boundaries only will not be considered intersecting.}
	{prototype: LmiBool LmiRectangleIntersects(const LmiRectangle *a, const LmiRectangle *b)}
	{parameter: {name: a} {description: The first rectangle.}}
	{parameter: {name: b} {description: The second rectangle.}}
	{return: A boolean indicating if the two rectangles intersect.}
}
*/
LmiBool LmiRectangleIntersects(const LmiRectangle *a, const LmiRectangle *b);

/**
{function:
	{name: LmiRectangleEnclose}
	{parent: LmiRectangle}
	{description: Finds the smallest rectangle that contains two specified rectangles.}
	{prototype: void LmiRectangleEnclose(const LmiRectangle *a, const LmiRectangle *b, LmiRectangle *r)}
	{parameter: {name: a} {description: The first rectangle.}}
	{parameter: {name: b} {description: The second rectangle.}}
	{parameter: {name: r} {description: The enclosing rectangle will be written into this object.}}
}
*/
void LmiRectangleEnclose(const LmiRectangle *a, const LmiRectangle *b, LmiRectangle *r);

/**
{function:
	{name: LmiRectangleClip}
	{parent: LmiRectangle}
	{description: Reduce the size of a rectangle such that it does not intersect another rectangle. This may be useful
		for calculating the new shape of a window when it is desired to keep the whole window visible in the presence
		of another screen element. If there is more than one way to accomplish this, the resulting rectangle with the
		largest area is chosen. If there is no way to do this (because the rectangle r lies entirely within the other rectangle),
		then r is left unchanged.}
	{prototype: void LmiRectangleClip(LmiRectangle *r, const LmiRectangle *avoid)}
	{parameter: {name: r} {description: The rectangle to clip.}}
	{parameter: {name: avoid} {description: The rectangle to clip to.}}
}
*/
void LmiRectangleClip(LmiRectangle *r, const LmiRectangle *avoid);

/**
{function:
	{name: LmiRectangleResizeToAspectRatio}
	{parent: LmiRectangle}
	{description: Resizes a rectangle so that it has the specified aspect ratio. The center position of
		the rectangle is left unchanged.}
	{prototype: void LmiRectangleResizeToAspectRatio(LmiRectangle* r, LmiUint width, LmiUint height, LmiBool letterbox)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: width} {description: The desired width.}}
	{parameter: {name: height} {description: The desired height.}}
	{parameter: {name: letterbox} {description: Set to LMI_TRUE to resize using letterbox mode. This will resize
		the rectangle to the largest rectangle of the proper aspect ratio fitting completely within the original
		rectangle. Set to LMI_FALSE to resize using crop mode. This will resize the rectangle to the smallest
		rectangle of the proper aspect ratio completely covering the original rectangle.}}
}
*/
void LmiRectangleResizeToAspectRatio(LmiRectangle *r, LmiUint width, LmiUint height, LmiBool letterbox);

/**
{function:
	{name: LmiRectangleScale}
	{parent: LmiRectangle}
	{description: Scale a rectangle by a constant factor. Both its position and size are scaled by this amount.}
	{prototype: void LmiRectangleScale(LmiRectangle* r, LmiFloat32 scale)}
	{parameter: {name: r} {description: The rectangle object.}}
	{parameter: {name: scale} {description: The amount to scale the rectangle.}}
}
*/
void LmiRectangleScale(LmiRectangle *r, LmiFloat32 factor);

#if defined(LMI_HAVE_CREATEWINDOWEXA)
LMI_INLINE_DECLARATION void LmiRectangleFromRECT(LmiRectangle *r, const RECT *wr);
LMI_INLINE_DECLARATION void LmiRectangleToRECT(const LmiRectangle *r, RECT *wr);
LMI_INLINE_DECLARATION void LmiRectangleFromRECTWithScale(LmiRectangle *r, const RECT *wr, LmiFloat32 scale);
void LmiRectangleToRECTWithScale(const LmiRectangle *r, RECT *wr, LmiFloat32 scale);

#endif

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiRectangleInline.h>
#endif

#endif

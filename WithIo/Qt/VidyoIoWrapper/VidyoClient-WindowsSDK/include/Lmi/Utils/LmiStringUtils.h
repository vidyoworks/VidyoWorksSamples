/**
{file:
	{name: LmiStringUtils.h}
	{description: Miscellaneous string utilities}
	{copyright:
		(c) 2005-2015 Vidyo, Inc.,
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
#ifndef LMI_STRINGUTILS_H
#define LMI_STRINGUTILS_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Utils/LmiBasicTypesContainer.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="private":
	{name: LmiPrintfBuffer}
	{parent: Utils}
	{include: Lmi/Utils/LmiStringUtils.h}
	{description: A simple class for managing multiple formatted writes to a fixed size
		buffer. The size of the desired string is maintained whether or not there was
		truncation, a la LmiSNPrintf.}
}
*/
typedef struct
{
	char *buffer;
	LmiSizeT bufferLength;
	LmiSizeT stringLength;
} LmiPrintfBuffer;

/**
{function visibility="private":
	{name: LmiPrintfBufferConstruct}
	{parent: LmiPrintfBuffer}
	{description: Constructs an LmiPrintfBuffer object.}
	{prototype: LmiPrintfBuffer *LmiPrintfBufferConstruct(LmiPrintfBuffer *pb, char *buffer, LmiSizeT bufferLength)}
	{parameter: {name: pb} {description: The LmiPrintfBuffer object to construct.}}
	{parameter: {name: buffer} {description: The buffer to manage.}}
	{parameter: {name: bufferLength} {description: The length of the buffer in bytes.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiPrintfBuffer *LmiPrintfBufferConstruct(LmiPrintfBuffer *pb, char *buffer, LmiSizeT bufferLength);

/**
{function visibility="private":
	{name: LmiPrintfBufferDestruct}
	{parent: LmiPrintfBuffer}
	{description: Destructs an LmiPrintfBuffer object.}
	{prototype: void LmiPrintfBufferDestruct(LmiPrintfBuffer *pb)}
	{parameter: {name: pb} {description: The LmiPrintfBuffer object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiPrintfBufferDestruct(LmiPrintfBuffer *pb);

/**
{function visibility="private":
	{name: LmiPrintfBufferAppendFormatted}
	{parent: LmiPrintfBuffer}
	{description: Appends formatted text to an LmiPrintfBuffer's string without overflowing its buffer.}
	{prototype: void LmiPrintfBufferAppendFormatted(LmiPrintfBuffer *pb, const char *format, ...)}
	{parameter: {name: pb} {description: The LmiPrintfBuffer object.}}
	{parameter: {name: format} {description: A format string. The format string is interpreted 
		as it would be for printf.}}
	{parameter: {name: ...} {description: Arguments to the format string.}}
}
*/
void LmiPrintfBufferAppendFormatted(LmiPrintfBuffer *pb, const char *format, ...);

/**
{function visibility="private":
	{name: LmiPrintfBufferGetStringLength}
	{parent: LmiPrintfBuffer}
	{description: Returns the length of the string that would have been written
		to an LmiPrintfBuffer object if its buffer size were unlimited.
		If this value is greater than or equal to the buffer length passed to
		LmiPrintfBufferConstruct, then the string was truncated.}
	{prototype: LmiSizeT LmiPrintfBufferGetStringLength(const LmiPrintfBuffer *pb)}
	{parameter: {name: pb} {description: The LmiPrintfBuffer object.}}
	{return: The length in bytes of the string the user tried to write.}
}
*/
LMI_INLINE_DECLARATION LmiSizeT LmiPrintfBufferGetStringLength(const LmiPrintfBuffer *pb);

Declare_LmiVector(LmiSizeT)

typedef enum
{
	LMI_STRINGCELL_BLANK,
	LMI_STRINGCELL_STRING,
	LMI_STRINGCELL_TABLE,
} LmiStringCellType;

typedef struct LmiStringCell_
{
	LmiStringCellType type;
	void *data;
	LmiAllocator *alloc;
} LmiStringCell;

struct LmiStringTable_;

 /* private */
LmiStringCell *LmiStringCellConstructBlank(LmiStringCell *sc, LmiAllocator *alloc);
LmiStringCell *LmiStringCellConstructTable(LmiStringCell *sc, const struct LmiStringTable_ *st, LmiAllocator *alloc);
LmiStringCell *LmiStringCellConstructCopy(LmiStringCell *d, const LmiStringCell *s);
void LmiStringCellDestruct(LmiStringCell *sc);
LmiStringCell *LmiStringCellAssign(LmiStringCell *d, const LmiStringCell *s);

Declare_LmiVector(LmiStringCell)

/**
{type visibility="private":
	{name: LmiStringTable}
	{parent: Utils}
	{include: Lmi/Utils/LmiStringUtils.h}
	{description: A class that prints a table of strings, automatically sizing columns to fit the data in the table.}
}
*/
typedef struct LmiStringTable_
{
	LmiVector(LmiStringCell) cells;
	LmiVector(LmiSizeT) colWidth;
	LmiVector(LmiSizeT) rowHeight;
	LmiVector(LmiBool) colRight;
	LmiSizeT width;
	LmiSizeT height;
	LmiBool hasHeader;
	LmiBool boxed;
	LmiAllocator *alloc;
} LmiStringTable;

/**
{function visibility="private":
	{name: LmiStringTableConstruct}
	{parent: LmiStringTable}
	{description: Constructs an LmiStringTableConstruct object.}
	{prototype: LmiStringTable *LmiStringTableConstruct(LmiStringTable *st, LmiSizeT cols, LmiBool hasHeader, LmiBool boxed, LmiAllocator *alloc)}
	{parameter: {name: st} {description: The LmiStringTable object to construct.}}
	{parameter: {name: cols} {description: The number of columns desired for the table.}}
	{parameter: {name: hasHeader} {description: A boolean indicating whether the first row of the table should be considered headers.
		If true, this row will be distinguished from the other rows when printed.}}
	{parameter: {name: boxed} {description: If true, lines will be used to separate the rows and columns of the table.
		Set this to false for a more compact table.}}
	{parameter: {name: alloc} {description: An allocator to use.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiStringTable *LmiStringTableConstruct(LmiStringTable *st, LmiSizeT cols, LmiBool hasHeader, LmiBool boxed, LmiAllocator *alloc);

/* private */
LmiStringTable *LmiStringTableConstructCopy(LmiStringTable *st, const LmiStringTable *other);

/**
{function visibility="private":
	{name: LmiStringTableDestruct}
	{parent: LmiStringTable}
	{description: Destructs an LmiStringTable object.}
	{prototype: void LmiStringTableDestruct(LmiStringTable *st)}
	{parameter: {name: st} {description: The LmiStringTable object to destruct.}}
}
*/
void LmiStringTableDestruct(LmiStringTable *st);

/**
{function visibility="private":
	{name: LmiStringTableJustifyRight}
	{parent: LmiStringTable}
	{description: Change a column's justification to right. Columns are left-justified by default.}
	{prototype: void LmiStringTableJustifyRight(LmiStringTable *st, LmiSizeT col)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: col} {description: The column number. (Columns are zero-indexed.)}}
}
*/
void LmiStringTableJustifyRight(LmiStringTable *st, LmiSizeT col);

/**
{function visibility="private":
	{name: LmiStringTableAddBlank}
	{parent: LmiStringTable}
	{description: Add a blank cell to a string table.}
	{prototype: void LmiStringTableAddBlank(LmiStringTable *st)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
}
*/
void LmiStringTableAddBlank(LmiStringTable *st);

/**
{function visibility="private":
	{name: LmiStringTableAdd}
	{parent: LmiStringTable}
	{description: Add a string to a string table.}
	{prototype: void LmiStringTableAdd(LmiStringTable *st, const LmiString *s)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: s} {description: The string to add.}}
}
*/
void LmiStringTableAdd(LmiStringTable *st, const LmiString *s);

/**
{function visibility="private":
	{name: LmiStringTableAddCStr}
	{parent: LmiStringTable}
	{description: Add a string to a string table.}
	{prototype: void LmiStringTableAddCStr(LmiStringTable *st, const char *s)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: s} {description: The string to add.}}
}
*/
void LmiStringTableAddCStr(LmiStringTable *st, const char *s);

/**
{function visibility="private":
	{name: LmiStringTableAddFormatted}
	{parent: LmiStringTable}
	{description: Add a string to a string table.}
	{prototype: void LmiStringTableAddFormatted(LmiStringTable *st, const char *format, ...)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: format} {description: A format string. The format string is interpreted 
		as it would be for printf.}}
	{parameter: {name: ...} {description: Arguments to the format string.}}
}
*/
void LmiStringTableAddFormatted(LmiStringTable *st, const char *format, ...);

/**
{function visibility="private":
	{name: LmiStringTableAddVFormatted}
	{parent: LmiStringTable}
	{description: Add a string to a string table.}
	{prototype: void LmiStringTableAddVFormatted(LmiStringTable *st, const char *format, va_list args)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: format} {description: A format string. The format string is interpreted 
		as it would be for printf.}}
	{parameter: {name: args} {description: Arguments to the format string.}}
}
*/
void LmiStringTableAddVFormatted(LmiStringTable *st, const char *format, va_list args);

/**
{function visibility="private":
	{name: LmiStringTableAddTable}
	{parent: LmiStringTable}
	{description: Add a string table as a cell in another table.}
	{prototype: void LmiStringTableAddTable(LmiStringTable *st, const LmiStringTable *sub)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: sub} {description: The other table to add as a cell.}}
}
*/
void LmiStringTableAddTable(LmiStringTable *st, const LmiStringTable *sub);

/**
{function visibility="private":
	{name: LmiStringTableWrite}
	{parent: LmiStringTable}
	{description: Append the contents of a string table to a destination string.}
	{prototype: void LmiStringTableWrite(const LmiStringTable *st, LmiString *s)}
	{parameter: {name: st} {description: The LmiStringTable object.}}
	{parameter: {name: s} {description: The destination string.}}
}
*/
void LmiStringTableWrite(const LmiStringTable *st, LmiString *s);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiStringUtilsInline.h>
#endif

#endif

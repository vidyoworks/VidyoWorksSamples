/**
{file:
    {name: LmiFile.h}
    {description: Objects to provide access to files on disk or other persistent storage.}
    {copyright:
    	(c) 2011-2016 Vidyo, Inc.,
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
#ifndef LMI_FILE_H_
#define LMI_FILE_H_

#include <Lmi/Utils/LmiTypes.h>

/**
	{type:
		{name: LmiFile}
		{parent: Os}
		{include: Lmi/Os/LmiFile.h}
		{description: Represents a file on a file system.}
		{constant:
			{name: LMI_FILE_PATH_MAX}
			{type: LmiSizeT}
			{description: The maximum size of a pathname on the platform.}}
	}
*/

/**
	{type:
		{name: LmiFilePosition}
		{parent: LmiFile}
		{description: A value representing a read/write position within an LmiFile object.}
		{note: This will be a signed integer type, but may be able to hold values larger than the maximum value of LmiSizeT.}
	}
*/

LMI_BEGIN_EXTERN_C

#if LMI_HAVE_STDIO_H
#include <stdarg.h>
#include <stdio.h>
#define LMI_FILE_USE_STDIO_ 1
typedef FILE* LmiFile;

#if LMI_HAVE_FSEEKO64 && LMI_HAVE___OFF64_T
typedef __off64_t LmiFilePosition;
#elif LMI_HAVE_FSEEKO64 && LMI_HAVE_OFF64_T
typedef off64_t LmiFilePosition;
#elif LMI_HAVE_FSEEKO
typedef off_t LmiFilePosition;
#elif LMI_HAVE__FSEEKI64
typedef __int64 LmiFilePosition;
#else
typedef long LmiFilePosition;
#endif

/* Include windows header for MAX_PATH */
#if LMI_HAVE_WINSOCK2_H
#include <winsock2.h>
#elif LMI_HAVE_WINDOWS_H
#include <windows.h>
#endif

#if defined(PATH_MAX)
#define LMI_FILE_PATH_MAX PATH_MAX
#elif defined(MAX_PATH)
#define LMI_FILE_PATH_MAX MAX_PATH
#else
#error Need definition of LMI_FILE_PATH_MAX
#endif

#else
#define LMI_FILE_USE_NONE_ 1
typedef int LmiFile;
typedef int LmiFilePosition;

#define LMI_FILE_PATH_MAX 256
#endif

/* Standard in, out and error */
extern LmiFile lmiFileIn;
extern LmiFile lmiFileOut;
extern LmiFile lmiFileError;

/**
	{type:
		{name: LmiFileOpenFlag}
		{parent: LmiFile}
		{description: A flag representing a mode in which to open an LmiFile.}
		{value: {name: LMI_FILEOPENFLAG_Read} {description: Indicates that a file is to be opened for reading.}}
		{value: {name: LMI_FILEOPENFLAG_Write} {description: Indicates that a file is to be opened for writing.  If the file does not exist the system will attempt to create it.}}
		{value: {name: LMI_FILEOPENFLAG_Append} {description: Indicates that a file is to be opened for appending (writing at the end of file).  This is only meaningful if LMI_FILEOPENFLAG_Write is also set in a flag set.}}
		{value: {name: LMI_FILEOPENFLAG_Binary} {description: Indicates that a file is to be read and/or written in binary mode, rather than text mode, for systems where this is a meaningful distinction.}}
	}
*/
enum {
	LMI_FILEOPENFLAG_Read = 1 << 0,
	LMI_FILEOPENFLAG_Write = 1 << 1,
	LMI_FILEOPENFLAG_Append = 1 << 2,
	LMI_FILEOPENFLAG_Binary = 1 << 3,
};

typedef int LmiFileOpenFlag;

/**
	{type:
		{name: LmiFileReadCStrFlag}
		{parent: LmiFile}
		{description: A flag representing a mode in which LmiFileReadCStr should operate.}
		{value: {name: LMI_FILEREADCSTRFLAG_IncludeDelimiter} {description: Indicates that the terminating delimiter should be included in the output string.}}
	}
*/
enum {
	LMI_FILEREADCSTRFLAG_None = 0,
	LMI_FILEREADCSTRFLAG_IncludeDelimiter = 1 << 0
};
typedef int LmiFileReadCStrFlag;

/**
	{function:
		{name: LmiFileConstructDefault}
		{parent: LmiFile}
		{description: Construct an LmiFile object which is not opened.}
		{prototype: LmiFile* LmiFileConstructDefault(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The file to construct.}}
		{return: The file object on success, or NULL on failure.}
	}
*/
LmiFile* LmiFileConstructDefault(LmiFile* f);


/**
	{function:
		{name: LmiFileConstruct}
		{parent: LmiFile}
		{description: Construct an LmiFile object by opening a file.}
		{prototype: LmiFile* LmiFileConstruct(LmiFile* f, const char* path, LmiFileOpenFlag flags)}
		{parameter:
			{name: f}
			{description: The file object to construct.}}
		{parameter:
			{name: path}
			{description: The path on disk to the file to open.  The syntax of this path is platform-dependent.}}
		{parameter:
			{name: flags}
			{description: A set of flags (bitwise-or'd together) indicating the mode in which to open the file.}}
		{return: The file object on success, or NULL on failure.}
	}
*/
LmiFile* LmiFileConstruct(LmiFile* f, const char* path, LmiFileOpenFlag flags);


/**
	{function:
		{name: LmiFileDestruct}
		{parent: LmiFile}
		{description: Destruct an LmiFile object, closing it if it is open.}
		{prototype: void LmiFileDestruct(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The object to destruct.}}
	}
*/
void LmiFileDestruct(LmiFile* f);


/**
	{function:
		{name: LmiFileOpen}
		{parent: LmiFile}
		{description: Open a file using an LmiFile object.  If the object
			already has a file open, this will fail.}
		{prototype: LmiBool LmiFileOpen(LmiFile* f, const char* path, LmiFileOpenFlag flags)}
		{parameter:
			{name: f}
			{description: The file object to use to open the file.}}
		{parameter:
			{name: path}
			{description: The path on disk to the file to open.  The syntax of this path is platform-dependent.}}
		{parameter:
			{name: flags}
			{description: A set of flags (bitwise-or'd together) indicating the mode in which to open the file.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiFileOpen(LmiFile* f, const char* path, LmiFileOpenFlag flags);


/**
	{function:
		{name: LmiFileClose}
		{parent: LmiFile}
		{description: Close a file object.}
		{prototype: LmiBool LmiFileClose(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The file object to close}}
		{return: LMI_TRUE on success, LMI_FALSE if an error was reported in closing the file.}
	}
*/
LmiBool LmiFileClose(LmiFile* f);


/**
	{function:
		{name: LmiFileRead}
		{parent: LmiFile}
		{description: Read data from a file at its current read position.}
		{prototype: LmiSizeT LmiFileRead(LmiFile* f, LmiUint8* buf, LmiSizeT bufSize)}
		{parameter:
			{name: f}
			{description: The file from which to read.}}
		{parameter:
			{name: buf}
			{description: A buffer into which to place the data read.}}
		{parameter:
			{name: bufSize}
			{description: The size of the buffer into which to read data, in bytes.}}
		{return: The number of bytes actually read.  On error or EOF, this will be 0.}
	}
*/
LmiSizeT LmiFileRead(LmiFile* f, LmiUint8* buf, LmiSizeT bufSize);


/**
	{function:
		{name: LmiFileReadCStr}
		{parent: LmiFile}
		{description:
			Read a string from a file starting at its current read position up to either
			the first occurrence of one of the {code:delimiters} or {code:n} - 1 characters
			which ever comes first. The read position is advanced to the byte just passed the
			first occurrence of one of the {code:delimiters} (regardless of {code:n}).
		}
		{prototype: char* LmiFileReadCStr(LmiFile* f, char* str, LmiSizeT n, const char* delimiters, LmiFileReadCStrFlag flags)}
		{parameter:
			{name: f}
			{description: The file from which to read.}}
		{parameter:
			{name: str}
			{description: A string into which to place the data read.}}
		{parameter:
			{name: n}
			{description: The size of the string (not the length) into which to read data, in bytes.}}
		{parameter:
			{name: delimiters}
			{description: A list of delimiters.}}
		{parameter:
			{name: flags}
			{description: A set of flags (bitwise-or'd together) indicating the mode in which to read the string.}}
		{return: A pointer to the string or NULL on error or EOF.  Use LmiFileAtEof to distinguish whether EOF or an error occurred.}
		{example:
			char str[80];
			\/\* Mimic fgets \*\/
			LmiFileReadCStr(file, str, sizeof(str), "\n", LMI_FILEREADCSTRFLAG_IncludeDelimiter);
		}
	}
*/
char* LmiFileReadCStr(LmiFile* f, char* str, LmiSizeT n, const char* delimiters, LmiFileReadCStrFlag flags);


/**
	{function:
		{name: LmiFileWrite}
		{parent: LmiFile}
		{description: Write data to a file at its current write position.}
		{prototype: LmiSizeT LmiFileWrite(LmiFile* f, const LmiUint8* buf, LmiSizeT bufSize)}
		{parameter:
			{name: f}
			{description: The file to which to write.}}
		{parameter:
			{name: buf}
			{description: The data to write to the file.}}
		{parameter:
			{name: bufSize}
			{description: The length of the data to write to the file.}}
		{return: The number of bytes actually written.  On error, this may be
			less than bufSize.}
	}
*/
LmiSizeT LmiFileWrite(LmiFile* f, const LmiUint8* buf, LmiSizeT bufSize);

/**
	{function:
		{name: LmiFilePrintf}
		{parent: LmiFile}
		{description: Format and Write data to a file at its current write position.}
		{prototype: LmiInt LmiFilePrintf(LmiFile* f, const char* format, ...)}
		{parameter:
			{name: f}
			{description: The file to which to write.}}
		{parameter:
			{name: format}
			{description: A printf-style format string.}}
		{parameter:
			{name: ...}
			{description: The arguments to the format string.}}
		{return: The number of bytes actually written or -1 on error.}
	}
*/
LmiInt LmiFilePrintf(LmiFile* f, const char* format, ...)
  LmiFunctionPrintfLike(2, 3);

/**
	{function:
		{name: LmiFileVPrintf}
		{parent: LmiFile}
		{description: Format and Write data to a file at its current write position, passing a va_list for the format arguments.}
		{prototype: LmiInt LmiFileVPrintf(LmiFile* f, const char* format, va_list args)}
		{parameter:
			{name: f}
			{description: The file to which to write.}}
		{parameter:
			{name: format}
			{description: A printf-style format string.}}
		{parameter:
			{name: args}
			{description: A stdarg.h collection of arguments.}}
		{return: The number of bytes actually written or -1 on error.}
	}
*/
LmiInt LmiFileVPrintf(LmiFile* f, const char* format, va_list args)
  LmiFunctionVPrintfLike(2);


/**
	{function:
		{name: LmiFileGetPosition}
		{parent: LmiFile}
		{description: Get the current read/write position of a file.}
		{prototype: LmiFilePosition LmiFileGetPosition(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The file whose position to get.}}
		{return: The current position in the file.  On error, including if the position is not representable in LmiFilePosition, this value will be negative.  Negative values will cause LmiFileSetPosition to return failure.}
	}
*/
LmiFilePosition LmiFileGetPosition(LmiFile* f);


/**
	{function:
		{name: LmiFileSetPosition}
		{parent: LmiFile}
		{description: Set the current read/write position of a file.}
		{prototype: LmiBool LmiFileSetPosition(LmiFile* f, LmiFilePosition pos)}
		{parameter:
			{name: f}
			{description: The file whose position to set.}}
		{parameter:
			{name: pos}
			{description: The position to set in the file.  The only portable values to set in this are positive values returned from LmiFileGetPosition, or 0 meaning beginning of file.}}
		{return: LMI_TRUE on success, LMI_FALSE on error.}
	}
*/
LmiBool LmiFileSetPosition(LmiFile* f, LmiFilePosition pos);

/**
	{function:
		{name: LmiFileAtEof}
		{parent: LmiFile}
		{description: Query whether a file's position is currently at the end of the file. }
		{prototype: LmiBool LmiFileAtEof(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The file object to query for EOF.}}
		{return: LMI_TRUE if the file is at EOF, LMI_FALSE if not or if an error was reported.}
	}
*/
LmiBool LmiFileAtEof(LmiFile* f);


/**
	{function:
		{name: LmiFileFlush}
		{parent: LmiFile}
		{description: Flush any buffered file data out to the file's storage medium. }
		{prototype: LmiBool LmiFileFlush(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The file object to flush.}}
		{return: LMI_TRUE on success, LMI_FALSE if an error was reported while flushing the file.}
	}
*/
LmiBool LmiFileFlush(LmiFile* f);

/**
	{function:
		{name: LmiFileGetSize}
		{parent: LmiFile}
		{description: Gets the size of the file. }
		{prototype: LmiUint64 LmiFileGetSize(LmiFile* f)}
		{parameter:
			{name: f}
			{description: The file object.}}
		{return: Size of the file.}
		{note: The file should be open in binary mode.}
	}
*/
LmiUint64 LmiFileGetSize(LmiFile* f);

/**
	{function:
		{name: LmiFileGetStdin}
		{parent: LmiFile}
		{description: Gets the standard input as an LmiFile object. }
		{prototype: LmiFile* LmiFileGetStdin(void)}
		{return: Returns the standard input as a pointer to an LmiFile object, or NULL if not supported.}
	}
*/
LmiFile* LmiFileGetStdin(void);

/**
	{function:
		{name: LmiFileGetStdout}
		{parent: LmiFile}
		{description: Gets the standard output as an LmiFile object. }
		{prototype: LmiFile* LmiFileGetStdout(void)}
		{return: Returns the standard output as a pointer to an LmiFile object, or NULL if not supported.}
	}
*/
LmiFile* LmiFileGetStdout(void);

/**
	{function:
		{name: LmiFileGetStderr}
		{parent: LmiFile}
		{description: Gets the standard error as an LmiFile object. }
		{prototype: LmiFile* LmiFileGetStderr(void)}
		{return: Returns the standard error as a pointer to an LmiFile object, or NULL if not supported.}
	}
*/
LmiFile* LmiFileGetStderr(void);

LmiBool LmiFileInitialize(void);
void LmiFileUninitialize(void);

/**
	{function:
		{name: LmiFileRename}
		{parent: LmiFile}
		{description: Rename (move) a file in the file system.}
		{prototype: LmiBool LmiFileRename(const char* currentPath, const char* newPath)}
		{parameter:
			{name: currentPath}
			{description: A path to an existing file.  The syntax of this path is platform-dependent.}}
		{parameter:
			{name: newPath}
			{description: A path to the desired new name and location of the file.  The syntax of this path is platform-dependent.}}
		{return: LMI_TRUE if the file was successfully moved; LMI_FALSE if not.}
		{note: In general, renaming a file within the same file system will succeed, if there is no existing file with the desired name.  (However, exceptions may occur, such as if some process has the file open exclusively.)  Moving a file across file systems, or so as to replace an existing file, is platform-dependent.}
	}
*/
LmiBool LmiFileRename(const char* oldPath, const char* newPath);


/**
	{function visibility="private":
		{name: LmiFileRename_}
		{parent: LmiFile}
		{description: Rename (move) a file in the file system without generating a log on error.}
		{prototype: LmiBool LmiFileRename_(const char* currentPath, const char* newPath)}
		{parameter:
			{name: currentPath}
			{description: A path to an existing file.  The syntax of this path is platform-dependent.}}
		{parameter:
			{name: newPath}
			{description: A path to the desired new name and location of the file.  The syntax of this path is platform-dependent.}}
		{return: LMI_TRUE if the file was successfully moved; LMI_FALSE if not.}
		{note: In general, renaming a file within the same file system will succeed, if there is no existing file with the desired name.  (However, exceptions may occur, such as if some process has the file open exclusively.)  Moving a file across file systems, or so as to replace an existing file, is platform-dependent.}
	}
*/
LmiBool LmiFileRename_(const char* oldPath, const char* newPath);

/**
	{function:
		{name: LmiFileDelete}
		{parent: LmiFile}
		{description: Remove a file in the file system.}
		{prototype: LmiBool LmiFileDelete(const char* path)}
		{parameter:
			{name: path}
			{description: A path to an existing file.  The syntax of this path is platform-dependent.}}
		{return: LMI_TRUE if the file was successfully deleted, LMI_FALSE if not.}
	}
*/
LmiBool LmiFileDelete(const char* path);


LMI_END_EXTERN_C


#endif /* LMI_FILE_H_ */

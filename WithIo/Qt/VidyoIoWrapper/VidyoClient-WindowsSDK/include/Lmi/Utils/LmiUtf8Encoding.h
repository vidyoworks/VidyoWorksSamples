/** 
{file:
	{name: LmiUtf8Encoding.h}
	{description: }
	{copyright:
		(c) 2011-2015 Vidyo, Inc.,
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
#ifndef LMI_UTF8ENCODING_H
#define LMI_UTF8ENCODING_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
	{package visibility="private":
		{name: Utf8}
		{parent: Utils}
		{include: Lmi/Utils/LmiUtf8Encoding.h}
		{description: Utilities for translating between wide characters (UCS-4) and UTF-8.}
	}
*/	


/**
	{function visibility="private":
		{name: LmiUtf8EncodeChar}
		{parent: Utf8}
		{description: Encode a single Unicode character as UTF-8.}
		{prototype: LmiSizeT LmiUtf8EncodeChar(LmiWideChar input, char* output, LmiSizeT outputSize)}
		{parameter:
			{name: input}
			{description: The input Unicode character to encode.  This must be a valid Unicode character, i.e. in the range U+00000 - U+10FFFF and not a surrogate code point (U+D800 - U+DFFF).}}
		{parameter:
			{name: output}
			{description: The output buffer to which to write the UTF-8 encoded character.}}
		{parameter:
			{name: outputSize}
			{description: The length, in bytes, of the buffer to which to write the character.}}
		{return: The total number of UTF-8 characters needed to encode the Unicode character, or 0 on failure.  If this is more than outputLen, the output was truncated.}
	}
*/
LmiSizeT LmiUtf8EncodeChar(LmiWideChar input, char* output, LmiSizeT outputLen);


/**
	{function visibility="private":
		{name: LmiUtf8Encode}
		{parent: Utf8}
		{description: Encode a NUL-terminated Unicode string as UTF-8.}
		{prototype: LmiBool LmiUtf8Encode(const LmiWideChar* input, char* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The input Unicode string to encode.  This must be NUL-terminated, and all characters in the string must be valid Unicode characters, i.e. in the range U+00000 - U+10FFFF and not surrogate code points (U+D800 - U+DFFF).}}
		{parameter:
			{name: output}
			{description: The output buffer to which to write the UTF-8 encoded string.}}
		{parameter:
			{name: outputSize}
			{description: The length, in bytes, of the buffer to which to write the encoded string.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, if not NULL, the total number of UTF-8 characters needed to encode the Unicode string, not counting the terminating NUL.  If this is greater than outputSize-1, the output was truncated; however, if outputSize > 0, the output will always have a terminating NUL appended to it.}}
		{return: LMI_TRUE if the string was successfully encoded, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiUtf8Encode(const LmiWideChar* input, char* output, LmiSizeT outputSize, LmiSizeT* outputLen);


/**
	{function visibility="private":
		{name: LmiUtf8EncodeUtf16}
		{parent: Utf8}
		{description: Encode a NUL-terminated UTF-16 string as UTF-8.}
		{prototype: LmiBool LmiUtf8EncodeUtf16(const LmiUint16* input, char* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The input UTF-16 string to encode.  This must be NUL-terminated, and the string must encode valid Unicode characters, i.e. any surrogate code points (U+D800 - U+DFFF) must appear in valid high/low pairs.}}
		{parameter:
			{name: output}
			{description: The output buffer to which to write the UTF-8 encoded string.}}
		{parameter:
			{name: outputSize}
			{description: The length, in bytes, of the buffer to which to write the encoded string.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, if not NULL, the total number of UTF-8 characters needed to encode the Unicode string, not counting the terminating NUL.  If this is greater than outputSize-1, the output was truncated; however, if outputSize > 0, the output will always have a terminating NUL appended to it.}}
		{return: LMI_TRUE if the string was successfully encoded, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiUtf8EncodeUtf16(const LmiUint16* input, char* output, LmiSizeT outputSize, LmiSizeT* outputLen);


/**
	{function visibility="private":
		{name: LmiUtf8DecodeChar}
		{parent: Utf8}
		{description: Decode a UTF-8 encoding of a single Unicode character.}
		{prototype: LmiBool LmiUtf8DecodeChar(const char** input, LmiSizeT inputLen, LmiWideChar* output)}
		{parameter:
			{name: input}
			{description: A pointer to a pointer to a C string containing the UTF-8 character to decode.  On successful return, the pointer will be advanced to point just past the UTF-8 character decoded.}}
		{parameter:
			{name: inputLen}
			{description: The maximum number of bytes to read from input.  May be LMI_SIZET_MAX for unbounded.}}
		{parameter:
			{name: output}
			{description: A pointer to an address to which, on successful return, the Unicode character will be written.}}
		{return: LMI_TRUE if the input encoded a proper UTF-8 character, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiUtf8DecodeChar(const char** input, LmiSizeT inputLen, LmiWideChar* output);


/**
	{function visibility="private":
		{name: LmiUtf8Decode}
		{parent: Utf8}
		{description: Decode a UTF-8 string to a string of Unicode (UCS-4) characters}
		{prototype: LmiBool LmiUtf8Decode(const char* input, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The NUL-terminated UTF-8 string to decode.}}
		{parameter:
			{name: output}
			{description: A pointer to the buffer to which to write the decoded Unicode characters.}}
		{parameter:
			{name: outputSize}
			{description: The size, in characters, of the buffer to which the decoded Unicode characters should be written.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, the number of Unicode characters needed to decode the UTF-8 string.  If this is more than outputSize-1, the output was truncated.}}
		{return: LMI_TRUE if the UTF-8 string was successfully decoded; LMI_FALSE if not.}
	}
*/
LmiBool LmiUtf8Decode(const char* input, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen);

/**
	{function visibility="private":
		{name: LmiUtf8DecodeUtf16}
		{parent: Utf8}
		{description: Decode a UTF-8 string to a string of UTF-16 characters}
		{prototype: LmiBool LmiUtf8DecodeUtf16(const char* input, LmiUint16* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The NUL-terminated UTF-8 string to decode.}}
		{parameter:
			{name: output}
			{description: A pointer to the buffer to which to write the decoded UTF-16 characters.}}
		{parameter:
			{name: outputSize}
			{description: The size, in 16-bit units, of the buffer to which the decoded UTF-16 characters should be written.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, the number of UTF-16 codepoints needed to decode the UTF-8 string.  If this is more than outputSize-1, the output was truncated.}}
		{return: LMI_TRUE if the UTF-8 string was successfully decoded; LMI_FALSE if not.}
	}
*/
LmiBool LmiUtf8DecodeUtf16(const char* input, LmiUint16* output, LmiSizeT outputSize, LmiSizeT* outputLen);

/**
	{function visibility="private":
		{name: LmiUtf8DecodeLen}
		{parent: Utf8}
		{description: Decode a UTF-8 string of a given length to a string of Unicode (UCS-4) characters}
		{prototype: LmiBool LmiUtf8DecodeLen(const char* input, LmiSizeT inputLen, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The UTF-8 string to decode.}}
		{parameter:
			{name: inputLen}
			{description: The length of the UTF-8 input to decode, in bytes.}}
		{parameter:
			{name: output}
			{description: A pointer to the buffer to which to write the decoded Unicode characters.}}
		{parameter:
			{name: outputSize}
			{description: The size, in 16-bit units, of the buffer to which the decoded Unicode characters should be written.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, the number of Unicode characters needed to decode the UTF-8 string.  If this is more than outputSize-1, the output was truncated.}}
		{return: LMI_TRUE if the UTF-8 string was successfully decoded; LMI_FALSE if not.}
	}
*/
LmiBool LmiUtf8DecodeLen(const char* input, LmiSizeT inputLen, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen);


/**
	{package visibility="private":
		{name: Utf16}
		{parent: Utils}
		{include: Lmi/Utils/LmiUtf8Encoding.h}
		{description: Utilities for translating between UTF-16 characters and both wide characters (UCS-4) and UTF-8.}
	}
*/	


/**
	{function visibility="private":
		{name: LmiUtf16EncodeChar}
		{parent: Utf16}
		{description: Encode a single Unicode character as UTF-16.}
		{prototype: LmiSizeT LmiUtf16EncodeChar(LmiWideChar input, LmiUint16* output, LmiSizeT outputSize)}
		{parameter:
			{name: input}
			{description: The input Unicode character to encode.  This must be a valid Unicode character, i.e. in the range U+00000 - U+10FFFF and not a surrogate code point (U+D1600 - U+DFFF).}}
		{parameter:
			{name: output}
			{description: The output buffer to which to write the UTF-16 encoded character.}}
		{parameter:
			{name: outputSize}
			{description: The length of the buffer to which to write the character, in 16-bit units.}}
		{return: The total number of UTF-16 characters needed to encode the Unicode character, or 0 on failure.  If this is more than outputLen, the output was truncated.}
	}
*/
LmiSizeT LmiUtf16EncodeChar(LmiWideChar input, LmiUint16* output, LmiSizeT outputLen);


/**
	{function visibility="private":
		{name: LmiUtf16Encode}
		{parent: Utf16}
		{description: Encode a NUL-terminated Unicode string as UTF-16.}
		{prototype: LmiBool LmiUtf16Encode(const LmiWideChar* input, LmiUint16* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The input Unicode string to encode.  This must be NUL-terminated, and all characters in the string must be valid Unicode characters, i.e. in the range U+00000 - U+10FFFF and not surrogate code points (U+D1600 - U+DFFF).}}
		{parameter:
			{name: output}
			{description: The output buffer to which to write the UTF-16 encoded string.}}
		{parameter:
			{name: outputSize}
			{description: The length of the buffer to which to write the encoded string, in 16-bit units.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, if not NULL, the total number of UTF-16 characters needed to encode the Unicode string, not counting the terminating NUL.  If this is greater than outputSize-1, the output was truncated; however, if outputSize > 0, the output will always have a terminating NUL appended to it.}}
		{return: LMI_TRUE if the string was successfully encoded, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiUtf16Encode(const LmiWideChar* input, LmiUint16* output, LmiSizeT outputSize, LmiSizeT* outputLen);


/**
	{function visibility="private":
		{name: LmiUtf16DecodeChar}
		{parent: Utf16}
		{description: Decode a UTF-16 encoding of a single Unicode character.}
		{prototype: LmiBool LmiUtf16DecodeChar(const LmiUint16** input, LmiSizeT inputLen, LmiWideChar* output)}
		{parameter:
			{name: input}
			{description: A pointer to a pointer to a C string containing the UTF-16 character to decode.  On successful return, the pointer will be advanced to point just past the UTF-16 character decoded.}}
		{parameter:
			{name: inputLen}
			{description: The maximum number of bytes to read from input.  May be LMI_SIZET_MAX for unbounded.}}
		{parameter:
			{name: output}
			{description: A pointer to an address to which, on successful return, the Unicode character will be written.}}
		{return: LMI_TRUE if the input encoded a proper UTF-16 character, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiUtf16DecodeChar(const LmiUint16** input, LmiSizeT inputLen, LmiWideChar* output);


/**
	{function visibility="private":
		{name: LmiUtf16Decode}
		{parent: Utf16}
		{description: Decode a UTF-16 string to a string of Unicode (UCS-4) characters}
		{prototype: LmiBool LmiUtf16Decode(const LmiUint16* input, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The NUL-terminated UTF-16 string to decode.}}
		{parameter:
			{name: output}
			{description: A pointer to the buffer to which to write the decoded Unicode characters.}}
		{parameter:
			{name: outputSize}
			{description: The size, in characters, of the buffer to which the decoded Unicode characters should be written.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, the number of Unicode characters needed to decode the UTF-16 string.  If this is more than outputSize-1, the output was truncated.}}
		{return: LMI_TRUE if the UTF-16 string was successfully decoded; LMI_FALSE if not.}
	}
*/
LmiBool LmiUtf16Decode(const LmiUint16* input, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen);

/**
	{function visibility="private":
		{name: LmiUtf16DecodeLen}
		{parent: Utf16}
		{description: Decode a UTF-16 string of a given length to a string of Unicode (UCS-4) characters}
		{prototype: LmiBool LmiUtf16DecodeLen(const LmiUint16* input, LmiSizeT inputLen, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen)}
		{parameter:
			{name: input}
			{description: The UTF-16 string to decode.}}
		{parameter:
			{name: inputLen}
			{description: The length of the UTF-16 input to decode, in bytes.}}
		{parameter:
			{name: output}
			{description: A pointer to the buffer to which to write the decoded Unicode characters.}}
		{parameter:
			{name: outputSize}
			{description: The size, in characters, of the buffer to which the decoded Unicode characters should be written.}}
		{parameter:
			{name: outputLen}
			{description: On successful return, the number of Unicode characters needed to decode the UTF-16 string.  If this is more than outputSize-1, the output was truncated.}}
		{return: LMI_TRUE if the UTF-16 string was successfully decoded; LMI_FALSE if not.}
	}
*/
LmiBool LmiUtf16DecodeLen(const LmiUint16* input, LmiSizeT inputLen, LmiWideChar* output, LmiSizeT outputSize, LmiSizeT* outputLen);


LMI_END_EXTERN_C

#endif

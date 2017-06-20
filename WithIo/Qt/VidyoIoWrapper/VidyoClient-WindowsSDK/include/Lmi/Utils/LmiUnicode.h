/** {file:
      {name: LmiUnicode.h}
      {description: Functions to perform Unicode text transformations.}
      {copyright:
      	(c) 2014-2015 Vidyo, Inc.,
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

#ifndef LMI_UNICODE_H_
#define LMI_UNICODE_H_

#include <Lmi/Utils/LmiWideString.h>

LMI_BEGIN_EXTERN_C

/**
	{package visibility="private":
		{name: Unicode}
		{parent: Utils}
		{include: Lmi/Utils/LmiUnicode.h}
		{description: Utilities for manipulating and normalizing Unicode strings.}
	}
*/	

/**
	{function visibility="private":
		{name: LmiUnicodeDoWidthAndCaseFolding}
		{parent: Unicode}
		{description: Perform the Unicode Default Case Folding algorithm on a Unicode string,
			and map all halfwidth or fullwidth characters to their compatibility forms.}
		{prototype: LmiBool LmiUnicodeDoWidthAndCaseFolding(LmiWideString* dst, const LmiWideString* src)}
		{parameter:
			{name: dst}
			{description: The destination string to which to write the case- and width-folded string.  This may be
				the same as src for in-place normalization.}}
		{parameter:
			{name: src}
			{description: The source string to case- and width-fold.}}
		{return: LMI_TRUE if folding was successfully performed, LMI_FALSE if not.}
	}
*/
LmiBool LmiUnicodeDoWidthAndCaseFolding(LmiWideString* dst, const LmiWideString* src);


/**
	{type visibility="private":
		{name: LmiUnicodeQuickCheckValue}
		{parent: Unicode}
		{description: The result of a unicode quick check algorithm to determine whether a
			string is in a particular normalization form.}
		{value:
			{name: LMI_UNICODEQUICKCHECKVALUE_Yes}
			{description: The string is definitely in the specified normalization form.}}
		{value:
			{name: LMI_UNICODEQUICKCHECKVALUE_Maybe}
			{description: The quick check algorithm could not determine whether the string was in
				the specified normalization form.}}
		{value:
			{name: LMI_UNICODEQUICKCHECKVALUE_No}
			{description: The string is definitely not in the specified normalization form.}}
	}
*/		
typedef enum {
	LMI_UNICODEQUICKCHECKVALUE_Yes = 0,
	LMI_UNICODEQUICKCHECKVALUE_Maybe = 1,
	LMI_UNICODEQUICKCHECKVALUE_No = 2
} LmiUnicodeQuickCheckValue;

/**
	{function visibility="private":
		{name: LmiUnicodeCheckNFC}
		{parent: Unicode}
		{description: Check whether a string is in Unicode Normalization Form C,
			using the Unicode Quick-Check algorithm (UAX 15 section 9).}
		{prototype: LmiUnicodeQuickCheckValue LmiUnicodeCheckNFC(const LmiWideString* str)}
		{parameter:
			{name: str}
			{description: The string to check for Normalization Form C.}}
		{return: Whether the string is in Normalization Form C, or LMI_UNICODEQUICKCHECKVALUE_Maybe if }
	}
*/
LmiUnicodeQuickCheckValue LmiUnicodeCheckNFC(const LmiWideString* str);

/**
	{function visibility="private":
		{name: LmiUnicodeNormalizeNFC}
		{parent: Unicode}
		{description: Normalize a Unicode string to Unicode Normalization Form C (Composed, Unicode Chapter 3 Definition D120).}
		{prototype: LmiBool LmiUnicodeNormalizeNFC(LmiWideString* dst, const LmiWideString* src)}
		{parameter:
			{name: dst}
			{description: The destination string to which to write the normalized string.  This may be the same
				as src for in-place normalization.}}
		{parameter:
			{name: src}
			{description: The source string to normalize.}}
		{return: LMI_TRUE if the string was successfully normalized, LMI_FALSE if not.}
		{note: Thus functions performs a quick-check of the string (as in LmiUnicodeCheckNFC) and
			avoids the complexity of the full normalization algorithm if the string can be determined
			to already be normalized.}
	}
*/
LmiBool LmiUnicodeNormalizeNFC(LmiWideString* dst, const LmiWideString* src);

/**
	{function visibility="private":
		{name: LmiUnicodeNormalizeNFD}
		{parent: Unicode}
		{description: Normalize a Unicode string to Unicode Normalization Form D (Decomposed, Unicode Chapter 3 Definition D118).}
		{prototype: LmiBool LmiUnicodeNormalizeNFD(LmiWideString* dst, const LmiWideString* src)}
		{parameter:
			{name: dst}
			{description: The destination string to which to write the normalized string.  This may be the same
				as src for in-place normalization.}}
		{parameter:
			{name: src}
			{description: The source string to normalize.}}
		{return: LMI_TRUE if the string was successfully normalized, LMI_FALSE if not.}
	}
*/
LmiBool LmiUnicodeNormalizeNFD(LmiWideString* dst, const LmiWideString* src);

/**
	{function visibility="private":
		{name: LmiUnicodeCanonicalizeSpaces}
		{parent: Unicode}
		{description: Canonicalize a Unicode string so that all characters with a compatibility mapping to Space (U+0020)
			are converted to space.}
		{prototype: LmiBool LmiUnicodeCanonicalizeSpaces(LmiWideString* dst, const LmiWideString* src)}
		{parameter:
			{name: dst}
			{description: The destination string to which to write the canonicalized string.  This may be the same
				as src for in-place canonicalization.}}
		{parameter:
			{name: src}
			{description: The source string to canonicalize.}}
		{return: LMI_TRUE if the string was successfully canonicalized, LMI_FALSE if not.}
	}
*/
LmiBool LmiUnicodeCanonicalizeSpaces(LmiWideString* dst, const LmiWideString* src);

LMI_END_EXTERN_C

#endif /* LMI_UNICODE_H_ */

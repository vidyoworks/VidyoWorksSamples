/** {file:
      {name: LmiUnicodePrecis.h}
      {description: Functions to perform PRECIS validations for Unicode strings.}
      {copyright:
      	(c) 2014 Vidyo, Inc.,
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

#ifndef LMI_UNICODE_PRECIS_H_
#define LMI_UNICODE_PRECIS_H_

#include <Lmi/Utils/LmiUnicode.h>
#include <Lmi/Utils/LmiBitset.h>

LMI_BEGIN_EXTERN_C

/**
	{function visibility="private":
		{name: LmiUnicodeValidatePrecisIdentifier}
		{parent: Unicode}
		{include: Lmi/Utils/LmiUnicodePrecis.h}
		{description: Validate whether a string is a valid Unicode Precis "IdentifierClass" string.}
		{prototype: LmiBool LmiUnicodeValidatePrecisIdentifier(const LmiWideString* str, const LmiBitset* additionalExclusions)}
		{parameter:
			{name: str}
			{description: The string to validate.  This should have already had appropriate normalization applied.}}
		{parameter:
			{name: additionalExclusions}
			{description: Optionally, a bitset of any additional characters that should be excluded from the string, or NULL if none.  The bitset should have codepoints set of the values to be excluded.}}
		{return: LMI_TRUE if the string validates, LMI_FALSE if not.}
	}
*/
LmiBool LmiUnicodeValidatePrecisIdentifier(const LmiWideString* str, const LmiBitset* additionalExclusions);

/**
	{function visibility="private":
		{name: LmiUnicodeValidatePrecisFreeform}
		{parent: Unicode}
		{include: Lmi/Utils/LmiUnicodePrecis.h}
		{description: Validate whether a string is a valid Unicode Precis "FreeformClass" string.}
		{prototype: LmiBool LmiUnicodeValidatePrecisFreeform(const LmiWideString* str, const LmiBitset* additionalExclusions)}
		{parameter:
			{name: str}
			{description: The string to validate.  This should have already had appropriate normalization applied.}}
		{parameter:
			{name: additionalExclusions}
			{description: Optionally, a bitset of any additional characters that should be excluded from the string, or NULL if none.  The bitset should have codepoints set of the values to be excluded.}}
		{return: LMI_TRUE if the string validates, LMI_FALSE if not.}
	}
*/
LmiBool LmiUnicodeValidatePrecisFreeform(const LmiWideString* str, const LmiBitset* additionalExclusions);


LMI_END_EXTERN_C

#endif /* LMI_UNICODE_PRECIS_H_ */

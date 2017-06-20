/**
{file:
	{name: LmiWildcardExpression.h}
	{description: A wildcard expression class.  The class can be used determine if arbitrary strings match a given wildcard expression. }
    {copyright:
		(c) 2016 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
*/


#ifndef LMI_WILDCARDEXPRESSION_H
#define LMI_WILDCARDEXPRESSION_H

#if 0 /* Save for when there is a BasicString(T) template */
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiWideString.h>

#define LmiWildcardExpression(T_)				LmiTemplate1(LmiWildcardExpression, T_)
#define LmiWildcardExpressionConstruct(T_)		LmiClassFunc(LmiWildcardExpression(T_), Construct)
#define LmiWildcardExpressionConstructCopy(T_)	LmiClassFunc(LmiWildcardExpression(T_), ConstructCopy)
#define LmiWildcardExpressionAssign(T_)			LmiClassFunc(LmiWildcardExpression(T_), Assign)
#define LmiWildcardExpressionDetruct(T_)		LmiClassFunc(LmiWildcardExpression(T_), Destruct)
#define LmiWildcardExpressionGetPattern(T_)		LmiClassFunc(LmiWildcardExpression(T_), GetPattern)
#define LmiWildcardExpressionMatch(T_)			LmiClassFunc(LmiWildcardExpression(T_), Match)
#define LmiWildcardExpressionEqual_(T_)			LmiClassFunc(LmiWildcardExpression(T_), Equal_)
#define LmiWildcardExpressionFind_(T_)			LmiClassFunc(LmiWildcardExpression(T_), Find_)
#define LmiWildcardExpressionLookAhead_(T_)		LmiClassFunc(LmiWildcardExpression(T_), LookAhead_)

#define Declare_LmiWildcardExpression(T_) \
typedef struct { \
	LmiBasicString(T_) pattern; \
} LmiWildcardExpression(T_); \
LmiWildcardExpression(T_)* LmiWildcardExpressionConstruct(T_)(LmiWildcardExpression(T_)* x, const LmiBasicString(T_)* pattern); \
LmiWildcardExpression(T_)* LmiWildcardExpressionConstructCopy(T_)(LmiWildcardExpression(T_)* x, const LmiWildcardExpression(T_)* y); \
LmiWildcardExpression(T_)* LmiWildcardExpressionAssign(T_)(LmiWildcardExpression(T_)* x, const LmiWildcardExpression(T_)* y); \
void LmiWildcardExpressionDestruct(T_)(LmiWildcardExpression(T_)* x); \
const T* LmiWildcardExpressionGetPattern(T_)(const LmiWildcardExpression(T_)* x); \
LmiBool LmiWildcardExpressionMatch(T_)(const LmiWildcardExpression(T_)* x, LmiBasicString(T_)* s, LmiBool caseSensitive);

#define Define_LmiWildcardExpression(T_) \
LmiWildcardExpression(T_)* LmiWildcardExpressionConstruct(T_)(LmiWildcardExpression(T_)* x, const LmiBasicString(T_)* pattern) { \
	return (LmiBasicStringConstructCopy(T_)(&x->pattern, pattern) != NULL) ? x : NULL; \
} \
LmiWildcardExpression(T_)* LmiWildcardExpressionConstructCopy(T_)(LmiWildcardExpression(T_)* x, const LmiWildcardExpression(T_)* y) { \
	return (LmiBasicStringConstructCopy(T_)(&x->pattern, &y->pattern) != NULL) ? x : NULL; \
} \
LmiWildcardExpression(T_)* LmiWildcardExpressionAssign(T_)(LmiWildcardExpression(T_)* x, const LmiWildcardExpression(T_)* y) { \
	return (LmiBasicStringAssign(T_)(&x->pattern, &y->pattern) != NULL) ? x : NULL; \
} \
void LmiWildcardExpressionDestruct(T_)(LmiWildcardExpression(T_)* x) { \
	LmiBasicStringDestruct(T_)(x->pattern); \
} \
const LmiBasicString(T_)* LmiWildcardExpressionGetPattern(T_)(const LmiWildcardExpression(T_)* x) { \
	return &x->pattern; \
} \
static LmiBool LmiWildcardExpressionEqual_(T_)(T_ a, T_ b, LmiBool caseSensitive) { \
	return a == b || ((!caseSensitive) && (LmiToLower_(T_)(a) == LmiToLower(T_)(b))); \
} \
static LmiSizeT LmiWildcardExpressionFind_(T_)(T_ c, LmiBasicString(T_)* s, LmiSizeT i, LmiBool caseSensitive) { \
	for (; i < LmiBasicStringSize(T_)(s); ++i) \
		if (c == (T_)'?' || LmiWildcardExpressionEqual_(T_)(LmiBasicStringAtConst(T_)(s, i), c, caseSensitive)) \
			return i; \
	return LmiBasicStringNpos(T_); \
} \
static LmiSizeT LmiWildcardExpressionLookAhead_(T_)(const LmiWildcardExpression(T_)* x, LmiSizeT i) { \
	while ((i < LmiBasicStringSize(T_)(&x->pattern)) && (LmiBasicStringAtConst(T_)(s, i) == (T_)'*') \
		++i; \
	return i; \
} \
LmiBool LmiWildcardExpressionMatch_(T_)(const LmiBasicString(T_)* pattern, LmiBasicString(T_)* s, LmiBool caseSensitive) { \
	LmiSizeT i, j = 0; \
	for (i = 0; i < LmiBasicStringSize(T_)(pattern); ++i) { \
		if (LmiBasicStringAtConst(T_)(pattern, i) == (T_)'?') { \
			++j; \
		} else if (LmiBasicStringAtConst(T_)(pattern, i) == (T_)'*') { \
			i = LmiWildcardExpressionLookAhead_(T_)(x, i + 1); \
			/* If wildcard is found at the end of the pattern */ \
			if (i == LmiBasicStringSize(T_)(pattern)) \
				return LMI_TRUE; \
			/* For all matches to the lookahead character, match substrings */ \
			while ((j = LmiWildcardExpressionFind_(T_)(LmiBasicStringAtConst(T_)(pattern, i), s, j, caseSensitive)) != LmiBasicStringNpos(T_)) { \
				LmiBasicString(T_) patternSubstring, substring; \
				LmiBool match; \
				LmiBasicStringConstruct(T_)(&patternSubstring, pattern, i + 1); \
				LmiBasicStringConstruct(T_)(&substring, s, j + 1); \
				match = LmiWildcardExpressionMatch_(T_)(&patternSubstring, &substring, caseSensitive); \
				LmiBasicStringDestruct(T_)(&patternSubstring); \
				LmiBasicStringDestruct(T_)(&substring); \
				if (match) return LMI_TRUE; \
				++j; \
			} \
			return LMI_FALSE; \
		} else { \
			if (LmiWildcardExpressionEqual_(T_)(LmiBasicStringAtConst(T_)(pattern, i), LmiBasicStringAtConst(T_)(s, j), caseSensitive)) \
				return LMI_FALSE; \
			++j; \
		} \
	}\
	return j == LmiBasicStringSize(T_)(s); \
} \
LmiBool LmiWildcardExpressionMatch(T_)(const LmiWildcardExpression(T_)* x, LmiBasicString(T_)* s, LmiBool caseSensitive) { \
	return LmiWildcardExpressionMatch_(T_)(&x->pattern, s, caseSensitive); \
} \

#else

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>

/**
{type visibility="private":
	{name: LmiWildcardExpressionOptions}
	{parent: LmiWildcardExpression}
	{include: Lmi/Utils/LmiWildcardExpression.h}
	{description: Options for controlling how the wildcard expression performs matches.}
	{value: {name: LMI_WILDCARDEXPRESSION_OPTIONS_None} {description: No options. Matches are case sensitive and support both exactly-one-character wildcards ('?') and zero-or-more-character wildcards ('*').}}
	{value: {name: LMI_WILDCARDEXPRESSION_OPTIONS_CaseInsensitive} {description: Matching is case insensitive.}}
	{value: {name: LMI_WILDCARDEXPRESSION_OPTIONS_QuestionMarksAreNotSignificant} {description: exactly-one-character wildcards ('?') are not recognized and are treated as a non-wildcard character in expressions.}}
}
*/
typedef LmiUint32 LmiWildcardExpressionOptions;
#define LMI_WILDCARDEXPRESSION_OPTIONS_None								0x00000000
#define LMI_WILDCARDEXPRESSION_OPTIONS_CaseInsensitive					0x00000001
#define LMI_WILDCARDEXPRESSION_OPTIONS_QuestionMarksAreNotSignificant	0x00000002


/**
{type visibility="private":
	{name: LmiWildcardExpression}
	{parent: Utils}
	{include: Lmi/Utils/LmiWildcardExpression.h}
	{description: A wildcard expression class.  The class can be used determine if arbitrary strings match a given wildcard expression.}
}
*/
typedef struct {
	LmiString pattern;
} LmiWildcardExpression;

LMI_BEGIN_EXTERN_C

/**
{function visibility="private":
	{name: LmiWildcardExpressionConstruct}
	{parent: LmiWildcardExpression}
	{description: Constructs a new wildcard expression.}
	{prototype: LmiWildcardExpression* LmiWildcardExpressionConstruct(LmiWildcardExpression* x, const LmiString* pattern)}
	{parameter:
		{name: x}
		{description: A pointer to the LmiWildcardExpression object to construct.}
	}
	{parameter:
		{name: pattern}
		{description: A pattern to intitialize the wildcard expression. The pattern consists of sequences of wildcard characters ('*' and possibly '?') and non-wildcard chracters (all other characters). An '*' matches zero or more characters,  A '?' matches exactly one character.}
	}
	{return: Returns a pointer to the constructed object or {code: NULL} otherwise.}
}
*/
LmiWildcardExpression* LmiWildcardExpressionConstruct(LmiWildcardExpression* x, const LmiString* pattern);


/**
{function visibility="private":
	{name: LmiWildcardExpressionConstructCopy}
	{parent: LmiWildcardExpression}
	{description: Constructs a new wildcard expression from and an existing one.}
	{prototype: LmiWildcardExpression* LmiWildcardExpressionConstructCopy(LmiWildcardExpression* x, const LmiWildcardExpression* y)}
	{parameter:
		{name: x}
		{description: A pointer to a wildcard expression object to construct.}
	}
	{parameter:
		{name: y}
		{description: A pointer to another wildcard expression from which to construct the wildcard expression. }
	}
	{return: Returns a pointer to the constructed object or {code: NULL} otherwise.}
}
*/
LmiWildcardExpression* LmiWildcardExpressionConstructCopy(LmiWildcardExpression* x, const LmiWildcardExpression* y);

/**
{function visibility="private":
	{name: LmiWildcardExpressionAssign}
	{parent: LmiWildcardExpression}
	{description: Assign one wildcard expression to another.}
	{prototype: LmiWildcardExpression* LmiWildcardExpressionAssign(LmiWildcardExpression* x, const LmiWildcardExpression* y)}
	{parameter:
		{name: x}
		{description: A pointer to a wildcard expression to be assigned to.}
	}
	{parameter:
		{name: y}
		{description: A pointer to another wildcard expression to be assigned from. }
	}
	{return: Returns a pointer to the assigned object or {code: NULL} otherwise.}
}
*/
LmiWildcardExpression* LmiWildcardExpressionAssign(LmiWildcardExpression* x, const LmiWildcardExpression* y);

/**
{function visibility="private":
	{name: LmiWildcardExpressionDestruct}
	{parent: LmiWildcardExpression}
	{description: Destruct a wildcard expression.}
	{prototype: void LmiWildcardExpressionDestruct(LmiWildcardExpression* x)}
	{parameter:
		{name: x}
		{description: Returns a pointer to a wildcard expression to destruct.}
	}
}
*/
void LmiWildcardExpressionDestruct(LmiWildcardExpression* x);

/**
{function visibility="private":
	{name: LmiWildcardExpressionGetPattern}
	{parent: LmiWildcardExpression}
	{description: Gets a point to the string containing the wildcard expressions pattern.}
	{prototype: const LmiString* LmiWildcardExpressionGetPattern(const LmiWildcardExpression* x)}
	{parameter:
		{name: x}
		{description: A pointer to a wildcard expression.}
	}
	{return: Returns a pointer to the wildcard expressions pattern.}
}
*/
const LmiString* LmiWildcardExpressionGetPattern(const LmiWildcardExpression* x);


/**
{function visibility="private":
	{name: LmiWildcardExpressionMatch}
	{parent: LmiWildcardExpression}
	{description: Determine whether a string matches the wildcard expression.}
	{prototype: LmiBool LmiWildcardExpressionMatch(const LmiWildcardExpression* x, LmiWildcardExpressionOptions options, const LmiString* s)}
	{parameter:
		{name: x}
		{description: A pointer to a wildcard expression.}
	}
  	{parameter:
		{name: options}
		{description: Options to control how the string is matched to the wildcard expression.}
	}
 	{parameter:
		{name: s}
		{description: A pointer to the string to match to the wildcard expression.}
	}
	{return: Returns LMI_TRUE if the string matches the wildcard expression or LMI_FALSE if it does not.}
}
*/
LmiBool LmiWildcardExpressionMatch(const LmiWildcardExpression* x, LmiWildcardExpressionOptions options, const LmiString* s);

LMI_END_EXTERN_C

#endif

#endif /* LMI_WILDCARDEXPRESSION_H */

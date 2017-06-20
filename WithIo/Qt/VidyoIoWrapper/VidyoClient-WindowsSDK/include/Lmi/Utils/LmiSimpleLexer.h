/** 
{file:
	{name: LmiSimpleLexer.h}
	{description: Object to provide a simple lexer.}
	{copyright:
		(c) 2006-2012 Vidyo, Inc.,
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
#ifndef LMI_SIMPLELEXER_H_
#define LMI_SIMPLELEXER_H_

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="private":
	{name: LmiSimpleLexer}
	{parent: Utils}
	{include: Lmi/Utils/LmiSimpleLexer.h}
	{description: 
		{p: Construct a simple lexical analyzer.}
	}
}
*/
typedef struct {
	char* p;
} LmiSimpleLexer;

/**
{function visibility="private":
	{name: LmiSimpleLexerConstruct}
	{parent: LmiSimpleLexer}
	{description: 
		{p: Construct a simple lexical analyzer.}
	}
	{prototype: LmiSimpleLexer* LmiSimpleLexerConstruct(LmiSimpleLexer* x, char* buf)}
	{parameter:
		{name: x}
		{description: A pointer to the simple lexical analyzer to construct.}
	}
	{parameter:
		{name: buf}
		{description: The input buffer to be scanned for tokens.}
	}

	{return: A pointer to the lexical analyzer, or NULL on failure.}
}
*/
LmiSimpleLexer* LmiSimpleLexerConstruct(LmiSimpleLexer* x, char* buf);

/**
{function visibility="private":
	{name: LmiSimpleLexerDestruct}
	{parent: LmiSimpleLexer}
	{description: 
		{p: Destruct a simple lexical analyzer.}
	}
	{prototype: void LmiSimpleLexerDestruct(LmiSimpleLexer* x)}
	{parameter:
		{name: x}
		{description: A pointer to the simple lexical analyzer to destruct.}
	}
}
*/
void LmiSimpleLexerDestruct(LmiSimpleLexer* x);

/**
{function visibility="private":
	{name: LmiSimpleLexerGetToken}
	{parent: LmiSimpleLexer}
	{description: 
		{p: Find the next token in input buffer.}
	}
	{prototype: char* LmiSimpleLexerGetToken(LmiSimpleLexer* x, const char* delimiters, LmiBool skipLeading, LmiBool enableEscape)}
	{parameter:
		{name: x}
		{description: A pointer to the simple lexical analyzer.}
	}
	{parameter:
		{name: delimiters}
		{description: A C string containing the delimiter characters.}
	}
	{parameter:
		{name: skipLeading}
		{description: 
			Indicates whether leading delimiter characters should be 
			skipped before searching to the delimiters.
		}
	}
	{parameter:
		{name: enableEscape}
		{description: 
			Indicates whether backslash characters should be interpreted as an 
			"escape" preventing interpretation of the character following the 
			backslash.
		}
	}
	{return: A pointer to a C string containing the next token or NULL at end of string.}
}
*/
char* LmiSimpleLexerGetToken(LmiSimpleLexer* x, const char* delimiters, LmiBool skipLeading, LmiBool enableEscape);

LMI_END_EXTERN_C

#endif

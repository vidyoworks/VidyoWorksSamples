/** {file:
      {name: LmiAssert.h}
      {description: Functionality to support run-time assertions.}
      {copyright:
      	(c) 2005-2011 Vidyo, Inc.,
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

#ifndef LMI_ASSERT_H_
#define LMI_ASSERT_H_

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

#ifdef NDEBUG /* Standard C's <assert.h> macro to disable assertions */
#define LMI_ASSERT_DISABLE
#endif

/**
   {package:
     {name: Assert}
	 {parent: Utils}
     {include: Lmi/Utils/LmiAssert.h}
	 {description: Functions for asserting conditions.}
   }
*/

/**
   {function visibility="private":
     {name: LmiAssert}
     {parent: Assert}
     {description: Declare that a condition must hold, or terminate
       execution of the program.}
     {prototype: void LmiAssert(LmiBool expression)}
     {parameter:
       {name: expression}
       {description: A boolean expression that must evaluate to true.}}
     {note: If an assert callback has been set with LmiAssertSetCallback,
       it will be invoked by failing assertions.  Otherwise, a
       system-dependent operation will be performed.}
     {note: This function does not return.}
	 {note: If the system is compiled with the LMI_ASSERT_DISABLE
	   preprocessor symbol set, this function is compiled to nothing.
	   Note that this includes any side-effects of its argument.}
	 {note: The Standard C NDEBUG preprocessor symbol implies LMI_ASSERT_DISABLE.}
   }
*/

#if defined(LMI_ASSERT_DISABLE)

#define LmiAssert(expression) ((void)(0 && (expression)))

#else

#define LmiAssert(expression) \
  ((expression) ? (void)0 : \
   LmiDoAssert_(#expression, LMI_FUNCTION, __FILE__, __LINE__))

#endif

/**
   {function visibility="internal":
     {name: LmiDoAssert_}
     {parent: Assert}
     {description: Function called by LmiAssert macro when an assertion
     fails.}
     {prototype: void LmiDoAssert_(const char* expression, const char* function,
                  const char* file, LmiInt line)}
     {parameter:
       {name: expression}
       {description: A string containing the literal contents, in the
         source code, of the failing call to LmiAssert.}}
     {parameter:
       {name: function}
       {description: The name of the function containing the failing
         call to LmiAssert, if available from the compiler.  Otherwise,
         the empty string "".}}
     {parameter:
       {name: file}
       {description: The name of the file containing the failing call to
         LmiAssert.}}
     {parameter:
       {name: line}
       {description: The line number of the failing call to LmiAssert.}}
   }
*/
LMI_NO_RETURN void LmiDoAssert_(const char* expression, const char *function,
                  const char *file, LmiInt line);


/**
   {callback:
     {name: LmiAssertCallback}
     {parent: Assert}
     {description: Report a failing assertion, and terminate program
       execution.}
     {prototype: void (*LmiAssertCallback)(const char* expression,
                                           const char* function,
                                           const char* file, LmiInt line)}
     {parameter:
       {name: expression}
       {description: A string containing the literal contents, in the
         source code, of the failing call to LmiAssert.}}
     {parameter:
       {name: function}
       {description: The name of the function containing the failing
         call to LmiAssert, if available from the compiler.  Otherwise,
         the empty string "".}}
     {parameter:
       {name: file}
       {description: The name of the file containing the failing call to
         LmiAssert.}}
     {parameter:
       {name: line}
       {description: The line number of the failing call to LmiAssert.}}
     {note: This function terminates program execution; it should not return.}
   }
*/

typedef void (*LmiAssertCallback)(const char* expression,
                                  const char* function,
                                  const char* file, LmiInt line);


/**
   {function:
     {name: LmiAssertSetCallback}
     {parent: Assert}
     {description: Set a callback function to be invoked when an assertion
       fails.}
     {prototype: void LmiAssertSetCallback(LmiAssertCallback callback)}
     {parameter:
       {name: callback}
       {description: The callback to be invoked, or NULL.  If NULL, a
         system-dependent operation will be performed when an assertion
         fails.}}
     {note: This function is not thread-safe.  The assert callback should
       generally be set at program startup time and not modified thereafter.}
   }
*/

void LmiAssertSetCallback(LmiAssertCallback callback);

LMI_END_EXTERN_C

#endif /* LMI_ASSERT_H_ */

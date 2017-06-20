/**
{file:
	{name: LmiWindowIdInline.h}
	{description: Describes an Operating System specific window identifier.}
	{copyright:
		(c) 2012-2015 Vidyo, Inc.,
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

#if defined(ANDROID)
#include <Lmi/Os/LmiAndroid.h>

LMI_INLINE LmiWindowId *LmiWindowIdConstructInvalid(LmiWindowId *x)
{
    *x = 0;
    return x;
}

LMI_INLINE LmiWindowId *LmiWindowIdConstructCopy(LmiWindowId *a, const LmiWindowId *b)
{
    *a = *b;
    return a;
}

LMI_INLINE void LmiWindowIdDestruct(LmiWindowId *x)
{
}

LMI_INLINE LmiWindowId *LmiWindowIdAssign(LmiWindowId *a, const LmiWindowId *b)
{
    *a = *b;
    return a;
}

LMI_INLINE LmiBool LmiWindowIdEqual(const LmiWindowId *a, const LmiWindowId *b)
{
    return *a == *b;
}

LMI_INLINE LmiBool LmiWindowIdLess(const LmiWindowId *a, const LmiWindowId *b)
{
    return *a < *b;
}

LMI_INLINE LmiBool LmiWindowIdIsValid(const LmiWindowId *x)
{
    return *x != 0;
}


LMI_INLINE LmiViewId *LmiViewIdConstructInvalid(LmiViewId *x)
{
    *x = 0;
    return x;
}

LMI_INLINE LmiViewId *LmiViewIdConstructCopy(LmiViewId *a, const LmiViewId *b)
{
    LmiAndroid android;
    JNIEnv* env;

	if (*b == 0) {
		*a = 0;
		return a;
	}

    if(LmiAndroidConstruct(&android) == NULL)
        return NULL;
    env = LmiAndroidGetEnv(&android);
    if(env == NULL){
        LmiAndroidDestruct(&android);
        return NULL;
    }
    
    *a = (*env)->NewGlobalRef(env, *b);
    
    LmiAndroidReleaseEnv(&android);
    LmiAndroidDestruct(&android);

    if (*a == NULL)
        return NULL;

    return a;
}

LMI_INLINE void LmiViewIdDestruct(LmiViewId *x)
{
    LmiAndroid android;
    JNIEnv* env;
    if(LmiAndroidConstruct(&android) == NULL)
        return;
    env = LmiAndroidGetEnv(&android);
    if(env == NULL){
        LmiAndroidDestruct(&android);
        return;
    }
    
    if(*x)
        (*env)->DeleteGlobalRef(env, *x);
    
    LmiAndroidReleaseEnv(&android);
    LmiAndroidDestruct(&android);
    return;
  
}

LMI_INLINE LmiViewId *LmiViewIdAssign(LmiViewId *a, const LmiViewId *b)
{

    LmiAndroid android;
    JNIEnv* env;
    LmiViewId* ret = a;
	LmiViewId save;

    if(LmiAndroidConstruct(&android) == NULL)
        return NULL;
    env = LmiAndroidGetEnv(&android);
    if(env == NULL){
        LmiAndroidDestruct(&android);
        return NULL;
    }
    
	save = *a;	/* Handle failure and self-assignment correctly. */
	if (*b != 0) {
		*a = (*env)->NewGlobalRef(env, *b);
		if (*a == NULL) {
			ret = NULL;
		}
	} else {
		*a = 0;
	}

	if (save != 0 && ret != NULL) {
		(*env)->DeleteGlobalRef(env, save);
	}
    
    LmiAndroidReleaseEnv(&android);
    LmiAndroidDestruct(&android);

    return ret;
}

LMI_INLINE LmiBool LmiViewIdEqual(const LmiViewId *a, const LmiViewId *b)
{
    LmiAndroid android;
    JNIEnv* env;
    LmiBool ret = LMI_FALSE;
    if(LmiAndroidConstruct(&android) == NULL)
        return ret;
    env = LmiAndroidGetEnv(&android);
    if(env == NULL){
        LmiAndroidDestruct(&android);
        return ret;
    }
	if (*a == 0 || *b == 0){
		ret = (*a == *b);
	} else {
		ret = (*env)->IsSameObject(env, *a, *b);
    }
    
    LmiAndroidReleaseEnv(&android);
    LmiAndroidDestruct(&android);
    return ret;
}

LMI_INLINE LmiBool LmiViewIdLess(const LmiViewId *a, const LmiViewId *b)
{
    return *a < *b;
}

LMI_INLINE LmiBool LmiViewIdIsValid(const LmiViewId *x)
{
    return *x != 0;
}


#else
LMI_INLINE LmiWindowId *LmiWindowIdConstructInvalid(LmiWindowId *x)
{
    *x = 0;
    return x;
}

LMI_INLINE LmiWindowId *LmiWindowIdConstructCopy(LmiWindowId *a, const LmiWindowId *b)
{
    *a = *b;
    return a;
}

LMI_INLINE void LmiWindowIdDestruct(LmiWindowId *x)
{
}

LMI_INLINE LmiWindowId *LmiWindowIdAssign(LmiWindowId *a, const LmiWindowId *b)
{
    *a = *b;
    return a;
}

LMI_INLINE LmiBool LmiWindowIdEqual(const LmiWindowId *a, const LmiWindowId *b)
{
    return *a == *b;
}

LMI_INLINE LmiBool LmiWindowIdLess(const LmiWindowId *a, const LmiWindowId *b)
{
    return *a < *b;
}

LMI_INLINE LmiBool LmiWindowIdIsValid(const LmiWindowId *x)
{
    return *x != 0;
}


LMI_INLINE LmiViewId *LmiViewIdConstructInvalid(LmiViewId *x)
{
    *x = 0;
    return x;
}

LMI_INLINE LmiViewId *LmiViewIdConstructCopy(LmiViewId *a, const LmiViewId *b)
{
    *a = *b;
    return a;
}

LMI_INLINE void LmiViewIdDestruct(LmiViewId *x)
{
}

LMI_INLINE LmiViewId *LmiViewIdAssign(LmiViewId *a, const LmiViewId *b)
{
    *a = *b;
    return a;
}

LMI_INLINE LmiBool LmiViewIdEqual(const LmiViewId *a, const LmiViewId *b)
{
    return *a == *b;
}

LMI_INLINE LmiBool LmiViewIdLess(const LmiViewId *a, const LmiViewId *b)
{
    return *a < *b;
}

LMI_INLINE LmiBool LmiViewIdIsValid(const LmiViewId *x)
{
    return *x != 0;
}


#endif





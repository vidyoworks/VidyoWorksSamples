/**
{file: 
        {name: LmiVersionInline.h}
        {description: Inline functions of the LmiVersion class.}
        {copyright:
                (c) 2009-2015 Vidyo, Inc.,
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
LMI_INLINE LmiVersion* LmiVersionConstruct(LmiVersion* x, LmiUint major, LmiUint minor, LmiUint engineering, LmiUint patch) {
	*x = (major << 24) | ((minor & 0xFF) << 16) | ((engineering & 0xFF) << 8) | (patch & 0xFF);
	return x;
}

LMI_INLINE LmiVersion* LmiVersionConstructCopy(LmiVersion* x, const LmiVersion* y) {
	*x = *y;
	return x;
}

LMI_INLINE LmiVersion* LmiVersionAssign(LmiVersion* x, const LmiVersion* y) {
	*x = *y;
	return x;
}

LMI_INLINE LmiBool LmiVersionEqual(const LmiVersion* x, const LmiVersion* y) {
	return *x == *y;
}

LMI_INLINE LmiBool LmiVersionLess(const LmiVersion* x, const LmiVersion* y) {
	return *x < *y;
}

LMI_INLINE LmiUint LmiVersionGetMajor(const LmiVersion* x) {
	return (LmiUint)(*x >> 24);	
}

LMI_INLINE LmiUint LmiVersionGetMinor(const LmiVersion* x) {
	return (LmiUint)((*x >> 16) & 0xFF);	
}

LMI_INLINE LmiUint LmiVersionGetEngineering(const LmiVersion* x) {
	return (LmiUint)((*x >> 8) & 0xFF);	
}

LMI_INLINE LmiUint LmiVersionGetPatch(const LmiVersion* x) {
	return (LmiUint)(*x & 0xFF);	
} 


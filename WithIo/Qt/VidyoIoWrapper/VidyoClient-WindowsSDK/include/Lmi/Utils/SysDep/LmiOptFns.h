/** {file:
      {name: LmiOptFns.h}
      {description: File that determines what types of optimized functions are supported..}
      {copyright:
      	(c) 2007-2015 Vidyo, Inc.,
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

#ifndef LMI_OPT_FNS_H_
#define LMI_OPT_FNS_H_

/* Define these if we can *assume* these CPU features are present. */
/* #define LMI_OPTFNS_ASSUME_SSE 1 */
/* #define LMI_OPTFNS_ASSUME_SSE2 1 */ /* Must also define LMI_OPTFNS_ASSUME_SSE */
/* #define LMI_OPTFNS_ASSUME_SSSE3 1 */ /* Must also define LMI_OPTFNS_ASSUME_SSE2 */
/* #define LMI_OPTFNS_ASSUME_AESNI 1 */ /* Must also define LMI_OPTFNS_ASSUME_SSSE3 */

/* #define LMI_OPTFNS_ASSUME_NEON 1 */
/* #define LMI_OPTFNS_ASSUME_ARM_CRYPT 1 */

// #define LMI_OPTFNS_USE_C_CODE 1

#ifndef LMI_OPTFNS_USE_C_CODE
/* Determine what types of in-line optimized function definitions are
 * available.  This file defines macros for all the available types; function
 * definitions must be #ifdef'd appropriately. */

/* This file must be included after the appropriate LmiConfig*.h file.
 * (In general, it should only be included from Lmi/Utils/LmiCompiler.h.) */

/* Microsoft Visual C/Intel x86 __asm { } syntax. */

#if defined(_MSC_VER) && defined(_M_IX86) && !defined(_WIN64) && !defined(LMI_OPTFNS_NO_INLINE_ASM)
#define LMI_OPTFNS_HAVE_VISUALSTUDIO_INTEL_ASM 1
#endif


#if LMI_HAVE_XMMINTRIN_H
#define LMI_HAVE_SSE_INTRINSICS 1
#endif

#if LMI_HAVE_EMMINTRIN_H
#define LMI_OPTFNS_HAVE_INTEL_INTRINSICS 1
#define LMI_HAVE_SSE2_INTRINSICS 1
#endif

#if LMI_HAVE_TMMINTRIN_H
#define LMI_HAVE_SSSE3_INTRINSICS 1
#endif

#if LMI_HAVE_SMMINTRIN_H
#define LMI_HAVE_SSSE4_1_INTRINSICS 1
#endif

#if LMI_HAVE_NMMINTRIN_H
#define LMI_HAVE_SSSE4_2_INTRINSICS 1
#endif

#if LMI_HAVE_WMMINTRIN_H
#define LMI_HAVE_AESNI_INTRINSICS 1
#endif

#if LMI_HAVE_IMMINTRIN_H
#define LMI_HAVE_AVX_INTRINSICS 1
#if LMI_HAVE__MM256_ADD_EPI32
#define LMI_HAVE_AVX2_INTRINSICS 1
#endif
#endif

/* GCC extended ASM on the x86 */
#if __GNUC__ &&  __i386__ && !defined(LMI_OPTFNS_NO_INLINE_ASM)
#define LMI_OPTFNS_HAVE_GCC_INTEL_ASM 1
#endif

/* GCC extended ASM on the x86-64 */
#if __GNUC__ && __x86_64__ && !defined(LMI_OPTFNS_NO_INLINE_ASM)
#define LMI_OPTFNS_HAVE_GCC_INTEL64_ASM 1
#endif

#if LMI_OPTFNS_HAVE_GCC_INTEL_ASM
#define LMI_X86_RAX  "eax"
#define LMI_X86_RBX  "ebx"
#define LMI_X86_RCX  "ecx"
#define LMI_X86_RDX  "edx"
#define LMI_X86_RDI  "edi"
#define LMI_X86_RSI  "esi"
#elif LMI_OPTFNS_HAVE_GCC_INTEL64_ASM
#define LMI_X86_RAX  "rax"
#define LMI_X86_RBX  "rbx"
#define LMI_X86_RCX  "rcx"
#define LMI_X86_RDX  "rdx"
#define LMI_X86_RDI  "rdi"
#define LMI_X86_RSI  "rsi"
#endif



/* Apple gcc/PowerPC __asm { } syntax. */
#if LMI_HAVE_POWERPC_ALTIVEC_ASM && !defined(LMI_OPTFNS_NO_INLINE_ASM)
#define LMI_OPTFNS_HAVE_POWERPC_ALTIVEC_ASM 1
#endif

/* GCC extended ASM on ARM */
#if __GNUC__ &&  __arm__ && !defined(LMI_OPTFNS_NO_INLINE_ASM)
#define LMI_OPTFNS_HAVE_GCC_ARM_ASM 1
#endif

/* Old name of this define, deprecated */
#if defined(LMI_OPTFNS_HAVE_GCC_ARM_ASM)
#define LMI_OPTFNS_HAVE_GCC_ARM LMI_OPTFNS_HAVE_GCC_ARM_ASM
#endif

/* GCC extended ASM on ARM64 */
#if __GNUC__ &&  (__arm64__ || __aarch64__) && !defined(LMI_OPTFNS_NO_INLINE_ASM)
#define LMI_OPTFNS_HAVE_GCC_ARM64_ASM 1
#endif

/* ARM Neon intrinsics: <arm_neon.h>.  Detected by autoconf
 * or the like. */
#if LMI_HAVE_ARM_NEON_H && (__i386__ || __x86_64__ || defined(_M_IX86) || defined(_M_X64))
/* Emulated arm_neon.h on x86 (neon2sse).  We don't want to use it. */
#undef LMI_HAVE_ARM_NEON_H
#endif

#if LMI_HAVE_ARM_NEON_H
#define LMI_OPTFNS_HAVE_ARM_NEON 1

#if defined(__arm64__) || defined(__aarch64__)
#define LMI_OPTFNS_HAVE_ARM64_NEON 1
#endif

#if LMI_HAVE_VAESEQ_U8
#define LMI_OPTFNS_HAVE_ARM_CRYPT 1
#endif

/* Initial Apple versions of arm64 had the name of some Neon intrinsics different than
 the names the ARM ACLE 2.0 eventually decided for them. */
#if LMI_OPTFNS_HAVE_ARM64_NEON && defined(__APPLE_CC__) && __apple_build_version__ < 6020000
#define LMI_NEON_VQTBL1_U8(t, idx) vtbl1q_u8(t, idx)
#define LMI_NEON_VQTBL2_U8(t, idx) vtbl2q_u8(t, idx)

#else
#define LMI_NEON_VQTBL1_U8(t, idx) vqtbl1_u8(t, idx)
#define LMI_NEON_VQTBL2_U8(t, idx) vqtbl2_u8(t, idx)

#endif

#endif

#if LMI_OPTFNS_HAVE_GCC_ARM_ASM

/* ARM Unified syntax (the only form accepted by recent Clang) differs
 * from the classic syntax (the only form accepted by GNU as in ARM mode)
 * for certain forms of conditional stores. */
#if __clang__ || __thumb__
#define LMI_ARM_STRHGE "strhge"
#define LMI_ARM_STRBGE "strbge"
#else
#define LMI_ARM_STRHGE "strgeh"
#define LMI_ARM_STRBGE "strgeb"
#endif

#endif

#endif /* !defined LMI_OPTFNS_USE_C_CODE */

#if !defined(LMI_OPTFNS_USE_C_CODE) \
	&& !defined(LMI_OPTFNS_HAVE_VISUALSTUDIO_INTEL_ASM) \
	&& !defined(LMI_OPTFNS_HAVE_INTEL_INTRINSICS) \
	&& !defined(LMI_OPTFNS_HAVE_GCC_INTEL_ASM) \
	&& !defined(LMI_OPTFNS_HAVE_GCC_INTEL64_ASM) \
	&& !defined(LMI_OPTFNS_HAVE_POWERPC_ALTIVEC_ASM) \
	&& !defined(LMI_OPTFNS_HAVE_GCC_ARM_ASM) \
	&& !defined(LMI_OPTFNS_HAVE_ARM_NEON) \
	&& !defined(LMI_OPTFNS_HAVE_ARM_CRYPT)

/* If we have no way of doing optimized code at all, force use of C code. */
#define LMI_OPTFNS_USE_C_CODE 1

#endif

#if defined(LMI_OPTFNS_USE_C_CODE)

#undef LMI_OPTFNS_ASSUME_SSE2
#undef LMI_OPTFNS_ASSUME_SSSE3
#undef LMI_OPTFNS_ASSUME_AESNI

#undef LMI_OPTFNS_ASSUME_NEON
#undef LMI_OPTFNS_ASSUME_ARM_CRYPT

#endif 

#if defined(LMI_OPTFNS_ASSUME_SSE2)
#define LMI_INLINE_DECLARATION_SSE2 LMI_INLINE_DECLARATION
#else
#define LMI_INLINE_DECLARATION_SSE2 /* */
#endif

#if defined(LMI_OPTFNS_ASSUME_SSSE2)
#define LMI_INLINE_DECLARATION_SSSE3 LMI_INLINE_DECLARATION
#else
#define LMI_INLINE_DECLARATION_SSSE3 /* */
#endif

#if defined(LMI_OPTFNS_ASSUME_AESNI)
#define LMI_INLINE_DECLARATION_AESNI LMI_INLINE_DECLARATION
#else
#define LMI_INLINE_DECLARATION_AESNI /* */
#endif

#if defined(LMI_OPTFNS_ASSUME_NEON)
#define LMI_INLINE_DECLARATION_NEON LMI_INLINE_DECLARATION
#else
#define LMI_INLINE_DECLARATION_NEON /* */
#endif

#if defined(LMI_OPTFNS_ASSUME_ARM_CRYPT)
#define LMI_INLINE_DECLARATION_ARM_CRYPT LMI_INLINE_DECLARATION
#else
#define LMI_INLINE_DECLARATION_ARM_CRYPT /* */
#endif


#endif /* LMI_OPT_FNS_H_ */


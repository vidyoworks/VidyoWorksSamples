/**
   {file:
     {name: LmiProcessorInline.h}
     {description: Inline functions for LmiProcessor.}
     {copyright:
     	(c) 2013-2014 Vidyo, Inc.,
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

#include <Lmi/Utils/LmiStdCLib.h>

LMI_INLINE LmiProcessorTimes *LmiProcessorTimesConstructDefault(LmiProcessorTimes *t)
{
	t->idleTime = 0;
	t->totalTime = 0;
	return t;
}

LMI_INLINE LmiProcessorTimes *LmiProcessorTimesConstructCopy(LmiProcessorTimes *d, const LmiProcessorTimes *s)
{
	*d = *s;
	return d;
}

LMI_INLINE void LmiProcessorTimesDestruct(LmiProcessorTimes *t)
{
}

LMI_INLINE LmiProcessorTimes *LmiProcessorTimesAssign(LmiProcessorTimes *d, const LmiProcessorTimes *s)
{
	*d = *s;
	return d;
}

LMI_INLINE LmiUint64 LmiProcessorTimesGetIdleTime(const LmiProcessorTimes* t)
{
	return t->idleTime;
}


LMI_INLINE LmiUint64 LmiProcessorTimesGetTotalTime(const LmiProcessorTimes* t)
{
	return t->totalTime;
}


LMI_INLINE LmiProcessorArch LmiProcessorGetArch(const LmiProcessor* p)
{
	return p->arch;
}


LMI_INLINE LmiProcessorVendor LmiProcessorGetVendor(const LmiProcessor* p)
{
	return p->vendor;
}


LMI_INLINE LmiBool LmiProcessorGetX86VendorId(const LmiProcessor* p, char nameBuf[13])
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	LmiMemCpy(nameBuf, p->u.x86.vendorId, 13);
	return LMI_TRUE;
}


LMI_INLINE LmiBool LmiProcessorGetX86ProcessorBrandString(const LmiProcessor* p, char nameBuf[49])
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	LmiMemCpy(nameBuf, p->u.x86.processorBrandString, 49);
	return LMI_TRUE;
}


LMI_INLINE LmiUint LmiProcessorGetX86FamilyId(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return 0;

	return p->u.x86.familyId;
}


LMI_INLINE LmiUint LmiProcessorGetX86ModelId(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return 0;

	return p->u.x86.modelId;
}


LMI_INLINE LmiUint LmiProcessorGetX86SteppingId(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return 0;

	return p->u.x86.steppingId;
}


LMI_INLINE LmiUint LmiProcessorGetArmImplementer(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM)
		return 0;

	return p->u.arm.implementor;
}


LMI_INLINE LmiProcessorArmArch LmiProcessorGetArmArchitecture(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM)
		return LMI_PROCESSORARMARCH_Unknown;

	return p->u.arm.architecture;
}


LMI_INLINE LmiUint LmiProcessorGetArmVariant(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM)
		return 0;

	return p->u.arm.variant;
}


LMI_INLINE LmiUint LmiProcessorGetArmPart(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM)
		return 0;

	return p->u.arm.part;
}


LMI_INLINE LmiUint LmiProcessorGetArmRevision(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM)
		return 0;

	return p->u.arm.revision;
}


LMI_INLINE LmiProcessorModel LmiProcessorGetModel(const LmiProcessor* p)
{
	return p->model;
}


LMI_INLINE LmiUint LmiProcessorGetNumPhysicalCores(const LmiProcessor* p)
{
	return p->physicalCores;
}


LMI_INLINE LmiUint LmiProcessorGetNumLogicalCores(const LmiProcessor* p)
{
	return p->logicalCores;
}


LMI_INLINE LmiUint LmiProcessorGetSpeed(const LmiProcessor* p)
{
	return p->speed;
}


LMI_INLINE LmiBool LmiProcessorHasHyperthreading(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasHyperthreading;
}


LMI_INLINE LmiBool LmiProcessorHasSse(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasSse;
}


LMI_INLINE LmiBool LmiProcessorHasSse2(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasSse2;
}


LMI_INLINE LmiBool LmiProcessorHasSse3(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasSse3;
}


LMI_INLINE LmiBool LmiProcessorHasSsse3(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasSsse3;
}


LMI_INLINE LmiBool LmiProcessorHasSse4_1(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasSse4_1;
}


LMI_INLINE LmiBool LmiProcessorHasSse4_2(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasSse4_2;
}


LMI_INLINE LmiBool LmiProcessorHasAes(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasAes;
}


LMI_INLINE LmiBool LmiProcessorHasAvx(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasAvx;
}


LMI_INLINE LmiBool LmiProcessorHasAvx2(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_X86 && p->arch != LMI_PROCESSORARCH_X86_64)
		return LMI_FALSE;

	return p->u.x86.hasAvx2;
}


LMI_INLINE LmiBool LmiProcessorHasNeon(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM && p->arch != LMI_PROCESSORARCH_ARM64)
		return LMI_FALSE;

	return p->u.arm.hasNeon;
}


LMI_INLINE LmiBool LmiProcessorHasArmCrypt(const LmiProcessor* p)
{
	if (p->arch != LMI_PROCESSORARCH_ARM && p->arch != LMI_PROCESSORARCH_ARM64)
		return LMI_FALSE;

	return p->u.arm.hasArmCrypt;
}


LMI_INLINE LmiBool LmiProcessorGetTimes(const LmiProcessor* p, LmiProcessorTimes *t)
{
	return p->getTimes(p, t, p->userData);
}


LMI_INLINE LmiBool LmiProcessorGetTimesPerCore(const LmiProcessor* p, LmiProcessorTimes *t, LmiUint* n)
{
	return p->getTimesPerCore(p, t, n, p->userData);
}

/**
{file:
	{name: LmiProcessor.h}
	{description: A generic class to learn about the processor information}
	{copyright:
		(c) 2008-2016 Vidyo, Inc.
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
#ifndef LMI_PROCESSOR_H
#define LMI_PROCESSOR_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

/**
	{package:
		{name: Processor}
		{parent: Os}
		{include: Lmi/Os/LmiProcessor.h}
		{description: Information about system processors.}
	}
*/


/**
	{type:
		{name: LmiProcessorTimes}
		{parent: Processor}
		{description: A representation of the time usage of a processor.}
	}
*/
typedef struct
{
	LmiUint64 idleTime;
	LmiUint64 totalTime;
} LmiProcessorTimes;


/**
	{function:
		{name: LmiProcessorTimesConstructDefault}
		{parent: LmiProcessorTimes}
		{description: Construct a default instance of an LmiProcessorTimes object.}
		{prototype: LmiProcessorTimes* LmiProcessorTimesConstructDefault(LmiProcessorTimes* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiProcessorTimes object to initialize.}}
		{return: The constructed object on success, otherwise NULL.}
		{note: Both the total time and idle time values of the LmiProcessorTimes object will be
			initialized with the value 0.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorTimes *LmiProcessorTimesConstructDefault(LmiProcessorTimes *t);

/**
	{function:
		{name: LmiProcessorTimesConstructCopy}
		{parent: LmiProcessorTimes}
		{description: Construct a new LmiProcessorTimes object as a copy of an
			existing one.}
		{prototype: LmiProcessorTimes* LmiProcessorTimesConstructCopy(LmiProcessorTimes* dst, const LmiProcessorTimes* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiProcessorTimes object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiProcessorTimes object.}}
		{return: The constructed object on success, otherwise NULL.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorTimes *LmiProcessorTimesConstructCopy(LmiProcessorTimes *d, const LmiProcessorTimes *s);

/**
	{function:
		{name: LmiProcessorTimesDestruct}
		{parent: LmiProcessorTimes}
		{description: Destruct an LmiProcessorTimes object.}
		{prototype: void LmiProcessorTimesDestruct(LmiProcessorTimes* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiProcessorTimes object to destruct.}}
	}
*/
LMI_INLINE_DECLARATION void LmiProcessorTimesDestruct(LmiProcessorTimes *t);

/**
	{function:
		{name: LmiProcessorTimesAssign}
		{parent: LmiProcessorTimes}
		{description: Assign the value of one LmiProcessorTimes object to another one.}
		{prototype: LmiProcessorTimes* LmiProcessorTimesAssign(LmiProcessorTimes* dst, const LmiProcessorTimes* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiProcessorTimes object to be assigned.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiProcessorTimes object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorTimes *LmiProcessorTimesAssign(LmiProcessorTimes *d, const LmiProcessorTimes *s);
   

/**
	{function:
		{name: LmiProcessorTimesGetIdleTime}
		{parent: LmiProcessorTimes}
		{description: Get the number of idle cycles represented in an LmiProcessorTimes object.}
		{prototype: LmiUint64 LmiProcessorTimesGetIdleTime(const LmiProcessorTimes* t)}
		{parameter:
			{name: t}
			{description: The LmiProcessorTimes object from which to get the idle time.}}
		{return: The number of idle cycles represented in this object.  The units are
			system-dependent and arbitrary, but are consistent with the total time in the same
			object, and with other LmiProcessorTimes derived from the same processor or core.}
	}
*/
LMI_INLINE_DECLARATION LmiUint64 LmiProcessorTimesGetIdleTime(const LmiProcessorTimes* t);


/**
	{function:
		{name: LmiProcessorTimesGetTotalTime}
		{parent: LmiProcessorTimes}
		{description: Get the total number of cycles represented in an LmiProcessorTimes object.}
		{prototype: LmiUint64 LmiProcessorTimesGetTotalTime(const LmiProcessorTimes* t)}
		{parameter:
			{name: t}
			{description: The LmiProcessorTimes object from which to get the total time.}}
		{return: The total number of cycles represented in this object.  The units are
			system-dependent and arbitrary, but are consistent with the idle time in the same
			object, and with other LmiProcessorTimes derived from the same processor or core.}
	}
*/
LMI_INLINE_DECLARATION LmiUint64 LmiProcessorTimesGetTotalTime(const LmiProcessorTimes* t);


/**
	{function:
		{name: LmiProcessorTimesCalcAvgUsage}
		{parent: LmiProcessorTimes}
		{description: Calculate percentage CPU usage that has occurred between two LmiProcessorTimes instances.}
		{prototype: LmiUint LmiProcessorTimesCalcAvgUsage(const LmiProcessorTimes* t1, const LmiProcessorTimes* t2)}
		{parameter:
			{name: t1}
			{description: An earlier LmiProcessorTimes object.}}
		{parameter:
			{name: t2}
			{description: A later LmiProcessorTimes object.}}
		{return: The usage level of the processor in this interval, as a percentage.}
		{note: If the two LmiProcessorTimes objects have the same total time -- indicating that no
			time has elapsed between them -- the value returned will instead be the percentage
			usage represented in t2.}
	}
*/
LmiUint LmiProcessorTimesCalcAvgUsage(const LmiProcessorTimes* t1, const LmiProcessorTimes* t2);


/**
	{type:
		{name: LmiProcessorArch}
		{parent: Processor}
		{description: The architecture of a processor.}
		{value:
			{name: LMI_PROCESSORARCH_Unknown}
			{description: An unknown processor type.}}
		{value:
			{name: LMI_PROCESSORARCH_X86}
			{description: An x86 (ia32) CPU, running in 32-bit mode.}}
		{value replaced-by="LMI_PROCESSORARCH_X64":
			{name: LMI_PROCESSORARCH_X86_64}
			{description: An x86-64 (X64, AMD64, Intel64) CPU, running in 64-bit mode.}}
		{value:
			{name: LMI_PROCESSORARCH_X64}
			{description: An x86-64 (X64, AMD64, Intel64) CPU, running in 64-bit mode.}}
		{value:
			{name: LMI_PROCESSORARCH_PPC}
			{description: A PowerPC CPU.}}
		{value:
			{name: LMI_PROCESSORARCH_ARM}
			{description: An ARM CPU, running in 32-bit mode.}}
		{value:
			{name: LMI_PROCESSORARCH_ARM64}
			{description: An ARM CPU, running in 64-bit mode (Aarch64, arm64).}}
		{note visibility="private": These symbols are also available as preprocessor symbols
			with trailing underscores (LMI_PROCESSORARCH_X86_, etc.).  The preprocessor
			symbol LMI_PROCESSORARCH_Current_ is defined to one of these values, based on
			the current build environment.}
	}
*/

#define LMI_PROCESSORARCH_Unknown_	0
#define LMI_PROCESSORARCH_X86_		1
#define LMI_PROCESSORARCH_X86_64_	2
#define LMI_PROCESSORARCH_X64_	    LMI_PROCESSORARCH_X86_64_
#define LMI_PROCESSORARCH_PPC_		3
#define LMI_PROCESSORARCH_ARM_		4
#define LMI_PROCESSORARCH_ARM64_	5


#if defined(__i386__) || defined(_M_IX86)
#define LMI_PROCESSORARCH_Current_ LMI_PROCESSORARCH_X86_
#elif defined(__x86_64__) || defined(_M_X64)
#define LMI_PROCESSORARCH_Current_ LMI_PROCESSORARCH_X86_64_
#elif defined(__POWERPC__)
#define LMI_PROCESSORARCH_Current_ LMI_PROCESSORARCH_PPC_
#elif defined(__arm__) || defined(_M_ARM)
#define LMI_PROCESSORARCH_Current_ LMI_PROCESSORARCH_ARM_
#elif defined(__arm64__) || defined(__aarch64__)
#define LMI_PROCESSORARCH_Current_ LMI_PROCESSORARCH_ARM64_
#else
#warning Unknown processor architecture
#define LMI_PROCESSORARCH_Current_ LMI_PROCESSORARCH_Unknown_
#endif


typedef enum {
	LMI_PROCESSORARCH_Unknown = LMI_PROCESSORARCH_Unknown_,
	LMI_PROCESSORARCH_X86 = LMI_PROCESSORARCH_X86_,
	LMI_PROCESSORARCH_X86_64 = LMI_PROCESSORARCH_X86_64_,
	LMI_PROCESSORARCH_X64 = LMI_PROCESSORARCH_X64_,
	LMI_PROCESSORARCH_PPC = LMI_PROCESSORARCH_PPC_,
	LMI_PROCESSORARCH_ARM = LMI_PROCESSORARCH_ARM_,
	LMI_PROCESSORARCH_ARM64 = LMI_PROCESSORARCH_ARM64_,
} LmiProcessorArch;



/**
	{type:
		{name: LmiProcessorVendor}
		{parent: Processor}
		{description: The vendor (manufacturer) of a CPU.}
		{value:
			{name: LMI_PROCESSORVENDOR_Unknown}
			{description: An unknown processor vendor.}}
		{value:
			{name: LMI_PROCESSORVENDOR_Intel}
			{description: Intel.}}
		{value:
			{name: LMI_PROCESSORVENDOR_AMD}
			{description: AMD.}}
		{value:
			{name: LMI_PROCESSORVENDOR_ARM}
			{description: ARM.}}
		{value:
			{name: LMI_PROCESSORVENDOR_Qualcomm}
			{description: Qualcomm.}}
		{value:
			{name: LMI_PROCESSORVENDOR_Apple}
			{description: Apple.}}
	}
*/
typedef enum
{
	LMI_PROCESSORVENDOR_Unknown,
	LMI_PROCESSORVENDOR_Intel,
	LMI_PROCESSORVENDOR_AMD,
	LMI_PROCESSORVENDOR_ARM,
	LMI_PROCESSORVENDOR_Qualcomm,
	LMI_PROCESSORVENDOR_Apple,
} LmiProcessorVendor;


/**
	{type:
		{name: LmiProcessorArmArch}
		{parent: Processor}
		{description: An ARM processor's architecture type.}
		{value:
			{name: LMI_PROCESSORARMARCH_Unknown}
			{description: An unknown type of ARM processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv3}
			{description: An ARM v3 processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv4}
			{description: An ARM v4 processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv4T}
			{description: An ARM v4T processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv5}
			{description: An ARM v5 processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv5T}
			{description: An ARM v5T processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv5TE}
			{description: An ARM v5TE processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv5TEJ}
			{description: An ARM v5TEJ processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv6}
			{description: An ARM v6 processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv7}
			{description: An ARM v7 processor.}}
		{value:
			{name: LMI_PROCESSORARMARCH_ARMv8}
			{description: An ARM v8 processor.}}
}
*/

typedef enum
{
	LMI_PROCESSORARMARCH_Unknown,
	LMI_PROCESSORARMARCH_ARMv3,
	LMI_PROCESSORARMARCH_ARMv4,
	LMI_PROCESSORARMARCH_ARMv4T,
	LMI_PROCESSORARMARCH_ARMv5,
	LMI_PROCESSORARMARCH_ARMv5T,
	LMI_PROCESSORARMARCH_ARMv5TE,
	LMI_PROCESSORARMARCH_ARMv5TEJ,
	LMI_PROCESSORARMARCH_ARMv6,
	LMI_PROCESSORARMARCH_ARMv7,
	LMI_PROCESSORARMARCH_ARMv8,
} LmiProcessorArmArch;



typedef enum
{
	LMI_PROCESSORMODEL_Unknown,

	/* Intel */
	/* Models from Intel Application Note 405, August 2009, plus
	   Specification Updates */

	/* Sheet 1 */
	LMI_PROCESSORMODEL_Intel486DX,
	LMI_PROCESSORMODEL_Intel486SX,
	LMI_PROCESSORMODEL_IntelDX2,
	LMI_PROCESSORMODEL_Intel486SL,
	LMI_PROCESSORMODEL_IntelSX2,
	LMI_PROCESSORMODEL_IntelDX4,
	LMI_PROCESSORMODEL_IntelPentium,
	
	/* Sheet 2 */
	LMI_PROCESSORMODEL_IntelPentiumMMX,
	LMI_PROCESSORMODEL_IntelPentiumPro,
	LMI_PROCESSORMODEL_IntelPentiumII,
	LMI_PROCESSORMODEL_IntelCeleron,
	LMI_PROCESSORMODEL_IntelEP80579,
	LMI_PROCESSORMODEL_IntelPentiumIII,
	LMI_PROCESSORMODEL_IntelPentiumM,
	LMI_PROCESSORMODEL_IntelCore,

	/* Sheet 3 */
	LMI_PROCESSORMODEL_IntelCore2,
	LMI_PROCESSORMODEL_IntelPentium4,

	/* Sheet 4 and subsequent*/
	LMI_PROCESSORMODEL_IntelAtom,
	LMI_PROCESSORMODEL_IntelNehalem,
	LMI_PROCESSORMODEL_IntelWestmere,
	LMI_PROCESSORMODEL_IntelSandyBridge,
	LMI_PROCESSORMODEL_IntelIvyBridge,
	LMI_PROCESSORMODEL_IntelHaswell,
	LMI_PROCESSORMODEL_IntelBroadwell,
	LMI_PROCESSORMODEL_IntelSkylake,
	LMI_PROCESSORMODEL_IntelKabyLake,


	/* AMD */
	LMI_PROCESSORMODEL_AMDK5,
	LMI_PROCESSORMODEL_AMDK6,
	LMI_PROCESSORMODEL_AMDK7,
	LMI_PROCESSORMODEL_AMDK8,
	LMI_PROCESSORMODEL_AMDK10,
	LMI_PROCESSORMODEL_AMDFusion,
	LMI_PROCESSORMODEL_AMDBulldozer,
	LMI_PROCESSORMODEL_AMDPiledriver,
	LMI_PROCESSORMODEL_AMDSteamroller,
	LMI_PROCESSORMODEL_AMDExcavator,
	LMI_PROCESSORMODEL_AMDBobcat,
	LMI_PROCESSORMODEL_AMDJaguar,
	LMI_PROCESSORMODEL_AMDPuma,
	

	/* ARM */
	LMI_PROCESSORMODEL_ARMCortexA5,
	LMI_PROCESSORMODEL_ARMCortexA7,
	LMI_PROCESSORMODEL_ARMCortexA8,
	LMI_PROCESSORMODEL_ARMCortexA9,
	LMI_PROCESSORMODEL_ARMCortexA15,
	LMI_PROCESSORMODEL_ARMCortexA17,
	LMI_PROCESSORMODEL_ARMCortexA53,
	LMI_PROCESSORMODEL_ARMCortexA57,
	LMI_PROCESSORMODEL_ARMCortexA72,
	LMI_PROCESSORMODEL_ARMCortexA73,

	/* Qualcomm */
	LMI_PROCESSORMODEL_QualcommSnapdragonS1,
	LMI_PROCESSORMODEL_QualcommSnapdragonS3,
	LMI_PROCESSORMODEL_QualcommSnapdragonS4Plus,
	LMI_PROCESSORMODEL_QualcommSnapdragonS4Pro,

	/* Apple */
	LMI_PROCESSORMODEL_AppleA6,
	LMI_PROCESSORMODEL_AppleA7,
	LMI_PROCESSORMODEL_AppleA8,
	LMI_PROCESSORMODEL_AppleA9,
	LMI_PROCESSORMODEL_AppleA10,
} LmiProcessorModel;

struct LmiProcessor_;

/**
	{callback visibility="private":
		{name: LmiProcessorGetTimesCallback}
		{parent: LmiProcessor}
		{description: Return a description of the current total processor time used by all cores of a processor.}
		{prototype: LmiBool (*LmiProcessorGetTimesCallback)(const LmiProcessor* p, LmiProcessorTimes* t, LmiVoidPtr userData)}
		{parameter:
			{name: p}
			{description: The processor from which to get its current times.}}
		{parameter:
			{name: t}
			{description: An LmiProcessorTimes object into which to place the time usage.}}
		{parameter:
			{name: userData}
			{description: User-provided data.}}
		{return: LMI_TRUE if the time was successfully returned; LMI_FALSE otherwise.}
	}
*/
typedef LmiBool (*LmiProcessorGetTimesCallback)(const struct LmiProcessor_* p, LmiProcessorTimes *t, LmiVoidPtr userData);


/**
	{callback visibility="private":
		{name: LmiProcessorGetTimesPerCoreCallback}
		{parent: LmiProcessor}
		{description: Return a description of the current processor time used by each core of a processor.}
		{prototype: LmiBool (*LmiProcessorGetTimesPerCoreCallback)(const LmiProcessor* p, LmiProcessorTimes* t, LmiUint* n, LmiVoidPtr userData)}
		{parameter:
			{name: p}
			{description: The processor from which to get the times for each of its cores.}}
		{parameter:
			{name: t}
			{description: An array of LmiProcessorTimes objects into which to place the cores' time usages.}}
		{parameter:
			{name: n}
			{description: On input, a pointer to the size of the array pointed to by t.  (This should be of size
				at least as big as the processor's number of logical cores.)  On return, the actual number
				of cores whose data is filled in.  This may be less than the total number of logical cores, if
				some cores have been disabled.}}
		{parameter:
			{name: userData}
			{description: User-provided data.}}
		{return: LMI_TRUE if the times were successfully returned; LMI_FALSE otherwise.}
	}
*/
typedef LmiBool (*LmiProcessorGetTimesPerCoreCallback)(const struct LmiProcessor_* p, LmiProcessorTimes *t, LmiUint* n, LmiVoidPtr userData);


/**
	{type:
		{name: LmiProcessor}
		{parent: Processor}
		{description: A representation of a system\'s processor.}
	}
*/
typedef struct LmiProcessor_ {
	LmiProcessorArch arch;
	LmiProcessorVendor vendor;
	LmiProcessorModel model;

	LmiUint physicalCores;
	LmiUint logicalCores;
	LmiUint speed;

	union {
		struct {
			char vendorId[13];
			char processorBrandString[49];
			LmiUint familyId;
			LmiUint modelId;
			LmiUint steppingId;
			LmiBool hasHyperthreading;
			LmiBool hasSse;
			LmiBool hasSse2;
			LmiBool hasSse3;
			LmiBool hasSsse3;
			LmiBool hasSse4_1;
			LmiBool hasSse4_2;
			LmiBool hasAes;
			LmiBool hasAvx;
			LmiBool hasAvx2;
		} x86;
		struct {
			LmiUint implementor;
			LmiProcessorArmArch architecture;
			LmiUint variant;
			LmiUint part;
			LmiUint revision;
			LmiBool hasNeon;
			LmiBool hasArmCrypt;
		} arm;
	} u;

	LmiProcessorGetTimesCallback getTimes;
	LmiProcessorGetTimesPerCoreCallback getTimesPerCore;
	LmiVoidPtr userData;
} LmiProcessor;


/**
	{function visibility="private":
		{name: LmiProcessorConstructDefault}
		{parent: LmiProcessor}
		{description: Construct an LmiProcessor object with default values.}
		{prototype: LmiProcessor* LmiProcessorConstructDefault(LmiProcessor* p)}
		{parameter:
			{name: p}
			{description: The object to construct}}
		{return: The constructed object, or NULL on failure.}
		{note: This is expected to be useful only when simulating LmiProcessor objects
			for systems other than the current one.}
	}
*/
LmiProcessor* LmiProcessorConstructDefault(LmiProcessor* p);


/**
	{function visibility="private":
		{name: LmiProcessorConstructCurrent}
		{parent: LmiProcessor}
		{description: Construct an LmiProcessor object describing the processor on which the
			system is running.}
		{prototype: LmiProcessor* LmiProcessorConstructCurrent(LmiProcessor* p)}
		{parameter:
			{name: p}
			{description: The object to construct.}}
		{return: The constructed object, or NULL on failure.}
		{note: In almost all cases, LmiProcessorGetCurrent() should be called instead.}
	}
*/
LmiProcessor* LmiProcessorConstructCurrent(LmiProcessor* p);


/**
	{function visibility="private":
		{name: LmiProcessorDestruct}
		{parent: LmiProcessor}
		{description: Destruct an LmiProcessor object.}
		{prototype: void LmiProcessorDestruct(LmiProcessor* p)}
		{parameter:
			{name: p}
			{description: The object to destruct.}}
	}
*/
void LmiProcessorDestruct(LmiProcessor* p);



/**
	{function:
		{name: LmiProcessorGetCurrent}
		{parent: LmiProcessor}
		{description: Get a description of the processor on which the system is running.}
		{prototype: const LmiProcessor* LmiProcessorGetCurrent(void)}
		{return: A description of the current processor.}
	}
*/	
const LmiProcessor* LmiProcessorGetCurrent(void);

/**
	{function:
		{name: LmiProcessorGetArch}
		{parent: LmiProcessor}
		{description: Get the architecture of an LmiProcessor.}
		{prototype: LmiProcessorArch LmiProcessorGetArch(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose architecture to get.}}
		{return: The architecture described in the processor.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorArch LmiProcessorGetArch(const LmiProcessor* p);

/**
	{function:
		{name: LmiProcessorGetVendor}
		{parent: LmiProcessor}
		{description: Get the vendor (manufacturer) of the CPU of an LmiProcessor.}
		{prototype: LmiProcessorVendor LmiProcessorGetVendor(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose vendor to get.}}
		{return: The vendor described in the processor.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorVendor LmiProcessorGetVendor(const LmiProcessor* p);



/**
	{function:
		{name: LmiProcessorGetX86VendorId}
		{parent: LmiProcessor}
		{description: Get an X86 CPU's vendor ID string, e.g. "GenuineIntel" or "AuthenticAMD".}
		{prototype: LmiBool LmiProcessorGetX86VendorId(const LmiProcessor* p, char nameBuf[13])}
		{parameter: {name: p} {description: The processor whose vendor ID to get.}}
		{parameter:
			{name: nameBuf}
			{description: A buffer into which to place the CPU's vendor ID string.  On successful return, the vendor ID will be copied to this buffer, as a NUL-terminated string.}}
		{return: LMI_TRUE if the vendor ID string was successfully copied to the buffer, LMI_FALSE otherwise (including if the processor was not an X86 CPU).}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorGetX86VendorId(const LmiProcessor* p, char nameBuf[13]);


/**
	{function:
		{name: LmiProcessorGetX86ProcessorBrandString}
		{parent: LmiProcessor}
		{description: Get an X86 CPU's processor brand string, e.g. "Intel(R) Core(TM)2 Duo CPU &#160; &#160; T7500 &#160;@ 2.20GHz".}
		{prototype: LmiBool LmiProcessorGetX86ProcessorBrandString(const LmiProcessor* p, char nameBuf[49])}
		{parameter: {name: p} {description: The processor whose brand string to get.}}
		{parameter:
			{name: nameBuf}
			{description: A buffer into which to place the CPU's brand ID string.  On successful return, the brand ID will be copied to this buffer, as a NUL-terminated string.}}
		{return: LMI_TRUE if the brand ID string was successfully copied to the buffer, LMI_FALSE otherwise (including if the processor was not an X86 CPU).}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorGetX86ProcessorBrandString(const LmiProcessor* p, char nameBuf[49]);


/**
	{function:
		{name: LmiProcessorGetX86FamilyId}
		{parent: LmiProcessor}
		{description: Get an x86 CPU's extended CPU family ID.}
		{prototype: LmiUint LmiProcessorGetX86FamilyId(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose extended family ID to get.}}
		{return: The extended family id, or 0 if this is not an X86 CPU.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetX86FamilyId(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetX86ModelId}
		{parent: LmiProcessor}
		{description: Get an x86 CPU's extended CPU model ID.}
		{prototype: LmiUint LmiProcessorGetX86ModelId(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose extended model ID to get.}}
		{return: The extended model id, or 0 if this is not an X86 CPU.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetX86ModelId(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetX86SteppingId}
		{parent: LmiProcessor}
		{description: Get an x86 CPU's stepping ID.}
		{prototype: LmiUint LmiProcessorGetX86SteppingId(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose extended model ID to get.}}
		{return: The stepping ID, or 0 if this is not an X86 CPU.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetX86SteppingId(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetArmImplementer}
		{parent: LmiProcessor}
		{description: Get an ARM CPU's implementor ID.}
		{prototype: LmiUint LmiProcessorGetArmImplementer(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose implementor to get.}}
		{return: The ARM implementor ID, or 0 if this is not an ARM CPU.}
		{note: This is currently only supported on Linux-based ARM OSes; it will be 0 on iOS.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetArmImplementer(const LmiProcessor* p);

/**
	{function:
		{name: LmiProcessorGetArmArchitecture}
		{parent: LmiProcessor}
		{description: Get an ARM CPU's architecture type.}
		{prototype: LmiProcessorArmArch LmiProcessorGetArmArchitecture(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose architecture type to get.}}
		{return: The CPU's architecture type, or LMI_PROCESSORARMARCH_Unknown if the type is unknown or if this is not an ARM CPU.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorArmArch LmiProcessorGetArmArchitecture(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetArmVariant}
		{parent: LmiProcessor}
		{description: Get an ARM CPU's variant ID.}
		{prototype: LmiUint LmiProcessorGetArmVariant(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose variant ID to get.}}
		{return: The ARM variant ID, or 0 if this is not an ARM CPU.}
		{note: This is currently only supported on Linux-based ARM OSes; it will be 0 on iOS.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetArmVariant(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetArmPart}
		{parent: LmiProcessor}
		{description: Get an ARM CPU's part ID.}
		{prototype: LmiUint LmiProcessorGetArmPart(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose part ID to get.}}
		{return: The ARM part ID, or 0 if this is not an ARM CPU.}
		{note: This is currently only supported on Linux-based ARM OSes; it will be 0 on iOS.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetArmPart(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetArmRevision}
		{parent: LmiProcessor}
		{description: Get an ARM CPU's revision ID.}
		{prototype: LmiUint LmiProcessorGetArmRevision(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose revision ID to get.}}
		{return: The ARM revision ID, or 0 if this is not an ARM CPU.}
		{note: This is currently only supported on Linux-based ARM OSes; it will be 0 on iOS.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetArmRevision(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorArmArchitectureGetName}
		{parent: LmiProcessor}
		{description: Get a textual description of an ARM architecture value.}
		{prototype: const char* LmiProcessorArmArchitectureGetName(LmiProcessorArmArch armArch)}
		{parameter:
			{name: armArch}
			{description: The ARM architecture.}}
		{return: The textual description of the architecture.}
	}
*/
const char* LmiProcessorArmArchitectureGetName(LmiProcessorArmArch armArch);


/**
	{type:
		{name: LmiProcessorModel}
		{parent: LmiProcessor}
		{description: A CPU's model type.}
		{value:
			{name: LMI_PROCESSORMODEL_Unknown}
			{description: An unknown model of processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_Intel486DX}
			{description: An Intel 486DX processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_Intel486SX}
			{description: An Intel 486SX processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelDX2}
			{description: An Intel DX2 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_Intel486SL}
			{description: An Intel 486SL processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelSX2}
			{description: An Intel SX2 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelDX4}
			{description: An Intel DX4 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentium}
			{description: An Intel Pentium processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentiumMMX}
			{description: An Intel Pentium MMX processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentiumPro}
			{description: An Intel Pentium Pro processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentiumII}
			{description: An Intel Pentium II processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelCeleron}
			{description: An Intel Celeron processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelEP80579}
			{description: An Intel EP 80579 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentiumIII}
			{description: An Intel Pentium III processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentiumM}
			{description: An Intel Pentium M processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelCore}
			{description: An Intel Core processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelCore2}
			{description: An Intel Core 2 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelPentium4}
			{description: An Intel Pentium 4 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelAtom}
			{description: An Intel Atom processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelNehalem}
			{description: A "Nehalem" Intel Core i3, i5, i7, or Xeon processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelWestmere}
			{description: A "Westmere" Intel Core i3, i5, i7, or Xeon processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelSandyBridge}
			{description: A "Sandy Bridge" Intel Core i3, i5, i7, or Xeon processor (2nd generation).}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelIvyBridge}
			{description: An "Ivy Bridge" Intel Core i3, i5, i7, or Xeon processor (3rd generation).}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelHaswell}
			{description: A "Haswell" Intel Core i3, i5, i7, or Xeon processor (4th generation).}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelBroadwell}
			{description: A "Broadwell" Intel Core i3, i5, i7, or Xeon processor (5th generation).}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelSkylake}
			{description: A "Skylake" Intel Core i3, i5, i7, or Xeon processor (6th generation).}}
		{value:
			{name: LMI_PROCESSORMODEL_IntelKabyLake}
			{description: A "Kaby Lake" Intel Core i3, i5, i7, or Xeon processor (7th generation).}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDK5}
			{description: An AMD K5 architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDK6}
			{description: An AMD K6 architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDK7}
			{description: An AMD K7 architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDK8}
			{description: An AMD K8 architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDK10}
			{description: An AMD K10 architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDFusion}
			{description: An AMD Fusion architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDBulldozer}
			{description: An AMD Bulldozer architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDPiledriver}
			{description: An AMD Piledriver architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDSteamroller}
			{description: An AMD Steamroller architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDExcavator}
			{description: An AMD Excavator architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDBobcat}
			{description: An AMD Bobcat architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDJaguar}
			{description: An AMD Jaguar architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_AMDPuma}
			{description: An AMD Puma architecture processor}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA5}
			{description: An ARM Cortex-A5 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA7}
			{description: An ARM Cortex-A7 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA8}
			{description: An ARM Cortex-A8 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA9}
			{description: An ARM Cortex-A9 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA15}
			{description: An ARM Cortex-A15 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA17}
			{description: An ARM Cortex-A17 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA53}
			{description: An ARM Cortex-A53 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA57}
			{description: An ARM Cortex-A57 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA72}
			{description: An ARM Cortex-A72 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_ARMCortexA73}
			{description: An ARM Cortex-A73 processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_QualcommSnapdragonS1}
			{description: A Qualcomm Snapdragon S1 (Scorpion) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_QualcommSnapdragonS3}
			{description: A Qualcomm Snapdragon S3 (Scorpion) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_QualcommSnapdragonS4Plus}
			{description: A Qualcomm Snapdragon S4 Plus (Krait) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_QualcommSnapdragonS4Pro}
			{description: A Qualcomm Snapdragon S4 Pro (Krait) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_AppleA6}
			{description: An Apple A6 (Swift) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_AppleA7}
			{description: An Apple A7 (Cyclone) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_AppleA8}
			{description: An Apple A8 (Typhoon) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_AppleA9}
			{description: An Apple A9 (Twister) processor.}}
		{value:
			{name: LMI_PROCESSORMODEL_AppleA10}
			{description: An Apple A10 (Hurricane) processor.}}
	}
*/

/**
	{function:
		{name: LmiProcessorGetModel}
		{parent: LmiProcessor}
		{description: Get the model of an LmiProcessor.}
		{prototype: LmiProcessorModel LmiProcessorGetModel(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose model to get.}}
		{return: The system's model, or LMI_PROCESSORMODEL_Unknown if it is unknown.}
		{note: This is currently only supported for Intel CPUs.}
	}
*/
LMI_INLINE_DECLARATION LmiProcessorModel LmiProcessorGetModel(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorModelGetName}
		{parent: LmiProcessor}
		{description: Get a textual description of a processor model identifier.}
		{prototype: const char* LmiProcessorModelGetName(LmiProcessorModel model)}
		{parameter:
			{name: model}
			{description: The processor model.}}
		{return: A textual description of the processor model.}
	}
*/
const char* LmiProcessorModelGetName(LmiProcessorModel model);


/**
	{function:
		{name: LmiProcessorGetNumPhysicalCores}
		{parent: LmiProcessor}
		{description: Get a processor's number of physical CPU cores (ignoring hyperthreading).}
		{prototype: LmiUint LmiProcessorGetNumPhysicalCores(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose number of physical cores to get.}}
		{return: The number of physical CPU cores.}
		{note: This is the total number of available physical CPU cores, not all of which may
			necessarily be enabled at any given time.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetNumPhysicalCores(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetNumLogicalCores}
		{parent: LmiProcessor}
		{description: Get a processor's number of logical CPU cores (including hyperthreading).}
		{prototype: LmiUint LmiProcessorGetNumLogicalCores(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose number of physical cores to get.}}
		{return: The number of logical CPU cores.}
		{note: This is the total number of available logical CPU cores, not all of which may
			necessarily be enabled at any given time.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetNumLogicalCores(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetSpeed}
		{parent: LmiProcessor}
		{description: Get a processor's frequency, in MHz.}
		{prototype: LmiUint LmiProcessorGetSpeed(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor whose frequency to get.}}
		{return: The processor's frequency, or 0 if unknown.}
	}
*/
LMI_INLINE_DECLARATION LmiUint LmiProcessorGetSpeed(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasHyperthreading}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel Hyperthreading.}
		{prototype: LmiBool LmiProcessorHasHyperthreading(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel Hyperthreading.}}
		{return: Whether the processor supports Intel Hyperthreading.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasHyperthreading(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasSse}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel SSE instructions.}
		{prototype: LmiBool LmiProcessorHasSse(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel SSE.}}
		{return: Whether a processor supports Intel SSE instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasSse(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasSse2}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel SSE2 instructions.}
		{prototype: LmiBool LmiProcessorHasSse2(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel SSE2.}}
		{return: Whether the processor supports Intel SSE2 instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasSse2(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasSse3}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel SSE3 instructions.}
		{prototype: LmiBool LmiProcessorHasSse3(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel SSE3.}}
		{return: Whether the processor supports Intel SSE3 instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasSse3(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasSsse3}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel Supplemental SSE3 instructions.}
		{prototype: LmiBool LmiProcessorHasSsse3(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel Supplemental SSE3.}}
		{return: Whether the processor supports Intel Supplemental SSE3 instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasSsse3(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasSse4_1}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel SSE4.1 instructions.}
		{prototype: LmiBool LmiProcessorHasSse4_1(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel SSE4.1.}}
		{return: Whether the processor supports Intel SSE4.1 instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasSse4_1(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasSse4_2}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel SSE4.2 instructions.}
		{prototype: LmiBool LmiProcessorHasSse4_2(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel SSE4.2.}}
		{return: Whether the processor supports Intel SSE4.2 instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasSse4_2(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasAes}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel AES-NI instructions.}
		{prototype: LmiBool LmiProcessorHasAes(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel AES-NI.}}
		{return: Whether the processor supports Intel AES-NI instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasAes(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasAvx}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel AVX instructions.}
		{prototype: LmiBool LmiProcessorHasAvx(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel AVX.}}
		{return: Whether the processor supports Intel AVX instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasAvx(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasAvx2}
		{parent: LmiProcessor}
		{description: Return whether a processor supports Intel AVX2 instructions.}
		{prototype: LmiBool LmiProcessorHasAvx2(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for Intel AVX2.}}
		{return: Whether the processor supports Intel AVX2 instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasAvx2(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasNeon}
		{parent: LmiProcessor}
		{description: Return whether the processor supports ARM NEON instructions.}
		{prototype: LmiBool LmiProcessorHasNeon(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for ARM NEON.}}
		{return: Whether the processor supports ARM NEON instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasNeon(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorHasArmCrypt}
		{parent: LmiProcessor}
		{description: Return whether the processor supports ARM Cryptographic instructions.}
		{prototype: LmiBool LmiProcessorHasArmCrypt(const LmiProcessor* p)}
		{parameter: {name: p} {description: The processor to query for ARM Cryptographic instructions.}}
		{return: Whether the processor supports ARM Cryptographic instructions.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorHasArmCrypt(const LmiProcessor* p);


/**
	{function:
		{name: LmiProcessorGetTimes}
		{parent: LmiProcessor}
		{description: Return a description of the current total processor time used by all cores of a processor.}
		{prototype: LmiBool LmiProcessorGetTimes(const LmiProcessor* p, LmiProcessorTimes* t)}
		{parameter:
			{name: p}
			{description: The processor from which to get its current times.}}
		{parameter:
			{name: t}
			{description: A constructed LmiProcessorTimes object into which to place the time usage.}}
		{return: LMI_TRUE if the time was successfully returned; LMI_FALSE otherwise.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorGetTimes(const LmiProcessor* p, LmiProcessorTimes *t);


/**
	{function:
		{name: LmiProcessorGetTimesPerCore}
		{parent: LmiProcessor}
		{description: Return a description of the current processor time used by each core of a processor.}
		{prototype: LmiBool LmiProcessorGetTimesPerCore(const LmiProcessor* p, LmiProcessorTimes* t, LmiUint* n)}
		{parameter:
			{name: p}
			{description: The processor from which to get the times for each of its cores.}}
		{parameter:
			{name: t}
			{description: An array of constructed LmiProcessorTimes objects into which to place the cores' time usages.}}
		{parameter:
			{name: n}
			{description: On input, a pointer to the size of the array pointed to by t.  (This should be of size
				at least as big as the processor's number of logical cores.)  On return, the actual number
				of cores whose data is filled in.  This may be less than the total number of logical cores, if
				some cores have been disabled.}}
		{return: LMI_TRUE if the times were successfully returned; LMI_FALSE otherwise.}
	}
*/
LMI_INLINE_DECLARATION LmiBool LmiProcessorGetTimesPerCore(const LmiProcessor* p, LmiProcessorTimes *t, LmiUint* n);


/**
	{function visibility="private":
		{name: LmiProcessorSetArch}
		{parent: LmiProcessor}
		{description: Set the architecture of an LmiProcessor.}
		{prototype: LmiBool LmiProcessorSetArch(LmiProcessor* p, LmiProcessorArch x)}
		{parameter: {name: p} {description: The processor whose architecture to set.}}
		{parameter: {name: x} {description: The architecture to set for the processor.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: If a processor\'s architecture is changed, all processor-specific fields will be reset.}
	}
*/
LmiBool LmiProcessorSetArch(LmiProcessor* p, LmiProcessorArch x);

/**
	{function visibility="private":
		{name: LmiProcessorSetVendor}
		{parent: LmiProcessor}
		{description: Set the vendor (manufacturer) of the CPU of an LmiProcessor.}
		{prototype: LmiBool LmiProcessorSetVendor(LmiProcessor* p, LmiProcessorVendor x)}
		{parameter: {name: p} {description: The processor whose vendor to set.}}
		{parameter: {name: x} {description: The vendor to set for the processor.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiProcessorSetVendor(LmiProcessor* p, LmiProcessorVendor x);


/**
	{function visibility="private":
		{name: LmiProcessorSetX86VendorId}
		{parent: LmiProcessor}
		{description: Set an X86 CPU's vendor ID string, e.g. "GenuineIntel" or "AuthenticAMD".}
		{prototype: LmiBool LmiProcessorSetX86VendorId(LmiProcessor* p, const char nameBuf[13])}
		{parameter: {name: p} {description: The processor whose vendor ID to set.}}
		{parameter:
			{name: nameBuf}
			{description: The vendor ID string to set for the processor.}}
		{return: LMI_TRUE if the vendor ID string was successfully copied to the processor, LMI_FALSE otherwise (including if the processor's architecture is not X86).}
	}
*/
LmiBool LmiProcessorSetX86VendorId(LmiProcessor* p, const char nameBuf[13]);


/**
	{function visibility="private":
		{name: LmiProcessorSetX86ProcessorBrandString}
		{parent: LmiProcessor}
		{description: Set an X86 CPU's processor brand string, e.g. "Intel(R) Core(TM)2 Duo CPU &#160; &#160; T7500 &#160;@ 2.20GHz".}
		{prototype: LmiBool LmiProcessorSetX86ProcessorBrandString(LmiProcessor* p, const char nameBuf[49])}
		{parameter: {name: p} {description: The processor whose brand string to set.}}
		{parameter:
			{name: nameBuf}
			{description: The CPU's brand ID string to set for the processor.}}
		{return: LMI_TRUE if the brand ID string was successfully copied to the processor, LMI_FALSE otherwise (including if the processor's architecture is not X86).}
	}
*/
LmiBool LmiProcessorSetX86ProcessorBrandString(LmiProcessor* p, const char nameBuf[49]);


/**
	{function visibility="private":
		{name: LmiProcessorSetX86FamilyId}
		{parent: LmiProcessor}
		{description: Set an x86 CPU's extended CPU family ID.}
		{prototype: LmiBool LmiProcessorSetX86FamilyId(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose extended family ID to set.}}
		{parameter: {name: x} {description: The extended family id to set.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not X86.}
	}
*/
LmiBool LmiProcessorSetX86FamilyId(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetX86ModelId}
		{parent: LmiProcessor}
		{description: Set an x86 CPU's extended CPU model ID.}
		{prototype: LmiBool LmiProcessorSetX86ModelId(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose extended model ID to set.}}
		{parameter: {name: x} {description: The extended model id.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not X86.}
	}
*/
LmiBool LmiProcessorSetX86ModelId(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetX86SteppingId}
		{parent: LmiProcessor}
		{description: Set an x86 CPU's stepping ID.}
		{prototype: LmiBool LmiProcessorSetX86SteppingId(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose extended model ID to set.}}
		{parameter: {name: x} {description: The stepping ID.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not X86.}
	}
*/
LmiBool LmiProcessorSetX86SteppingId(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetArmImplementer}
		{parent: LmiProcessor}
		{description: Set an ARM CPU's implementor ID.}
		{prototype: LmiBool LmiProcessorSetArmImplementer(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose implementor to set.}}
		{parameter: {name: x} {description: The ARM implementor ID.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not ARM.}
	}
*/
LmiBool LmiProcessorSetArmImplementer(LmiProcessor* p, LmiUint x);

/**
	{function visibility="private":
		{name: LmiProcessorSetArmArchitecture}
		{parent: LmiProcessor}
		{description: Set an ARM CPU's architecture type.}
		{prototype: LmiBool LmiProcessorSetArmArchitecture(LmiProcessor* p, LmiProcessorArmArch x)}
		{parameter: {name: p} {description: The processor whose architecture type to set.}}
		{parameter: {name: x} {description: The CPU's architecture type.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not ARM.}
	}
*/
LmiBool LmiProcessorSetArmArchitecture(LmiProcessor* p, LmiProcessorArmArch x);


/**
	{function visibility="private":
		{name: LmiProcessorSetArmVariant}
		{parent: LmiProcessor}
		{description: Set an ARM CPU's variant ID.}
		{prototype: LmiBool LmiProcessorSetArmVariant(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose variant ID to set.}}
		{parameter: {name: x} {description: The ARM variant ID.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not ARM.}
	}
*/
LmiBool LmiProcessorSetArmVariant(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetArmPart}
		{parent: LmiProcessor}
		{description: Set an ARM CPU's part ID.}
		{prototype: LmiBool LmiProcessorSetArmPart(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose part ID to set.}}
		{parameter: {name: x} {description: The ARM part ID.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not ARM.}
	}
*/
LmiBool LmiProcessorSetArmPart(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetArmRevision}
		{parent: LmiProcessor}
		{description: Set an ARM CPU's revision ID.}
		{prototype: LmiBool LmiProcessorSetArmRevision(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose revision ID to set.}}
		{parameter: {name: x} {description: The ARM revision ID.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if the processor's arch is not ARM.}
	}
*/
LmiBool LmiProcessorSetArmRevision(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetModel}
		{parent: LmiProcessor}
		{description: Set the model an LmiProcessor.}
		{prototype: LmiBool LmiProcessorSetModel(LmiProcessor* p, LmiProcessorModel x)}
		{parameter: {name: p} {description: The processor whose model to set.}}
		{parameter: {name: x} {description: The system's model.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiProcessorSetModel(LmiProcessor* p, LmiProcessorModel x);


/**
	{function visibility="private":
		{name: LmiProcessorSetNumPhysicalCores}
		{parent: LmiProcessor}
		{description: Set a processor's number of physical CPU cores (ignoring hyperthreading).}
		{prototype: LmiBool LmiProcessorSetNumPhysicalCores(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose number of physical cores to set.}}
		{parameter: {name: x} {description: The number of physical CPU cores.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: This is the total number of available physical CPU cores, not all of which may
			necessarily be enabled at any given time.}
	}
*/
LmiBool LmiProcessorSetNumPhysicalCores(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetNumLogicalCores}
		{parent: LmiProcessor}
		{description: Set a processor's number of logical CPU cores (including hyperthreading).}
		{prototype: LmiBool LmiProcessorSetNumLogicalCores(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose number of physical cores to set.}}
		{parameter: {name: x} {description: The number of logical CPU cores.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: This is the total number of available logical CPU cores, not all of which may
			necessarily be enabled at any given time.}
	}
*/
LmiBool LmiProcessorSetNumLogicalCores(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetSpeed}
		{parent: LmiProcessor}
		{description: Set a processor's frequency, in MHz.}
		{prototype: LmiBool LmiProcessorSetSpeed(LmiProcessor* p, LmiUint x)}
		{parameter: {name: p} {description: The processor whose frequency to set.}}
		{parameter: {name: x} {description: The processor's frequency.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
	}
*/
LmiBool LmiProcessorSetSpeed(LmiProcessor* p, LmiUint x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasHyperthreading}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel Hyperthreading.}
		{prototype: LmiBool LmiProcessorSetHasHyperthreading(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel Hyperthreading.}}
		{parameter: {name: x} {description: Whether the processor supports Intel Hyperthreading.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasHyperthreading(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasSse}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel SSE instructions.}
		{prototype: LmiBool LmiProcessorSetHasSse(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel SSE.}}
		{parameter: {name: x} {description: Whether a processor supports Intel SSE instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasSse(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasSse2}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel SSE2 instructions.}
		{prototype: LmiBool LmiProcessorSetHasSse2(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel SSE2.}}
		{parameter: {name: x} {description: Whether the processor supports Intel SSE2 instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasSse2(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasSse3}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel SSE3 instructions.}
		{prototype: LmiBool LmiProcessorSetHasSse3(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel SSE3.}}
		{parameter: {name: x} {description: Whether the processor supports Intel SSE3 instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasSse3(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasSsse3}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel Supplemental SSE3 instructions.}
		{prototype: LmiBool LmiProcessorSetHasSsse3(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel Supplemental SSE3.}}
		{parameter: {name: x} {description: Whether the processor supports Intel Supplemental SSE3 instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasSsse3(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasSse4_1}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel SSE4.1 instructions.}
		{prototype: LmiBool LmiProcessorSetHasSse4_1(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel SSE4.1.}}
		{parameter: {name: x} {description: Whether the processor supports Intel SSE4.1 instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasSse4_1(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasSse4_2}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel SSE4.2 instructions.}
		{prototype: LmiBool LmiProcessorSetHasSse4_2(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel SSE4.2.}}
		{parameter: {name: x} {description: Whether the processor supports Intel SSE4.2 instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasSse4_2(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasAes}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel AES-NI instructions.}
		{prototype: LmiBool LmiProcessorSetHasAes(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel AES-NI.}}
		{parameter: {name: x} {description: Whether the processor supports Intel AES-NI instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasAes(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasAvx}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel AVX instructions.}
		{prototype: LmiBool LmiProcessorSetHasAvx(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel AVX.}}
		{parameter: {name: x} {description: Whether the processor supports Intel AVX instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasAvx(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasAvx2}
		{parent: LmiProcessor}
		{description: Set whether a processor supports Intel AVX2 instructions.}
		{prototype: LmiBool LmiProcessorSetHasAvx2(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for Intel AVX2.}}
		{parameter: {name: x} {description: Whether the processor supports Intel AVX2 instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an X86 CPU.}
	}
*/
LmiBool LmiProcessorSetHasAvx2(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasNeon}
		{parent: LmiProcessor}
		{description: Set whether the processor supports ARM NEON instructions.}
		{prototype: LmiBool LmiProcessorSetHasNeon(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for ARM NEON.}}
		{parameter: {name: x} {description: Whether the processor supports ARM NEON instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an ARM CPU.}
	}
*/
LmiBool LmiProcessorSetHasNeon(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetHasArmCrypt}
		{parent: LmiProcessor}
		{description: Set whether the processor supports ARM Cryptographic instructions.}
		{prototype: LmiBool LmiProcessorSetHasArmCrypt(LmiProcessor* p, LmiBool x)}
		{parameter: {name: p} {description: The processor to query for ARM Cryptographic instructions.}}
		{parameter: {name: x} {description: Whether the processor supports ARM Cryptographic instructions.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure, including if this is not an ARM CPU.}
	}
*/
LmiBool LmiProcessorSetHasArmCrypt(LmiProcessor* p, LmiBool x);


/**
	{function visibility="private":
		{name: LmiProcessorSetGetTimesCallbacks}
		{parent: LmiProcessor}
		{description: Set the callbacks used for a processor's LmiProcessorGetTimes and LmiProcessorGetTimesPerCore functions.}
		{prototype: LmiBool LmiProcessorSetGetTimesCallbacks(LmiProcessor* p, LmiProcessorGetTimesCallback getTimes, LmiProcessorGetTimesPerCoreCallback getTimesPerCore, LmiVoidPtr userData)}
		{parameter: {name: p} {description: The processor whose getTimes callbacks to invoke.}}
		{parameter: {name: getTimes} {description: The callback to invoke for LmiProcessorGetTimes.}}
		{parameter: {name: getTimesPerCore} {description: The callback to invoke for LmiProcessorGetTimesPerCore.}}
		{parameter: {name: userData} {description: A user data pointer to pass to the callbacks.}}
		{return: LMI_TRUE if the callbacks were set, LMI_FALSE otherwise.}
	}
*/
LmiBool LmiProcessorSetGetTimesCallbacks(LmiProcessor* p, LmiProcessorGetTimesCallback getTimes, LmiProcessorGetTimesPerCoreCallback getTimesPerCore, LmiVoidPtr userData);


/**
	{function visibility="private":
		{name: LmiProcessorInitialize}
		{parent: Processor}
		{description: Initialize data related to CPU processor information.}
		{prototype: LmiBool LmiProcessorInitialize(void)}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: This function should not normally be called directly; instead,
			LmiOsInitialize should be called.}
	}
*/
LmiBool LmiProcessorInitialize(void);


/**
	{function visibility="private":
		{name: LmiProcessorUninitialize}
		{parent: Processor}
		{description: Free data related to CPU processor information.}
		{prototype: void LmiProcessorUninitialize(void)}
		{note: This function should not normally be called directly; instead,
			LmiOsUninitialize should be called.}
	}
*/
void LmiProcessorUninitialize(void);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiProcessorInline.h>
#endif

#endif

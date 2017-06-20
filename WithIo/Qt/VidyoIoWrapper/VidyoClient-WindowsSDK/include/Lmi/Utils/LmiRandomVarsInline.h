/**
{file:
	{name: LmiRandomVarsInline.h}
	{description: }
	{copyright:
		(c) 2010-2015 Vidyo, Inc.,
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
LMI_INLINE LmiVariableSimulator *LmiVariableSimulatorConstructBase_(LmiVariableSimulator *sim, LmiVariableSimulatorPlugIn *plugIn)
{
	sim->plugIn = plugIn;
	return sim;
}

LMI_INLINE void LmiVariableSimulatorDestruct_(LmiVariableSimulator *sim)
{
}

LMI_INLINE void LmiVariableSimulatorGenerateBytes_(LmiVariableSimulator *sim, void *buf, LmiSizeT length)
{
	sim->plugIn->generateBytes(sim, buf, length);
}

LMI_INLINE LmiFloat64 LmiVariableSimulatorGetUniform(LmiVariableSimulator *sim, LmiFloat64 min_, LmiFloat64 max_)
{
	return min_ + LmiVariableSimulatorGetStandardUniform(sim) * (max_ - min_);
}

LMI_INLINE LmiInt LmiVariableSimulatorGetDiscreteUniformInRange(LmiVariableSimulator *sim, LmiInt min_, LmiInt max_)
{
	return min_ + LmiVariableSimulatorGetDiscreteUniform(sim, (LmiUint)(max_ - min_ + 1));
}

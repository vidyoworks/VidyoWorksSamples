/** {file:
	  {name: LmiLinearProgrammingInline.h}
	  {description: Inline functions for LmiLinearProgramming.}
	  {copyright:
	  	(c) 2014-2015 Vidyo, Inc.,
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



LMI_INLINE LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstructDefault(LmiLinearProgrammingVariable *variable, LmiAllocator *alloc)
{
	variable->type = LMI_LINEARPROGRAMMINGVARIABLETYPE_FLOAT32;
	variable->index = 0;
	
	if(LmiStringConstructDefault(&variable->name, alloc) == NULL)
		goto FAIL1;
	
	return variable;
	
	LmiStringDestruct(&variable->name);		FAIL1:
	
	return NULL;
}

LMI_INLINE LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstruct(LmiLinearProgrammingVariable *variable, LmiLinearProgrammingVariableType type, LmiUint index, const LmiString *name, LmiAllocator *alloc)
{
	variable->type = type;
	variable->index = index;
	
	if(LmiStringConstructCopy(&variable->name, name) == NULL)
		goto FAIL1;
	
	return variable;
	
	LmiStringDestruct(&variable->name);		FAIL1:
	
	return NULL;
}

LMI_INLINE void LmiLinearProgrammingVariableDestruct(LmiLinearProgrammingVariable *variable)
{
	LmiStringDestruct(&variable->name);
}

LMI_INLINE LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstructCopy(LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)
{
	x->type = y->type;
	x->index = y->index;
	
	if(LmiStringConstructCopy(&x->name, &y->name) == NULL)
		goto FAIL1;
	
	return x;
	
	LmiStringDestruct(&x->name);		FAIL1:
	
	return NULL;
}

LMI_INLINE LmiLinearProgrammingVariable* LmiLinearProgrammingVariableAssign(LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)
{
	x->type = y->type;
	x->index = y->index;
	
	if(LmiStringAssign(&x->name, &y->name) == NULL)
		return NULL;
	
	return x;
}

LMI_INLINE LmiBool LmiLinearProgrammingVariableEqual(const LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)
{
	return ( (x->type == y->type) && (x->index == y->index) && LmiStringEqual(&x->name, &y->name) );
}

LMI_INLINE LmiBool LmiLinearProgrammingVariableLess(const LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)
{
	return LMI_FALSE;
}


LMI_INLINE void LmiLinearProgrammingVariableSetName(LmiLinearProgrammingVariable *variable, const LmiString *name)
{
	LmiStringAssign(&variable->name, name);
}

LMI_INLINE void LmiLinearProgrammingVariableSetType(LmiLinearProgrammingVariable *variable, LmiLinearProgrammingVariableType type)
{
	variable->type = type;
}

LMI_INLINE void LmiLinearProgrammingVariableSetIndex(LmiLinearProgrammingVariable *variable, LmiUint index)
{
	variable->index = index;
}

LMI_INLINE const LmiString* LmiLinearProgrammingVariableGetName(const LmiLinearProgrammingVariable *variable)
{
	return &variable->name;
}

LMI_INLINE LmiLinearProgrammingVariableType LmiLinearProgrammingVariableGetType(const LmiLinearProgrammingVariable *variable)
{
	return variable->type;
}

LMI_INLINE LmiUint LmiLinearProgrammingVariableGetIndex(const LmiLinearProgrammingVariable *variable)
{
	return variable->index;
}


LMI_INLINE LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstructIndex(LmiLinearProgrammingConstraint *constraint, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *variableCoefficients, LmiFloat32 rhs, LmiAllocator *alloc)
{
	constraint->type = LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX;
	
	if(LmiVectorConstructCopy(LmiPair(LmiUint, LmiFloat32))(&constraint->u.variableCoefficientsByIndex, variableCoefficients) == NULL)
		goto FAIL1;
	
	constraint->rhs = rhs;
	
	return constraint;
	
	LmiVectorDestruct(LmiPair(LmiUint, LmiFloat32))(&constraint->u.variableCoefficientsByIndex);	FAIL1:
	
	return NULL;
}

LMI_INLINE LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstruct(LmiLinearProgrammingConstraint *constraint, const LmiVector(LmiPair(LmiString, LmiFloat32)) *variableCoefficients, LmiFloat32 rhs, LmiAllocator *alloc)
{
	constraint->type = LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_NAME;
	
	if(LmiVectorConstructCopy(LmiPair(LmiString, LmiFloat32))(&constraint->u.variableCoefficientsByName, variableCoefficients) == NULL)
		goto FAIL1;
	
	constraint->rhs = rhs;
	
	return constraint;
	
	LmiVectorDestruct(LmiPair(LmiString, LmiFloat32))(&constraint->u.variableCoefficientsByName);	FAIL1:
	
	return NULL;
}

LMI_INLINE void LmiLinearProgrammingConstraintDestruct(LmiLinearProgrammingConstraint *constraint)
{
	if(constraint->type == LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX)
	{
		LmiVectorDestruct(LmiPair(LmiUint, LmiFloat32))(&constraint->u.variableCoefficientsByIndex);
	}
	else
	{
		LmiVectorDestruct(LmiPair(LmiString, LmiFloat32))(&constraint->u.variableCoefficientsByName);
	}
}

LMI_INLINE LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstructCopy(LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)
{
	x->type = y->type;
	
	if(x->type == LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX)
	{
		if(LmiVectorConstructCopy(LmiPair(LmiUint, LmiFloat32))(&x->u.variableCoefficientsByIndex, &y->u.variableCoefficientsByIndex) == NULL)
			goto FAIL1;
	}
	else
	{
		if(LmiVectorConstructCopy(LmiPair(LmiString, LmiFloat32))(&x->u.variableCoefficientsByName, &y->u.variableCoefficientsByName) == NULL)
			goto FAIL1;
	}
	
	x->rhs = y->rhs;
	
	return x;
	
	if(x->type == LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX)
	{
		LmiVectorDestruct(LmiPair(LmiUint, LmiFloat32))(&x->u.variableCoefficientsByIndex);
	}
	else
	{
		LmiVectorDestruct(LmiPair(LmiString, LmiFloat32))(&x->u.variableCoefficientsByName);
	}
																										FAIL1:
	
	return NULL;
}

LMI_INLINE LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintAssign(LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)
{
	x->type = y->type;
	
	if(x->type == LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX)
	{
		if(LmiVectorAssign(LmiPair(LmiUint, LmiFloat32))(&x->u.variableCoefficientsByIndex, &y->u.variableCoefficientsByIndex) == NULL)
			return NULL;
	}
	else
	{
		if(LmiVectorConstructCopy(LmiPair(LmiString, LmiFloat32))(&x->u.variableCoefficientsByName, &y->u.variableCoefficientsByName) == NULL)
			return NULL;
	}
	
	x->rhs = y->rhs;
	
	return x;
}

LMI_INLINE LmiBool LmiLinearProgrammingConstraintEqual(const LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)
{
	return LMI_FALSE;
}

LMI_INLINE LmiBool LmiLinearProgrammingConstraintLess(const LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)
{
	return LMI_FALSE;
}


LMI_INLINE LmiLinearProgrammingVariableAccessType LmiLinearProgrammingConstraintGetVariableAccessType(const LmiLinearProgrammingConstraint *c)
{
	return c->type;
}

LMI_INLINE const LmiVector(LmiPair(LmiUint, LmiFloat32))* LmiLinearProgrammingConstraintGetVariablesCoefficientsByIndex(const LmiLinearProgrammingConstraint *c)
{
	if(c->type == LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX)
		return &c->u.variableCoefficientsByIndex;
	
	return NULL;
}

LMI_INLINE const LmiVector(LmiPair(LmiString, LmiFloat32))* LmiLinearProgrammingConstraintGetVariablesCoefficientsByName(const LmiLinearProgrammingConstraint *c)
{
	if(c->type == LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_NAME)
		return &c->u.variableCoefficientsByName;
	
	return NULL;
}

LMI_INLINE LmiFloat32 LmiLinearProgrammingConstraintGetRhs(const LmiLinearProgrammingConstraint *c)
{
	return c->rhs;
}


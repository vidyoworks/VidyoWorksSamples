/** {file:
      {name: LmiLinearProgramming.h}
      {description: Linear programming solver.}
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

#ifndef LMI_LINEARPROGRAMMING_H_
#define LMI_LINEARPROGRAMMING_H_

#include <Lmi/Utils/LmiMatrix.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiUnordered.h>

LMI_BEGIN_EXTERN_C

Declare_LmiMatrix_Unsigned(LmiUint)
Declare_LmiMatrix(LmiFloat32)

Declare_LmiPair(LmiUint, LmiFloat32)
Declare_LmiVector(LmiPair(LmiUint, LmiFloat32))

Declare_LmiPair(LmiString, LmiFloat32)
Declare_LmiVector(LmiPair(LmiString, LmiFloat32))


/**
   {type:
     {name: LmiLinearProgrammingVariableType}
     {parent: LmiLinearProgramming}
     {include: Lmi/Utils/LmiLinearProgramming.h}
     {description: This class represents linear programming variable type.}
   }
*/
typedef enum
{
	LMI_LINEARPROGRAMMINGVARIABLETYPE_FLOAT32,
	LMI_LINEARPROGRAMMINGVARIABLETYPE_INTEGER,
	LMI_LINEARPROGRAMMINGVARIABLETYPE_BOOLEAN,
} LmiLinearProgrammingVariableType;

/**
   {type:
     {name: LmiLinearProgrammingVariable}
     {parent: LmiLinearProgramming}
     {include: Lmi/Utils/LmiLinearProgramming.h}
     {description: This class represents linear programming variable.}
   }
*/
typedef struct
{
	LmiLinearProgrammingVariableType type;
	LmiUint index;
	LmiString name;
} LmiLinearProgrammingVariable;


/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableConstructDefault}
	{parent: LmiLinearProgrammingVariable}
	{description: Construct a default linear programming variable object.}
	{prototype: LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstructDefault(LmiLinearProgrammingVariable *variable, LmiAllocator *alloc)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object to be constructed.}
	}
	{parameter: 
		{name: alloc}
		{description: An allocator to allocate memory.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstructDefault(LmiLinearProgrammingVariable *variable, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableConstruct}
	{parent: LmiLinearProgrammingVariable}
	{description: Construct a linear programming variable object.}
	{prototype: LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstruct(LmiLinearProgrammingVariable *variable, LmiLinearProgrammingVariableType type, LmiUint index, const LmiString *name, LmiAllocator *alloc)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object to be constructed.}
	}
    {parameter: 
		{name: type}
		{description: The LmiLinearProgrammingVariable object to be constructed.}
	}
    {parameter: 
		{name: index}
		{description: The index of the variable.}
	}
    {parameter: 
		{name: name}
		{description: The name of the variable.}
	}
	{parameter: 
		{name: alloc}
		{description: An allocator to allocate memory.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstruct(LmiLinearProgrammingVariable *variable, LmiLinearProgrammingVariableType type, LmiUint index, const LmiString *name, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableDestruct}
	{parent: LmiLinearProgrammingVariable}
	{description: Destruct the linear programming variable object.}
	{prototype: void LmiLinearProgrammingVariableDestruct(LmiLinearProgrammingVariable *variable)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object to be destructed.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiLinearProgrammingVariableDestruct(LmiLinearProgrammingVariable *variable);


/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableConstructCopy}
	{parent: LmiLinearProgrammingVariable}
	{description: Construct copy a linear programming variable object from another object.}
	{prototype: LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstructCopy(LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingVariable object to be constructed.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingVariable object from which the new object need to be constructed.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingVariable* LmiLinearProgrammingVariableConstructCopy(LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableAssign}
	{parent: LmiLinearProgrammingVariable}
	{description: Assign a linear programming variable object from another object.}
	{prototype: LmiLinearProgrammingVariable* LmiLinearProgrammingVariableAssign(LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingVariable object to be assigned.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingVariable object from which the object need to be assigned.}
	}
	{return: Pointer to the assigned object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingVariable* LmiLinearProgrammingVariableAssign(LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableEqual}
	{parent: LmiLinearProgrammingVariable}
	{description: Check for the equality of two linear programming variable objects.}
	{prototype: LmiBool LmiLinearProgrammingVariableEqual(const LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingVariable object.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingVariable object.}
	}
	{return: LMI_TRUE if equal, LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiLinearProgrammingVariableEqual(const LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableLess}
	{parent: LmiLinearProgrammingVariable}
	{description: Check whether a linear programming variable object is less than another object.}
	{prototype: LmiBool LmiLinearProgrammingVariableLess(const LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingVariable object.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingVariable object.}
	}
	{return: LMI_TRUE if x is less than y, LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiLinearProgrammingVariableLess(const LmiLinearProgrammingVariable *x, const LmiLinearProgrammingVariable *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableSetName}
	{parent: LmiLinearProgrammingVariable}
	{description: Set name on the linear programming variable object.}
	{prototype: void LmiLinearProgrammingVariableSetName(LmiLinearProgrammingVariable *variable, const LmiString *name)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object.}
	}
    {parameter: 
		{name: name}
		{description: The name of the variable.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiLinearProgrammingVariableSetName(LmiLinearProgrammingVariable *variable, const LmiString *name);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableSetType}
	{parent: LmiLinearProgrammingVariable}
	{description: Set type on the linear programming variable object.}
	{prototype:  void LmiLinearProgrammingVariableSetType(LmiLinearProgrammingVariable *variable, LmiLinearProgrammingVariableType type)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object.}
	}
    {parameter: 
		{name: type}
		{description: The type of the variable.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiLinearProgrammingVariableSetType(LmiLinearProgrammingVariable *variable, LmiLinearProgrammingVariableType type);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableSetIndex}
	{parent: LmiLinearProgrammingVariable}
	{description: Set index on the linear programming variable object.}
	{prototype:  void LmiLinearProgrammingVariableSetIndex(LmiLinearProgrammingVariable *variable, LmiUint index)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object.}
	}
    {parameter: 
		{name: index}
		{description: The index of the variable.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiLinearProgrammingVariableSetIndex(LmiLinearProgrammingVariable *variable, LmiUint index);


/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableGetName}
	{parent: LmiLinearProgrammingVariable}
	{description: Get name of the linear programming variable object.}
	{prototype: const LmiString* LmiLinearProgrammingVariableGetName(const LmiLinearProgrammingVariable *variable)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object.}
	}
    {return: The name of the variable.}
}
*/
LMI_INLINE_DECLARATION const LmiString* LmiLinearProgrammingVariableGetName(const LmiLinearProgrammingVariable *variable);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableGetType}
	{parent: LmiLinearProgrammingVariable}
	{description: Get type of the linear programming variable object.}
	{prototype: LmiLinearProgrammingVariableType LmiLinearProgrammingVariableGetType(const LmiLinearProgrammingVariable *variable)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object.}
	}
    {return: The type of the variable.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingVariableType LmiLinearProgrammingVariableGetType(const LmiLinearProgrammingVariable *variable);

/**
{function visibility="public":
	{name: LmiLinearProgrammingVariableGetIndex}
	{parent: LmiLinearProgrammingVariable}
	{description: Get index of the linear programming variable object.}
	{prototype: LmiUint LmiLinearProgrammingVariableGetIndex(const LmiLinearProgrammingVariable *variable)}
	{parameter: 
		{name: variable}
		{description: The LmiLinearProgrammingVariable object.}
	}
    {return: The index of the variable.}
}
*/
LMI_INLINE_DECLARATION LmiUint LmiLinearProgrammingVariableGetIndex(const LmiLinearProgrammingVariable *variable);


Declare_LmiUnorderedMap(LmiString, LmiLinearProgrammingVariable)


/**
   {type:
     {name: LmiLinearProgrammingVariableAccessType}
     {parent: LmiLinearProgramming}
     {include: Lmi/Utils/LmiLinearProgramming.h}
     {description: This class represents variable access type.}
   }
*/
typedef enum
{
	LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_INDEX,
	LMI_LINEARPROGRAMMINGVARIABLEACCESSTYPE_NAME,
} LmiLinearProgrammingVariableAccessType;

/**
   {type:
     {name: LmiLinearProgrammingConstraint}
     {parent: LmiLinearProgramming}
     {include: Lmi/Utils/LmiLinearProgramming.h}
     {description: This class represents a linear programming constraint.}
   }
*/
typedef struct
{
	LmiLinearProgrammingVariableAccessType type;
	union {
		LmiVector(LmiPair(LmiUint, LmiFloat32)) variableCoefficientsByIndex;
		LmiVector(LmiPair(LmiString, LmiFloat32)) variableCoefficientsByName;
	} u;
	LmiFloat32 rhs;
} LmiLinearProgrammingConstraint;


/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintConstructIndex}
	{parent: LmiLinearProgrammingConstraint}
	{description: Construct a linear programming constraint object by providing variable coefficients by index.}
	{prototype: LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstructIndex(LmiLinearProgrammingConstraint *constraint, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *variableCoefficients, LmiFloat32 rhs, LmiAllocator *alloc)}
	{parameter: 
		{name: constraint}
		{description: The LmiLinearProgrammingConstraint object to be constructed.}
	}
    {parameter: 
		{name: variableCoefficients}
		{description: The variable coefficients by index.}
	}
    {parameter: 
		{name: rhs}
		{description: The RHS value of the constraint.}
	}
	{parameter: 
		{name: alloc}
		{description: An allocator to allocate memory.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstructIndex(LmiLinearProgrammingConstraint *constraint, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *variableCoefficients, LmiFloat32 rhs, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintConstruct}
	{parent: LmiLinearProgrammingConstraint}
	{description: Construct a linear programming constraint object by providing variable coefficients by name of variables.}
	{prototype: LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstruct(LmiLinearProgrammingConstraint *constraint, const LmiVector(LmiPair(LmiString, LmiFloat32)) *variableCoefficients, LmiFloat32 rhs, LmiAllocator *alloc)}
	{parameter: 
		{name: constraint}
		{description: The LmiLinearProgrammingConstraint object to be constructed.}
	}
    {parameter: 
		{name: variableCoefficients}
		{description: The variable coefficients by name of variables.}
	}
    {parameter: 
		{name: rhs}
		{description: The RHS value of the constraint.}
	}
	{parameter: 
		{name: alloc}
		{description: An allocator to allocate memory.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstruct(LmiLinearProgrammingConstraint *constraint, const LmiVector(LmiPair(LmiString, LmiFloat32)) *variableCoefficients, LmiFloat32 rhs, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintDestruct}
	{parent: LmiLinearProgrammingConstraint}
	{description: Destruct the linear programming constraint object.}
	{prototype: void LmiLinearProgrammingConstraintDestruct(LmiLinearProgrammingConstraint *constraint)}
	{parameter: 
		{name: constraint}
		{description: The LmiLinearProgrammingConstraint object to be destructed.}
	}
}
*/
LMI_INLINE_DECLARATION void LmiLinearProgrammingConstraintDestruct(LmiLinearProgrammingConstraint *constraint);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintConstructCopy}
	{parent: LmiLinearProgrammingConstraint}
	{description: Construct copy a linear programming constraint object from another object.}
	{prototype: LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstructCopy(LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingConstraint object to be constructed.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingConstraint object from which the new object need to be constructed.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintConstructCopy(LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintAssign}
	{parent: LmiLinearProgrammingConstraint}
	{description: Assign a linear programming constraint object from another object.}
	{prototype: LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintAssign(LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingConstraint object to be assigned.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingConstraint object from which the object need to be assigned.}
	}
	{return: Pointer to the assigned object on success, NULL otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingConstraint* LmiLinearProgrammingConstraintAssign(LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintEqual}
	{parent: LmiLinearProgrammingConstraint}
	{description: Check for the equality of two linear programming constraint objects.}
	{prototype: LmiBool LmiLinearProgrammingConstraintEqual(const LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingConstraint object.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingConstraint object.}
	}
	{return: LMI_TRUE if equal, LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiLinearProgrammingConstraintEqual(const LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintLess}
	{parent: LmiLinearProgrammingConstraint}
	{description: Check whether a linear programming constraint object is less than another object.}
	{prototype: LmiBool LmiLinearProgrammingConstraintLess(const LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y)}
	{parameter: 
		{name: x}
		{description: The LmiLinearProgrammingConstraint object.}
	}
   {parameter: 
		{name: y}
		{description: The LmiLinearProgrammingConstraint object.}
	}
	{return: LMI_TRUE if x is less than y, LMI_FALSE otherwise.}
}
*/
LMI_INLINE_DECLARATION LmiBool LmiLinearProgrammingConstraintLess(const LmiLinearProgrammingConstraint *x, const LmiLinearProgrammingConstraint *y);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintGetVariableAccessType}
	{parent: LmiLinearProgrammingConstraint}
	{description: Get variable access type of the linear programming constraint object.}
	{prototype: LmiLinearProgrammingVariableAccessType LmiLinearProgrammingConstraintGetVariableAccessType(const LmiLinearProgrammingConstraint *c)}
	{parameter: 
		{name: c}
		{description: The LmiLinearProgrammingConstraint object.}
	}
    {return: The variable access type of the constraint.}
}
*/
LMI_INLINE_DECLARATION LmiLinearProgrammingVariableAccessType LmiLinearProgrammingConstraintGetVariableAccessType(const LmiLinearProgrammingConstraint *c);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintGetVariablesCoefficientsByIndex}
	{parent: LmiLinearProgrammingConstraint}
	{description: Get the variable coefficients of the linear programming constraint object by index of variables.}
	{prototype: const LmiVector(LmiPair(LmiUint, LmiFloat32))* LmiLinearProgrammingConstraintGetVariablesCoefficientsByIndex(const LmiLinearProgrammingConstraint *c)}
	{parameter: 
		{name: c}
		{description: The LmiLinearProgrammingConstraint object.}
	}
    {return: The variable coefficients by index of variables.}
}
*/
LMI_INLINE_DECLARATION const LmiVector(LmiPair(LmiUint, LmiFloat32))* LmiLinearProgrammingConstraintGetVariablesCoefficientsByIndex(const LmiLinearProgrammingConstraint *c);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintGetVariablesCoefficientsByName}
	{parent: LmiLinearProgrammingConstraint}
	{description: Get the variable coefficients of the linear programming constraint object by name of variables.}
	{prototype: const LmiVector(LmiPair(LmiString, LmiFloat32))* LmiLinearProgrammingConstraintGetVariablesCoefficientsByName(const LmiLinearProgrammingConstraint *c)}
	{parameter: 
		{name: c}
		{description: The LmiLinearProgrammingConstraint object.}
	}
    {return: The variable coefficients by name of variables.}
}
*/
LMI_INLINE_DECLARATION const LmiVector(LmiPair(LmiString, LmiFloat32))* LmiLinearProgrammingConstraintGetVariablesCoefficientsByName(const LmiLinearProgrammingConstraint *c);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstraintGetRhs}
	{parent: LmiLinearProgrammingConstraint}
	{description: Get the RHS of the linear programming constraint.}
	{prototype: LmiFloat32 LmiLinearProgrammingConstraintGetRhs(const LmiLinearProgrammingConstraint *c)}
	{parameter: 
		{name: c}
		{description: The LmiLinearProgrammingConstraint object.}
	}
    {return: The RHS of the constraint.}
}
*/
LMI_INLINE_DECLARATION LmiFloat32 LmiLinearProgrammingConstraintGetRhs(const LmiLinearProgrammingConstraint *c);

Declare_LmiUnorderedMap(LmiUint, LmiLinearProgrammingConstraint)


/**
   {type:
     {name: LmiLinearProgrammingResultType}
     {parent: LmiLinearProgramming}
     {include: Lmi/Utils/LmiLinearProgramming.h}
     {description: This class represents linear programming result.}
   }
*/
typedef enum
{
	LMI_LINEARPROGRAMMINGRESULTTYPE_Ok,
	LMI_LINEARPROGRAMMINGRESULTTYPE_InvalidInput,
	LMI_LINEARPROGRAMMINGRESULTTYPE_Unbounded,
	LMI_LINEARPROGRAMMINGRESULTTYPE_Infeasible,
} LmiLinearProgrammingResultType;


/**
   {type:
     {name: LmiLinearProgramming}
     {parent: Utils}
     {include: Lmi/Utils/LmiLinearProgramming.h}
     {description: This class implements the linear programming solver.}
   }
*/
typedef struct
{
	LmiAllocator *alloc;
	LmiUint numVars;
	LmiUint numConstraints;
	
	LmiMatrix(LmiFloat32) A;
	LmiMatrix(LmiFloat32) b;
	LmiMatrix(LmiFloat32) c;
	
	LmiMatrix(LmiUint) basic;		/* Basic variable index vector */
	LmiMatrix(LmiUint) independent; /* Non-basic variable index vector */
	
	LmiUnorderedMap(LmiString, LmiLinearProgrammingVariable) variables;
	LmiUnorderedMap(LmiUint, LmiLinearProgrammingConstraint) constraints;
	LmiVector(LmiPair(LmiUint, LmiFloat32)) objective;
	
	LmiVector(LmiPair(LmiString, LmiFloat32)) variableValues;
	LmiFloat32 objectiveValue;
}LmiLinearProgramming;



/**
{function visibility="public":
	{name: LmiLinearProgrammingConstructDefault}
	{parent: LmiLinearProgramming}
	{description: Construct a default linear programming object.}
	{prototype: LmiLinearProgramming* LmiLinearProgrammingConstructDefault(LmiLinearProgramming* lp, LmiAllocator *alloc)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object to be constructed.}
	}
	{parameter: 
		{name: alloc}
		{description: An allocator to allocate memory.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LmiLinearProgramming* LmiLinearProgrammingConstructDefault(LmiLinearProgramming* lp, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearProgrammingConstruct}
	{parent: LmiLinearProgramming}
	{description: Construct a linear programming object.}
	{prototype: LmiLinearProgramming* LmiLinearProgrammingConstruct(LmiLinearProgramming* lp, LmiUint numVars, LmiAllocator *alloc)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object to be constructed.}
	}
	{parameter: 
		{name: numVars}
		{description: Number of decision variables.}
	}
	{parameter: 
		{name: alloc}
		{description: An allocator to allocate memory.}
	}
	{return: Pointer to the constructed object on success, NULL otherwise.}
}
*/
LmiLinearProgramming* LmiLinearProgrammingConstruct(LmiLinearProgramming* lp, LmiUint numVars, LmiAllocator *alloc);

/**
{function visibility="public":
	{name: LmiLinearProgrammingDestruct}
	{parent: LmiLinearProgramming}
	{description: Destruct the linear programming object.}
	{prototype: void LmiLinearProgrammingDestruct(LmiLinearProgramming *lp)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object to be destructed.}
	}
}
*/
void LmiLinearProgrammingDestruct(LmiLinearProgramming *lp);


/**
{function visibility="public":
	{name: LmiLinearProgrammingSetNumVars}
	{parent: LmiLinearProgramming}
	{description: Set number of decision variables on linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetNumVars(LmiLinearProgramming* lp, LmiUint numVars)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: numVars}
		{description: Number of decision variables.}
	}
    {return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetNumVars(LmiLinearProgramming* lp, LmiUint numVars);


/**
{function visibility="public":
	{name: LmiLinearProgrammingGetNumVars}
	{parent: LmiLinearProgramming}
	{description: Get number of decision variables on linear programming object.}
	{prototype: LmiUint LmiLinearProgrammingGetNumVars(const LmiLinearProgramming* lp)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
    {return: Number of decision variables.}
}
*/
LmiUint LmiLinearProgrammingGetNumVars(const LmiLinearProgramming* lp);


/**
{function visibility="public":
	{name: LmiLinearProgrammingSetVariableInfo}
	{parent: LmiLinearProgramming}
	{description: Set variable names to decision variables of linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetVariableInfo(LmiLinearProgramming* lp, LmiUint variableIndex, const LmiString *name, LmiLinearProgrammingVariableType type)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: variableIndex}
		{description: Index of decision variable.}
	}
	{parameter: 
		{name: name}
		{description: Name of decision variable.}
	}
    {parameter: 
		{name: type}
		{description: Type of decision variable.}
	}
    {return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetVariableInfo(LmiLinearProgramming* lp, LmiUint variableIndex, const LmiString *name, LmiLinearProgrammingVariableType type);

/**
{function visibility="public":
	{name: LmiLinearProgrammingSetConstraintByIndex}
	{parent: LmiLinearProgramming}
	{description: Set a constraint by index of variables to the linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetConstraintByIndex(LmiLinearProgramming* lp, LmiUint constraintId, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *constraintValues, LmiFloat32 rhs)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: constraintId}
		{description: The id of the constraint.}
	}
	{parameter: 
		{name: constraintValues}
		{description: Coefficient of the decision variables in the constraint.
			Each element of the vector is a pair of index of the variable and the coefficient of the variable.}
	}
	{parameter: 
		{name: rhs}
		{description: Right hand side value of the constraint.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetConstraintByIndex(LmiLinearProgramming* lp, LmiUint constraintId, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *constraintValues, LmiFloat32 rhs);

/**
{function visibility="public":
	{name: LmiLinearProgrammingSetConstraintByName}
	{parent: LmiLinearProgramming}
	{description: Set constraint by name of variables on the linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetConstraintByName(LmiLinearProgramming* lp, LmiUint constraintId, const LmiVector(LmiPair(LmiString, LmiFloat32)) *constraintValues, LmiFloat32 rhs)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: constraintId}
		{description: The id of the constraint.}
	}
	{parameter: 
		{name: constraintValues}
		{description: Coefficient of the decision variables in the constraint.
			Each element of the vector is a pair of name of the variable and the coefficient of the variable.}
	}
	{parameter: 
		{name: rhs}
		{description: Right hand side value of the constraint.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetConstraintByName(LmiLinearProgramming* lp, LmiUint constraintId, const LmiVector(LmiPair(LmiString, LmiFloat32)) *constraintValues, LmiFloat32 rhs);

/**
{function visibility="public":
	{name: LmiLinearProgrammingSetConstraint}
	{parent: LmiLinearProgramming}
	{description: Set a constraint by id to the linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetConstraint(LmiLinearProgramming* lp, LmiUint constraintId, const LmiLinearProgrammingConstraint *constraint)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: constraintId}
		{description: The id of the constraint.}
	}
	{parameter: 
		{name: constraint}
		{description: The LmiLinearProgrammingConstraint object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetConstraint(LmiLinearProgramming* lp, LmiUint constraintId, const LmiLinearProgrammingConstraint *constraint);


/**
{function visibility="public":
	{name: LmiLinearProgrammingRemoveConstraint}
	{parent: LmiLinearProgramming}
	{description: Remove a constraint by id from the linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingRemoveConstraint(LmiLinearProgramming* lp, LmiUint constraintId)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: constraintId}
		{description: The id of the constraint.}
	}
    {return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingRemoveConstraint(LmiLinearProgramming* lp, LmiUint constraintId);

/**
{function visibility="public":
	{name: LmiLinearProgrammingGetNumConstraints}
	{parent: LmiLinearProgramming}
	{description: Get number of decision variables on linear programming object.}
	{prototype: LmiUint LmiLinearProgrammingGetNumConstraints(const LmiLinearProgramming* lp)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
    {return: Number of constraints.}
}
*/
LmiUint LmiLinearProgrammingGetNumConstraints(const LmiLinearProgramming* lp);


/**
{function visibility="public":
	{name: LmiLinearProgrammingSetObjective}
	{parent: LmiLinearProgramming}
	{description: Set the objective coefficients of decision variables by names to the linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetObjective(LmiLinearProgramming* lp, const LmiVector(LmiPair(LmiString, LmiFloat32)) *objectiveValues)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: objectiveValues}
		{description: Coefficient of the decision variables in the objective.
			Each element of the vector is a pair of name of the variable and the coefficient of the variable.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetObjective(LmiLinearProgramming* lp, const LmiVector(LmiPair(LmiString, LmiFloat32)) *objectiveValues);

/**
{function visibility="public":
	{name: LmiLinearProgrammingSetObjectiveByIndex}
	{parent: LmiLinearProgramming}
	{description: Set the objective coefficients of decision variables by index to the linear programming object.}
	{prototype: void LmiLinearProgrammingSetObjectiveByIndex(LmiLinearProgramming* lp, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *objectiveValues)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: objectiveValues}
		{description: Coefficient of the decision variables in the objective.
			Each element of the vector is a pair of index of the variable and the coefficient of the variable.}
	}
}
*/
void LmiLinearProgrammingSetObjectiveByIndex(LmiLinearProgramming* lp, const LmiVector(LmiPair(LmiUint, LmiFloat32)) *objectiveValues);

/**
{function visibility="private":
	{name: LmiLinearProgrammingSetInput}
	{parent: LmiLinearProgramming}
	{description: Set the inputs to the linear programming object.}
	{prototype: LmiBool LmiLinearProgrammingSetInput(LmiLinearProgramming* lp, const LmiMatrix(LmiFloat32) *A, const LmiMatrix(LmiFloat32) *b, const LmiMatrix(LmiFloat32) *c)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{parameter: 
		{name: A}
		{description: Matrix representing the LHS of constraints.}
	}
	{parameter: 
		{name: b}
		{description: Matrix representing the RHS of constraints.}
	}
	{parameter: 
		{name: c}
		{description: Matrix representing the objective values.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiBool LmiLinearProgrammingSetInput(LmiLinearProgramming* lp, const LmiMatrix(LmiFloat32) *A, const LmiMatrix(LmiFloat32) *b, const LmiMatrix(LmiFloat32) *c);

/**
{function visibility="public":
	{name: LmiLinearProgrammingSolve}
	{parent: LmiLinearProgramming}
	{description: Solve the linear programming problem.}
	{prototype: LmiLinearProgrammingResultType LmiLinearProgrammingSolve(LmiLinearProgramming* lp)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{return: LMI_TRUE on success, LMI_FALSE otherwise.}
}
*/
LmiLinearProgrammingResultType LmiLinearProgrammingSolve(LmiLinearProgramming* lp);

/**
{function visibility="public":
	{name: LmiLinearProgrammingGetObjectiveValue}
	{parent: LmiLinearProgramming}
	{description: Get the object value of linear programming problem solution.}
	{prototype: LmiFloat32 LmiLinearProgrammingGetObjectiveValue(const LmiLinearProgramming* lp)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{return: The objective value.}
}
*/
LmiFloat32 LmiLinearProgrammingGetObjectiveValue(const LmiLinearProgramming* lp);


/**
{function visibility="public":
	{name: LmiLinearProgrammingGetVariableValues}
	{parent: LmiLinearProgramming}
	{description: Get the decision variable values of linear programming problem solution.}
	{prototype: const LmiVector(LmiPair(LmiString, LmiFloat32))* LmiLinearProgrammingGetVariableValues(const LmiLinearProgramming* lp)}
	{parameter: 
		{name: lp}
		{description: The LmiLinearProgramming object.}
	}
	{return: The values of the decision variables.}
}
*/
const LmiVector(LmiPair(LmiString, LmiFloat32))* LmiLinearProgrammingGetVariableValues(const LmiLinearProgramming* lp);


LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiLinearProgrammingInline.h>
#endif


#endif /* LMI_LINEARPROGRAMMING_H_ */

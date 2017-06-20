/**
{file: 
	{name: LmiMatrix.h}
	{description: Matrix class.}
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

#if !defined(LMI_MATRIX_H_)
#define LMI_MATRIX_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAssert.h>
#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiStdCLib.h>
#include <Lmi/Utils/LmiMisc.h>

LMI_BEGIN_EXTERN_C

/* Name mangling */
#define LmiMatrix(T_)											LmiTemplate1(LmiMatrix, T_)
#define LmiMatrixDestruct(T_)									LmiClassFunc(LmiMatrix(T_), Destruct)
#define LmiMatrixConstructDefault(T_)							LmiClassFunc(LmiMatrix(T_), ConstructDefault)
#define LmiMatrixConstruct(T_)									LmiClassFunc(LmiMatrix(T_), Construct)
#define LmiMatrixConstructIdentity(T_)							LmiClassFunc(LmiMatrix(T_), ConstructIdentity)
#define LmiMatrixConstructCopy(T_)								LmiClassFunc(LmiMatrix(T_), ConstructCopy)
#define LmiMatrixConstructCopyRange(T_)							LmiClassFunc(LmiMatrix(T_), ConstructCopyRange)
#define LmiMatrixGetAllocator(T_)								LmiClassFunc(LmiMatrix(T_), GetAllocator)
#define LmiMatrixAssign(T_)										LmiClassFunc(LmiMatrix(T_), Assign)
#define LmiMatrixCopyRange(T_)									LmiClassFunc(LmiMatrix(T_), CopyRange)
#define LmiMatrixSwap(T_)										LmiClassFunc(LmiMatrix(T_), Swap)
#define LmiMatrixSwapRow(T_)									LmiClassFunc(LmiMatrix(T_), SwapRow)
#define LmiMatrixSwapColumn(T_)									LmiClassFunc(LmiMatrix(T_), SwapColumn)

#define LmiMatrixEqual(T_)										LmiClassFunc(LmiMatrix(T_), Equal)
#define LmiMatrixLess(T_)										LmiClassFunc(LmiMatrix(T_), Less)
#define LmiMatrixGetNumRows(T_)									LmiClassFunc(LmiMatrix(T_), GetNumRows)
#define LmiMatrixGetNumColumns(T_)								LmiClassFunc(LmiMatrix(T_), GetNumColumns)
#define LmiMatrixAt(T_)											LmiClassFunc(LmiMatrix(T_), At)
#define LmiMatrixReset(T_)										LmiClassFunc(LmiMatrix(T_), Reset)
#define LmiMatrixResize(T_)										LmiClassFunc(LmiMatrix(T_), Resize)
#define LmiMatrixSetVal(T_)										LmiClassFunc(LmiMatrix(T_), SetVal)

#define LmiMatrixAdd(T_)										LmiClassFunc(LmiMatrix(T_), Add)
#define LmiMatrixSubtract(T_)									LmiClassFunc(LmiMatrix(T_), Subtract)
#define LmiMatrixMultiply(T_)									LmiClassFunc(LmiMatrix(T_), Multiply)
#define LmiMatrixMultiplyScalar(T_)								LmiClassFunc(LmiMatrix(T_), MultiplyScalar)
#define LmiMatrixTranspose(T_)									LmiClassFunc(LmiMatrix(T_), Transpose)
#define LmiMatrixInverse(T_)									LmiClassFunc(LmiMatrix(T_), Inverse)

#define LmiMatrixDump(T_)										LmiClassFunc(LmiMatrix(T_), Dump)

/***** Declarations *****/

/* Matrix specific functions */
#define Declare_LmiMatrixConstruct(T_) \
	LmiMatrix(T_)* LmiMatrixConstruct(T_)(LmiMatrix(T_)* x, LmiUint rows, LmiUint cols, LmiAllocator *a);

#define Declare_LmiMatrixConstructIdentity(T_) \
	LmiMatrix(T_)* LmiMatrixConstructIdentity(T_)(LmiMatrix(T_)* x, LmiUint dimension, LmiAllocator *a);


#define Declare_LmiMatrixConstructCopyRange(T_) \
	LmiMatrix(T_)* LmiMatrixConstructCopyRange(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiUint sourceRow, LmiUint sourceCol,LmiUint numRows, LmiUint numCols, LmiAllocator *a);

#define Declare_LmiMatrixCopyRange(T_) \
	LmiMatrix(T_)* LmiMatrixCopyRange(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiUint xSourceRow, xSourceCol, LmiUint ySourceRow, LmiUint ySourceCol,LmiUint numRows, LmiUint numCols, LmiAllocator *a);

#define Declare_LmiMatrixSwapRow(T_) \
	LmiBool LmiMatrixSwapRow(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y, LmiUint rowX, LmiUint rowY);

#define Declare_LmiMatrixSwapColumn(T_) \
	LmiBool LmiMatrixSwapColumn(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y, LmiUint columnX, LmiUint columnY);

#define Declare_LmiMatrixAdd(T_) \
	LmiBool LmiMatrixAdd(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result);

#define Declare_LmiMatrixSubtract(T_) \
	LmiBool LmiMatrixSubtract(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result);

#define Declare_LmiMatrixMultiply(T_) \
	LmiBool LmiMatrixMultiply(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result);

#define Declare_LmiMatrixMultiplyScalar(T_) \
	LmiBool LmiMatrixMultiplyScalar(T_)(const LmiMatrix(T_)* x, T_ y, LmiMatrix(T_)* result);

#define Declare_LmiMatrixTranspose(T_) \
	LmiBool LmiMatrixTranspose(T_)(const LmiMatrix(T_)* x, LmiMatrix(T_)* result);

#define Declare_LmiMatrixInverse(T_) \
	LmiBool LmiMatrixInverse(T_)(const LmiMatrix(T_)* x, LmiMatrix(T_)* result);

#define Declare_LmiMatrixGetNumRows(T_) \
	LMI_INLINE_DECLARATION LmiUint LmiMatrixGetNumRows(T_)(const LmiMatrix(T_)* x);

#define Declare_LmiMatrixGetNumColumns(T_) \
	LMI_INLINE_DECLARATION LmiUint LmiMatrixGetNumColumns(T_)(const LmiMatrix(T_)* x);

#define Declare_LmiMatrixAt(T_) \
	LMI_INLINE_DECLARATION T_ LmiMatrixAt(T_)(const LmiMatrix(T_)* x, LmiUint row, LmiUint col);

#define Declare_LmiMatrixReset(T_) \
	LMI_INLINE_DECLARATION void LmiMatrixReset(T_)(LmiMatrix(T_)* x);

#define Declare_LmiMatrixSetVal(T_) \
	LMI_INLINE_DECLARATION void LmiMatrixSetVal(T_)(LmiMatrix(T_)* x, LmiUint row, LmiUint col, T_ val);

#define Declare_LmiMatrixResize(T_) \
	LmiMatrix(T_)* LmiMatrixResize(T_)(LmiMatrix(T_)* x, LmiUint row, LmiUint col);



/**
{type:
	{name: LmiMatrix}
	{parent: Utils}
	{include: Lmi/Utils/LmiMatrix.h}
	{description: A parameterized matrix class.}
	{template-prototype: LmiMatrix(T_)}
	{template-parameter:
		{name: T_}
		{description: The type of matrix elements.}
	}
	{note: 
		The macro Declare_LmiMatrix must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{function validate="no":
	{name: Declare_LmiMatrix}
	{parent: LmiMatrix}
	{description: Declare a parameterized matrix.}
	{prototype: void Declare_LmiMatrix(Type T)}
	{parameter:
		{name: T} 
		{description: The type of matrix elements.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate a matrix of integers *\/
		Declare_LmiMatrix(LmiInt)
		LmiMatrix(LmiInt) numbers;
	}
}
*/


#define Declare_LmiMatrixFuncs(T_) \
	Declare_LmiAssignable(LmiMatrix(T_)) \
	Declare_LmiEqualityComparable(LmiMatrix(T_)) \
	Declare_LmiLessThanComparable(LmiMatrix(T_)) \
	Declare_LmiDefaultConstructible(LmiMatrix(T_)) \
	Declare_LmiDumpable(LmiMatrix(T_)) \
	Declare_LmiMatrixConstruct(T_) \
	Declare_LmiMatrixConstructIdentity(T_) \
	Declare_LmiMatrixSwapRow(T_) \
	Declare_LmiMatrixSwapColumn(T_) \
	Declare_LmiMatrixAdd(T_) \
	Declare_LmiMatrixMultiply(T_) \
	Declare_LmiMatrixMultiplyScalar(T_) \
	Declare_LmiMatrixTranspose(T_) \
	Declare_LmiMatrixGetNumRows(T_) \
	Declare_LmiMatrixGetNumColumns(T_) \
	Declare_LmiMatrixAt(T_) \
	Declare_LmiMatrixReset(T_) \
	Declare_LmiMatrixSetVal(T_) \
	Declare_LmiMatrixResize(T_)


/* Matrix Template */
#define Declare_LmiMatrix_Unsigned(T_) \
	typedef struct LmiMatrix(T_) { \
		LmiAllocator* allocator; \
		LmiUint nr; \
		LmiUint nc; \
		T_* data; \
	} LmiMatrix(T_); \
	Declare_LmiMatrixFuncs(T_) \
	DefineInlineHeader_LmiMatrixFuncs(T_)

#define Declare_LmiMatrix_Integer(T_) \
	Declare_LmiMatrix_Unsigned(T_) \
	Declare_LmiMatrixSubtract(T_)

#define Declare_LmiMatrix(T_) \
	Declare_LmiMatrix_Integer(T_) \
	Declare_LmiMatrixInverse(T_)

/****** Definitions ******/

/**
{function:
	{name: LmiMatrixDestruct}
	{parent: LmiMatrix}
	{description: Destruct a matrix.}
	{prototype: void LmiMatrixDestruct(T_)(LmiMatrix(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to destruct. }
	}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define Define_LmiMatrixDestruct(T_) \
	void LmiMatrixDestruct(T_)(LmiMatrix(T_)* x) { \
		if(x->nr != 0) \
			LmiAllocatorDeallocate(x->allocator, x->data, (x->nr * x->nc) * sizeof(T_)); \
			x->nr = 0; \
			x->nc = 0; \
			x->data = NULL; \
	}

/**
{function:
	{name: LmiMatrixConstructDefault}
	{parent: LmiMatrix}
	{description: Construct an empty matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixConstructDefault(T_)(LmiMatrix(T_)* x, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to construct.}
	}
	{parameter:
		{name: a}
		{description: The matrix's allocator.}
	}
	{return: A pointer to the constructed matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define Define_LmiMatrixConstructDefault(T_)						\
	LmiMatrix(T_)* LmiMatrixConstructDefault(T_)(LmiMatrix(T_)* x, LmiAllocator* a) { \
		x->allocator = a; \
		x->nr = 0; \
		x->nc = 0; \
		x->data = NULL; \
		return x; \
	}
/**
{function:
	{name: LmiMatrixConstruct}
	{parent: LmiMatrix}
	{description: Construct a matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixConstruct(T_)(LmiMatrix(T_)* x, LmiUint numRows, LmiUint numCols, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to construct.}
	}
	{parameter:
		{name: numRows}
		{description: The number of rows in the matrix to construct.}
	}
	{parameter:
		{name: numCols}
		{description: The number of columns in the matrix to construct.}
	}
	{parameter:
		{name: a}
		{description: The matrix's allocator.}
	}
	{return: A pointer to the constructed matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		Number of rows and number of columns both need to be either zero or non-zero.
	}
}
*/
#define Define_LmiMatrixConstruct(T_) \
	LmiMatrix(T_)* LmiMatrixConstruct(T_)(LmiMatrix(T_)* x, LmiUint numRows, LmiUint numCols, LmiAllocator* a) { \
		if( (numRows == 0 && numCols != 0) || (numRows != 0 && numCols == 0) ) return NULL; \
		x->allocator = a; \
		x->nr = numRows; \
		x->nc = numCols; \
		x->data = NULL; \
		if(numRows != 0) \
		{ \
			x->data = (T_*)LmiAllocatorAllocate(x->allocator, numRows * numCols * sizeof(T_)); \
			if(x->data == NULL) return NULL; \
		} \
		return x; \
	}

/**
{function:
	{name: LmiMatrixConstructIdentity}
	{parent: LmiMatrix}
	{description: Construct an identity matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixConstructIdentity(T_)(LmiMatrix(T_)* x, LmiUint dimension, LmiAllocator* a)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to construct.}
	}
	{parameter:
		{name: dimension}
		{description: The size of the identity matrix to construct.}
	}
	{parameter:
		{name: a}
		{description: The matrix's allocator.}
	}
	{return: A pointer to the constructed matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		Dimension should be non-zero.
	}
}
*/
#define Define_LmiMatrixConstructIdentity(T_) \
	LmiMatrix(T_)* LmiMatrixConstructIdentity(T_)(LmiMatrix(T_)* x, LmiUint dimension, LmiAllocator* a) { \
		LmiUint i; \
		if(dimension == 0) return NULL; \
		x->allocator = a; \
		x->nr = x->nc = dimension; \
		x->data = NULL; \
		x->data = (T_*)LmiAllocatorAllocate(x->allocator, dimension * dimension * sizeof(T_)); \
		if(x->data == NULL) return NULL; \
		LmiMatrixReset(T_)(x); \
		for(i = 0; i < dimension; ++i) \
			x->data[i * dimension + i] = 1; \
		return x; \
	}

/**
{function:
	{name: LmiMatrixConstructCopy}
	{parent: LmiMatrix}
	{description: Construct a matrix from another matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixConstructCopy(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to construct.}
	}
	{parameter:
		{name: y}
		{description: The matrix to use to initialize the matrix being constructed.}
	}
	{return: A pointer to the constructed matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define Define_LmiMatrixConstructCopy(T_) \
	LmiMatrix(T_)* LmiMatrixConstructCopy(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y) { \
		x->allocator = y->allocator; \
		x->nr = y->nr; \
		x->nc = y->nc; \
		x->data = NULL; \
		if(y->nr != 0) \
		{ \
			x->data = (T_*)LmiAllocatorAllocate(x->allocator, y->nr * y->nc * sizeof(T_)); \
			if(x->data == NULL) return NULL; \
			LmiMemCpy(x->data, y->data, y->nr * y->nc * sizeof(T_)); \
		} \
		return x; \
	}
/**
{function:
	{name: LmiMatrixConstructCopyRange}
	{parent: LmiMatrix}
	{description: Construct a matrix as a sub-matrix of another matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixConstructCopyRange(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiUint sourceRow, LmiUint sourceCol, LmiUint numRows, LmiUint numCols, LmiAllocator *a)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to construct.}
	}
	{parameter:
		{name: y}
		{description: The matrix to use to initialize the matrix being constructed.}
	}
	{parameter:
		{name: sourceRow}
		{description: The source row in the source matrix from which the data is copied to the new matrix being constructed.}
	}
	{parameter:
		{name: sourceCol}
		{description:  The source column in the source matrix from which the data is copied to the new matrix being constructed.}
	}
	{parameter:
		{name: numRows}
		{description: The number of rows to be copied.}
	}
	{parameter:
		{name: numCols}
		{description: The number of columns to be copied.}
	}
	{parameter:
		{name: a}
		{description: The matrix's allocator.}
	}
	{return: A pointer to the constructed matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define Define_LmiMatrixConstructCopyRange(T_) \
	LmiMatrix(T_)* LmiMatrixConstructCopyRange(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiUint sourceRow, LmiUint sourceCol, LmiUint numRows, LmiUint numCols, LmiAllocator *a) { \
		if( ( (sourceRow + numRows) > LmiMatrixGetNumRows(T_)(y) ) || ( (sourceCol + numCols) > LmiMatrixGetNumColumns(T_)(y) ) ) return NULL; \
		x->allocator = y->allocator; \
		x->nr = numRows; \
		x->nc = numCols; \
		x->data = NULL; \
		if(x->nr != 0) \
		{ \
			LmiUint i, j; \
			x->data = (T_*)LmiAllocatorAllocate(x->allocator, numRows * numCols * sizeof(T_)); \
			if(x->data == NULL) return NULL; \
			for(i = 0; i < numRows; ++i) \
				for(j = 0; j < numCols; ++j) \
					x->data[i * x->nc + j] = y->data[(sourceRow + i) * y->nc + (sourceCol + j)]; \
		} \
		return x; \
	}



/**
{function:
	{name: LmiMatrixCopyRange}
	{parent: LmiMatrix}
	{description: Construct a matrix as a sub-matrix of another matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixCopyRange(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiUint xSourceRow, LmiUint xSourceCol, LmiUint ySourceRow, LmiUint ySourceCol, LmiUint numRows, LmiUint numCols)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to construct.}
	}
	{parameter:
		{name: y}
		{description: The matrix to use to initialize the matrix being constructed.}
	}
	{parameter:
		{name: xSourceRow}
		{description: The source row of the destination matrix to which the data is copied.}
	}
	{parameter:
		{name: xSourceCol}
		{description:  The source column of the source matrix to which the data is copied.}
	}
	{parameter:
		{name: ySourceRow}
		{description: The source row in the source matrix from which the data is copied.}
	}
	{parameter:
		{name: ySourceCol}
		{description:  The source column in the source matrix from which the data is copied.}
	}
	{parameter:
		{name: numRows}
		{description: The number of rows to be copied.}
	}
	{parameter:
		{name: numCols}
		{description: The number of columns to be copied.}
	}
	{return: A pointer to the constructed matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define Define_LmiMatrixCopyRange(T_) \
	LmiMatrix(T_)* LmiMatrixCopyRange(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiUint xSourceRow, LmiUint xSourceCol, LmiUint ySourceRow, LmiUint ySourceCol,LmiUint numRows, LmiUint numCols) { \
		if( ( (xSourceRow + numRows) > LmiMatrixGetNumRows(T_)(x) ) || ( (xSourceCol + numCols) > LmiMatrixGetNumColumns(T_)(x) ) || ( (ySourceRow + numRows) > LmiMatrixGetNumRows(T_)(y) ) || ( (ySourceCol + numCols) > LmiMatrixGetNumColumns(T_)(y) ) ) return NULL; \
		if(x->nr != 0) \
		{ \
			LmiUint i, j; \
			for(i = 0; i < numRows; ++i) \
				for(j = 0; j < numCols; ++j) \
					x->data[(xSourceRow + i) * x->nc + (xSourceCol + j)] = y->data[(ySourceRow + i) * y->nc + (ySourceCol + j)]; \
		} \
		return x; \
	}

/**
{function:
	{name: LmiMatrixAssign}
	{parent: LmiMatrix}
	{description: Copy one matrix to another.}
	{prototype: LmiMatrix(T_)* LmiMatrixAssign(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to assign to.}
	}
	{parameter:
		{name: y}
		{description: The matrix to assign from.}
	}
	{return: A pointer to the assigned to matrix or NULL on error.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		A matrix can be assigned with a matrix of different dimensions.
	}
}
*/
#define Define_LmiMatrixAssign(T_) \
	LmiMatrix(T_)* LmiMatrixAssign(T_)(LmiMatrix(T_)* x, const LmiMatrix(T_)* y) { \
		x->allocator = y->allocator; \
		if (x == y) return x; \
		if( (x->nr != y->nr) || (x->nc != y->nc) ) \
		{ \
			LmiAllocatorDeallocate(x->allocator, x->data, (x->nr * x->nc) * sizeof(T_)); \
			x->nr = y->nr; \
			x->nc = y->nc; \
			x->data = NULL; \
			if(y->nr != 0) \
			{ \
				x->data = (T_*)LmiAllocatorAllocate(x->allocator, y->nr * y->nc * sizeof(T_)); \
				if(x->data == NULL) return NULL; \
			} \
		} \
		if(y->nr != 0) \
			LmiMemCpy(x->data, y->data, y->nr * y->nc * sizeof(T_)); \
		return x; \
	}

/**
{function:
	{name: LmiMatrixSwap}
	{parent: LmiMatrix}
	{description: Swap two matrices.}
	{prototype: LmiBool LmiMatrixSwap(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to swap.}
	}
	{parameter:
		{name: y}
		{description: The other matrix to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		The dimensions of both the matrices should be same.
	}
}
*/
#define Define_LmiMatrixSwap(T_) \
	LmiBool LmiMatrixSwap(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y) { \
		LmiMatrix(T_) temp; \
		if( (x->nr != y->nr) || (x->nc != y->nc) ) return LMI_FALSE; \
		LmiMatrixConstructCopy(T_)(&temp, x); \
		LmiMatrixAssign(T_)(x, y); \
		LmiMatrixAssign(T_)(y, &temp); \
		LmiMatrixDestruct(T_)(&temp); \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiMatrixSwapRow}
	{parent: LmiMatrix}
	{description: Swap a row of two matrices.}
	{prototype: LmiBool LmiMatrixSwapRow(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y, LmiUint rowX, LmiUint rowY)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to swap.}
	}
	{parameter:
		{name: y}
		{description: The other matrix to swap.}
	}
	{parameter:
		{name: rowX}
		{description: The row of matrix x to swap.}
	}
	{parameter:
		{name: rowY}
		{description: The row of matrix y to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		Number of columns of both the matrices should be same.
	}
}
*/
#define Define_LmiMatrixSwapRow(T_) \
	LmiBool LmiMatrixSwapRow(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y, LmiUint rowX, LmiUint rowY) { \
		T_ temp; \
		LmiUint i; \
		if( (x->nc != y->nc) || (rowX >= x->nr) || (rowY >= y->nr) ) return LMI_FALSE; \
		for(i = 0; i < x->nc; ++i) \
		{ \
			temp = x->data[rowX * x->nc + i]; \
			x->data[rowX * x->nc + i] = y->data[rowY * y->nc + i]; \
			y->data[rowY * y->nc + i] = temp; \
		} \
		return LMI_TRUE; \
	}


/**
{function:
	{name: LmiMatrixSwapColumn}
	{parent: LmiMatrix}
	{description: Swap a column of two matrices.}
	{prototype: LmiBool LmiMatrixSwapColumn(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y, LmiUint columnX, LmiUint columnY)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to swap.}
	}
	{parameter:
		{name: y}
		{description: The other matrix to swap.}
	}
	{parameter:
		{name: columnX}
		{description: The column of matrix x to swap.}
	}
	{parameter:
		{name: columnY}
		{description: The column of matrix y to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		Number of rows of both the matrices should be same.
	}
}
*/
#define Define_LmiMatrixSwapColumn(T_) \
	LmiBool LmiMatrixSwapColumn(T_)(LmiMatrix(T_)* x, LmiMatrix(T_)* y, LmiUint columnX, LmiUint columnY) { \
		T_ temp; \
		LmiUint i; \
		if( (x->nr != y->nr) || (columnX >= x->nc) || (columnY >= y->nc) ) return LMI_FALSE; \
		for(i = 0; i < x->nr; ++i) \
		{ \
			temp = x->data[i * x->nc + columnX]; \
			x->data[i * x->nc + columnX] = y->data[i * y->nc + columnY]; \
			y->data[i * y->nc + columnY] = temp; \
		} \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiMatrixAdd}
	{parent: LmiMatrix}
	{description: Add two matrices.}
	{prototype: LmiBool LmiMatrixAdd(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: One of the matrix to add.}
	}
	{parameter:
		{name: y}
		{description: Other matrix to add.}
	}
	{parameter:
		{name: result}
		{description: Default constructed matrix to which the result of matrix addition is stored.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		The dimensions of both the matrices to add should be the same.
	}
}
*/
#define Define_LmiMatrixAdd(T_) \
	LmiBool LmiMatrixAdd(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result) { \
		LmiUint i, j; \
		if(x->nr != y->nr || x->nc != y->nc) return LMI_FALSE;	\
		LmiMatrixResize(T_)(result, x->nr, x->nc); \
		for(i = 0; i < x->nr; ++i) \
		{ \
			for(j = 0; j < x->nc; ++j) \
			{ \
				result->data[i * x->nc + j] = x->data[i * x->nc + j] + y->data[i * x->nc + j]; \
			} \
		} \
		return LMI_TRUE; \
	}


/**
{function:
	{name: LmiMatrixSubtract}
	{parent: LmiMatrix}
	{description: Subtract two matrices.}
	{prototype: LmiBool LmiMatrixSubtract(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: Matrix to subtract from.}
	}
	{parameter:
		{name: y}
		{description: Matrix to subtract.}
	}
	{parameter:
		{name: result}
		{description: Default constructed matrix to which the result of matrix subtraction is stored.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		The dimensions of both the matrices to subtract should be the same.
	}
}
*/
#define Define_LmiMatrixSubtract(T_) \
	LmiBool LmiMatrixSubtract(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result) { \
		LmiUint i, j; \
		if(x->nr != y->nr || x->nc != y->nc) return LMI_FALSE;	\
		LmiMatrixResize(T_)(result, x->nr, x->nc); \
		for(i = 0; i < x->nr; ++i) \
		{ \
			for(j = 0; j < x->nc; ++j) \
			{ \
				result->data[i * x->nc + j] = x->data[i * x->nc + j] - y->data[i * x->nc + j]; \
			} \
		} \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiMatrixMultiply}
	{parent: LmiMatrix}
	{description: Multiply two matrices.}
	{prototype: LmiBool LmiMatrixMultiply(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: LHS matrix to multiply.}
	}
	{parameter:
		{name: y}
		{description: RHS matrix to multiply.}
	}
	{parameter:
		{name: result}
		{description: Default constructed matrix to which the result of matrix multiplication is stored.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		The number of columns of x should be same as the number of rows of y.
	}
	{note: 
		The dimension of the result matrix is number of rows of x by number of columns of y.
	}
}
*/
#define Define_LmiMatrixMultiply(T_) \
	LmiBool LmiMatrixMultiply(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y, LmiMatrix(T_)* result) { \
		LmiUint i, j, k; \
		if(x->nc != y->nr) return LMI_FALSE;	\
		LmiMatrixResize(T_)(result, x->nr, y->nc); \
		for(i = 0; i < x->nr; ++i) \
		{ \
			for(j = 0; j < y->nc; ++j) \
			{ \
				T_ temp = 0; \
				for(k = 0; k < y->nr; ++k) \
				{ \
					temp += x->data[i * x->nc + k] * y->data[k * y->nc + j]; \
				}\
				result->data[i * result->nc + j] = temp; \
			} \
		} \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiMatrixMultiplyScalar}
	{parent: LmiMatrix}
	{description: Multiply a matrix by a scalar.}
	{prototype: LmiBool LmiMatrixMultiplyScalar(T_)(const LmiMatrix(T_)* x, T_* y, LmiMatrix(T_)* result)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: LHS matrix to multiply.}
	}
	{parameter:
		{name: y}
		{description: A scalar to multiply the matrix with.}
	}
	{parameter:
		{name: result}
		{description: Default constructed matrix to which the result of matrix scalar multiplication is stored.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		The number of columns of x should be same as the number of rows of y.
	}
	{note: 
		The dimension of the result matrix is number of rows of x by number of columns of y.
	}
}
*/
#define Define_LmiMatrixMultiplyScalar(T_) \
	LmiBool LmiMatrixMultiplyScalar(T_)(const LmiMatrix(T_)* x, T_ y, LmiMatrix(T_)* result) { \
		LmiUint i, j; \
		LmiMatrixResize(T_)(result, x->nr, x->nc); \
		for(i = 0; i < x->nr; ++i) \
		{ \
			for(j = 0; j < x->nc; ++j) \
			{ \
				result->data[i * x->nc + j] = x->data[i * x->nc + j] * y; \
			} \
		} \
		return LMI_TRUE; \
	}


/**
{function:
	{name: LmiMatrixTranspose}
	{parent: LmiMatrix}
	{description: Transpose a matrix.}
	{prototype: LmiBool LmiMatrixTranspose(T_)(const LmiMatrix(T_)* x, LmiMatrix(T_)* result)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: Matrix which need to be transposed.}
	}
	{parameter:
		{name: result}
		{description: Default constructed matrix to which the transposed matrix is stored.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions.
	}
	{note:
		The rows and columns of the matrix are exchanged in the result matrix.
		The dimension of the result matrix is number of columns of x by number of rows of x.
	}
}
*/
#define Define_LmiMatrixTranspose(T_) \
	LmiBool LmiMatrixTranspose(T_)(const LmiMatrix(T_)* x, LmiMatrix(T_)* result) { \
		LmiUint i, j; \
		LmiMatrixResize(T_)(result, x->nc, x->nr); \
		for(i = 0; i < x->nr; ++i) \
		{ \
			for(j = 0; j < x->nc; ++j) \
			{ \
				result->data[j * result->nc + i] = x->data[i * x->nc + j]; \
			} \
		} \
		return LMI_TRUE; \
	}

/**
{function:
	{name: LmiMatrixInverse}
	{parent: LmiMatrix}
	{description: Inverse a matrix.}
	{prototype: LmiBool LmiMatrixInverse(T_)(const LmiMatrix(T_)* x, LmiMatrix(T_)* result)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: Matrix which need to be inverted.}
	}
	{parameter:
		{name: result}
		{description: Default constructed matrix to which the inverse matrix is stored.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note:
		The input matrix should be a square matrix, with the number of rows equal to 
		the number of columns.
	}
	{note:
		The dimensions of the result matrix is same as that of x.
	}
}
*/
#define Define_LmiMatrixInverse(T_) \
	LmiBool LmiMatrixInverse(T_)(const LmiMatrix(T_)* x, LmiMatrix(T_)* result) { \
		LmiUint rows, cols, i, j, k; \
		LmiMatrix(T_) y; \
		LmiMatrixConstructCopy(T_)(&y, x); \
		if(y.nc == 0 || y.nr != y.nc) return LMI_FALSE; \
		LmiMatrixResize(T_)(result, x->nr, x->nc); \
		/* Gauss-Jordan elimination method is used to find the inverse of a matrix .*/ \
		rows = cols = y.nc; \
		for(i = 0; i < rows; ++i) \
		{ \
			for(j = 0; j < cols; ++j) \
			{ \
				if(i == j) \
					result->data[i * cols + i] = 1; \
				else \
					result->data[i * cols + j] = 0; \
			} \
		} \
		for(k = 0; k < rows; ++k) \
		{ \
			/* Find pivot for column k, which is the largest absolute value. */ \
			LmiUint i_max = k; \
			T_ max = LmiAbs(y.data[k * cols + k]); \
			T_ kkValue; \
			for(i = k+1; i < rows; ++i) \
			{ \
				if(LmiAbs(y.data[i * cols + k]) > max) \
				{ \
				   i_max = i; \
				   max = LmiAbs(y.data[i * cols + k]); \
				} \
			} \
			if(max == 0) \
			{ \
				LmiMatrixDestruct(T_)(&y); \
				return LMI_FALSE; \
			} \
			/* Exchange rows in both the matrices. */ \
			for(i = 0; i < cols; ++i) \
			{ \
				T_ temp1, temp2; \
				temp1 = y.data[k * cols + i]; \
				y.data[k * cols + i] = y.data[i_max * cols + i]; \
				y.data[i_max * cols + i] = temp1; \
				temp2 = result->data[k * cols + i];\
				result->data[k * cols + i] = result->data[i_max * cols + i]; \
				result->data[i_max * cols + i] = temp2; \
			} \
			/* Make diagonal elements 1 by dividing the rows by current diagonal element value. */ \
			kkValue = y.data[k * cols + k]; \
			for(i = 0; i < cols; ++i) \
			{ \
				y.data[k * cols + i] = y.data[k * cols + i] / kkValue; \
				result->data[k * cols + i] = result->data[k * cols + i] / kkValue; \
			} \
			/* Make all non diagonal matrix elements zero to get an identity matrix. */ \
			for(i = 0; i < rows; ++i) \
			{ \
				T_ ikValue; \
				if(i == k) \
					continue; \
				ikValue = y.data[i * cols + k]; \
				for(j = 0; j < cols; ++j) \
				{ \
					y.data[i * cols + j] = y.data[i * cols + j] - (y.data[k * cols + j] * ikValue); \
					result->data[i * cols + j] = result->data[i * cols + j] - (result->data[k * cols + j] * ikValue); \
				} \
			} \
		} \
		LmiMatrixDestruct(T_)(&y); \
		return LMI_TRUE; \
	}


/**
{function:
	{name: LmiMatrixGetAllocator}
	{parent: LmiMatrix}
	{description: Gets a pointer to the matrix's allocator.}
	{prototype: LmiAllocator* LmiMatrixGetAllocator(T_)(const LmiMatrix(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix.}
	}
	{return: A pointer to the matrix's allocator.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define DefineInline_LmiMatrixGetAllocator(T_, INLINE_) \
  INLINE_ LmiAllocator* LmiMatrixGetAllocator(T_)(const LmiMatrix(T_)* x) { return x->allocator; }


/**
{function:
	{name: LmiMatrixEqual}
	{parent: LmiMatrix}
	{description: Test two matrices for equality.}
	{prototype: LmiBool LmiMatrixEqual(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to compare.}
	}
	{parameter:
		{name: y}
		{description: The other matrix to compare.}
	}
	{return: LMI_TRUE if the matrices are equal or LMI_FALSE if they are not.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define Define_LmiMatrixEqual(T_) \
	LmiBool LmiMatrixEqual(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y) { \
		if(x->nr != y->nr || x->nc != y->nc) return LMI_FALSE; \
		return (LmiMemCmp(x->data, y->data, x->nr * x->nc * sizeof(T_)) == 0); \
	}

/**
{function:
	{name: LmiMatrixLess}
	{parent: LmiMatrix}
	{description: Test whether one matrix is lexicographically less than another.}
	{prototype: LmiBool LmiMatrixLess(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to compare.}
	}
	{parameter:
		{name: y}
		{description: The other matrix to compare.}
	}
	{return: LMI_TRUE if the first matrix is lexicographically less than the second matrix or LMI_FALSE if it is not.}
	{note: 
		The macro Declare_LmiMatrixLess must be called at global scope before calling
		LmiMatrixLess member functions.
	}
}
*/
#define Define_LmiMatrixLess(T_) \
	LmiBool LmiMatrixLess(T_)(const LmiMatrix(T_)* x, const LmiMatrix(T_)* y) { \
		return LMI_FALSE; \
	}

/**
{function:
	{name: LmiMatrixGetNumRows}
	{parent: LmiMatrix}
	{description: Get the number of rows of the matrix.}
	{prototype: LmiUint LmiMatrixGetNumRows(T_)(const LmiMatrix(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix.}
	}
	{return: The number of rows of the matrix.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define DefineInline_LmiMatrixGetNumRows(T_, INLINE_)                                         \
	INLINE_ LmiUint LmiMatrixGetNumRows(T_)(const LmiMatrix(T_)* x) \
	{ \
		return x->nr; \
	}

/**
{function:
	{name: LmiMatrixGetNumColumns}
	{parent: LmiMatrix}
	{description: Get the number of columns of the matrix.}
	{prototype: LmiUint LmiMatrixGetNumColumns(T_)(const LmiMatrix(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix.}
	}
	{return: The number of columns of the matrix.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define DefineInline_LmiMatrixGetNumColumns(T_, INLINE_)                                         \
	INLINE_ LmiUint LmiMatrixGetNumColumns(T_)(const LmiMatrix(T_)* x) \
	{ \
		return x->nc; \
	}


/**
{function:
	{name: LmiMatrixAt}
	{parent: LmiMatrix}
	{description: Retrieve a pointer to the element of the matrix at index {italic:row,col}.}
	{prototype: T_ LmiMatrixAt(T_)(const LmiMatrix(T_)* x, LmiUint row, LmiUint col)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix.}
	}
	{parameter:
		{name: row}
		{description: The row index of the element to retrieve.}
	}
	{parameter:
		{name: col}
		{description: The column index of the element to retrieve.}
	}
	{return: The element of the matrix at index {italic:row,col}.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define DefineInline_LmiMatrixAt(T_, INLINE_)                                         \
	INLINE_ T_ LmiMatrixAt(T_)(const LmiMatrix(T_)* x, LmiUint row, LmiUint col) \
	{ \
		LmiAssert(row < x->nr && col < x->nc); \
		return x->data[row * x->nc + col]; \
	}

/**
{function:
	{name: LmiMatrixResize}
	{parent: LmiMatrix}
	{description: Resize a matrix.}
	{prototype: LmiMatrix(T_)* LmiMatrixResize(T_)(LmiMatrix(T_)* x, LmiUint rows, LmiUint cols)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to resize.}
	}
	{parameter:
		{name: rows}
		{description: The new number of rows in the matrix.}
	}
	{parameter:
		{name: cols}
		{description: The new number of columns in the matrix.}
	}
	{return: Pointer to the resized matrix or NULL on failure.}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		Number of rows and number of columns both need to be either zero or non-zero.
	}
}
*/
#define Define_LmiMatrixResize(T_)                                         \
	LmiMatrix(T_)* LmiMatrixResize(T_)(LmiMatrix(T_)* x, LmiUint rows, LmiUint cols) \
	{ \
		if( (rows == 0 && cols != 0) || (rows != 0 && cols == 0) ) return NULL; \
		if(x->nr != rows || x->nc != cols) \
		{ \
			if(x->nr != 0) \
				LmiAllocatorDeallocate(x->allocator, x->data, (x->nr * x->nc) * sizeof(T_)); \
			x->nr = rows; \
			x->nc = cols; \
			if(x->nr == 0) \
			{ \
				x->data = NULL; \
				return x; \
			} \
			x->data = (T_*)LmiAllocatorAllocate(x->allocator, rows * cols * sizeof(T_)); \
			if(x->data == NULL) return NULL; \
			return x; \
		} \
		return x; \
	}
/**
{function:
	{name: LmiMatrixReset}
	{parent: LmiMatrix}
	{description: Reset of content of the matrix.}
	{prototype: void LmiMatrixReset(T_)(LmiMatrix(T_)* x)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix to reset.}
	}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
	{note: 
		All the elements of the matrix will be set to zero.
	}
}
*/
#define DefineInline_LmiMatrixReset(T_, INLINE_)                                         \
	INLINE_ void LmiMatrixReset(T_)(LmiMatrix(T_)* x) \
	{ \
		LmiMemSet(x->data, 0, x->nr * x->nc * sizeof(T_)); \
	}


/**
{function:
	{name: LmiMatrixSetVal}
	{parent: LmiMatrix}
	{description: Set the value of an element of the matrix at index {italic:row,col}.}
	{prototype: void LmiMatrixSetVal(T_)(LmiMatrix(T_)* x, LmiUint row, LmiUint col, T_ val)}
	{template-parameter:
		{name: T_} 
		{description: The type of matrix elements.}
	}
	{parameter:
		{name: x}
		{description: The matrix.}
	}
	{parameter:
		{name: row}
		{description: The row index of the element to set.}
	}
	{parameter:
		{name: col}
		{description: The column index of the element to set.}
	}
	{parameter:
		{name: val}
		{description: The value to set.}
	}
	{note: 
		The macro Declare_LmiMatrix must be called at global scope before calling 
		any LmiMatrix member functions. 
	}
}
*/
#define DefineInline_LmiMatrixSetVal(T_, INLINE_)                                         \
	INLINE_ void LmiMatrixSetVal(T_)(LmiMatrix(T_)* x, LmiUint row, LmiUint col, T_ val) \
	{ \
		LmiAssert(row < x->nr && col < x->nc); \
		x->data[row * x->nc + col] = val; \
	}


#if defined(LMI_DEBUG)
#define Define_LmiMatrixDump(T_) \
	void LmiMatrixDump(T_)(const LmiMatrix(T_)* x, const char* name, unsigned int tabStop) { \
	}
#else
#define Define_LmiMatrixDump(T_) \
	void LmiMatrixDump(T_)(const LmiMatrix(T_)* x, const char* name, unsigned int tabStop) {}
#endif

/**
{function validate="no":
	{name: Define_LmiMatrix}
	{parent: LmiMatrix}
	{description: Define a parameterized matrix.}
	{prototype: void Define_LmiMatrix(Type T)}
	{parameter:
		{name: T} 
		{description: The type of matrix elements.}
	}
	{example:
		/\* Instantiate a matrix of integers container class *\/
		Define_LmiMatrix(LmiInt)
		void func() \{
			LmiMatrix(LmiInt) numbers;
			LmiInt i;
			LmiMatrixConstructDefault(LmiInt)(&numbers, LmiMallocAllocatorGetDefault());
			for (i = 0; i < 10; ++i)
				for (j = 0; j < 10; ++j)
					LmiMatrixSetVal(LmiInt)(&numbers, i, j, i+j);
			LmiMatrixDestruct(LmiInt)(&numbers);
		\}
	}
}
*/	
#define Define_LmiMatrix_Unsigned(T_) \
	Define_LmiMatrixDestruct(T_) \
	Define_LmiMatrixConstructDefault(T_) \
	Define_LmiMatrixConstruct(T_) \
	Define_LmiMatrixConstructIdentity(T_) \
	Define_LmiMatrixConstructCopy(T_) \
	Define_LmiMatrixConstructCopyRange(T_) \
	Define_LmiMatrixAssign(T_) \
	Define_LmiMatrixCopyRange(T_) \
	Define_LmiMatrixSwap(T_) \
	Define_LmiMatrixSwapRow(T_) \
	Define_LmiMatrixSwapColumn(T_) \
	Define_LmiMatrixGetAllocator(T_) \
	Define_LmiMatrixEqual(T_) \
	Define_LmiMatrixLess(T_) \
	Define_LmiMatrixGetNumRows(T_) \
	Define_LmiMatrixGetNumColumns(T_) \
	Define_LmiMatrixAt(T_) \
	Define_LmiMatrixReset(T_) \
	Define_LmiMatrixSetVal(T_) \
	Define_LmiMatrixResize(T_) \
	Define_LmiMatrixAdd(T_) \
	Define_LmiMatrixMultiply(T_) \
	Define_LmiMatrixMultiplyScalar(T_) \
	Define_LmiMatrixTranspose(T_) \
	Define_LmiMatrixDump(T_)

#define Define_LmiMatrix_Integer(T_) \
	Define_LmiMatrix_Unsigned(T_) \
	Define_LmiMatrixSubtract(T_)

#define Define_LmiMatrix(T_) \
	Define_LmiMatrix_Integer(T_) \
	Define_LmiMatrixInverse(T_)

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS

#define DefineInlineHeader_LmiMatrixFuncs(T_) \
	DefineInline_LmiMatrixGetAllocator(T_, LMI_INLINE) \
	DefineInline_LmiMatrixGetNumRows(T_, LMI_INLINE) \
	DefineInline_LmiMatrixGetNumColumns(T_, LMI_INLINE) \
	DefineInline_LmiMatrixAt(T_, LMI_INLINE) \
	DefineInline_LmiMatrixReset(T_, LMI_INLINE) \
	DefineInline_LmiMatrixSetVal(T_, LMI_INLINE)
#else

#define DefineInlineHeader_LmiMatrixFuncs(T_) /* defined as empty */

#endif


#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS

#define Define_LmiMatrixGetAllocator(T_) \
	DefineInline_LmiMatrixGetAllocator(T_, LMI_INLINE_SOURCE_FILE)

#define Define_LmiMatrixGetNumRows(T_) \
	DefineInline_LmiMatrixGetNumRows(T_, LMI_INLINE_SOURCE_FILE)

#define Define_LmiMatrixGetNumColumns(T_) \
	DefineInline_LmiMatrixGetNumColumns(T_, LMI_INLINE_SOURCE_FILE)

#define Define_LmiMatrixAt(T_) \
	DefineInline_LmiMatrixAt(T_, LMI_INLINE_SOURCE_FILE)

#define Define_LmiMatrixReset(T_) \
	DefineInline_LmiMatrixReset(T_, LMI_INLINE_SOURCE_FILE)

#define Define_LmiMatrixSetVal(T_) \
  DefineInline_LmiMatrixSetVal(T_, LMI_INLINE_SOURCE_FILE)

#else

#define Define_LmiMatrixGetAllocator(T_) /* defined as empty */
#define Define_LmiMatrixGetNumRows(T_) /* defined as empty */
#define Define_LmiMatrixGetNumColumns(T_) /* defined as empty */
#define Define_LmiMatrixAt(T_) /* defined as empty */
#define Define_LmiMatrixReset(T_) /* defined as empty */
#define Define_LmiMatrixSetVal(T_) /* defined as empty */

#endif

LMI_END_EXTERN_C

#endif


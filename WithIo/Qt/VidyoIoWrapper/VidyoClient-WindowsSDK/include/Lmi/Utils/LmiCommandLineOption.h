/**
{file:
	{name: LmiCommandLineOption.h}
	{description: Parsing of command line options.}
	{copyright:
		(c) 2008-2012 Vidyo, Inc.,
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
#ifndef LMI_COMMANDLINEOPTION_H
#define LMI_COMMANDLINEOPTION_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

typedef enum
{
	LMI_COMMANDLINEPARAMETERTYPE_STRING,
	LMI_COMMANDLINEPARAMETERTYPE_INTEGER,
	LMI_COMMANDLINEPARAMETERTYPE_SIGNED,
	LMI_COMMANDLINEPARAMETERTYPE_ENUM,
} LmiCommandLineParameterType;

/**
{type:
	{name: LmiCommandLineEnum}
	{parent: Utils}
	{include: Lmi/Utils/LmiCommandLineOption.h}
	{description: Holds a name-value pair mapping an enumeration string to its integer value.}
	{member: {name: name} {type: const char *} {description: The enumeration name.}}
	{member: {name: value} {type: LmiInt} {description: The enumeration value.}}
}
*/
typedef struct
{
	const char *name;
	LmiInt value;
} LmiCommandLineEnum;

/**
{type:
	{name: LmiCommandLineParameter}
	{parent: Utils}
	{include: Lmi/Utils/LmiCommandLineOption.h}
	{description: Represents a command line parameter in a program's argument vector.}
}
*/
typedef struct
{
	LmiCommandLineParameterType type;
	union
	{
		struct
		{
			const char **ptr;
		} stringParam;
		struct
		{
			LmiUint *ptr;
			LmiUint min;
			LmiUint max;
		} integerParam;
		struct
		{
			LmiInt *ptr;
			LmiInt min;
			LmiInt max;
		} signedParam;
		struct
		{
			LmiInt *ptr;
			const LmiCommandLineEnum *enums;
			LmiSizeT numEnums;
		} enumParam;
	} u;
} LmiCommandLineParameter;

/**
{function:
	{name: LmiCommandLineParameterConstructString}
	{parent: LmiCommandLineParameter}
	{description: Constructs a command line parameter expecting string input.}
	{prototype: LmiCommandLineParameter *LmiCommandLineParameterConstructString(LmiCommandLineParameter *p, const char **ptr)}
	{parameter: {name: p} {description: The command line parameter object to construct.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if the parameter is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineParameter *LmiCommandLineParameterConstructString(LmiCommandLineParameter *p, const char **ptr);

/**
{function:
	{name: LmiCommandLineParameterConstructInteger}
	{parent: LmiCommandLineParameter}
	{description: Constructs a command line parameter expecting an unsigned integer for input.}
	{prototype: LmiCommandLineParameter *LmiCommandLineParameterConstructInteger(LmiCommandLineParameter *p, LmiUint *ptr)}
	{parameter: {name: p} {description: The command line parameter object to construct.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if a valid parameter is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineParameter *LmiCommandLineParameterConstructInteger(LmiCommandLineParameter *p, LmiUint *ptr);

/**
{function:
	{name: LmiCommandLineParameterConstructIntegerRange}
	{parent: LmiCommandLineParameter}
	{description: Constructs a command line parameter expecting an unsigned integer for input.
		The integer must lie within a specified range.}
	{prototype: LmiCommandLineParameter *LmiCommandLineParameterConstructIntegerRange(LmiCommandLineParameter *p, LmiUint *ptr, LmiUint min, LmiUint max)}
	{parameter: {name: p} {description: The command line parameter object to construct.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if a valid parameter is found.}}
	{parameter: {name: min} {description: The minimum allowed value for the parameter.}}
	{parameter: {name: max} {description: The maximum allowed value for the parameter.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineParameter *LmiCommandLineParameterConstructIntegerRange(LmiCommandLineParameter *p, LmiUint *ptr, LmiUint min, LmiUint max);

/**
{function:
	{name: LmiCommandLineParameterConstructSignedInteger}
	{parent: LmiCommandLineParameter}
	{description: Constructs a command line parameter expecting a signed integer for input.}
	{prototype: LmiCommandLineParameter *LmiCommandLineParameterConstructSignedInteger(LmiCommandLineParameter *p, LmiInt *ptr)}
	{parameter: {name: p} {description: The command line parameter object to construct.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if a valid parameter is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineParameter *LmiCommandLineParameterConstructSignedInteger(LmiCommandLineParameter *p, LmiInt *ptr);

/**
{function:
	{name: LmiCommandLineParameterConstructSignedIntegerRange}
	{parent: LmiCommandLineParameter}
	{description: Constructs a command line parameter expecting a signed integer for input.
		The integer must lie within a specified range.}
	{prototype: LmiCommandLineParameter *LmiCommandLineParameterConstructSignedIntegerRange(LmiCommandLineParameter *p, LmiInt *ptr, LmiInt min, LmiInt max)}
	{parameter: {name: p} {description: The command line parameter object to construct.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if a valid parameter is found.}}
	{parameter: {name: min} {description: The minimum allowed value for the parameter.}}
	{parameter: {name: max} {description: The maximum allowed value for the parameter.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineParameter *LmiCommandLineParameterConstructSignedIntegerRange(LmiCommandLineParameter *p, LmiInt *ptr, LmiInt min, LmiInt max);

/**
{function:
	{name: LmiCommandLineParameterConstructEnum}
	{parent: LmiCommandLineParameter}
	{description: Constructs a command line parameter expecting one of a fixed set of strings. Each string has an associated integer value.
		This object can be used to retrieve a value for an enumerated type.}
	{prototype: LmiCommandLineParameter *LmiCommandLineParameterConstructEnum(LmiCommandLineParameter *p, LmiInt *ptr, const LmiCommandLineEnum *enums, LmiSizeT numEnums)}
	{parameter: {name: p} {description: The command line parameter object to construct.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if a valid parameter is found.}}
	{parameter: {name: enums} {description: An array containing the set of enumerated values for this parameter.}}
	{parameter: {name: numEnums} {description: The number of values in the array.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineParameter *LmiCommandLineParameterConstructEnum(LmiCommandLineParameter *p, LmiInt *ptr, const LmiCommandLineEnum *enums, LmiSizeT numEnums);

/**
{function:
	{name: LmiCommandLineParameterDestruct}
	{parent: LmiCommandLineParameter}
	{description: Destructs a command line parameter object.}
	{prototype: void LmiCommandLineParameterDestruct(LmiCommandLineParameter *p)}
	{parameter: {name: p} {description: The command line parameter object to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiCommandLineParameterDestruct(LmiCommandLineParameter *p);

/**
{type:
	{name: LmiCommandLineOption}
	{parent: Utils}
	{include: Lmi/Utils/LmiCommandLineOption.h}
	{description: Represents an optional command line argument to search for in a program's argument vector.}
}
*/
typedef struct
{
	const char *tag;
	LmiBool *found;
	LmiBool foundValue;
	LmiCommandLineParameter *parameters;
	LmiInt numParameters;
	LmiCommandLineParameter parameter; /* storage for 1 item */
} LmiCommandLineOption;

/**
{function:
	{name: LmiCommandLineOptionConstruct}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstruct(LmiCommandLineOption *opt, const char *tag,
		LmiCommandLineParameter *parameters, LmiInt numParameters)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: parameters} {description: An array of parameters expected for the option. Can be NULL if the
		option has no parameters.}}
	{parameter: {name: numParameters} {description: The number of parameters in the array.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstruct(LmiCommandLineOption *opt, const char *tag,
	LmiCommandLineParameter *parameters, LmiInt numParameters);

/**
{function:
	{name: LmiCommandLineOptionConstructEx}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructEx(LmiCommandLineOption *opt, const char *tag,
		LmiCommandLineParameter *parameters, LmiInt numParameters, LmiBool *found, LmiBool foundValue)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: parameters} {description: An array of parameters expected for the option. Can be NULL if the
		option has no parameters.}}
	{parameter: {name: numParameters} {description: The number of parameters in the array.}}
	{parameter: {name: found} {description: A boolean variable that will be written to if the option is found.}}
	{parameter: {name: foundValue} {description: The value that should be written into *found if the option is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructEx(LmiCommandLineOption *opt, const char *tag,
	LmiCommandLineParameter *parameters, LmiInt numParameters, LmiBool *found, LmiBool foundValue);

/**
{function:
	{name: LmiCommandLineOptionConstructBoolean}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has no parameters.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructBoolean(LmiCommandLineOption *opt, const char *tag, LmiBool *ptr)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: This boolean variable will be set to LMI_TRUE if the option is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LMI_INLINE_DECLARATION LmiCommandLineOption *LmiCommandLineOptionConstructBoolean(LmiCommandLineOption *opt, const char *tag, LmiBool *ptr);

/**
{function:
	{name: LmiCommandLineOptionConstructBooleanEx}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has no parameters.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructBooleanEx(LmiCommandLineOption *opt, const char *tag, LmiBool *ptr, LmiBool value)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: A boolean variable that will be written to if the option is found.}}
	{parameter: {name: value} {description: The value that should be written into *ptr if the option is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructBooleanEx(LmiCommandLineOption *opt, const char *tag, LmiBool *ptr, LmiBool value);

/**
{function:
	{name: LmiCommandLineOptionConstructString}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has one string parameter.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructString(LmiCommandLineOption *opt, const char *tag, const char **ptr)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if the option is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructString(LmiCommandLineOption *opt, const char *tag, const char **ptr);

/**
{function:
	{name: LmiCommandLineOptionConstructInteger}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has one unsigned integer parameter.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructInteger(LmiCommandLineOption *opt, const char *tag, LmiUint *ptr)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if the option is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructInteger(LmiCommandLineOption *opt, const char *tag, LmiUint *ptr);

/**
{function:
	{name: LmiCommandLineOptionConstructIntegerRange}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has one unsigned integer parameter.
		The integer must lie within a specified range.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructIntegerRange(LmiCommandLineOption *opt,
		const char *tag, LmiUint *ptr, LmiUint min, LmiUint max)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if the option is found.}}
	{parameter: {name: min} {description: The minimum allowed value for the parameter.}}
	{parameter: {name: max} {description: The maximum allowed value for the parameter.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructIntegerRange(LmiCommandLineOption *opt, const char *tag, LmiUint *ptr, LmiUint min, LmiUint max);

/**
{function:
	{name: LmiCommandLineOptionConstructSignedInteger}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has one signed integer parameter.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructSignedInteger(LmiCommandLineOption *opt, const char *tag, LmiInt *ptr)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if the option is found.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructSignedInteger(LmiCommandLineOption *opt, const char *tag, LmiInt *ptr);

/**
{function:
	{name: LmiCommandLineOptionConstructSignedIntegerRange}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has one signed integer parameter.
		The integer must lie within a specified range.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructSignedIntegerRange(LmiCommandLineOption *opt,
		const char *tag, LmiInt *ptr, LmiInt min, LmiInt max)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: The value of the parameter will be written into this variable if the option is found.}}
	{parameter: {name: min} {description: The minimum allowed value for the parameter.}}
	{parameter: {name: max} {description: The maximum allowed value for the parameter.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructSignedIntegerRange(LmiCommandLineOption *opt, const char *tag, LmiInt *ptr, LmiInt min, LmiInt max);

/**
{function:
	{name: LmiCommandLineOptionConstructEnum}
	{parent: LmiCommandLineOption}
	{description: Constructs a command line option that has one parameter that is an enumerated type.}
	{prototype: LmiCommandLineOption *LmiCommandLineOptionConstructEnum(LmiCommandLineOption *opt,
		const char *tag, LmiInt *ptr, const LmiCommandLineEnum *enums, LmiSizeT numEnums)}
	{parameter: {name: opt} {description: The command line option to construct.}}
	{parameter: {name: tag} {description: The name of the command line option. This is not case-sensitive.}}
	{parameter: {name: ptr} {description: The numeric value of the parameter will be written into this variable if the option is found.}}
	{parameter: {name: enums} {description: An array containing the set of enumerated values for this option.}}
	{parameter: {name: numEnums} {description: The number of values in the array.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiCommandLineOption *LmiCommandLineOptionConstructEnum(LmiCommandLineOption *opt, const char *tag, LmiInt *ptr, const LmiCommandLineEnum *enums, LmiSizeT numEnums);

/**
{function:
	{name: LmiCommandLineOptionDestruct}
	{parent: LmiCommandLineOption}
	{description: Destructs a command line option.}
	{prototype: void LmiCommandLineOptionDestruct(LmiCommandLineOption *opt)}
	{parameter: {name: opt} {description: The command line option to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiCommandLineOptionDestruct(LmiCommandLineOption *opt);

/**
{function:
	{name: LmiCommandLineOptionGetTag}
	{parent: LmiCommandLineOption}
	{description: Gets the name of a command line option.}
	{prototype: const char *LmiCommandLineOptionGetTag(const LmiCommandLineOption *opt)}
	{parameter: {name: opt} {description: The command line option.}}
	{return: The name of the command line option.}
}
*/
LMI_INLINE_DECLARATION const char *LmiCommandLineOptionGetTag(const LmiCommandLineOption *opt);

/**
{type:
	{name: LmiCommandLineOptionParseStatus}
	{parent: LmiCommandLineOption}
	{description: Indicates the status of a call to LmiCommandLineOptionParse.}
	{value: {name: LMI_COMMANDLINEOPTIONPARSESTATUS_SUCCESS} {description: The parse was successful. The parse terminated
		either because all arguments were parsed, or the next argument found did not match any of the command line options.}}
	{value: {name: LMI_COMMANDLINEOPTIONPARSESTATUS_MISSINGPARAMETER} {description: The parse failed. A command line option
		was expected to be followed by one or more parameters, but there were not enough parameters present.}}
	{value: {name: LMI_COMMANDLINEOPTIONPARSESTATUS_INVALIDPARAMETER} {description: The parse failed. A command line option
		expected a parameter to be of a certain format, but the parameter did not parse successfully. This could be:
		An integer parameter was expected but the parameter was not numeric. An enumerated type was expected but the parameter
		did not match any of the allowed values.}}
	{value: {name: LMI_COMMANDLINEOPTIONPARSESTATUS_OUTOFRANGE} {description: The parse failed. A command line option
		expected an integer parameter within a certain range, but the parameter was not within the range.}}
}
*/
typedef enum
{
	LMI_COMMANDLINEOPTIONPARSESTATUS_SUCCESS,
	LMI_COMMANDLINEOPTIONPARSESTATUS_MISSINGPARAMETER,
	LMI_COMMANDLINEOPTIONPARSESTATUS_INVALIDPARAMETER,
	LMI_COMMANDLINEOPTIONPARSESTATUS_OUTOFRANGE,
} LmiCommandLineOptionParseStatus;

/**
{function:
	{name: LmiCommandLineOptionParse}
	{parent: LmiCommandLineOption}
	{description: Search for optional command line arguments in a program's argument vector.}
	{prototype: LmiCommandLineOptionParseStatus LmiCommandLineOptionParse(const LmiCommandLineOption *options, LmiSizeT numOptions,
		LmiInt argc, char **argv, LmiInt *nextArg, const LmiCommandLineOption **badOption)}
	{parameter: {name: options} {description: An array of command line options to search for.}}
	{parameter: {name: numOptions} {description: The number of command line options in the array.}}
	{parameter: {name: argc} {description: The number of program arguments passed to main().}}
	{parameter: {name: argv} {description: The vector of program arguments passed to main().}}
	{parameter: {name: nextArg} {description: If the function returns LMI_COMMANDLINEOPTIONPARSESTATUS_SUCCESS,
		the index of the first unparsed argument will be written into this variable. The caller can begin the
		processing of required options at this index.}}
	{parameter: {name: badOption} {description: If the function returns a status other than
		LMI_COMMANDLINEOPTIONPARSESTATUS_SUCCESS, the address of the option whose parameters could not
		be parsed will be written into this variable.}}
	{return: An LmiCommandLineOptionParseStatus value indicating the result of the parse.}
}
*/
LmiCommandLineOptionParseStatus LmiCommandLineOptionParse(const LmiCommandLineOption *options, LmiSizeT numOptions,
	LmiInt argc, char **argv, LmiInt *nextArg, const LmiCommandLineOption **badOption);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiCommandLineOptionInline.h>
#endif

#endif

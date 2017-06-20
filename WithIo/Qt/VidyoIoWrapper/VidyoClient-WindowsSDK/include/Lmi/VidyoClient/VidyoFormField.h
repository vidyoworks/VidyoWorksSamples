/**
{file:
	{name: VidyoFormField.h}
	{description: Representation of HTML form input fields and thier attributes. }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
	}
}
*/
#ifndef VIDYO_FORMFIELD_H_ 
#define VIDYO_FORMFIELD_H_ 

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiStringVector.h>
#include <Lmi/Os/LmiTime.h>

LMI_BEGIN_EXTERN_C

/**
{type visibility="public":
	{name: VidyoFormFieldType}
	{parent: CalendarManager}
	{include: Lmi/VidyoClient/VidyoFormField.h}
	{description: 
		This enum contains type values that releate directly to HTML form input fields.
	}
	{value:
		{name: VIDYO_FORMFIELDTYPE_Text}
		{description: HTML form field type for a text input.}
	}
	{value:
		{name: VIDYO_FORMFIELDTYPE_TextArea}
		{description: HTML form field type for a textarea input.}
	}
	{value:
		{name: VIDYO_FORMFIELDTYPE_Password}
		{description: HTML form field type for a password input.}
	}
	{value:
		{name: VIDYO_FORMFIELDTYPE_Checkbox}
		{description: HTML form field type for a checkbox input.}
	}
	{value:
		{name: VIDYO_FORMFIELDTYPE_Radio}
		{description: HTML form field type for a radio input.}
	}
	{value:
		{name: VIDYO_FORMFIELDTYPE_Select}
		{description: HTML form field type for a dropdown select input.}
	}
}
*/
typedef enum
{
	VIDYO_FORMFIELDTYPE_Text,
	VIDYO_FORMFIELDTYPE_TextArea,
	VIDYO_FORMFIELDTYPE_Password,
	VIDYO_FORMFIELDTYPE_Checkbox,
	VIDYO_FORMFIELDTYPE_Radio,
	VIDYO_FORMFIELDTYPE_Select
} VidyoFormFieldType;


/**
{type visibility="public":
	{name: VidyoFormFieldTextWrapMode}
	{parent: CalendarManager}
	{description:
		This enum is used to represent the wrapping modes defined for a textarea HTML form input field.
	}
	{value:
		{name: VIDYO_FORMFIELDTEXTWRAPMODE_Off}
		{description: No wrapping}
	}
	{value:
		{name: VIDYO_FORMFIELDTEXTWRAPMODE_Virtual}
		{description: Shows linebreaks, but sends text as entered}
	}
	{value:
		{name: VIDYO_FORMFIELDTEXTWRAPMODE_Physical}
		{description: Inserts linebreaks as needed and sends text with them.}
	}
}
*/
typedef enum
{
	VIDYO_FORMFIELDTEXTWRAPMODE_Off,
	VIDYO_FORMFIELDTEXTWRAPMODE_Virtual,
	VIDYO_FORMFIELDTEXTWRAPMODE_Physical
} VidyoFormFieldTextWrapMode;

/**
{type visibility="public":
	{name: VidyoFormFieldOption}
	{parent: CalendarManager}
	{description: Option properties for an HTML drop down select input field.}
	{member:
		{name: value}
		{type: LmiString}
		{description: String value representing the option text label }
	}
	{member:
		{name: selected}
		{type: LmiBool}
		{description: Indicates whether the option was selected or not}
	}
}
*/
typedef struct
{
	LmiString	value;
	LmiBool		selected;
} VidyoFormFieldOption;


/**
{function visibility="private":
	{name: VidyoFormFieldOptionConstructDefault}
	{parent: VidyoFormFieldOption}
	{description: Constructs an VidyoFormFieldOption object.}
	{prototype:
		VidyoFormFieldOption *VidyoFormFieldOptionConstructDefault(VidyoFormFieldOption *p, LmiAllocator *alloc)
	}
	{parameter:
	{name: p}
	{description: The VidyoFormFieldOption object to construct.}
	}
	{parameter:
	{name: alloc}
	{description: An allocator to use for miscellaneous items.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoFormFieldOption *VidyoFormFieldOptionConstructDefault(VidyoFormFieldOption *p, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoFormFieldOptionConstructCopy}
	{parent: VidyoFormFieldOption}
	{description: Constructs an VidyoFormFieldOption object as a copy of another.}
	{prototype: VidyoFormFieldOption *VidyoFormFieldOptionConstructCopy(VidyoFormFieldOption *d, const VidyoFormFieldOption *s)}
	{parameter: {name: d} {description: Pointer to the VidyoFormFieldOption object to construct.}}
	{parameter: {name: s} {description: Pointer to the VidyoFormFieldOption object to make a copy of.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoFormFieldOption* VidyoFormFieldOptionConstructCopy(VidyoFormFieldOption* d, const VidyoFormFieldOption* s);

/**
{function visibility="private":
	{name: VidyoFormFieldOptionDestruct}
	{parent: VidyoFormFieldOption}
	{description: Destructs an VidyoFormFieldOption object.}
	{prototype: void VidyoFormFieldOptionDestruct(VidyoFormFieldOption *c)}
	{parameter: {name: c} {description: Pointer to the VidyoFormFieldOption object.}}
}
*/
void VidyoFormFieldOptionDestruct(VidyoFormFieldOption* x);

/**
{function visibility="private":
	{name: VidyoFormFieldOptionAssign}
	{parent: VidyoFormFieldOption}
	{description: Assigns one VidyoFormFieldOption object the value of another.}
	{prototype: VidyoFormFieldOption *VidyoFormFieldOptionAssign(VidyoFormFieldOption *d, const VidyoFormFieldOption *s)}
	{parameter: {name: d} {description: Pointer to the VidyoFormFieldOption object.}}
	{parameter: {name: s} {description: Pointer to the VidyoFormFieldOption object to assign.}}
	{return: Pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoFormFieldOption* VidyoFormFieldOptionAssign(VidyoFormFieldOption* x, const VidyoFormFieldOption* y);

Declare_LmiVector(VidyoFormFieldOption)


/**
{type visibility="public":
	{name: VidyoFormField}
	{parent: CalendarManager}	
	{description: Attributes related to an HTML form input field.}
	{member:
		{name: type}
		{type: VidyoFormFieldType}
		{description: Type that corresponds to the HTML form input fields that can be used to display and collect user data }
	}
	{member:
		{name: name}
		{type: LmiString }
		{description: Label used to uniquely identify the input field for this element }
	}
	{member:
		{name: value}
		{type: LmiString }
		{description: Default value to display in the input field if this struct is returned to the application, or a collected user input if this structure is passed back as a method argument}
	}
	{member:
		{name: size}
		{type: LmiUint }
		{description: Number of characters for the value }
	}
	{member:
		{name: maxlength}
		{type: LmiUint }
		{description: Maximum number of characters allowed for the input field }
	}
	{member:
		{name: rows}
		{type: LmiUint }
		{description: For a textarea input field, the number of rows the field should show }
	}
	{member:
		{name: cols}
		{type: LmiUint }
		{description: For a textarea input field, the number of columns the field should show }
	}
	{member:
		{name: multiple}
		{type: LmiBool }
		{description: For a select drop-down input field, whether multiple selections are allowed }
	}
	{member:
		{name: wrap}
		{type: VidyoFormFieldTextWrapMode }
		{description: For a textarea input field, how linebreaks should be handled}
	}
	{member:
		{name: options}
		{type: LmiVector(VidyoFormFieldOption) }
		{description: For a select drop-down input field, a list of the options and their selection status }
	}
}
*/
typedef struct
{	
	VidyoFormFieldType type;
	LmiString	name;
	LmiString	value;
	LmiUint		size;
	LmiUint		maxlength;
	LmiUint		rows;
	LmiUint		cols;
	LmiBool		multiple;
	VidyoFormFieldTextWrapMode wrap;
	LmiVector(VidyoFormFieldOption) options;

} VidyoFormField;

/**
{function visibility="private":
	{name: VidyoFormFieldConstructDefault}
	{parent: VidyoFormField}
	{description: Constructs an VidyoFormField object.}
	{prototype: 
		VidyoFormField *VidyoFormFieldConstructDefault(VidyoFormField *p, LmiAllocator *alloc)
	}
	{parameter: 
		{name: p} 
		{description: The VidyoFormField object to construct.}
	}
	{parameter: 
		{name: alloc} 
		{description: An allocator to use for miscellaneous items.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoFormField *VidyoFormFieldConstructDefault(VidyoFormField *p, LmiAllocator *alloc);

/**
{function visibility="private":
	{name: VidyoFormFieldConstructCopy}
	{parent: VidyoFormField}
	{description: Constructs an VidyoFormField object as a copy of an existing object.}
	{prototype: 
		VidyoFormField *VidyoFormFieldConstructCopy(VidyoFormField *d, const VidyoFormField *s)
	}
	{parameter: 
		{name: d} 
		{description: The VidyoFormField object to construct.}
	}
	{parameter: 
		{name: s} 
		{description: The existing VidyoFormField object to copy.}
	}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
VidyoFormField *VidyoFormFieldConstructCopy(VidyoFormField *d, const VidyoFormField *s);

/**
{function visibility="private":
	{name: VidyoFormFieldDestruct}
	{parent: VidyoFormField}
	{description: Destructs an VidyoFormField object.}
	{prototype: 
		void VidyoFormFieldDestruct(VidyoFormField *p)
	}
	{parameter: 
		{name: p} 
		{description: The VidyoFormField object to destruct.}
	}
}
*/
void VidyoFormFieldDestruct(VidyoFormField *p);

/**
{function visibility="private":
	{name: VidyoFormFieldAssign}
	{parent: VidyoFormField}
	{description: Assign the contents of one VidyoFormField to another.}
	{prototype: 
		VidyoFormField *VidyoFormFieldAssign(VidyoFormField *d, const VidyoFormField *s)
	}
	{parameter: 
		{name: d} 
		{description: The object to assign to.}
	}
	{parameter: 
		{name: s} 
		{description: The object to copy.}
	}
	{return: A pointer to the assigned object on success, or NULL on failure.}
}
*/
VidyoFormField *VidyoFormFieldAssign(VidyoFormField *d, const VidyoFormField *s);

/**
{function visibility="private":
	{name: VidyoFormFieldEqual}
	{parent: VidyoFormField}
	{description: Check the equality of VidyoFormField object.}
	{prototype: 
		LmiBool VidyoFormFieldEqual(const VidyoFormField *a, const VidyoFormField *b)
	}
	{parameter: 
		{name: a} 
		{description: The VidyoFormField object to compare.}
	}
	{parameter: 
		{name: b} 
		{description: The VidyoFormField object to compare.}
	}
	{return: LMI_TRUE if equal LMI_FALSE otherwise.}
}
*/
LmiBool VidyoFormFieldEqual(const VidyoFormField *a, const VidyoFormField *b);


Declare_LmiVector(VidyoFormField)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include "VidyoFormFieldInline.h"
#endif

#endif /* VIDYO_FORMFIELD_H_ */
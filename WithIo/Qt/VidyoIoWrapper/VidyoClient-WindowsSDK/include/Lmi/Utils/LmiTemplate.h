/**
   {file: 
   {name: LmiTemplate.h}
   {description: Support macros for name mangling for LMI's
    C-preprocessor-based objects and templates.}
   {copyright:
   	(c) 2005-2015 Vidyo, Inc.,
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

#ifndef LMI_TEMPLATE_H_
#define LMI_TEMPLATE_H_

/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiTemplate1Internal_}
     {parent: Utils}
     {description: Internal macro used by LmiTemplate1, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiTemplate1Internal_(Type Tmpl_, Type T_)}
   }
*/
#define LmiTemplate1Internal_(Tmpl_, T_) Tmpl_ ## _ ## T_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiTemplate1}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a one-parameter LMI
      template over the given template class.}
     {prototype: Type LmiTemplate1(Type Tmpl_, Type T_)}
     {parameter: {name: Tmpl_} {description: The name of the template.}}
     {parameter: {name: T_} {description: The name of the class.}}
     {return: Expands to a symbol representing a one-parameter LMI
      template over the given template class.}
   }
*/
#define LmiTemplate1(Tmpl_, T_) LmiTemplate1Internal_(Tmpl_,T_)

/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiTemplate2Internal_}
     {parent: Utils}
     {description: Internal macro used by LmiTemplate2, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiTemplate2Internal_(Type Tmpl_, Type T1_, Type T2_)}
   }
*/
#define LmiTemplate2Internal_(Tmpl_, T1_, T2_) Tmpl_ ## _ ## T1_ ## __ ## T2_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiTemplate2}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a two-parameter LMI
      template over the given template classes.}
     {prototype: Type LmiTemplate2(Type Tmpl_, Type T1_, Type T2_)}
     {parameter: {name: Tmpl_} {description: The name of the template.}}
     {parameter: {name: T1_} {description: The name of the first class.}}
     {parameter: {name: T2_} {description: The name of the second class.}}
     {return: Expands to a symbol representing a two-parameter LMI
      template over the given template classes.}
   }
*/
#define LmiTemplate2(Tmpl_, T1_, T2_) LmiTemplate2Internal_(Tmpl_,T1_,T2_)

/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiTemplate3_}
     {parent: Utils}
     {description: Internal macro used by LmiTemplate3, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiTemplate1_(Type Tmpl_, Type T1_, Type T2_, Type T3_)}
   }
*/
#define LmiTemplate3_(Tmpl_, T1_, T2_, T3_) \
  Tmpl_ ## _ ## T1_ ## __ ## T2_ ## __ ## T3_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiTemplate3}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a three-parameter LMI
      template over the given template classes.}
     {prototype: Type LmiTemplate3(Type Tmpl_, Type T1_, Type T2_, Type T3_)}
     {parameter: {name: Tmpl_} {description: The name of the template.}}
     {parameter: {name: T1_} {description: The name of the first class.}}
     {parameter: {name: T2_} {description: The name of the second class.}}
     {parameter: {name: T3_} {description: The name of the third class.}}
     {return: Expands to a symbol representing a three-parameter LMI
      template over the given template classes.}
   }
*/
#define LmiTemplate3(Tmpl_, T1_, T2_, T3_) LmiTemplate3_(Tmpl_,T1_,T2_,T3_)

#define LmiTemplate4_(Tmpl_, T1_, T2_, T3_, T4_) \
  Tmpl_ ## _ ## T1_ ## __ ## T2_ ## T3_ ## T4_
#define LmiTemplate4(Tmpl_, T1_, T2_, T3_, T4_) LmiTemplate4_(Tmpl_,T1_,T2_,T3_,T4_)

/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiClassFunc_}
     {parent: Utils}
     {description: Internal macro used by LmiClassFunc, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiClassFunc_(Type T_, Type Func_)}
   }
*/
#define LmiClassFunc_(T_, Func_) T_ ## Func_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiClassFunc}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a member function of a
      given class, in the LMI object mechanism.}
     {prototype: Type LmiClassFunc(Type T_, Type Func_)}
     {parameter: {name: T_} {description: The name of the class.}}
     {parameter: {name: Func_} {description: The name of the function.}}
     {return: Expands to a symbol representing a member function of a
      given class, in the LMI object mechanism.}
   }
*/
#define LmiClassFunc(T_, Func_) LmiClassFunc_(T_, Func_)

/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiClassTemplateFunc1_}
     {parent: Utils}
     {description: Internal macro used by LmiClassTemplateFunc1, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiClassTemplateFunc1_(Type T_, Type Func_, Type Arg1_)}
   }
*/
#define LmiClassTemplateFunc1_(T_, Func_, Arg1_) T_ ## Func_ ## _ ## Arg1_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiClassTemplateFunc1}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a member template function (with one template argument) of a
      given class, in the LMI object mechanism.}
     {prototype: Type LmiClassTemplateFunc1(Type T_, Type Func_, Type Arg1_)}
     {parameter: {name: T_} {description: The name of the class.}}
     {parameter: {name: Func_} {description: The name of the memeber template function.}}
     {parameter: {name: Arg1_} {description: The first template argument of the member template function.}}
     {return: Expands to a symbol representing a member function of a
      given class, in the LMI object mechanism.}
   }
*/
#define LmiClassTemplateFunc1(T_, Func_, Arg1_) LmiClassTemplateFunc1_(T_, Func_, Arg1_)

/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiClassTemplateFunc2_}
     {parent: Utils}
     {description: Internal macro used by LmiClassTemplateFunc2, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiClassTemplateFunc2_(Type T_, Type Func_, Type Arg1_, Type Arg2_)}
   }
*/
#define LmiClassTemplateFunc2_(T_, Func_, Arg1_) T_ ## Func_ ## _ ## Arg1_ ## __ ## Arg2_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiClassTemplateFunc2}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a member template function (with two template argument) of a
      given class, in the LMI object mechanism.}
     {prototype: Type LmiClassTemplateFunc2(Type T_, Type Func_, Type Arg1_, Type Arg2_)}
     {parameter: {name: T_} {description: The name of the class.}}
     {parameter: {name: Func_} {description: The name of the memeber template function.}}
     {parameter: {name: Arg1_} {description: The first template argument of the member template function.}}
     {parameter: {name: Arg2_} {description: The second template argument of the member template function.}}
     {return: Expands to a symbol representing a member template function of a given class, in the LMI object mechanism.}
   }
*/
#define LmiClassTemplateFunc2(T_, Func_, Arg1_, Arg2_) LmiClassTemplateFunc2_(T_, Func_, Arg1_, Arg2_)


/* *** NOT A DOCBLOCK ***
   {function visibility="internal":
     {name: LmiClassType_}
     {parent: Utils}
     {description: Internal macro used by LmiClassType, to get the expansion
      order of C preprocessor arguments correct.}
     {prototype: Type LmiClassType_(Type T_, Type Type_)}
   }
*/
#define LmiClassType_(T_, Type_) T_ ## Type_

/* *** NOT A DOCBLOCK ***
   {function visibility="private":
     {name: LmiClassType}
     {parent: Utils}
	 {include: Lmi/Utils/LmiTemplate.h}
     {description: Expands to a symbol representing a member type of a
      given class, in the LMI object mechanism.}
     {prototype: Type LmiClassType(Type T_, Type Type_)}
     {parameter: {name: T_} {description: The name of the class.}}
     {parameter: {name: Type_} {description: The name of the member type.}}
     {return: Expands to a symbol representing a member type of a
      given class, in the LMI object mechanism.}
   }
*/
#define LmiClassType(T_, Type_) LmiClassType_(T_, Type_)

#endif /* LMI_TEMPLATE_H_ */

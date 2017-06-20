
/**
{file: 
	{name: VidyoConstruct.h}
	{description: Helper template class to wrap LMI "C classes" into C++. }
	{copyright:
		(c) 2008 Vidyo, Inc.,
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

#if !defined(VIDYO_CONSTRUCT_H_)
#define VIDYO_CONSTRUCT_H_

#if defined(__cplusplus)

#include <exception>

/**
{type:
	{name: Construct}
	{parent: Utils}
	{include: Lmi/Utils/VidyoConstruct.h}
	{description: Construct an LMI "C class".  A constructed object of this template class will 
	  call the LMI "C classes" destruct function when the object goes out of scope.  The template 
	  class also throws the exception Vidyo::Construct::Failed when the LMI C class's constructor fails.}
	{template-prototype: Construct<class T_, bool exceptions_ = true>}
	{template-parameter:
		{name: T_}
		{description: The LMI C type stored in Construct object.}
	}
	{template-parameter:
		{name: exception_}
		{description: A boolean specifying whether or not C++ exceptions should be throw when the LMI object fails.}
	}
	{example: 
		void func() \{
			try \{
				Construct<LmiUri> c(LmiUriConstructCStr(&uri, "sip://", LmiMallocAllocatorGetDefault()), LmiUriDestruct);
				if (IsMoonFull()) {
					// ...
					return; // LmiUriDestruct automatically called
				}
				if (IsTuesday()) {
					// ...
					return; // LmiUriDestruct automatically called
				}
				// ...
			\} // LmiUriDestruct automatically called
			catch(Vidyo::FailedToConstruct& e) \{
				printf("Exception: %s\n", e.what());
			\}
		\}
	}
}
*/
namespace Vidyo {
	struct FailedToConstruct : std::exception {
		FailedToConstruct() throw() {}
		virtual const char* what() const throw() { return "A 'C' constructor failed"; }
		virtual const char* What() const throw() { return what(); }
	};
	
	template<class T_, bool exceptions_ = true>
	class Construct {
		T_* obj_;
		void (*destructor_)(T_*);
	public:
		Construct(T_* obj, void (*destructor)(T_*)) throw(FailedToConstruct) : obj_(obj), destructor_(destructor) {
			if ((obj_ == NULL) && exceptions_) {
				FailedToConstruct e;
				throw e;
			}
		}
		~Construct() throw() {
			if (obj_ != NULL)
				destructor_(obj_);
		}
		bool Failed() throw() { return obj_ == NULL; }
	};
};

#endif /* __cplusplus */

#endif /* VIDYO_CONSTRUCT_H_ */

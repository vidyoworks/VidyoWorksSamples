#pragma once
#include "IVidyoClient.h"
#include <boost/smart_ptr.hpp>


class ClientVidyoWorksImpl;
typedef boost::shared_ptr<ClientVidyoWorksImpl> ClientVidyoWorksImplPtr;

class ClientVidyoWorks :
	public IVidyoClient
{
public:
	ClientVidyoWorks();
	virtual ~ClientVidyoWorks();

	virtual VidyoClientSwitchDefs::ErrorType Initialize(const char* strParameter, VidyoClientCallerPtr& caller);
	virtual VidyoClientSwitchDefs::ErrorType Start(const char* strParameter);
	virtual bool Stop();
	virtual bool Uninitialize();
	virtual VidyoClientSwitchDefs::ErrorType Join(const char* strParameter);
	virtual bool Leave();
	virtual void tmp(const char * test);
private:
	ClientVidyoWorksImplPtr m_impl;
};
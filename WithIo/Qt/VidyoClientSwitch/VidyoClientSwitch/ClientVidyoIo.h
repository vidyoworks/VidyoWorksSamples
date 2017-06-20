#pragma once
#include "IVidyoClient.h"
#include <boost/smart_ptr.hpp>



class ClientVidyoIoImpl;
typedef boost::shared_ptr<ClientVidyoIoImpl> ClientVidyoIoImplPtr;

class ClientVidyoIo :
	public IVidyoClient
{
public:
	ClientVidyoIo();
	virtual ~ClientVidyoIo();

	virtual VidyoClientSwitchDefs::ErrorType Initialize(const char* strParameter, VidyoClientCallerPtr& caller);
	virtual VidyoClientSwitchDefs::ErrorType Start(const char* strParameter);
	virtual bool Stop();
	virtual bool Uninitialize();
	virtual VidyoClientSwitchDefs::ErrorType Join(const char* strParameter);
	virtual bool Leave();
	virtual void tmp(const char * test);
private:
	ClientVidyoIoImplPtr m_impl;
};
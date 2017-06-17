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

	virtual VidyoClientSwitchDefs::ErrorType Initialize(map<string, string> &parameter, VidyoClientCallerPtr& caller);
	virtual VidyoClientSwitchDefs::ErrorType Start(map<string, string> &parameter);
	virtual bool Stop();
	virtual bool Uninitialize();
	virtual VidyoClientSwitchDefs::ErrorType Join(map<string, string> &parameter);
	virtual bool Leave();
private:
	ClientVidyoIoImplPtr m_impl;
};


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

	virtual VidyoClientSwitchDefs::ErrorType Initialize(map<string, string> &parameter, VidyoClientCallerPtr& caller);
	virtual VidyoClientSwitchDefs::ErrorType Start(map<string, string> &parameter);
	virtual bool Stop();
	virtual bool Uninitialize();
	virtual VidyoClientSwitchDefs::ErrorType Join(map<string, string> &parameter);
	virtual bool Leave();
private:
	ClientVidyoWorksImplPtr m_impl;
};
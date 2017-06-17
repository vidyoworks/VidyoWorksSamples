#pragma once

#include <string>
#include <map>
using namespace std;

namespace VidyoClientSwitchDefs
{
	enum ClientType{
		ClientTypeVw = 0,
		ClientTypeIo
	};

	enum ErrorType{
		ErrorSuccess = 0,
		ErrorDllNotFound = 1000,
		ErrorFuncNotFound = 1001,
		ErrorVcInitialize = 1002,
		ErrorVcMissingPara = 1003,
		ErrorVcSendEvent = 1004
	};

	enum ErrorCall{
		ErrorCallSuccess = 0,
		ErrorCallLicense = 1000
	};
}


class IVidyoClientCaller
{
public:
	virtual void CallComplete() = 0;
	virtual void CallFailure(VidyoClientSwitchDefs::ErrorCall errorCall) = 0;
	virtual void CallEnd() = 0;
	virtual ~IVidyoClientCaller(void){}
};
typedef  IVidyoClientCaller* VidyoClientCallerPtr;

class IVidyoClient
{
public:
	virtual VidyoClientSwitchDefs::ErrorType Initialize(map<string, string> &parameter, VidyoClientCallerPtr& caller) = 0;
	virtual VidyoClientSwitchDefs::ErrorType Start(map<string, string> &parameter) = 0;
	virtual bool Stop() = 0;
	virtual bool Uninitialize() = 0;
	virtual VidyoClientSwitchDefs::ErrorType Join(map<string, string> &parameter) = 0;
	virtual bool Leave() = 0;

	virtual ~IVidyoClient(){}
};

typedef IVidyoClient* VidyoClientPtr;


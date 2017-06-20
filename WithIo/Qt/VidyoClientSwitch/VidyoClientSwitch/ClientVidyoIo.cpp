#include "stdafx.h"
#include "ClientVidyoIo.h"
#include "VidyoIoWrapper.h"
#include "VidyoClientSwitchUtils.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>




typedef bool(__cdecl  *VIoWrapperInitializePtr)(VidyoWindowId parentWindow, VidyoRect *videoRect);

typedef bool(__cdecl  *VIoWrapperUninitializePtr)();

typedef bool(__cdecl  *VIoWrapperConnectPtr)(const char *host, const char * token, const char *displayName, const char* resourceId,
	VidyoIoWrapperOnSuccess onSuccess, VidyoIoWrapperOnFailure onFailure, VidyoIoWrapperOnDisconnected onDisconnected);


static ClientVidyoIoImpl* gImpl = NULL;


class ClientVidyoIoImpl
{
public:
	ClientVidyoIoImpl()
	{
		m_hDLL = NULL;
		VIoWrapperInitialize = NULL;
		VIoWrapperUninitialize = NULL;
		VIoWrapperConnect = NULL;
		m_caller = NULL;
		gImpl = const_cast<ClientVidyoIoImpl*>(this);
	}

#ifdef Q_WS_WIN
	void __stdcall SampleCbOnSuccess
#else
	void SampleCbOnSuccess
#endif
		()
	{

	}

#ifdef Q_WS_WIN
	void __stdcall SampleCbOnFailure
#else
	void SampleCbOnFailure
#endif
		(VidyoIoWrapperFailReason reason)
	{

	}


#ifdef Q_WS_WIN
	void __stdcall SampleCbOnDisconnect
#else
	void SampleCbOnDisconnect
#endif
		(VidyoIoWrapperDisconnectReason reason)
	{

	}




	HMODULE m_hDLL;
	VIoWrapperInitializePtr VIoWrapperInitialize;
	VIoWrapperUninitializePtr VIoWrapperUninitialize;
	VIoWrapperConnectPtr VIoWrapperConnect;
	VidyoClientCallerPtr m_caller;
};

ClientVidyoIo::ClientVidyoIo()
{
	m_impl = ClientVidyoIoImplPtr(new ClientVidyoIoImpl());
}


ClientVidyoIo::~ClientVidyoIo()
{
}


VidyoClientSwitchDefs::ErrorType ClientVidyoIo::Initialize(const char* strParameter, VidyoClientCallerPtr& caller)
{
	{
		wchar_t szFullPath[MAX_PATH + 1] = {};

		GetModuleFileName(NULL, szFullPath, MAX_PATH + 1);
		std::wstring wsPath(szFullPath);
		vector<wstring> pathComps;
		boost::split(pathComps, wsPath, boost::is_any_of("\\"));
		pathComps[pathComps.size() - 1] = L"VidyoIoWrapper.dll";
		wsPath = boost::algorithm::join(pathComps, "\\");
		m_impl->m_hDLL = LoadLibrary(wsPath.c_str());
	}

	if (m_impl->m_hDLL == NULL)
		return VidyoClientSwitchDefs::ErrorDllNotFound;

	{
		m_impl->VIoWrapperInitialize = (VIoWrapperInitializePtr)GetProcAddress(m_impl->m_hDLL, "VIoWrapperInitialize");
		if (m_impl->VIoWrapperInitialize == NULL)
			return VidyoClientSwitchDefs::ErrorFuncNotFound;

	}

	{
		m_impl->VIoWrapperUninitialize = (VIoWrapperUninitializePtr)GetProcAddress(m_impl->m_hDLL, "VIoWrapperUninitialize");
		if (m_impl->VIoWrapperUninitialize == NULL)
			return VidyoClientSwitchDefs::ErrorFuncNotFound;

	}

	{
		m_impl->VIoWrapperConnect = (VIoWrapperConnectPtr)GetProcAddress(m_impl->m_hDLL, "VIoWrapperConnect");
		if (m_impl->VIoWrapperConnect == NULL)
			return VidyoClientSwitchDefs::ErrorFuncNotFound;
	}

	
	return VidyoClientSwitchDefs::ErrorSuccess;
}


VidyoClientSwitchDefs::ErrorType ClientVidyoIo::Start(const char* strParameter)
{

	map<string, string> parameters;
	ConvertFromStringToMap(strParameter, parameters);

	m_impl->m_caller = NULL;

	VidyoWindowId winId = (VidyoWindowId)VidyoClientSwitchGetPara(parameters, "WindowId", 0);
	VidyoRect vidyoRect;
	vidyoRect.xPos = 0;
	vidyoRect.yPos = 0;
	vidyoRect.width = VidyoClientSwitchGetPara(parameters, "WindowWidth", 100);
	vidyoRect.height = VidyoClientSwitchGetPara(parameters, "WindowHeight", 100);

	if (!m_impl->VIoWrapperInitialize(winId, &vidyoRect))
		return VidyoClientSwitchDefs::ErrorVcInitialize;
	return VidyoClientSwitchDefs::ErrorSuccess;
}

bool ClientVidyoIo::Stop()
{
	m_impl->VIoWrapperUninitialize();
	return true;
}

bool ClientVidyoIo::Uninitialize()
{
	FreeLibrary(m_impl->m_hDLL);
	return true;
}


VidyoClientSwitchDefs::ErrorType ClientVidyoIo::Join(const char* strParameter)
{
	map<string, string> parameters;
	ConvertFromStringToMap(strParameter, parameters);
	string strHost = VidyoClientSwitchGetPara(parameters, "Host", strHost, "");
	string strToken = VidyoClientSwitchGetPara(parameters, "Token", strToken, "");
	string strDisplayName = VidyoClientSwitchGetPara(parameters, "DisplayName", strDisplayName, "");
	string strResourceId = VidyoClientSwitchGetPara(parameters, "ResourceId", strResourceId, "");
	VidyoIoWrapperOnSuccess onSuccess = &m_impl->SampleCbOnSuccess;

	if (!m_impl->VIoWrapperConnect(strHost.c_str(), strToken.c_str(), strDisplayName.c_str(), strResourceId.c_str(),
		(VidyoIoWrapperOnSuccess)m_impl->SampleCbOnSuccess, m_impl->SampleCbOnFailure, m_impl->SampleCbOnDisconnect))
		return VidyoClientSwitchDefs::ErrorVcInitialize;
	return VidyoClientSwitchDefs::ErrorSuccess;
}

bool ClientVidyoIo::Leave()
{
	
	return true;
}

void ClientVidyoIo::tmp(const char * test)
{

}
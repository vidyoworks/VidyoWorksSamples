#include "stdafx.h"
#include "ClientVidyoWorks.h"
#include "VidyoClient.h"
#include "VidyoClientSwitchUtils.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>




typedef VidyoBool(__cdecl  *VidyoClientInitializePtr)(VidyoClientOutEventCallback eventCb,
	VidyoVoidPtr data,
	VidyoClientLogParams *logParams);

typedef VidyoBool(__cdecl  *VidyoClientStartPtr)(VidyoClientOutEventCallback eventCb,
	VidyoVoidPtr data,
	VidyoClientLogParams *logParams,
	VidyoWindowId parentWindow,
	VidyoRect *videoRect,
	VidyoClientAppStringsInfo *appStringsInfo,
	VidyoClientProfileParams *profileParams,
	VidyoBool reserved2);

typedef VidyoBool(__cdecl  *VidyoClientStopPtr)();

typedef void(__cdecl  *VidyoClientUninitializePtr)();

typedef VidyoBool(__cdecl  *VidyoClientSendEventPtr)(VidyoClientInEvent event,
	VidyoVoidPtr param,
	VidyoSizeT paramSize);

typedef VidyoUint(__cdecl  *VidyoClientSendRequestPtr)(VidyoClientRequest request,
	VidyoVoidPtr param,
	VidyoSizeT paramSize);


static ClientVidyoWorksImpl* gImpl = NULL;


class ClientVidyoWorksImpl
{
public:
	ClientVidyoWorksImpl()
	{
		m_hDLL = NULL;
		VidyoClientInitialize = NULL;
		VidyoClientStart = NULL;
		VidyoClientStop = NULL;
		VidyoClientUninitialize = NULL;
		VidyoClientSendEvent = NULL;
		VidyoClientSendRequest = NULL;
		m_caller = NULL;
		gImpl = const_cast<ClientVidyoWorksImpl*>(this);
	}

	void VidyoClientOutCallback(VidyoClientOutEvent event,
		VidyoVoidPtr param, VidyoUint paramSize,
		VidyoVoidPtr data)
	{
		if ((event <= VIDYO_CLIENT_OUT_EVENT_MIN
			|| event >= VIDYO_CLIENT_OUT_EVENT_MAX))
			return;

		switch (event)
		{
		case VIDYO_CLIENT_OUT_EVENT_SIGN_IN:
		{

			VidyoClientOutEventSignIn * eventSignIn = (VidyoClientOutEventSignIn*)param;
			if (eventSignIn){
				if (!eventSignIn->activeEid){
					//we need to consume a license
					//As VidyoClient just informed that we never consume a license
					VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0);}
											   }
			}
			break;

		}
	}

	HMODULE m_hDLL;
	VidyoClientInitializePtr VidyoClientInitialize;
	VidyoClientStartPtr VidyoClientStart;
	VidyoClientStopPtr VidyoClientStop;
	VidyoClientUninitializePtr VidyoClientUninitialize;
	VidyoClientSendEventPtr VidyoClientSendEvent;
	VidyoClientSendRequestPtr VidyoClientSendRequest;
	VidyoClientCallerPtr m_caller;
};

#ifdef VIDYO_WIN32
static void __stdcall VidyoClientOutCallback
#else
static void VidyoClientOutCallback
#endif
(VidyoClientOutEvent event,
VidyoVoidPtr param, VidyoUint paramSize,
VidyoVoidPtr data)
{

	gImpl->VidyoClientOutCallback(event, param, paramSize, data);
}

ClientVidyoWorks::ClientVidyoWorks()
{
	m_impl = ClientVidyoWorksImplPtr(new ClientVidyoWorksImpl());
}


ClientVidyoWorks::~ClientVidyoWorks()
{
}

static void InitLogParams(VidyoClientLogParams& logParams, map<string, string> &parameter, string &buffer, string &folder)
{
	const unsigned int maxLogFileSize = 1000000;

#ifdef VIDYO_WIN32
	folder = ("log\\");
#else
	folder = QDir::homePath() + QString("/VsLog/");
#endif
	logParams.pathToLogDir = folder.c_str();
	logParams.pathToDumpDir = folder.c_str();
	logParams.pathToConfigDir = folder.c_str();

	logParams.logBaseFileName = "VidyoSample_";

	logParams.logLevelsAndCategories = VidyoClientSwitchGetPara(parameter, "logLevelsAndCategories", buffer, 
		"fatal error warning info@App info@AppEmcpClient info@AppEvents all@AppVcsoapClient");
	
	logParams.logSize = maxLogFileSize;

}

static void InitProfileParams(VidyoClientProfileParams& profileParams, map<string, string> &parameter,
						vector<string>& buffer)
{
#ifdef VIDYO_WIN32
	profileParams.PROGFILES_DIR = ".\\";
	profileParams.CONFIG_KEY_PATH = "SOFTWARE\\Vidyo\\Vidyo Desktop\\";

	profileParams.MYDOCS_DIR = ".\\";
	profileParams.VIDYO_DIR = ".\\";
#else
	/*profileParams.PROGFILES_DIR = "./";
	profileParams.CONFIG_KEY_PATH = "./";

	profileParams.MYDOCS_DIR = "./";
	profileParams.VIDYO_DIR = "./";*/

#endif
	buffer.resize(4);
	profileParams.PRODUCT_NAME = VidyoClientSwitchGetPara(parameter, "progfiles_dir", buffer[0], "VidyoDesktop");
	profileParams.CONFIG_KEY_PATH = VidyoClientSwitchGetPara(parameter, "config_key_path", buffer[1], "SOFTWARE\\Vidyo\\Vidyo Desktop\\");
	profileParams.MYDOCS_DIR = VidyoClientSwitchGetPara(parameter, "mydocs_dir", buffer[2], ".\\");
	profileParams.VIDYO_DIR = VidyoClientSwitchGetPara(parameter, "vidyo_dir", buffer[3], ".\\");
	profileParams.portNumber = VidyoClientSwitchGetPara(parameter, "portNumber", 63460);
}

VidyoClientSwitchDefs::ErrorType ClientVidyoWorks::Initialize(const char* strParameter, VidyoClientCallerPtr& caller)
{
	{
		wchar_t szFullPath[MAX_PATH + 1] = {};

		GetModuleFileName(NULL, szFullPath, MAX_PATH + 1);
		std::wstring wsPath(szFullPath);
		vector<wstring> pathComps;
		boost::split(pathComps, wsPath, boost::is_any_of("\\"));
		pathComps[pathComps.size() - 1] = L"VidyoClientDll.dll";
		wsPath = boost::algorithm::join(pathComps, "\\");
		m_impl->m_hDLL = LoadLibrary(wsPath.c_str());
	}

		if (m_impl->m_hDLL == NULL)
			return VidyoClientSwitchDefs::ErrorDllNotFound;

		{
			m_impl->VidyoClientInitialize = (VidyoClientInitializePtr)GetProcAddress(m_impl->m_hDLL, "VidyoClientInitialize");
			if (m_impl->VidyoClientInitialize == NULL)
				return VidyoClientSwitchDefs::ErrorFuncNotFound;

		}

		{
			m_impl->VidyoClientStart = (VidyoClientStartPtr)GetProcAddress(m_impl->m_hDLL, "VidyoClientStart");
			if (m_impl->VidyoClientStart == NULL)
				return VidyoClientSwitchDefs::ErrorFuncNotFound;

		}

		{
			m_impl->VidyoClientStop = (VidyoClientStopPtr)GetProcAddress(m_impl->m_hDLL, "VidyoClientStop");
			if (m_impl->VidyoClientStop == NULL)
				return VidyoClientSwitchDefs::ErrorFuncNotFound;
		}

		{
			m_impl->VidyoClientUninitialize = (VidyoClientUninitializePtr)GetProcAddress(m_impl->m_hDLL, "VidyoClientUninitialize");
			if (m_impl->VidyoClientUninitialize == NULL)
				return VidyoClientSwitchDefs::ErrorFuncNotFound;

		}

		{
			m_impl->VidyoClientSendEvent = (VidyoClientSendEventPtr)GetProcAddress(m_impl->m_hDLL, "VidyoClientSendEvent");
			if (m_impl->VidyoClientSendEvent == NULL)
				return VidyoClientSwitchDefs::ErrorFuncNotFound;

		}

		{
			m_impl->VidyoClientSendRequest = (VidyoClientSendRequestPtr)GetProcAddress(m_impl->m_hDLL, "VidyoClientSendRequest");
			if (m_impl->VidyoClientSendRequest == NULL)
				return VidyoClientSwitchDefs::ErrorFuncNotFound;

		}

		map<string, string> parameters;
		ConvertFromStringToMap(strParameter, parameters);

		m_impl->m_caller = caller;

		const unsigned int maxLogFileSize = 1000000;
		VidyoClientLogParams logParams = { 0 };

		string result, folder;
		InitLogParams(logParams, parameters, result, folder);

		VidyoBool retVal = m_impl->VidyoClientInitialize((VidyoClientOutEventCallback)VidyoClientOutCallback, NULL, &logParams);
	
		if (retVal == VIDYO_FALSE)
			return VidyoClientSwitchDefs::ErrorVcInitialize;

	return VidyoClientSwitchDefs::ErrorSuccess;
}


VidyoClientSwitchDefs::ErrorType ClientVidyoWorks::Start(const char* strParameter)
{
	const unsigned int maxLogFileSize = 1000000;
	VidyoClientLogParams logParams = { 0 };
	VidyoClientProfileParams profileParams = { 0 };
	int window_origin_x = 0;
	int window_origin_y = 0;
	unsigned window_width = 400;
	unsigned window_height = 300;

	map<string, string> parameters;
	ConvertFromStringToMap(strParameter, parameters);

	string buffer1, buffer2;
	InitLogParams(logParams, parameters, buffer1, buffer2);
	vector<string> profileBuffer;
	InitProfileParams(profileParams, parameters, profileBuffer);

	VidyoRect videoRect = { window_origin_x, window_origin_y, window_width, window_height };

	// startup VidyoClient library
	if (!m_impl->VidyoClientStart((VidyoClientOutEventCallback)VidyoClientOutCallback,
		NULL,
		&logParams,
		NULL,
		//                      (VidyoWindowId)frame_window,
		&videoRect,
		NULL,
		&profileParams,
		NULL))
	{
		// user already notified by VidyoClientStart()
		return VidyoClientSwitchDefs::ErrorVcInitialize;
	}
	return VidyoClientSwitchDefs::ErrorSuccess;
}

bool ClientVidyoWorks::Stop()
{
	m_impl->VidyoClientStop();
	return true;
}

bool ClientVidyoWorks::Uninitialize()
{
	m_impl->VidyoClientUninitialize();
	FreeLibrary(m_impl->m_hDLL);
	return true;
}


VidyoClientSwitchDefs::ErrorType ClientVidyoWorks::Join(const char* strParameter)
{
	map<string, string> parameters;
	ConvertFromStringToMap(strParameter, parameters);

	VidyoClientInEventRoomLink backendReq = {};
	{
		string portalUri;
		VidyoClientSwitchGetPara(parameters, "portalUri", portalUri);
		if (!portalUri.empty())
		{
			SAFE_STRING_CPY((char *)backendReq.portalUri, portalUri.c_str(), sizeof(backendReq.portalUri));
		}
		else
			return VidyoClientSwitchDefs::ErrorVcMissingPara;
	}

	{
		string roomKey;
		VidyoClientSwitchGetPara(parameters, "roomKey", roomKey);
		if (!roomKey.empty())
		{
			SAFE_STRING_CPY((char *)backendReq.roomKey, roomKey.c_str(), sizeof(backendReq.roomKey));
		}
		else
			return VidyoClientSwitchDefs::ErrorVcMissingPara;
	}

	{
		string displayName;
		VidyoClientSwitchGetPara(parameters, "displayName", displayName);
		if (!displayName.empty())
		{
			SAFE_STRING_CPY((char *)backendReq.displayName, displayName.c_str(), sizeof(backendReq.displayName));
		}
		else
			return VidyoClientSwitchDefs::ErrorVcMissingPara;
	}

	{
		string pin;
		VidyoClientSwitchGetPara(parameters, "pin", pin);
		if (!pin.empty())
		{
			SAFE_STRING_CPY((char *)backendReq.pin, pin.c_str(), sizeof(backendReq.pin));
		}
	}

	backendReq.clientType = VIDYO_CLIENT_CLIENTTYPE_L;



	if (!m_impl->VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &backendReq, sizeof(VidyoClientInEventRoomLink)))

	{

		return VidyoClientSwitchDefs::ErrorVcSendEvent;;

	}
	return VidyoClientSwitchDefs::ErrorSuccess;
}

bool ClientVidyoWorks::Leave()
{
	if (!m_impl->VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE, NULL, 0))
		return false;
	return true;
}

void ClientVidyoWorks::tmp(const char * test)
{

}
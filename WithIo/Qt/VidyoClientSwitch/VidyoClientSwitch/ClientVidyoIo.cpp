#include "stdafx.h"
#include "ClientVidyoIo.h"
#include "VidyoClient.h"
#include "VidyoClientSwitchUtils.h"
#include <boost/lexical_cast.hpp>

using boost::bad_lexical_cast;



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


ClientVidyoIoImpl* gImpl = NULL;


class ClientVidyoIoImpl
{
public:
	ClientVidyoIoImpl()
	{
		m_hDLL = NULL;
		VidyoClientInitialize = NULL;
		VidyoClientStart = NULL;
		VidyoClientStop = NULL;
		VidyoClientUninitialize = NULL;
		VidyoClientSendEvent = NULL;
		VidyoClientSendRequest = NULL;
		m_caller = NULL;
		gImpl = const_cast<ClientVidyoIoImpl*>(this);
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
													   VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0);
												   }
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

ClientVidyoIo::ClientVidyoIo()
{
	m_impl = ClientVidyoIoImplPtr(new ClientVidyoIoImpl());
}


ClientVidyoIo::~ClientVidyoIo()
{
}

static void InitLogParams(VidyoClientLogParams& logParams, map<string, string> &parameter)
{
	const unsigned int maxLogFileSize = 1000000;

#ifdef VIDYO_WIN32
	string folder("log\\");
#else
	string folder = QDir::homePath() + QString("/VsLog/");
#endif
	logParams.pathToLogDir = folder.c_str();
	logParams.pathToDumpDir = folder.c_str();
	logParams.pathToConfigDir = folder.c_str();

	logParams.logBaseFileName = "VidyoSample_";
	logParams.logLevelsAndCategories = "fatal error warning info@App info@AppEmcpClient info@AppEvents all@AppVcsoapClient";

	auto search = parameter.find("logLevelsAndCategories");
	if (search != parameter.end())
	{
		logParams.logLevelsAndCategories = search->second.c_str();
	}

	logParams.logSize = maxLogFileSize;

}

static void InitProfileParams(VidyoClientProfileParams& profileParams, map<string, string> &parameter)
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
	profileParams.portNumber = 63460;
	profileParams.PRODUCT_NAME = "VidyoDesktop";

	{
		auto search = parameter.find("progfiles_dir");
		if (search != parameter.end())
		{
			profileParams.PROGFILES_DIR = search->second.c_str();
		}
	}

	{
		auto search = parameter.find("config_key_path");
		if (search != parameter.end())
		{
			profileParams.CONFIG_KEY_PATH = search->second.c_str();
		}
	}

	{
		auto search = parameter.find("mydocs_dir");
		if (search != parameter.end())
		{
			profileParams.MYDOCS_DIR = search->second.c_str();
		}
	}

	{
		auto search = parameter.find("vidyo_dir");
		if (search != parameter.end())
		{
			profileParams.VIDYO_DIR = search->second.c_str();
		}
	}

	{
		auto search = parameter.find("portNumber");
		if (search != parameter.end())
		{
			try
			{
				profileParams.portNumber = boost::lexical_cast<int>(search->second);
			}
			catch (const bad_lexical_cast &)
			{

			}
		}
	}

}





VidyoClientSwitchDefs::ErrorType ClientVidyoIo::Initialize(map<string, string> &parameter, VidyoClientCallerPtr& caller)
{
	{
		wchar_t szFullPath[MAX_PATH] = {};
		GetCurrentDirectory(MAX_PATH, szFullPath);
		std::wstring wsPath(szFullPath);
		wsPath += L"\\VidyoClientDll.dll";
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

	m_impl->m_caller = caller;

	const unsigned int maxLogFileSize = 1000000;
	VidyoClientLogParams logParams = { 0 };

	InitLogParams(logParams, parameter);

	VidyoBool retVal = m_impl->VidyoClientInitialize((VidyoClientOutEventCallback)VidyoClientOutCallback, NULL, &logParams);

	if (retVal == VIDYO_FALSE)
		return VidyoClientSwitchDefs::ErrorVcInitialize;

	return VidyoClientSwitchDefs::ErrorSuccess;
}


VidyoClientSwitchDefs::ErrorType ClientVidyoIo::Start(map<string, string> &parameter)
{
	const unsigned int maxLogFileSize = 1000000;
	VidyoClientLogParams logParams = { 0 };
	VidyoClientProfileParams profileParams = { 0 };
	int window_origin_x = 0;
	int window_origin_y = 0;
	unsigned window_width = 400;
	unsigned window_height = 300;

	InitLogParams(logParams, parameter);
	InitProfileParams(profileParams, parameter);

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

bool ClientVidyoIo::Stop()
{
	m_impl->VidyoClientStop();
	return true;
}

bool ClientVidyoIo::Uninitialize()
{
	m_impl->VidyoClientUninitialize();
	FreeLibrary(m_impl->m_hDLL);
	return true;
}


VidyoClientSwitchDefs::ErrorType ClientVidyoIo::Join(map<string, string> &parameter)
{
	VidyoClientInEventRoomLink backendReq = {};
	{
		auto search = parameter.find("portalUri");
		if (search != parameter.end())
		{
			SAFE_STRING_CPY((char *)backendReq.portalUri, search->second.c_str(), sizeof(backendReq.portalUri));
		}
		else
			return VidyoClientSwitchDefs::ErrorVcMissingPara;
	}

	{
		auto search = parameter.find("roomKey");
		if (search != parameter.end())
		{
			SAFE_STRING_CPY((char *)backendReq.roomKey, search->second.c_str(), sizeof(backendReq.roomKey));
		}
		else
			return VidyoClientSwitchDefs::ErrorVcMissingPara;
	}

	{
		auto search = parameter.find("displayName");
		if (search != parameter.end())
		{
			SAFE_STRING_CPY((char *)backendReq.displayName, search->second.c_str(), sizeof(backendReq.displayName));
		}
		else
			return VidyoClientSwitchDefs::ErrorVcMissingPara;
	}

	{
		auto search = parameter.find("pin");
		if (search != parameter.end())
		{
			SAFE_STRING_CPY((char *)backendReq.pin, search->second.c_str(), sizeof(backendReq.pin));
		}
	}

	backendReq.clientType = VIDYO_CLIENT_CLIENTTYPE_L;



	if (!m_impl->VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &backendReq, sizeof(VidyoClientInEventRoomLink)))

	{

		return VidyoClientSwitchDefs::ErrorVcSendEvent;;

	}
	return VidyoClientSwitchDefs::ErrorSuccess;
}

bool ClientVidyoIo::Leave()
{
	if (!m_impl->VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE, NULL, 0))
		return false;
	return true;
}
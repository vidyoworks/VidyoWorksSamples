// SampleVidyoClient.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "VidyoClient.h"
#include "SampleVidyoClient.h"
//#include "VidyoClientPrivate.h"
#include <string>
#include <sstream>

#define LmiFourCC(_a, _b, _c, _d) ( ((unsigned int)(_d)<<24) | ((unsigned int)(_c) << 16) | ((unsigned int)(_b) << 8) | ((unsigned int)(_a)) )
#define LMI_MEDIAFORMAT_I420 LmiFourCC('I', '4', '2', '0')
#define LMI_MEDIAFORMAT_YU12 LmiFourCC('Y', 'U', '1', '2')
#define LMI_MEDIAFORMAT_ARGB LmiFourCC('A', 'R', 'G', 'B')


typedef struct
{
	const char *confName;
} ConferenceData;

typedef struct
{
	VidyoClientOutEvent actionType;
	VidyoVoidPtr data;
	VidyoUint paramSize;
	VidyoVoidPtr param;
} EventData;


ConferenceData confData = { "My first conference" };


#define MAX_LOADSTRING 100
#define MAX_PARTICIPANTS 16										// Max participants in the call

// Global Variables:
HINSTANCE hInst;												// current instance
TCHAR szTitle[MAX_LOADSTRING];									// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];							// the main window class name
HWND hWnd, hWndRaw, hWndSelf;									// main window handle
char portalAddress[URI_LEN] = {0};								// Address of the portal
char userId[USERID_SIZE] = {0};									// Username for login
char passwd[PASSWORD_SIZE] = {0};								// Password for login
char outgoingChatMessage[MAX_CHAT_MESSAGE_LEN] = {0};			// Outgoing chat text
char incomingChatMessage[MAX_CHAT_MESSAGE_LEN] = {0};			// Incoming chat text
VidyoUint numOfParticipants = 0;								// Total number of participants
char chatSender[USERID_SIZE] = {0};								// display name of the sender of chat msg
char participantUri[MAX_PARTICIPANTS][URI_LEN] = {0};			// URIs of the remote participants
char participantNames[MAX_PARTICIPANTS][USERID_SIZE] = {0};		// display names of the remote participants
VidyoUint appShareHandles[] = {0};								// Window handles of other applications
VidyoBool participantMode = VIDYO_FALSE;
VidyoBool willBackground = VIDYO_FALSE;
char remoteAppUri[MAX_REMOTE_SHARE_APP][MAX_URI_LEN] = {0};		// URIs of the remote shares available for viewing
char remoteAppname[MAX_REMOTE_SHARE_APP][MAX_URI_LEN] = {0};	// App names of the remote shares available for viewing
char eventUri[MAX_URI_LEN] = {0};

const char kChinese[] = {-28, -72, -83, -26, -106, -121, 0};//utf-8 encoded values for “中文”
const char kArabic[] = {-40, -89, -39, -124, -40, -71, -40, -79, -40, -88, -39, -118, -40, -87, 0};//utf-8 encoded values for ‘العربية’
const char kSpanish[] = {99, 97, -61, -79, -61, -77, 110, 0};//utf-8 encoded values for +cañón
const char kJapanese[] = {227, 131, 165, 227, 131, 188, 227, 129, 150, 227, 131, 188, 0}; //utf-8 encoded values for ユーザー 

static VidyoClientInEventMute privacy = {FALSE};
static VidyoClientInEventPreview preview = {VIDYO_CLIENT_PREVIEW_MODE_NONE};
static VidyoClientInEventParticipantsLimit participantsLimit= {0};
static VidyoClientRequestParticipantsLimit reqParticipantLimit = {0};
static VidyoClientRequestGetMuted microphoneMute = {FALSE};
static VidyoClientInEventMute inEventMuteMic = {0};
static VidyoClientInEventMute inEventMuteSpeaker = {0};
static VidyoClientInEventGroupChat sendGroupChat = {0};
static VidyoClientRequestParticipants reqParticipants = {0};
static VidyoClientInEventPrivateChat sendPrivateChat = {0};
static VidyoClientRequestParticipantStatisticsList stats = {0};
static VidyoClientParticipantStatistics participantStats = {0};
static VidyoClientRequestGetNumParticipants getNumParticipants = {0};
static VidyoClientInEventLogIn logInParams = {0};
static VidyoClientInEventSetOffline inEventSetOffline = {0};
static VidyoClientOutEventGroupChat *outEventGroupChat;
static VidyoClientInEventShare inEventShare;
static VidyoClientOutEventIncomingCall *outEventincomingCall;
static VidyoClientRequestGetMuted getMutedRequest = {0};
static VidyoClientInEventLayout layout = {0};
static VidyoClientInEventSetFlag echoDetect = {0};
static VidyoClientInEventSetFlag echoCancel = {0};
static VidyoClientInEventSetFlag agc = {0};
static VidyoClientInEventSetFlag freezeImage = {0};
static VidyoClientInEventControlCamera panLeft = {0};
static VidyoClientInEventControlCamera panRight = {0};
static VidyoClientInEventControlCamera tiltUp = {0};
static VidyoClientInEventControlCamera tiltDown = {0};
static VidyoClientInEventControlCamera zoomIn = {0};
static VidyoClientInEventControlCamera zoomOut = {0};
static VidyoClientInEventControlCamera stop = {0};
static VidyoClientInEventControlCamera freeze = {0};
static VidyoClientInEventControlCamera unfreeze = {0};
//static VidyoClientInEventSetParticipantVideoMode participantVideoMode = {0};
static VidyoClientInEventSetDisplayName setDisplayName = {0};
static VidyoClientRequestConfiguration reqConfig = {0};
static VidyoClientRequestSetLabel setLabel = {VIDYO_CLIENT_LABEL_SELF_VIEW};
static VidyoClientVideoPreferences videoPreference = { VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_QUALITY };
static VidyoClientInEventSetSendBandwidth setBandwidth = {0};
static VidyoClientRequestSetBackground background = {VIDYO_FALSE};
static VidyoClientRequestVolume requestVolume = {0};
static VidyoClientRequestParticipantInfo getParticipantInfo = {0};
static VidyoClientParticipantStatistics statsAt = {0};
static VidyoClientRequestWindowShares windowShares = {LIST_SHARING_WINDOWS};
static VidyoClientInEventSignIn signInEvent = {0};
static VidyoClientInEventStartWatchVideoSource watchSource = {0};
//static VidyoClientOutEventVideoFrameReceived videoFrame = {0};

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcRaw(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcSelf(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Signin(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	GuestSignin(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	IncomingChat(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	sendChat(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK		EnumerateWindows( HWND, LPARAM);


#define LOG_INFO(WHAT)										\
	TestLog(__FILE__,__LINE__, "", 3, WHAT.str())

void TestLog(const char *file, int line, const char *function, unsigned severity, std::string logEntry)
{
	VidyoLogLevel level = (VidyoLogLevel)severity;
	static char* cSeverityStr[] = {"FATAL ", "WARNING ", "ERROR ", "INFO ", "DEBUG "};
	std::string severityStr = cSeverityStr[severity];
	std::string now("current date time");
	VidyoClientLog(level, file, line, function, logEntry.c_str());
}

void WINAPI VDAPIConsoleOutEventCB (VidyoClientOutEvent actionType,
									VidyoVoidPtr param, 
									VidyoUint paramSize,
									VidyoVoidPtr data)
{
	EventData* event_data = (EventData*)malloc(sizeof(EventData)+paramSize);
	event_data->actionType = actionType;
	event_data->param = param;
	event_data->paramSize = paramSize;
	event_data->data  = (char*)event_data + sizeof(EventData);
	memcpy(event_data->data, param, paramSize);

	std::stringstream ss;
	ss << "This is the message ************* " << actionType;
	//LOG_INFO(ss);

	switch(actionType)
	{
	case VIDYO_CLIENT_OUT_EVENT_SELF_VIEW_VIDEO_FRAME_RECEIVED:
		PostMessage(hWndSelf, WM_USER, (WPARAM)event_data, NULL);
		break;
	case VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED:
		PostMessage(hWndRaw, WM_USER, (WPARAM)event_data, NULL);
		break;
	default:
		PostMessage(hWnd, WM_USER, (WPARAM)event_data, NULL);
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SAMPLEVIDYOCLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLEVIDYOCLIENT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	VidyoClientStop();
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLEVIDYOCLIENT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOWTEXT+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SAMPLEVIDYOCLIENT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SAMPLEVIDYOCLIENT));

	RegisterClassEx(&wcex);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProcRaw;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLEVIDYOCLIENT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOWTEXT+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_SAMPLEVIDYOCLIENT);
	wcex.lpszClassName	= _T("RAW_WINDOW");
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SAMPLEVIDYOCLIENT));

	RegisterClassEx(&wcex);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProcSelf;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLEVIDYOCLIENT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOWTEXT+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_SAMPLEVIDYOCLIENT);
	wcex.lpszClassName	= _T("SELF_WINDOW");
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SAMPLEVIDYOCLIENT));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hWndRaw = CreateWindow(_T("RAW_WINDOW"), _T("Raw frame renderer"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWndRaw)
	{
		return FALSE;
	}

	ShowWindow(hWndRaw, nCmdShow);
	UpdateWindow(hWndRaw);

	hWndSelf = CreateWindow(_T("SELF_WINDOW"), _T("Self Raw frame renderer"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWndSelf)
	{
		return FALSE;
	}

	ShowWindow(hWndSelf, nCmdShow);
	UpdateWindow(hWndSelf);

	return TRUE;
}

void DrawRawFrame(VidyoClientInEventVideoFrame *pFrame, HWND hWnd, int nCount, int nPos)
{
	if (pFrame == NULL || hWnd == NULL)
		return;

	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC dc = GetDC(hWnd);

	RECT dest = rect;
	switch(nCount)
	{
	case 2:
		if (nPos == 0)
		{
			dest.left = rect.left;
			dest.top = rect.top;
			dest.right = rect.right / 2;
			dest.bottom = rect.bottom;
		}
		else
		{
			dest.left = rect.left + (rect.right / 2) + 1;
			dest.top = rect.top;
			dest.right = rect.right;
			dest.bottom = rect.bottom;
		}
		break;

	case 3:
		if (nPos == 0)
		{
			dest.left = rect.left;
			dest.top = rect.top;
			dest.right = rect.right / 2;
			dest.bottom = rect.bottom / 2;
		}
		else if (nPos == 1)
		{
			dest.left = rect.left + (rect.right / 2) + 1;
			dest.top = rect.top;
			dest.right = rect.right;
			dest.bottom = rect.bottom / 2;
		}
		else
		{
			dest.left = rect.left + (rect.right / 4);
			dest.top = rect.top + (rect.bottom / 2) + 1;
			dest.right = dest.left + (rect.right / 2);
			dest.bottom = rect.bottom;
		}
		break;

	case 4:
		if (nPos == 0)
		{
			dest.left = rect.left;
			dest.top = rect.top;
			dest.right = rect.right / 2;
			dest.bottom = rect.bottom / 2;
		}
		else if (nPos == 1)
		{
			dest.left = rect.left + (rect.right / 2) + 1;
			dest.top = rect.top;
			dest.right = rect.right;
			dest.bottom = rect.bottom / 2;
		}
		else if (nPos == 2)
		{
			dest.left = rect.left;
			dest.top = rect.top + (rect.bottom / 2) + 1;
			dest.right = dest.left + (rect.right / 2);
			dest.bottom = rect.bottom;
		}
		else
		{
			dest.left = rect.left + (rect.right / 2) + 1;
			dest.top = rect.top + (rect.bottom / 2) + 1;
			dest.right = rect.right;
			dest.bottom = rect.bottom;
		}
		break;
	}

	switch(pFrame->format)
	{
	case LMI_MEDIAFORMAT_ARGB:
		{
			BITMAPINFO info;
			ZeroMemory(&info, sizeof(BITMAPINFO));
			info.bmiHeader.biBitCount = 32;
			info.bmiHeader.biWidth = pFrame->width;
			info.bmiHeader.biHeight = pFrame->height;
			info.bmiHeader.biPlanes = 1;
			info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			info.bmiHeader.biSizeImage = pFrame->width * pFrame->height * 4;
			info.bmiHeader.biCompression = BI_RGB;

			StretchDIBits(dc, dest.left, dest.top, (dest.right-dest.left), (dest.bottom-dest.top),
				              0,         0,         pFrame->width,          pFrame->height,
							  pFrame->data, &info, DIB_RGB_COLORS, SRCCOPY);
		}
		break;

	case LMI_MEDIAFORMAT_YU12:
		break;

	case LMI_MEDIAFORMAT_I420:
		break;
	}

	ReleaseDC(hWnd, dc);
}

//
//  FUNCTION: WndProcRaw(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProcRaw(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static char sPartURI[4][MAX_URI_LEN]={0};
	static char sPartName[4][MAX_URI_LEN]={0};
	static int nFrame[4] = {0};
	static UINT nFPS[4] = {0};
	static int nCount = 0;
	static DWORD dwTick[4] = {0};
	

	switch (message)
	{
	case WM_USER:
		{
			EventData *pData = (EventData*)wParam;
			if (pData == NULL || pData->data == NULL)
				break;

			switch (pData->actionType)
			{
			case VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED:
				{
					VidyoClientOutEventVideoFrameReceived *videoFrame = (VidyoClientOutEventVideoFrameReceived*)pData->data;
					VidyoClientInEventVideoFrame *pFrame = &videoFrame->frame;
					if (pFrame == NULL || pFrame->size <= 0)
						break;
					
					bool found = false;
					int nPos = 0;
					// find the participant URI
					for(; nPos < nCount; ++nPos)
					{
						if (strncmp(sPartURI[nPos], videoFrame->participantURI, MAX_URI_LEN) == 0)
						{
							found = true;
							++nFrame[nPos];
							++nFPS[nPos];
							break;
						}
					}

					if (found == false)
					{
						strncpy(sPartURI[nCount], videoFrame->participantURI, MAX_URI_LEN);
						VidyoClientRequestParticipants req;
						memset(&req, NULL, sizeof(req));
						VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &req, sizeof(req));
						for (int i=0; i < req.numberParticipants; ++i)
						{
							if (strncmp(sPartURI[nCount], req.URI[i], MAX_URI_LEN) == 0)
								strncpy(sPartName[nCount], req.name[i], MAX_URI_LEN);
						}

						nPos = nCount;
						++nCount;
						if (nCount >= 4)
							nCount = 0;
					}

					

					if (dwTick[nPos] == 0)
						dwTick[nPos] = GetTickCount();
					else
					{
						DWORD dwNow = GetTickCount();
						if ((dwNow - dwTick[nPos]) >= 2000)
						{
							dwTick[nPos] = 0;
							VIDYO_CLIENT_LOG_INFO_FORMATTED("Participant:[%s], FPS:[%d], width:[%d], height:[%d]", sPartName[nPos], (nFPS[nPos]/2), pFrame->width, pFrame->height);
							nFPS[nPos] = 0;
						}
					}

					DrawRawFrame(pFrame, hWnd, nCount, nPos);

					if (nFrame[nPos] >= 100)
					{
						//VIDYO_CLIENT_LOG_INFO_FORMATTED("URI:[%s], width:[%d], height:[%d]", sPartName[nPos], pFrame->width, pFrame->height);

						nFrame[nPos] = 0;
					}
				}
				free(pData);
                break;
			default:
				break;
			}
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//
//  FUNCTION: WndProcSelf(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProcSelf(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_USER:
		{
			EventData *pData = (EventData*)wParam;
			if (pData == NULL || pData->data == NULL)
				break;

			switch (pData->actionType)
			{
			case VIDYO_CLIENT_OUT_EVENT_SELF_VIEW_VIDEO_FRAME_RECEIVED:
				{
					VidyoClientOutEventVideoFrameReceived *selfViewFrame = (VidyoClientOutEventVideoFrameReceived *)pData->data;
					VidyoClientInEventVideoFrame *pFrame = &selfViewFrame->frame;
					if (pFrame == NULL || pFrame->size <= 0)
						break;
					DrawRawFrame(pFrame, hWnd, 1, 0);
				}
				free(pData);
                break;
			default:
				break;
			}
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	MENUITEMINFO menuInfo;
	HMENU hMenu = GetMenu(hWnd);
	menuInfo.cbSize=sizeof(MENUITEMINFO);  
	menuInfo.fMask = MIIM_STATE;

	VidyoClientInEventPrecallTestCamera preCallTest = {};
	VidyoClientInEventRoomLink roomLink;

	VidyoClientRequestEventSetWatchVideoFormat watch= {};

	switch (message)
	{
	case WM_CREATE:
		{
			VidyoClientLogParams logParam;
			VidyoClientProfileParams profileParam;
			memset(&logParam, 0, sizeof(logParam));
			memset(&profileParam, 0, sizeof(profileParam));

			logParam.logLevelsAndCategories = "FATAL ERROR WARNING INFO@AppGuiUser INFO@AppGui INFO@App INFO@LmiApp INFO@LmiUi INFO@AppEmcpClient INFO@AppWebProxy ALL@AppVcsoapClient INFO@AppEvents";
			//logParam.logLevelsAndCategories = "all";
			logParam.logSize = 5000000;
			logParam.pathToLogDir = ".\\Logs\\";
			logParam.logBaseFileName = "VidyoSampleApplication";
			logParam.pathToDumpDir = ".\\Logs\\";
			logParam.pathToConfigDir = "";

			/* the default values are configured in VidyoClientConstants.h */
#define DEF_DIR ""
			profileParam.PROGFILES_DIR = "";				// "\\Vidyo\\Vidyo Desktop\\"
			profileParam.CONFIG_KEY_PATH = "";		// "SOFTWARE\\Vidyo\\Vidyo Desktop\\"
			profileParam.PRODUCT_NAME = "VidyoClientSample";							// "VidyoDesktop"
			profileParam.MYDOCS_DIR = DEF_DIR;								// "\\Vidyo Desktop\\"
			profileParam.VIDYO_DIR = DEF_DIR;								// "\\Vidyo"
			profileParam.CERT_FILE_DIR = DEF_DIR;
			profileParam.INSTALLED_APP_DIR = DEF_DIR;
			profileParam.portNumber = 0;								// DEF_HELP_PORT;	// 63457

			VidyoRect VRect;
			RECT rect;
			GetClientRect(hWnd,&rect);
			VRect.height = rect.bottom-rect.top;
			VRect.width = rect.right-rect.left;
			VRect.xPos = 0;
			VRect.yPos = 0;
			//const unsigned int maxLogFileSize = 5000000;
			//const char* logPath = ".\\VDAPIConsole.log";

			/* This is for 2.3 clients 
			if (VidyoClientInitialize(VDAPIConsoleOutEventCB, &confData, &logParam) != VIDYO_TRUE) {
			SetWindowText(hWnd, L"VidyoClient sample - Client Initialization failed");
			return 0;
			}*/

			// This is for 2.2.2 clients 
			if (VidyoClientInitialize(VDAPIConsoleOutEventCB, &confData, &logParam) != VIDYO_TRUE) {
				SetWindowText(hWnd, L"VidyoClient sample - Client Initialization failed");
				break;
			}
			
			VidyoClientSetLogConfidentialityLevel(VIDYO_CLIENT_LOG_CONFIDENTIALITY_LEVEL_EXCLUDE_PERSONALLY_IDENTIFIABLE_INFO);

			//internal rendering
			if (VidyoClientStart(VDAPIConsoleOutEventCB, &confData, &logParam, hWnd, &VRect, NULL, &profileParam, NULL) != VIDYO_TRUE) {
			//only custom rendering
			//if (VidyoClientStart(VDAPIConsoleOutEventCB, &confData, &logParam, NULL, NULL, NULL, &profileParam, NULL) != VIDYO_TRUE) {
					SetWindowText(hWnd, L"VidyoClient sample - Client Start failed");
					break;
			}

			SetWindowText(hWnd, L"VidyoClient sample - Started");

			// send the in event to mute the rendering
			VidyoClientInEventMute evt;
			evt.willMute = VIDYO_TRUE;
			//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_DEFAULT_RENDERING, &evt, sizeof(evt));


			// set the dynamic watch
			// get base layer video of 4 loudest participants in the conference
			
			VidyoClientInEventSetDynamicWatchVideoSource dwSrc;
			memset(&dwSrc, NULL, sizeof(dwSrc));
			
			dwSrc.numParticipants = 4;

			// 1280 x 720, 640 x 360, 320 x 180, 960 x 540, 480 x 270
			
			dwSrc.dynamicViews[0].width = 1280;
			dwSrc.dynamicViews[0].height = 720;
			dwSrc.dynamicViews[0].maxFrameRate = 30;
			
			dwSrc.dynamicViews[1].width = 640;
			dwSrc.dynamicViews[1].height = 360;
			dwSrc.dynamicViews[1].maxFrameRate = 30;
			
			dwSrc.dynamicViews[2].width = 320;
			dwSrc.dynamicViews[2].height = 180;
			dwSrc.dynamicViews[2].maxFrameRate = 30;
			
			dwSrc.dynamicViews[3].width = 320;
			dwSrc.dynamicViews[3].height = 180;
			dwSrc.dynamicViews[3].maxFrameRate = 30;

			//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_DYNAMIC_WATCH_VIDEO_SOURCE, &dwSrc, sizeof(dwSrc));


			VidyoClientInEventSetParticipantVideoMode vdmode;
			memset(&vdmode,NULL, sizeof(vdmode));

			vdmode.actionType = VIDYO_CLIENT_ACTION_TYPE_PIN;
			//vdmode.uri;
			vdmode.videoMode = VIDYO_CLIENT_VIDEO_MODE_PINLOW;

			//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_TOGGLE_CAMERA, NULL, NULL);

			// get enhanced layer of loudest participant and base layer video of next 3 (last spoken) participants in the conference
		}

		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		case IDM_ABOUT:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			}
		case ID_PRE_GUESTSIGNIN:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_GUEST_SIGNIN), hWnd, GuestSignin);
			break;
		case ID_PRE_GUESTLINK:
			{

				//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO, NULL, 0);

				/* Enable show participant name and other configurable parameters before Signin */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");

				//reqConfig.proxySettings &= ~PROXY_WEB_LOCAL;	// Use AutoDetect WebProxy Setting from OS
				reqConfig.proxySettings |= PROXY_WEB_LOCAL;		// Dont use AutoDetect WebProxy Setting from OS, No WebProxy lookup

				/* Do a VIDYO_CLIENT_REQUEST_SET_CONFIGURATION with the above values changed. */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");

				// Send the Login event 
				memset(&roomLink,0, sizeof(roomLink));
				strcpy(roomLink.displayName, "Sample Guest");
				strcpy(roomLink.portalUri,"http://vvp5.vidyoqa.com");
				strcpy(roomLink.roomKey,"S2Elcic9k1PR");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &roomLink, sizeof(roomLink)) != VIDYO_TRUE) {
					SetWindowText(hWnd, L"VidyoClient sample - Sending Guest Link failed");
				}
				break;
			}
		/* Sign-in as a registered user */
		case ID_PRE_SIGNIN:
			{
				/* Enable show participant name and other configurable parameters before Signin */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");

				reqConfig.enableShowConfParticipantName = VIDYO_TRUE;	// display labels for participants
				reqConfig.enableFeccController = VIDYO_TRUE;			// enable FECC controlling
				reqConfig.enableAutoAnswer = VIDYO_FALSE;				// disable auto answer
				reqConfig.enableAutoLogIn = VIDYO_FALSE;				// disable auto login
				reqConfig.enableRendering = VIDYO_TRUE;					// enable rendering
				reqConfig.videoPreferences = videoPreference;			// Video mode set to Best Quality
				reqConfig.enableLogging = VIDYO_TRUE;					// enable logging
				reqConfig.enableEchoDetection = VIDYO_TRUE;				// enable echo detection
				reqConfig.enableEchoCancellation = VIDYO_TRUE;			// enable echo cancellation
				
				//reqConfig.proxySettings = PROXY_WEB_IE_MANUAL | PROXY_WEB_LOCAL_MANUAL;

				/* Enable client statistics */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_STATISTICS_ENABLE, NULL, 0) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_STATISTICS_ENABLE failed");

				/* Do a VIDYO_CLIENT_REQUEST_SET_CONFIGURATION with the above values changed. */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");

				/* Get the login details from the dialog box */
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SIGNINBOX), hWnd, Signin);

				break;
			}



		case ID_PRE_SIGNOUT:
			{
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SIGNOFF, NULL, 0) != VIDYO_TRUE) {
				SetWindowText(hWnd, L"VidyoClient sample - Sending Signout Event failed");
				}
				/*
				inEventSetOffline.offline = VIDYO_TRUE;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_OFFLINE, &inEventSetOffline, sizeof(inEventSetOffline)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_OFFLINE failed");
			    */
				break;
			}




		case ID_IN_SHARE_APPLICATION:
			{
				/* Get the window ID's from OS and share the first available window which is visible and not a system window.
				Will be enhanced later to select a particular window from drop down menu 
				Take a look at the callback code for "EnumerateWindows" to see how this is done */
				/*
				MARKR 
				*/
				/////////////////////////
				VidyoClientRequestGetWindowsAndDesktops eventData = {0};
				int error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS, &eventData, sizeof(VidyoClientRequestGetWindowsAndDesktops));
				/////////////////////////
				if (EnumWindows(EnumerateWindows, (LPARAM)appShareHandles) != VIDYO_TRUE) {
					SetWindowText(hWnd, L"VidyoClient sample - App Share failed");
				} else {
					SetWindowText(hWnd, L"VidyoClient sample - App Share Successful");
				}
				break;
			}

		case ID_IN_STOP_APPLICATION_SHARE:
			{
				/* Stop the application share that is in progress */
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_UNSHARE, NULL, 0) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - App UnShare failed");
				break;
			}

		case ID_GETOPERATIONS_GETMUTEDVIDEO:
			{
				/* Get the state of Muted video from Library */
				VidyoBool mutedVideo;
				memset(&getMutedRequest, 0, sizeof(getMutedRequest));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO, &getMutedRequest, sizeof(getMutedRequest)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO failed");
				mutedVideo = getMutedRequest.isMuted;
				break;
			}

		case ID_GETMUTED_SERVER_AUDIO:
			{
				/* Get the state of "Mic (mute/unmute) by Server" from the Library */
				VidyoBool mutedServerAudio;
				memset(&getMutedRequest, 0, sizeof(getMutedRequest));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_AUDIO_IN, &getMutedRequest, sizeof(getMutedRequest)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_AUDIO_IN failed");
				mutedServerAudio = getMutedRequest.isMuted;
				break;
			}

		case ID_GETOPERATIONS_GETMUTED_AUDIOOUT:
			{
				/* Get the state of speaker (mute/unmute) from the Library */
				VidyoBool mutedLocalAudioOut;
				memset(&getMutedRequest, 0, sizeof(getMutedRequest));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_OUT, &getMutedRequest, sizeof(getMutedRequest)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_OUT failed");
				mutedLocalAudioOut = getMutedRequest.isMuted;
				break;
			}

		case ID_GETOPERATIONS_GETMUTED_AUDIOIN:
			{
				/* Get the state of Mic (mute/unmute) from the library */
				VidyoBool mutedLocalAudioIn;
				memset(&getMutedRequest, 0, sizeof(getMutedRequest));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN, &getMutedRequest, sizeof(getMutedRequest)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN failed");
				mutedLocalAudioIn = getMutedRequest.isMuted;
				break;
			}

		case ID_GETOPERATIONS_GETMUTEDSERVER_VIDEO:
			{
				/* Get the state of "Camera (mute/unmute) by Server" from the library */
				VidyoBool mutedServerVideo;
				memset(&getMutedRequest, 0, sizeof(getMutedRequest));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_VIDEO, &getMutedRequest, sizeof(getMutedRequest)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_MUTED_SERVER_VIDEO failed");
				mutedServerVideo = getMutedRequest.isMuted;
				break;
			}

		case ID_INEVENTS_MUTERENDERING:
			{
				// send the in event to mute the rendering
				VidyoClientInEventMute evt;
				evt.willMute = VIDYO_TRUE;
				VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_DEFAULT_RENDERING, &evt, sizeof(evt));

				menuInfo.fState = MFS_CHECKED;
				SetMenuItemInfo(hMenu, ID_INEVENTS_MUTERENDERING, FALSE, &menuInfo);

				menuInfo.fState = MFS_UNCHECKED;
				SetMenuItemInfo(hMenu, ID_INEVENTS_UNMUTERENDERING, FALSE, &menuInfo);

			}
			break;

		case ID_INEVENTS_UNMUTERENDERING:
			{
				// send the in event to mute the rendering
				VidyoClientInEventMute evt;
				evt.willMute = VIDYO_FALSE;
				VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_DEFAULT_RENDERING, &evt, sizeof(evt));

				menuInfo.fState = MFS_CHECKED;
				SetMenuItemInfo(hMenu, ID_INEVENTS_UNMUTERENDERING, FALSE, &menuInfo);

				menuInfo.fState = MFS_UNCHECKED;
				SetMenuItemInfo(hMenu, ID_INEVENTS_MUTERENDERING, FALSE, &menuInfo);
			}
			break;
		case ID_INEVENTS_RESETRENDER:
			{

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants)) == VIDYO_CLIENT_ERROR_OK)
				{

					for(int index = 0; index < reqParticipants.numberParticipants; ++index)
					{

						VidyoClientInEventStopWatchVideoSource stopWatch = {0};
						strcpy(stopWatch.source.participantURI, reqParticipants.URI[index]);
						stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;

						if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &stopWatch, sizeof(stopWatch)) != VIDYO_TRUE){
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Video) failed");
						}else{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Video) sent");
						}
					}

					for(int index = 0; index < reqParticipants.numberParticipants; ++index)
					{

						strcpy(watchSource.source.participantURI, reqParticipants.URI[index]);
						watchSource.source.mediaType = VidyoClientMediaControlType::VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
						watchSource.source.sourceId = 0;
						watchSource.frameRate = 15;
						watchSource.height = 360;
						watchSource.width = 640;
						watchSource.minFrameInterval = 0;
						watchSource.watchData = NULL;
						if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource)) != VIDYO_TRUE){
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE failed");
						}else{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE sent");
						}
					}
				}
			}
			break;

		case ID_PARTICIPANTBORDER_ENABLE:
			{
				VidyoClientRequestSetBorder border;
				border.showBorder = VIDYO_TRUE;
				VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_PARTICIPANT_BORDER, &border, sizeof(VidyoClientRequestSetBorder));

				menuInfo.fState = MFS_CHECKED;
				SetMenuItemInfo(hMenu, ID_PARTICIPANTBORDER_ENABLE, FALSE, &menuInfo);

				menuInfo.fState = MFS_UNCHECKED;
				SetMenuItemInfo(hMenu, ID_PARTICIPANTBORDER_DISABLE, FALSE, &menuInfo);
			}
			break;

		case ID_PARTICIPANTBORDER_DISABLE:
			{
				VidyoClientRequestSetBorder border;
				border.showBorder = VIDYO_FALSE;
				VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_PARTICIPANT_BORDER, &border, sizeof(VidyoClientRequestSetBorder));

				menuInfo.fState = MFS_CHECKED;
				SetMenuItemInfo(hMenu, ID_PARTICIPANTBORDER_DISABLE, FALSE, &menuInfo);

				menuInfo.fState = MFS_UNCHECKED;
				SetMenuItemInfo(hMenu, ID_PARTICIPANTBORDER_ENABLE, FALSE, &menuInfo);
			}
			break;

		case ID_INEVENTS_FREEZEIMAGE:
			{
				/* Freeze/unfreeze the image being sent to the router */
				freezeImage.willEnable = !freezeImage.willEnable;
				menuInfo.fState = (freezeImage.willEnable)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_INEVENTS_FREEZEIMAGE, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_FREEZE_IMAGE, &freezeImage, sizeof(freezeImage)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_FREEZE_IMAGE failed");
				break;
			}

		case ID_INEVENTS_BACKGROUNDSTATE:
			{
				/* Enable background state */
				background.willBackground = !background.willBackground;
				menuInfo.fState = (background.willBackground)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_INEVENTS_BACKGROUNDSTATE, FALSE, &menuInfo);
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_BACKGROUND, &background, sizeof(background)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_BACKGROUND failed");
				break;
			}

		case IDM_EXIT:
			{
				DestroyWindow(hWnd);
				break;
			}

		case ID_COMMAND_PANLEFT:
			{
				/* The data for pan left needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				panLeft.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				//panLeft.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_PANLEFT;
				strcpy_s(panLeft.commandId, sizeof(panLeft.commandId), "Left");
				strcpy_s(panLeft.commandData, sizeof(panLeft.commandData), "81 01 06 01 02 00 01 03 FF");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &panLeft, sizeof(panLeft)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA pan left failed");
				break;
			}

		case ID_COMMAND_PANRIGHT:
			{
				/* The data for pan right needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				panRight.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				//panRight.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_PANRIGHT;
				strcpy_s(panRight.commandId, sizeof(panRight.commandId), "Right");
				strcpy_s(panRight.commandData, sizeof(panRight.commandData), "81 01 06 01 02 00 02 03 FF");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &panRight, sizeof(panRight)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA pan right failed");
				break;
			}

		case ID_COMMAND_TILTUP:
			{
				/* The data for tilt up needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				tiltUp.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				//tiltUp.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_TILTUP;
				strcpy_s(tiltUp.commandId, sizeof(tiltUp.commandId), "Up");
				strcpy_s(tiltUp.commandData, sizeof(tiltUp.commandData), "81 01 06 01 00 04 03 01 ff");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &tiltUp, sizeof(tiltUp)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA tilt up failed");
				break;
			}

		case ID_COMMAND_TILTDOWN:
			{
				/* The data for tilt down needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				tiltDown.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				//tiltDown.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_TILTDOWN;
				strcpy_s(tiltDown.commandId, sizeof(tiltDown.commandId), "Down");
				strcpy_s(tiltDown.commandData, sizeof(tiltDown.commandData), "81 01 06 01 00 04 03 02 ff");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &tiltDown, sizeof(tiltDown)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA tilt down failed");
				break;
			}

		case ID_COMMAND_ZOOMIN:
			{
				/* The data for zoom in needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				zoomIn.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				//zoomIn.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_ZOOMIN;
				strcpy_s(zoomIn.commandId, sizeof(zoomIn.commandId), "ZoomIn");
				strcpy_s(zoomIn.commandData, sizeof(zoomIn.commandData), "81 01 04 07 02 FF");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &zoomIn, sizeof(zoomIn)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA zoom in failed");
				break;
			}

		case ID_COMMAND_ZOOMOUT:
			{
				/* The data for zoom out needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				zoomOut.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				//zoomOut.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_ZOOMOUT;
				strcpy_s(zoomOut.commandId, sizeof(zoomOut.commandId), "ZoomOut");
				strcpy_s(zoomOut.commandData, sizeof(zoomOut.commandData), "81 01 04 07 03 FF");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &zoomOut, sizeof(zoomOut)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA zoom out failed");
				break;
			}

		case ID_COMMAND_STOPCAMERA:
			{
				/* The data for stopping current camera action needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				stop.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				strcpy_s(stop.commandId, sizeof(stop.commandId), "stop");
				strcpy_s(stop.commandData, sizeof(stop.commandData), "81 01 06 01 04 04 03 03 ff");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &stop, sizeof(stop)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA stop camera action failed");
				break;
			}

		case ID_COMMAND_FREEZE:
			{
				/* The data for freeze needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				freeze.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				strcpy_s(freeze.commandId, sizeof(freeze.commandId), "freeze");
				strcpy_s(freeze.commandData, sizeof(freeze.commandData), "81 01 04 62 02 ff");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &freeze, sizeof(freeze)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA freeze camera failed");
				break;
			}

		case ID_COMMAND_UNFREEZE:
			{
				/* The data for unfreeze needs to checked for the camera that is being controlled
				The following commands are for Sony Z20 camera */
				unfreeze.cameraCommand = VIDYO_CLIENT_CAMERA_CONTROL_VISCACOMMAND;
				strcpy_s(unfreeze.commandId, sizeof(unfreeze.commandId), "unfreeze");
				strcpy_s(unfreeze.commandData, sizeof(unfreeze.commandData), "81 01 04 62 03 ff");
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CONTROL_CAMERA, &unfreeze, sizeof(unfreeze)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VISCA unfreeze camera failed");
				break;
			}

		case ID_COMMAND_16LAYOUT:
			{
				/* Change the number of viewable participants to 16. It can be any value 0-16 */
				participantsLimit.maxNumParticipants = 16;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PARTICIPANTS_LIMIT, &participantsLimit, sizeof(participantsLimit)) != VIDYO_TRUE) {
					SetWindowText(hWnd, L"VidyoClient sample - Setting 16 participants failed");
				}

				/* Check if the number is updated by doing a get */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS_LIMIT, &reqParticipantLimit, sizeof(reqParticipantLimit)) != VIDYO_FALSE) {
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS_LIMIT failed");
				} else {
					VidyoUint bwLimit, cpuLimit, usrLimit;
					bwLimit = reqParticipantLimit.bandwidthLimit;		// # of viewable remote participants limited by download b/w available
					cpuLimit = reqParticipantLimit.cpuLimit;			// # of viewable remote participants limited by cpu utilization
					usrLimit = reqParticipantLimit.userLimit;			// # of viewable remote participants limited by maxNumParticipants
				}
				break;
			}

		case ID_IN_SET8PARTICIAPANTLAYOUT:
			{
				/* Change the number of viewable participants to 8. It can be any value 0-16 */
				participantsLimit.maxNumParticipants = 8;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PARTICIPANTS_LIMIT, &participantsLimit, sizeof(participantsLimit)) != VIDYO_TRUE) 
					SetWindowText(hWnd, L"VidyoClient sample - Setting 8 participants failed");
				break;
			}

/*		case ID_INEVENTS_PARTICIPANTVIDEOMODE:
			{
				participantMode = !participantMode;
				participantVideoMode.videoMode = (participantMode) ?VIDYO_CLIENT_VIDEO_MODE_PINHIGH:VIDYO_CLIENT_VIDEO_MODE_PINLOW;
				strcpy_s(participantVideoMode.uri, URI_LEN, participantUri[0]);
				menuInfo.fState = (participantMode)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_INEVENTS_PARTICIPANTVIDEOMODE, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_PARTICIPANT_VIDEO_MODE, &participantVideoMode, sizeof(participantVideoMode)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - Setting participant video mode failed");
				break;
			} */


		case ID_COMMAND_PRIVACY:
			{
				/* Put the participant in privacy or come out of privacy */
				privacy.willMute = !privacy.willMute;
				menuInfo.fState = (privacy.willMute)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_COMMAND_PRIVACY, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO, &privacy, sizeof(privacy)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - Video mute/unmute failed");
				break;
			}

		case ID_COMMAND_SELFVIEW:
			{
				/* Toggle between different self view modes */
				switch(preview.previewMode)
				{
				case VIDYO_CLIENT_PREVIEW_MODE_NONE:
					/* if current mode is no preview, change it to PIP */
					{
						preview.previewMode = VIDYO_CLIENT_PREVIEW_MODE_PIP;
						menuInfo.fState = MFS_CHECKED;
					}
					break;

				case VIDYO_CLIENT_PREVIEW_MODE_PIP:
					/* if current mode is PIP, dock the user */
					{
						preview.previewMode = VIDYO_CLIENT_PREVIEW_MODE_DOCK;
						menuInfo.fState = MFS_CHECKED;
					}
					break;

				case VIDYO_CLIENT_PREVIEW_MODE_DOCK:
					/* if current mode is docked, change it to no preview */
					{
						preview.previewMode = VIDYO_CLIENT_PREVIEW_MODE_NONE;
						menuInfo.fState = MFS_UNCHECKED;
					}
					break;
				}
				SetMenuItemInfo(hMenu,ID_COMMAND_SELFVIEW, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PREVIEW, &preview, sizeof(preview)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_PREVIEW failed");
				else
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_PREVIEW Sent");
			}
			break;

		case ID_COMMAND_MUTEMIC:
			{
				/* Set the microphone to mute/unmute */
				inEventMuteMic.willMute =!(inEventMuteMic.willMute);
				menuInfo.fState = (inEventMuteMic.willMute)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_COMMAND_MUTEMIC, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN, &inEventMuteMic, sizeof(inEventMuteMic)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN failed");
				break;
			}

		case ID_IN_DISPLAYLAYOUT:
			{
				/* Toggle between Preferred mode or Continuous presence mode */
				layout.numPreferred = !(layout.numPreferred);
				menuInfo.fState = (layout.numPreferred)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_IN_DISPLAYLAYOUT, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LAYOUT, &layout, sizeof(layout)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_LAYOUT failed");
				break;
			}

		case ID_IN_ECHO_DETECTION:
			{
				/* Toggle between echo detection on/off */
				echoDetect.willEnable = !(echoDetect.willEnable);
				menuInfo.fState = (echoDetect.willEnable)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_IN_ECHO_DETECTION, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_ECHO_DETECT, &echoDetect, sizeof(echoDetect)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_ECHO_DETECT failed");
				break;
			}

		case ID_IN_ECHO_CANCELLATION:
			{
				/* Toggle between echo cancellation on/off */
				echoCancel.willEnable = !(echoCancel.willEnable);
				menuInfo.fState = (echoCancel.willEnable)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_IN_ECHO_CANCELLATION, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_ECHO_CANCEL, &echoCancel, sizeof(echoCancel)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_ECHO_CANCEL failed");
				break;
			}

		case ID_IN_AUTOMATIC_GAIN_CONTROL:
			{
				/* Toggle between AGC on/off */
				agc.willEnable = !(agc.willEnable);
				menuInfo.fState = (agc.willEnable)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_IN_AUTOMATIC_GAIN_CONTROL, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_AUDIO_AGC, &agc, sizeof(agc)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_AUDIO_AGC failed");
				break;
			}

		case ID_PREFERENCES_BESTQUALITY:
			{
				/* Change the video preference mode to best quality */
				memset(&reqConfig, 0, sizeof(reqConfig));
				size_t x = sizeof(reqConfig);
				size_t y = sizeof(VidyoClientRequestConfiguration);
				SetWindowText(hWnd, L"VidyoClient sample - Size of Config Struct");
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				reqConfig.videoPreferences = videoPreference;					// initialized by default

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_BESTFRAMERATE:
			{
				/* Change the video preference mode to best framerate */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_FRAMERATE;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_BESTRESOLUTION:
			{
				/* Change the video preference mode to best resolution */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_RESOLUTION;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_LIMITEDBANDWIDTH:
			{
				/* Change the video preference mode to limited bandwidth */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_LIMITED_BANDWIDTH;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_ADVANCED450P30:
			{
				/* Change the video preference mode to advanced 450p30 */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_450p30;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_ADVANCED720P15:
			{
				/* Change the video preference mode to advanced 720p15 */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_720p15;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_ADVANCED720P30:
			{
				/* Change the video preference mode to advanced 720p30 */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_ADVANCED_720p30;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_PREFERENCES_ADVANCED1080P30:
			{
				/* Change the video preference mode to advanced 1080p30 */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				videoPreference = VIDYO_CLIENT_VIDEO_PREFERENCES_1080p30;
				reqConfig.videoPreferences = videoPreference;					

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
				break;
			}

		case ID_IN_MUTESPEAKER:
			{
				/* Toggle between speaker mute/unmute */
				inEventMuteSpeaker.willMute = !(inEventMuteSpeaker.willMute);
				menuInfo.fState = (inEventMuteSpeaker.willMute)?MFS_CHECKED:MFS_UNCHECKED;
				SetMenuItemInfo(hMenu,ID_IN_MUTESPEAKER, FALSE, &menuInfo);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_OUT, &inEventMuteSpeaker, sizeof(inEventMuteSpeaker)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_OUT failed");
				break;
			}

		case ID_COMMAND_GROUP_CHAT:
			{
				/* Read the chat message from the dialog box 
				The chat message is sent to all the participants of the conference */
				DialogBox(hInst, MAKEINTRESOURCE(IDD_OUTGOING_CHAT), hWnd, sendChat);
				strcpy_s(sendGroupChat.message, sizeof(sendGroupChat.message), outgoingChatMessage);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_GROUP_CHAT, &sendGroupChat, sizeof(sendGroupChat)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_GROUP_CHAT failed");
				memset(outgoingChatMessage, 0, MAX_CHAT_MESSAGE_LEN);
				break;
			}

		case ID_COMMAND_PRIVATE_CHAT:
			{
				/* Read the chat message from the dialog box */
				DialogBox(hInst, MAKEINTRESOURCE(IDD_OUTGOING_CHAT), hWnd, sendChat);

				/* Send the message as a private chat to each of the participants.
				If message is to be sent to only one of the participants, get the 
				display name of the receiver and query for his Scip URI */
				for (int i=0; i<numOfParticipants; i++) {
					if (strcmp(participantNames[i], userId)) {
						strcpy_s(sendPrivateChat.uri, URI_LEN, participantUri[i]);
						strcpy_s(sendPrivateChat.message, sizeof(sendPrivateChat.message), outgoingChatMessage);
						if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PRIVATE_CHAT, &sendPrivateChat, sizeof(sendPrivateChat)) != VIDYO_TRUE)
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_PRIVATE_CHAT failed");
						memset(&sendPrivateChat, 0, sizeof(VidyoClientInEventPrivateChat));
					}
				}
				break;			
			}

		case ID_INEVENTS_REMOTEDISPLAYNAME:
			{
				/* Get the name that needs to be displayed for the remote participant 
				Change the string to japanese, chinese, spanish, arabic as needed */
				strcpy_s(setDisplayName.displayName, sizeof(setDisplayName.displayName), kJapanese);
				strcpy_s(setDisplayName.uri, URI_LEN, participantUri[0]);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_DISPLAY_NAME, &setDisplayName, sizeof(setDisplayName)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_DISPLAY_NAME failed");
				break;
			}

		case ID_LAYOUT_RESETREMOTEDISPLAYNAME:
			{
				/* Reset the display name to the login name */
				VidyoClientInEventResetDisplayName resetDisplayName;
				strcpy_s(resetDisplayName.uri, URI_LEN, participantUri[0]);
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESET_DISPLAY_NAME, &resetDisplayName, sizeof(resetDisplayName)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_RESET_DISPLAY_NAME failed");
				break;
			}

		case ID_LAYOUT_SETLABEL:
			{
				/* Change the display name for self when self-view is enabled 
				Change the string to japanese, chinese, spanish, arabic as needed */
				VidyoClientRequestSetLabel setLabel;
				setLabel.labelID = VIDYO_CLIENT_LABEL_SELF_VIEW;
				strcpy_s(setLabel.labelText, MAX_LABEL_STRING_SIZE, kJapanese);
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_LABEL, &setLabel, sizeof(setLabel)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_LABEL failed");
				break;
			}

		case ID_COMMAND_LEAVECONFERENCE:
			{
				//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO, NULL, 0);

				/* Leave the conference */
				preview.previewMode = VIDYO_CLIENT_PREVIEW_MODE_NONE;
				privacy.willMute = FALSE;
				microphoneMute.isMuted = FALSE;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE, NULL, 0) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_LEAVE failed");
				
				//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO, NULL, 0);

				Sleep(50);
				VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_DECLINE, NULL, NULL);
				VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CANCEL, NULL, NULL);

				break;
			}

		case ID_SENDREQUESTS_GETCONFIGURATION:
			{
				/* Do a Get Configuration */
				memset(&reqConfig, 0, sizeof(reqConfig));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");
				break;
			}

		case ID_SETBANDWIDTH_768KBPS:
			{
				/* Change the max send bandwidth on client to 768 Kbps */
				setBandwidth.sendBandwidth = 7;
				setBandwidth.sLayers = 2;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH, &setBandwidth, sizeof(setBandwidth)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH failed");
				break;
			}

		case ID_SETBANDWIDTH_1:
			{
				/* Change the max send bandwidth on client to 1 Kbps */
				setBandwidth.sendBandwidth = 1;
				setBandwidth.sLayers = 2;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH, &setBandwidth, sizeof(setBandwidth)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH failed");
				break;
			}

		case ID_SETBANDWIDTH_2:
			{
				/* Change the max send bandwidth on client to 2 Kbps */
				setBandwidth.sendBandwidth = 2;
				setBandwidth.sLayers = 3;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH, &setBandwidth, sizeof(setBandwidth)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH failed");
				break;
			}

		case ID_SETBANDWIDTH_3:
			{
				/* Change the max send bandwidth on client to 3 Kbps */
				setBandwidth.sendBandwidth = 3;
				setBandwidth.sLayers = 3;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH, &setBandwidth, sizeof(setBandwidth)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH failed");
				break;
			}

		case ID_SETBANDWIDTH_4MBPS:
			{
				/* Change the max send bandwidth on client to 4 Kbps */
				setBandwidth.sendBandwidth = 4;
				setBandwidth.sLayers = 3;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH, &setBandwidth, sizeof(setBandwidth)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH failed");
				break;
			}

		case ID_SETBANDWIDTH_6MBPS:
			{
				/* Change the max send bandwidth on client to 6 Kbps */
				setBandwidth.sendBandwidth = 6;
				setBandwidth.sLayers = 3;
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH, &setBandwidth, sizeof(setBandwidth)) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SET_SEND_BANDWIDTH failed");
				break;
			}

		case ID_SENDREQUESTS_GETAUDIOIN:
			{
				/* Inquire level of audio input (capture/microphone) device */
				VidyoUint gainLevel;
				memset(&requestVolume, 0, sizeof(requestVolume));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_IN, &requestVolume, sizeof(requestVolume)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_IN failed");
				gainLevel = requestVolume.volume;
				break;
			}

		case ID_SENDREQUESTS_SETAUDIOIN:
			{
				/* set the gain level of the microphone */
				memset(&requestVolume, 0, sizeof(requestVolume));
				requestVolume.volume = 15000;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_IN, &requestVolume, sizeof(requestVolume)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_IN failed");
				break;
			}

		case ID_SENDREQUESTS_GETAUDIOOUT:
			{
				/* Inquire volume of audio output (playback/speaker) device */
				VidyoUint volumeLevel;
				memset(&requestVolume, 0, sizeof(requestVolume));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT, &requestVolume, sizeof(requestVolume)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT failed");
				volumeLevel = requestVolume.volume;
				break;
			}

		case ID_SENDREQUESTS_SETAUDIOOUT:
			{
				/* Inquire volume of audio output (playback/speaker) device */
				VidyoUint level;
				memset(&requestVolume, 0, sizeof(requestVolume));
				requestVolume.volume = 30000;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_OUT, &requestVolume, sizeof(requestVolume)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_OUT failed");
				memset(&requestVolume, 0, sizeof(requestVolume));
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT, &requestVolume, sizeof(requestVolume)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT failed");
				level = requestVolume.volume;
				break;

			}

		case ID_SENDREQUESTS_GETSTATISTICS:
			{
				/* Enable statistics before doing a get Statistics because of a known bug */
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_STATISTICS_ENABLE, NULL, 0) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_STATISTICS_ENABLE failed");

				/* Get the participant statistics, we are looking for URI  */
				char titleMessage[USERID_SIZE]={0}, displayStats[10][5000]={0}, strTemp[5000]={0};
				char audio[50]={0}, video[50]={0}, height[10]={0}, width[10]={0}, framerate[50]={0};
				char decodedfps[50] ={0}, displayedfps[50]={0}, finalStats[5000]={0};
				memset(&getParticipantInfo, 0, sizeof(getParticipantInfo));
				memset(&participantStats, 0, sizeof(participantStats));
				memset(&stats, 0, sizeof(stats));
				int i=0;

				 /*if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST, &stats, sizeof(stats)) != VIDYO_FALSE) {
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST failed.");
				} else {
					participantStats = stats.statistics[0];
					sprintf(displayStats[0], "\nParticipant URI is %s ", participantStats.uri);
					strcat(displayStats[0], "\nParticipant display name is \t");
					strcat(displayStats[0], participantStats.name);
					strcat(displayStats[0], "\nParticipant received audio is \t");
					sprintf(audio, "%d", participantStats.audioKBitsPerSecRecv);
					strcat(displayStats[0], audio);
					strcat(displayStats[0], "\nParticipant received video is \t");
					sprintf(video, "%d", participantStats.videoKBitsPerSecRecv);
					strcat(displayStats[0], video);
					strcat(displayStats[0], "\nParticipant receive resolution is \t");
					sprintf(width, "%d", participantStats.videoResolution.width);
					strcat(displayStats[0], width);
					strcat(displayStats[0], " X ");
					sprintf(height, "%d", participantStats.videoResolution.height);
					strcat(displayStats[0], height);
					strcat(displayStats[0], "\nParticipant received framerate is \t");
					sprintf(framerate, "%d", participantStats.videoFrameRate);
					strcat(displayStats[0], framerate);
					strcpy(finalStats, displayStats[0]);
				}*/

				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT, &statsAt, sizeof(statsAt)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT failed");	
				
				//if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_INFO, &getParticipantInfo, sizeof(getParticipantInfo)) != VIDYO_FALSE)
				//	SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_INFO failed");	
				
				// Using VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_INFO
				/*for (i=0; i<getParticipantInfo.numberParticipants; i++) {
					/* clean up all the values 
					memset(audio, 0, 50); memset(video, 0, 50); memset(height, 0, 10); memset(framerate, 0, 10); 
					memset(width, 0, 10); memset(decodedfps, 0, 50); memset(displayedfps, 0, 50);
					sprintf(displayStats[i], "\nParticipant URI is %s ", getParticipantInfo.URI[i]);
					strcat(displayStats[i], "\nParticipant display name is \t");
					strcat(displayStats[i], getParticipantInfo.Name[i]);
					strcat(displayStats[i], "\nParticipant received audio is \t");
					sprintf(audio, "%d", ((getParticipantInfo.receivedBytesAudio[i] * 8) % 1024));
					strcat(displayStats[i], audio);
					strcat(displayStats[i], "\nParticipant received video is \t");
					sprintf(video, "%d", ((getParticipantInfo.receivedBytesVideo[i] * 8) % 1024));
					strcat(displayStats[i], video);
					strcat(displayStats[i], "\nParticipant receive resolution is \t");
					sprintf(width, "%d", getParticipantInfo.receivedWidth[i]);
					strcat(displayStats[i], width);
					strcat(displayStats[i], " X ");
					sprintf(height, "%d", getParticipantInfo.receivedHeight[i]);
					strcat(displayStats[i], height);
					strcat(displayStats[i], "\nParticipant received framerate is \t");
					sprintf(framerate, "%d", getParticipantInfo.receivedFrameRate[i]);
					strcat(displayStats[i], framerate);
					strcat(displayStats[i], "\nParticipant decoded framerate is \t");
					sprintf(decodedfps, "%d", getParticipantInfo.decodedFrameRate[i]);
					strcat(displayStats[i], decodedfps);
					strcat(displayStats[i], "\nParticipant rendered framerate is \t");
					sprintf(displayedfps, "%d", getParticipantInfo.displayedFrameRate[i]);
					strcat(displayStats[i], displayedfps);
					strcat(displayStats[i], "\n");
					strcat(finalStats, displayStats[i]);
				} */
			 
			
				// Using VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_AT
				sprintf(displayStats[0], "\nParticipant URI is %s ", statsAt.uri);
				strcat(displayStats[0], "\nParticipant display name is \t");
				strcat(displayStats[0], statsAt.name);
				strcat(displayStats[0], "\nParticipant received audio is \t");
				sprintf(audio, "%d", statsAt.audioKBitsPerSecRecv);
				strcat(displayStats[0], audio);
				strcat(displayStats[0], "\nParticipant received video is \t");
				sprintf(video, "%d", statsAt.videoKBitsPerSecRecv);
				strcat(displayStats[0], video);
				strcat(displayStats[0], "\nParticipant receive resolution is \t");
				sprintf(width, "%d", statsAt.videoResolution.width);
				strcat(displayStats[0], width);
				strcat(displayStats[0], " X ");
				sprintf(height, "%d", statsAt.videoResolution.height);
				strcat(displayStats[0], height);
				strcat(displayStats[0], "\nParticipant received framerate is \t");
				sprintf(framerate, "%d", statsAt.videoFrameRate);
				strcat(displayStats[0], framerate);
				strcpy(finalStats, displayStats[0]);

				MultiByteToWideChar(CP_UTF8, 0, (LPSTR)"Display Statistics", -1, (LPWSTR)titleMessage, USERID_SIZE);
				MultiByteToWideChar(CP_UTF8, 0, (LPSTR)finalStats, -1, (LPWSTR)strTemp, sizeof(strTemp));
				MessageBox(hWnd, (LPCWSTR)strTemp, (LPCWSTR)titleMessage, MB_OK);
				break;
			}

		case ID_GETSENDBANDWIDTH:
			{
				VidyoInt kbpsValue = 0, resultKbps = 0;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_SEND_MAX_KBPS, &kbpsValue, sizeof(kbpsValue)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_SEND_MAX_KBPS failed ");
				resultKbps = kbpsValue;
				break;
			}

		case ID_SETSENDBANDWIDTH:
			{
				VidyoInt kbpsValue = 350;
				if(VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_SEND_MAX_KBPS, &kbpsValue, sizeof(kbpsValue)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_SEND_MAX_KBPS failed ");
				/* Do a Get again to check if the value has been set properly */
				kbpsValue = 0;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_SEND_MAX_KBPS, &kbpsValue, sizeof(kbpsValue)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_SEND_MAX_KBPS failed ");
				break;
			}

		case ID_GETRECEIVEBANDWIDTH:
			{
				VidyoInt kbpsValue = 0;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_RECV_MAX_KBPS, &kbpsValue, sizeof(kbpsValue)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_RECV_MAX_KBPS failed ");
				break;
			}

		case ID_SETRECEIVEBANDWIDTH:
			{
				VidyoInt kbpsValue = 350;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_RECV_MAX_KBPS, &kbpsValue, sizeof(kbpsValue)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_RECV_MAX_KBPS failed ");
				/* Do a Get again to check if the value has been set properly */
				kbpsValue = 0;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_RECV_MAX_KBPS, &kbpsValue, sizeof(kbpsValue)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_RECV_MAX_KBPS failed ");
				break;
			}

		case ID_INEVENTS_SETUPCAMERA:
			{
				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SETUP_CAMERA, NULL, 0) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_SETUP_CAMERA failed");
				break;
			}
		case ID_WATCHSELF_START:
			if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW, NULL, 0) != VIDYO_TRUE){
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW failed");
			}else{
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW sent");
			}
			break;
		case ID_WATCHSELF_STOP:
			if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_SELF_VIEW, NULL, 0) != VIDYO_TRUE){
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_SELF_VIEW failed");
			}else{
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_SELF_VIEW sent");
			}
			break;

		case ID_PRECALLTESTCAMERA_START:
			preCallTest.action = VidyoClientPrecallDeviceTestAction::VIDYO_CLIENT_DEVICE_TEST_START;
			if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA, &preCallTest, sizeof(preCallTest)) != VIDYO_TRUE) {
				SetWindowText(hWnd, L"VidyoClient sample - Sending PreCall Test Start failed");
			}else{
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA sent");
			}
			break;
		case ID_PRECALLTESTCAMERA_STOP:
			preCallTest.action = VidyoClientPrecallDeviceTestAction::VIDYO_CLIENT_DEVICE_TEST_STOP;
			if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PRECALL_TEST_CAMERA, &preCallTest, sizeof(preCallTest)) != VIDYO_TRUE) {
				SetWindowText(hWnd, L"VidyoClient sample - Sending PreCall Test Stop failed");
			}
			break;
		case ID_GETWINDOWSHARES:
			{
				memset(&windowShares, 0, sizeof(windowShares));
				VidyoInt newApp=0, numApp=0, currApp=0, i=0;
				VidyoClientWindowShareRequestType type = { LIST_SHARING_WINDOWS };
				windowShares.requestType = type;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, &windowShares, sizeof(windowShares)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES failed");
				currApp = windowShares.shareList.currApp;
				numApp = windowShares.shareList.numApp;
				numApp += 1; // Valid application names/URIs are filled from index 1 and 0th index is not used.
				newApp = windowShares.shareList.newApp;
				for (i=1; i<numApp; i++) {
					strcpy_s(remoteAppUri[i], MAX_URI_LEN, windowShares.shareList.remoteAppUri[i]);
					strcpy_s(remoteAppname[i], MAX_URI_LEN, windowShares.shareList.remoteAppName[i]);
				}
				strcpy_s(eventUri, MAX_URI_LEN, windowShares.shareList.eventUri);
				windowShares.shareList.newApp+=1; // increment this to start viewing the share using VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES
				break;
			}

		case ID_STARTWINDOWSHARE:
			{
				VidyoClientWindowShareRequestType type = { CHANGE_SHARING_WINDOW };
				windowShares.requestType = type;
				if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, &windowShares, sizeof(windowShares)) != VIDYO_FALSE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES failed ");
				break;
			}
		case ID_SETWATCHFORMAT_I420:
			watch.format = LMI_MEDIAFORMAT_I420;
			if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT, &watch, sizeof(watch)) != VIDYO_FALSE)
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT failed ");
			else
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT Set to I420 ");
			break;
		case ID_SETWATCHFORMAT_YU12:
			watch.format = LMI_MEDIAFORMAT_YU12;
			if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT, &watch, sizeof(watch)) != VIDYO_FALSE)
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT failed ");
			else
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT Set to YU12 ");
			break;
		case ID_SETWATCHFORMAT_ARGB:
			watch.format = LMI_MEDIAFORMAT_ARGB;
			if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT, &watch, sizeof(watch)) != VIDYO_FALSE)
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT failed ");
			else
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_WATCH_VIDEO_FRAME_FORMAT Set to ARGB ");
			break;
		case ID_GETWATCHFORMAT:
			if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT, &watch, sizeof(watch)) != VIDYO_FALSE)
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT failed ");
			else{
				if (watch.format==LMI_MEDIAFORMAT_ARGB)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT: ARGB");
				else if (watch.format==LMI_MEDIAFORMAT_YU12)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT: YU12");
				else if (watch.format==LMI_MEDIAFORMAT_I420)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_WATCH_VIDEO_FRAME_FORMAT: I420");
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		//InvalidateRect(hWnd,NULL,TRUE);
		{
			/* Resize the rendering window */
			VidyoClientInEventResize resize;
			resize.x=0;
			resize.y=0;
			resize.height=HIWORD(lParam);
			resize.width=LOWORD(lParam);
			if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESIZE, &resize, sizeof(resize)) != VIDYO_TRUE)
				SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_RESIZE failed ");
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;

	case WM_USER:
		{
			EventData* event_data = (EventData*)wParam;
			if (event_data)
			{
				if (event_data->data != NULL)
				{
					ConferenceData *confData = (ConferenceData *)event_data->data;
					switch (event_data->actionType)
					{


					case VIDYO_CLIENT_OUT_EVENT_SIGN_IN:
						/* First event that is received by the client after Login is sent */
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_SIGN_IN received");
							VidyoClientOutEventSignIn *outEventSignIn;
							outEventSignIn = (VidyoClientOutEventSignIn *)event_data->data;
							VidyoUint activeEid;
							activeEid = outEventSignIn->activeEid;
							// If Endpoint ID is 0, licensing issue
							if (!activeEid) {
								if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0) != VIDYO_TRUE)
									SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_LICENSE failed");
							}
							EnableMenuItem(GetMenu(hWnd), ID_PRE_SIGNOUT, MF_ENABLED); 

							//VidyoClientPrivateSoapInEventGetPortalFeatures features;
							//features.typeRequest = VIDYO_CLIENT_PRIVATE_SOAP_GET_PORTALFEATURES;
							//features.requestId = 1;

							//VidyoClientSendEvent((VidyoClientInEvent)VIDYO_CLIENT_PRIVATE_IN_EVENT_VCSOAP, 
							//					  &features, 
							//					  sizeof(VidyoClientPrivateSoapInEventGetPortalFeatures));

							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_LOGIN:
						/* Out event received when login is succesful */
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_LOGIN received");
							VidyoClientOutEventLogIn *outEventLogIn;
							outEventLogIn = (VidyoClientOutEventLogIn *)event_data->data;
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED:
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED received");

							/* Enable show participant name and other configurable parameters before Signin */
							if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_CONFIGURATION failed");

							reqConfig.enableAutoLogIn = VIDYO_FALSE;
							reqConfig.enableFeccController = VIDYO_TRUE;			// enable FECC controlling
							reqConfig.enableAutoAnswer = VIDYO_FALSE;				// disable auto answer
							reqConfig.enableRendering = VIDYO_FALSE;					// enable rendering
							reqConfig.enableLogging = VIDYO_TRUE;					// enable logging
							reqConfig.enableEchoDetection = VIDYO_TRUE;				// enable echo detection
							reqConfig.enableEchoCancellation = VIDYO_TRUE;			// enable echo cancellation

							/* Do a VIDYO_CLIENT_REQUEST_SET_CONFIGURATION with the above values changed. */
							if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &reqConfig, sizeof(reqConfig)) != VIDYO_FALSE)
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_SET_CONFIGURATION failed");
	
							VidyoClientInEventPreview eventPreview;	
							eventPreview.previewMode = VidyoClientPreviewMode::VIDYO_CLIENT_PREVIEW_MODE_PIP;
							VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PREVIEW, &eventPreview, sizeof(eventPreview));

							/*
							// Send the Login event 
							memset(&roomLink,0, sizeof(roomLink));
							strcpy(roomLink.displayName, "Guest");
							strcpy(roomLink.portalUri,"http:\/\/david.sandboxga.vidyo.com");
							strcpy(roomLink.roomKey,"3dVyymuzy8T08mE28Z1JHUA5Poc");
							if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &logInParams, sizeof(logInParams)) != VIDYO_TRUE) {
								SetWindowText(hWnd, L"VidyoClient sample - Sending Guest Link failed");
							}
							*/
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_LINKED:
						/* Out event received when Linkendpoint is successful with VM */
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_LINKED received");
							VidyoClientOutEventLinked *outEventLinked;
							outEventLinked = (VidyoClientOutEventLinked *)event_data->data;
							VidyoUint errorCode;
							errorCode = outEventLinked->error;
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_SIGNED_IN:
						/* Out event received when user is signed in successfully */
						{  
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_SIGNED_IN received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_SIGN_OUT:
						/* Out event received when library receives a sign out in event from application */
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_SIGN_OUT received");
							EnableMenuItem(GetMenu(hWnd), ID_PRE_SIGNOUT, MF_DISABLED);
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT:
						/* Out event when user sign out is successful */
						{
							VidyoClientOutEventSignedOut *outEventSignedOut;
							outEventSignedOut = (VidyoClientOutEventSignedOut *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MOUSE_DOWN:
						{
							VidyoUint button, count, xPos, yPos;
							VidyoClientOutEventMouse *mouseEvent;
							mouseEvent = (VidyoClientOutEventMouse *)event_data->data;
							//SetWindowText(hWnd, L"VidyoClient sample - Received a mouse down event");
							button = mouseEvent->button;
							count = mouseEvent->count;
							xPos = mouseEvent->xPos;
							yPos = mouseEvent->yPos;
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MOUSE_MOVE:
						{
							VidyoUint button2, count2, x1Pos, y1Pos;
							VidyoClientOutEventMouse *moveEvent;
							moveEvent = (VidyoClientOutEventMouse *)event_data->data;
							//SetWindowText(hWnd, L"VidyoClient sample - Received a mouse move event");
							button2 = moveEvent->button;
							count2 = moveEvent->count;
							x1Pos = moveEvent->xPos;
							y1Pos = moveEvent->yPos;
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED:
						{
							VidyoClientOutEventDeviceSelectionChanged *OutEventDeviceSelectionChanged;
							OutEventDeviceSelectionChanged = (VidyoClientOutEventDeviceSelectionChanged *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN:
						{
							VidyoClientOutEventMuted *OutEventMutedIn;
							OutEventMutedIn = (VidyoClientOutEventMuted *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT:
						{
							VidyoClientOutEventMuted *OutEventMutedOut;
							OutEventMutedOut = (VidyoClientOutEventMuted *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_PREVIEW:
						{
							VidyoClientOutEventPreview *outEventPreview;
							outEventPreview = (VidyoClientOutEventPreview *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_PREVIEW received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO:
						{
							VidyoClientOutEventMuted *OutEventMutedVideo;
							OutEventMutedVideo = (VidyoClientOutEventMuted *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN:
						/* Indicate change of mute state of audio input (capture/microphone) device, due to server */
						{
							VidyoClientOutEventMuted *OutEventMutedServerAudioIn;
							OutEventMutedServerAudioIn = (VidyoClientOutEventMuted *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO:
						/* Indicate change of privacy state of video (capture/camera) device, due to server */
						{
							VidyoClientOutEventMuted *OutEventMutedServerVideo;
							OutEventMutedServerVideo = (VidyoClientOutEventMuted *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL:
						/* Server-based media control command details against a media device type */
						{
							VidyoClientOutEventMediaControl *OutEventMediaControl;
							OutEventMediaControl = (VidyoClientOutEventMediaControl *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_LICENSE:
						/* Report licensing on Portal succes/error */
						{
							VidyoClientOutEventLicense *OutEventLicense;
							OutEventLicense = (VidyoClientOutEventLicense *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_LICENSE received ");
							break;
						}


					case VIDYO_CLIENT_OUT_EVENT_CALL_STATE:
						{
							VidyoClientOutEventCallState *OutEventCallState;
							OutEventCallState = (VidyoClientOutEventCallState *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_CALL_STATE received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_SHARE_CLOSED:
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_SHARE_CLOSED received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_RESIZE:
						{
							VidyoClientOutEventResize *OutEventResize;
							OutEventResize = (VidyoClientOutEventResize *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_RESIZE received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_ECHO_DETECTED:
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_ECHO_DETECTED received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_KEYDOWN:
						{
							VidyoClientOutEventKeyboard *OutEventKeyDown;
							OutEventKeyDown = (VidyoClientOutEventKeyboard *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_KEYDOWN received");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_KEYUP:
						{
							VidyoClientOutEventKeyboard *OutEventKeyUp;
							OutEventKeyUp = (VidyoClientOutEventKeyboard *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_KEYUP received ");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL:
						{
							VidyoUint button_t1, count_t1, xPos_t1, yPos_t1;
							VidyoClientOutEventMouse *mouseEvent_t1;
							mouseEvent_t1 = (VidyoClientOutEventMouse *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL received ");
							button_t1 = mouseEvent_t1->button;
							count_t1 = mouseEvent_t1->count;
							xPos_t1 = mouseEvent_t1->xPos;
							yPos_t1 = mouseEvent_t1->yPos;
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_GROUP_CHAT:
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_GROUP_CHAT received ");
							char titleMessageGroup[USERID_SIZE];
							MultiByteToWideChar(CP_UTF8, 0, (LPSTR)"Incoming chat message", -1, (LPWSTR)titleMessageGroup, USERID_SIZE);
							outEventGroupChat = (VidyoClientOutEventGroupChat *)event_data->data;
							MultiByteToWideChar(CP_UTF8, 0, (LPSTR)outEventGroupChat->message, -1, (LPWSTR)incomingChatMessage, MAX_CHAT_MESSAGE_LEN);
							MessageBox(hWnd, (LPCWSTR)incomingChatMessage, (LPCWSTR)titleMessageGroup, MB_OK);
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_PRIVATE_CHAT:
						{
							SetWindowText(hWnd, L"VidyoClient sample - Received VIDYO_CLIENT_OUT_EVENT_PRIVATE_CHAT");
							VidyoClientOutEventPrivateChat *outEventPrivateChat;
							char titleMessage[USERID_SIZE];
							MultiByteToWideChar(CP_UTF8, 0, (LPSTR)"Incoming chat message", -1, (LPWSTR)titleMessage, USERID_SIZE);
							outEventPrivateChat = (VidyoClientOutEventPrivateChat *)event_data->data;
							MultiByteToWideChar(CP_UTF8, 0, (LPSTR)outEventPrivateChat->displayName, -1, (LPWSTR)chatSender, USERID_SIZE);
							MultiByteToWideChar(CP_UTF8, 0, (LPSTR)outEventPrivateChat->message, -1, (LPWSTR)incomingChatMessage, MAX_CHAT_MESSAGE_LEN);
							MessageBox(hWnd, (LPCWSTR)incomingChatMessage, (LPCWSTR)titleMessage, MB_OK);
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT:
						{
							VidyoClientOutEventParticipantsLimit *outLimit;
							outLimit = (VidyoClientOutEventParticipantsLimit *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - Received VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_FECC_LIST_UPDATED:
						{
							VidyoClientRequestFeccList requestFeccList = {0};
							if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_FECC_LIST, &requestFeccList, sizeof(requestFeccList)) != VIDYO_FALSE) {
								SetWindowText(hWnd, L"VidyoClient sample - SendReq for VIDYO_CLIENT_REQUEST_GET_FECC_LIST failed.");
							}else{
								if (requestFeccList.numberParticipants == 0) {
									SetWindowText(hWnd, L"VidyoClient sample - No FECC cameras.");
								}

								if (requestFeccList.numberParticipants > 0) {
									strcpy_s(panLeft.uri, sizeof(panLeft.uri), requestFeccList.uri[0]);
									strcpy_s(panRight.uri, sizeof(panRight.uri), requestFeccList.uri[0]);
									strcpy_s(tiltUp.uri, sizeof(tiltUp.uri), requestFeccList.uri[0]);
									strcpy_s(tiltDown.uri, sizeof(tiltDown.uri), requestFeccList.uri[0]);
									strcpy_s(zoomIn.uri, sizeof(zoomIn.uri), requestFeccList.uri[0]);
									strcpy_s(zoomOut.uri, sizeof(zoomOut.uri), requestFeccList.uri[0]);
									strcpy_s(stop.uri, sizeof(stop.uri), requestFeccList.uri[0]);
									strcpy_s(freeze.uri, sizeof(freeze.uri), requestFeccList.uri[0]);
									strcpy_s(unfreeze.uri, sizeof(unfreeze.uri), requestFeccList.uri[0]);
								}
							}
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL:
						{
							char titlemsg[USERID_SIZE], finalMsg[DISPLAY_CONFERENCE_SIZE], final[DISPLAY_CONFERENCE_SIZE];
							outEventincomingCall = (VidyoClientOutEventIncomingCall *)event_data->data;
							if (outEventincomingCall->onCallFlag != VIDYO_TRUE) {
								/* Call initiated by the Server */
								strcpy_s(finalMsg, 20, "From SERVER, Accept?"); 
								MultiByteToWideChar(CP_UTF8, 0, (LPSTR)"Incoming Call", -1, (LPWSTR)titlemsg, USERID_SIZE);
								MultiByteToWideChar(CP_UTF8, 0, (LPSTR)finalMsg, -1, (LPWSTR)final, DISPLAY_CONFERENCE_SIZE);
								if (MessageBox(hWnd, (LPCWSTR)final, (LPCWSTR)titlemsg, MB_YESNO) == IDYES) {
									/* Accept the incoming call */
									VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ANSWER, NULL, 0);
								} else {
									/* Reject the incoming call */
									VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_DECLINE, NULL, 0);
								}
							} else {
								/* Call initiated by another endpoint */
								strcpy_s(finalMsg, DISPLAY_CONFERENCE_SIZE, outEventincomingCall->invitingUser);
								strcat_s(finalMsg, 20, ", ACCEPT ?");
								MultiByteToWideChar(CP_UTF8, 0, (LPSTR)"Incoming Call from", -1, (LPWSTR)titlemsg, USERID_SIZE);
								MultiByteToWideChar(CP_UTF8, 0, (LPSTR)finalMsg, -1, (LPWSTR)final, DISPLAY_CONFERENCE_SIZE);
								if (MessageBox(hWnd, (LPCWSTR)final, (LPCWSTR)titlemsg, MB_YESNO) == IDYES) {
									/* Accept the incoming call */
									VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ANSWER, NULL, 0);
								} else {
									/* Reject the incoming call */
									VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_DECLINE, NULL, 0);
								}
							}
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
						{
							//CheckMenuItem(GetMenu(hWnd),ID_COMMAND_INCONFERENCE,MF_CHECKED);
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE received ");
							//Sleep(2000);
							VidyoClientInEventPreview eventPreview;	
							eventPreview.previewMode = VidyoClientPreviewMode::VIDYO_CLIENT_PREVIEW_MODE_PIP;
							VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PREVIEW, &eventPreview, sizeof(eventPreview));

                            
							if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW, NULL, 0) != VIDYO_TRUE){
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW failed");
							}else{
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW sent");
							}
                        
							

							//memset(&inEventShare, 0, sizeof(inEventShare));
                            //VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SHARE, &inEventShare, sizeof(inEventShare));

							VidyoUint volumeLevel2;
							memset(&requestVolume, 0, sizeof(requestVolume));
							if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT, &requestVolume, sizeof(requestVolume)) != VIDYO_FALSE)
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_VOLUME_AUDIO_OUT failed");
							volumeLevel2 = requestVolume.volume;

							/* Get the participant URIs */
							memset(&participantStats, 0, sizeof(participantStats));
							memset(&stats, 0, sizeof(stats));
							if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST, &stats, sizeof(stats)) != VIDYO_FALSE) {
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST failed.");
							} else {
								if (stats.numParticipants != 0) {
									numOfParticipants = stats.numParticipants;
									for (int i=0; i<numOfParticipants; i++) {
										participantStats = stats.statistics[i];
										strcpy_s(participantUri[i], URI_LEN, participantStats.uri);
										strcpy_s(participantNames[i], USERID_SIZE, participantStats.name);
										memset(&participantStats, 0, sizeof(participantStats));
									}
								} else {
									SetWindowText(hWnd, L"VidyoClient sample - Participants GET_PARTICIPANTS_STATISTICS_LIST=0 .");
								}
							}

							/*VidyoClientInEventSetDynamicWatchVideoSource dwSrc;
							memset(&dwSrc, NULL, sizeof(dwSrc));
			
							dwSrc.numParticipants = 4;
			
							dwSrc.dynamicViews[0].width = 1280;
							dwSrc.dynamicViews[0].height = 720;
							dwSrc.dynamicViews[0].maxFrameRate = 30;
			
							dwSrc.dynamicViews[1].width = 360;
							dwSrc.dynamicViews[1].height = 180;
							dwSrc.dynamicViews[1].maxFrameRate = 30;
			
							dwSrc.dynamicViews[2].width = 360;
							dwSrc.dynamicViews[2].height = 180;
							dwSrc.dynamicViews[2].maxFrameRate = 30;
			
							dwSrc.dynamicViews[3].width = 360;
							dwSrc.dynamicViews[3].height = 180;
							dwSrc.dynamicViews[3].maxFrameRate = 30;

							VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_DYNAMIC_WATCH_VIDEO_SOURCE, &dwSrc, sizeof(dwSrc));*/

							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED:
						{
							//CheckMenuItem(GetMenu(hWnd),ID_COMMAND_INCONFERENCE,MF_UNCHECKED);
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED received ");

							int i=0;
							while(i < 10)
							{
								VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO, NULL, 0);
								++i;
								Sleep(100);
							}

							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_ADDED:
						{
							static bool done=false;
							//if (done == true)
								break;

							VidyoClientOutEventRemoteSourceChanged *pEvent = (VidyoClientOutEventRemoteSourceChanged*)event_data->data;
							if (pEvent->sourceType != VIDYO_CLIENT_SOURCE_TYPE_VIDEO)
								break;

							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_ADDED received ");

							if (strncmp(pEvent->displayName, "Sample Guest",USERID_SIZE) == 0)
								break;

							VidyoClientInEventStartWatchVideoSource startWatch={0};
							strcpy(startWatch.source.participantURI, pEvent->participantURI);
							startWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
							startWatch.source.sourceId = 0;
							startWatch.frameRate = 30;
							startWatch.height = 360;
							startWatch.width = 640;
							startWatch.minFrameInterval = 0;
							startWatch.watchData = NULL;

							if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &startWatch, sizeof(startWatch)) != VIDYO_TRUE){
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE (Video) failed");
                            }else{
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE (Video) sent");
                            }

							startWatch.frameRate = 0;
							startWatch.height = 0;
							startWatch.width = 0;

							VIDYO_CLIENT_LOG_INFO_FORMATTED("Static Watch started for: [%s]", pEvent->displayName);
							done = true;
						}
						break;

					case VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_REMOVED:
						{
							VidyoClientOutEventRemoteSourceChanged *pEvent = (VidyoClientOutEventRemoteSourceChanged*)event_data->data;
							if (pEvent->sourceType != VIDYO_CLIENT_SOURCE_TYPE_VIDEO)
								break;

							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_REMOVED received ");

							VidyoClientInEventStopWatchVideoSource stopWatch = {0};
							strcpy(stopWatch.source.participantURI, pEvent->participantURI);
							stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;

							if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &stopWatch, sizeof(stopWatch)) != VIDYO_TRUE){
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Video) failed");
                            }else{
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Video) sent");
                            }
						}
						break;

					case VIDYO_CLIENT_OUT_EVENT_ADD_SHARE:
						{
							VidyoClientOutEventAddShare *pEvent = (VidyoClientOutEventAddShare *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_ADD_SHARE received ");

							VidyoClientRequestWindowShares request;
							memset(&request, 0, sizeof(request));
							request.requestType = CHANGE_SHARING_WINDOW;
							strncpy(request.shareList.remoteAppUri[0], pEvent->URI, MAX_URI_LEN);
							strncpy(request.shareList.remoteAppName[0], "Share", MAX_URI_LEN);
						    request.shareList.numApp = 1;
							request.shareList.currApp = 1;
							//strncpy(request.shareList.eventUri, "", MAX_URI_LEN);
							request.shareList.newApp = 1;

							VidyoUint result = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, &request, sizeof(request));
							if (result != VIDYO_CLIENT_ERROR_OK) {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES failed");
							} else {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES sent");
							}

							VidyoClientInEventStartWatchVideoSource startWatch={0};
							strcpy(startWatch.source.participantURI, pEvent->URI);
							startWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_APPLICATION;
							startWatch.source.sourceId = 0;
							startWatch.frameRate = 30;
							startWatch.height = 720;
							startWatch.width = 1280;
							startWatch.minFrameInterval = 0;
							startWatch.watchData = NULL;

							if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &startWatch, sizeof(startWatch)) != VIDYO_TRUE){
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE (Application) failed");
                            }else{
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE (Application) sent");
                            }
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE:
						{
							VidyoClientOutEventRemoveShare *pEvent = (VidyoClientOutEventRemoveShare *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE received");
							
							VidyoClientRequestWindowShares request;
							memset(&request, 0, sizeof(request));
							request.requestType = CHANGE_SHARING_WINDOW;
							strncpy(request.shareList.remoteAppUri[0], pEvent->URI, MAX_URI_LEN);
							strncpy(request.shareList.remoteAppName[0], "Share", MAX_URI_LEN);
						    request.shareList.numApp = 0;
							request.shareList.currApp = 0;
							//strncpy(request.shareList.eventUri, "", MAX_URI_LEN);
							request.shareList.newApp = 0;

							VidyoUint result = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, &request, sizeof(request));
							if (result != VIDYO_CLIENT_ERROR_OK) {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES failed");
							} else {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES sent");
							}

							VidyoClientInEventStopWatchVideoSource stopWatch = {0};
							strcpy(stopWatch.source.participantURI, pEvent->URI);
							stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_APPLICATION;

							/*if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &stopWatch, sizeof(stopWatch)) != VIDYO_TRUE){
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Application) failed");
                            }else{
                                SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Application) sent");
                            }*/
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED:
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED received ");
							VidyoClientOutEventParticipantsChanged *OutEventParticipantsChanged = (VidyoClientOutEventParticipantsChanged *)event_data->data;
														
							VidyoClientRequestParticipantDetailsAt details= {0};
							details.index = (OutEventParticipantsChanged->participantCount - 1);
							VidyoUint error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT, &details, sizeof(VidyoClientRequestParticipantDetailsAt));

							
							//if (details.details.participantType==VidyoClientPrivateParticipantType::VidyoClientPrivateParticipantTypeGuest){
							//	SetWindowText(hWnd, L"VidyoClient sample - Guest Participant Joined");
							//}else if (details.details.participantType==VidyoClientPrivateParticipantType::VidyoClientPrivateParticipantTypeLegacy){
							//	SetWindowText(hWnd, L"VidyoClient sample - Legacy Participant Joined");
							//}else if (details.details.participantType==VidyoClientPrivateParticipantType::VidyoClientPrivateParticipantTypeNone){
							//	SetWindowText(hWnd, L"VidyoClient sample - None Participant Type Joined");
							//}

							
							if (OutEventParticipantsChanged->participantCount>1){
								
                                if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants)) == VIDYO_CLIENT_ERROR_OK){
									strcpy(watchSource.source.participantURI, reqParticipants.URI[OutEventParticipantsChanged->participantCount-1]);
									watchSource.source.mediaType = VidyoClientMediaControlType::VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
									watchSource.source.sourceId = 0;
									watchSource.frameRate = 15;
									watchSource.height = 720;
									watchSource.width = 1280;
									watchSource.minFrameInterval = 0;
									watchSource.watchData = NULL;
									if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE, &watchSource, sizeof(watchSource)) != VIDYO_TRUE){
                                        SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE failed");
                                    }else{
                                        SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_VIDEO_SOURCE sent");
                                    }
                                }
                                //memset(&inEventShare, 0, sizeof(inEventShare));
                                //VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SHARE, &inEventShare, sizeof(inEventShare));
								
                            }else{
                                VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_UNSHARE, NULL, 0);
                            }
							
							break;
						}
					case VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE:
						VidyoClientOutEventPrecallTestDevice *precallDevice;
                        precallDevice = (VidyoClientOutEventPrecallTestDevice *)event_data->data;
						if (precallDevice->action == VidyoClientPrecallDeviceTestAction::VIDYO_CLIENT_DEVICE_TEST_START){
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE [started] received ");
						}else{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE [stopped] received ");
						}
						break;

					}


				}
				free(event_data);
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Message handler for Guest Signin box.
INT_PTR CALLBACK GuestSignin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    char *strPtr;
    char strTemp[1000]={0};
    char strParse[1000]={0};
    VidyoClientInEventSignIn signInEvent = {0};
	VidyoClientRequestGetEid eid = {0};

/*
    char vmIdentity[VIDYO_MANAGER_ID_SIZE];
    char serverAddress[SIGNIN_SERVERADDRESS_SIZE];
    char serverPort[SIGNIN_SERVERPORT_SIZE];
    char userName[SIGNIN_USERNAME_SIZE];
    char portalAccessKey[SIGNIN_PORTAL_ACCESS_KEY_SIZE];
    char portalAddress[SIGNIN_PORTALADDRESS_SIZE];

    char locationTag[ENDPOINT_LOCATION_TAG_SIZE];
    VidyoClientProxyType proxyType;
    char vidyoProxyAddress[SIGNIN_VIDYO_PROXY_NUMBER][SIGNIN_VIDYO_PROXY_ADDRESS_SIZE];
    char vidyoProxyPort[SIGNIN_VIDYO_PROXY_NUMBER][SIGNIN_VIDYO_PROXY_PORT_SIZE];
    VidyoUint numberProxies;

    VidyoUint emcpSecured;
    VidyoBool guestLogin;
    VidyoUint guestId;
*/

     switch (message)
    {
        case WM_INITDIALOG:

			VidyoClientSendRequest(VidyoClientRequest::VIDYO_CLIENT_REQUEST_GET_EID, &eid, sizeof(VidyoClientRequestGetEid));
			MultiByteToWideChar(CP_UTF8, 0, (LPSTR)eid.EID, -1, (LPWSTR)strTemp, sizeof(strTemp));
			SetDlgItemText(hDlg, IDC_EDIT_GUEST_EID, (LPWSTR)strTemp);
            return (INT_PTR)TRUE;

        case WM_COMMAND:


            if (LOWORD(wParam) == IDCANCEL_GUEST_SIGNIN)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            if (LOWORD(wParam) == IDOK_GUEST_SIGNIN)
            {
				
                GetDlgItemText(hDlg, IDC_EDIT_GUEST_UN, (LPWSTR)&strTemp, SIGNIN_USERNAME_SIZE);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&signInEvent.userName, SIGNIN_USERNAME_SIZE, NULL, NULL);

                GetDlgItemText(hDlg, IDC_EDIT_GUEST_PAK, (LPWSTR)&strTemp, SIGNIN_PORTAL_ACCESS_KEY_SIZE);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&signInEvent.portalAccessKey, SIGNIN_PORTAL_ACCESS_KEY_SIZE, NULL, NULL);

                GetDlgItemText(hDlg, IDC_EDIT_GUEST_PORTAL, (LPWSTR)&strTemp, SIGNIN_PORTALADDRESS_SIZE);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&signInEvent.portalAddress, SIGNIN_PORTALADDRESS_SIZE, NULL, NULL);

                GetDlgItemText(hDlg, IDC_LOGINRESPONSE, (LPWSTR)&strTemp, 1000);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&strParse, 1000, NULL, NULL);

                GetDlgItemText(hDlg, IDC_EDIT_GUEST_VMADDRESS, (LPWSTR)&strTemp, 1000);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&strParse, 1000, NULL, NULL);
                //GKZGKCAH74NGG8XK2AKSCJZVXQDHRFPXQX6NM8RWA6AU400VM0001@ca2-m1-vp.vidyo.com:17992;transport=TLS
                strPtr = strtok(strParse,"@:;");
                strcpy(signInEvent.vmIdentity, strPtr);
				strPtr = strtok(NULL,"@:;");
				strcpy(signInEvent.serverAddress, strPtr);
                strPtr = strtok(NULL,"@:;");
				strcpy(signInEvent.serverPort, strPtr);
				strPtr = strtok(NULL,"@:;");
				if (strncmp(strPtr,"transport=TLS",13)==0)
					signInEvent.emcpSecured = VIDYO_TRUE;
				else
					signInEvent.emcpSecured = VIDYO_FALSE;
                /*
                <ns1:guestID>454352</ns1:guestID>;
                <ns1:isLocked>false</ns1:isLocked>;
                <ns1:hasPin>false</ns1:hasPin>;
                <ns1:proxyaddress>ca2-m1-vr3.vidyo.com:443</ns1:proxyaddress>;
                <ns1:loctag>Guest</ns1:loctag>;
                <ns1:un>M0TTHq2TIG9V2kxuN512XQ==</ns1:un>;
                <ns1:pak>Na4iqrHqmBGLB8DX</ns1:pak>;
                <ns1:portal>"https://Main.vidyo.com/services/"</ns1:portal>;
                <ns1:pak2>jNhavR6/ZUyua9hMlkmBGZj4Lu6M4Qt6Lr5x4Atebpi0AQUPk+/rfbvf2fsSZ4I=</ns1:pak2>;
                */

                GetDlgItemText(hDlg, IDC_EDIT_GUEST_PROXYADDRESS, (LPWSTR)&strTemp, SIGNIN_VIDYO_PROXY_ADDRESS_SIZE);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&signInEvent.vidyoProxyAddress[0], SIGNIN_VIDYO_PROXY_ADDRESS_SIZE, NULL, NULL);
				signInEvent.proxyType = VidyoClientProxyType::VIDYO_CLIENT_VIDYO_PROXY;
				signInEvent.numberProxies = 1;
				strcpy(signInEvent.vidyoProxyPort[0],"443");
                
                GetDlgItemText(hDlg, IDC_EDIT_GUEST_LOCTAG, (LPWSTR)&strTemp, ENDPOINT_LOCATION_TAG_SIZE);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&signInEvent.locationTag, ENDPOINT_LOCATION_TAG_SIZE, NULL, NULL);

                GetDlgItemText(hDlg, IDC_EDIT_GUESTID, (LPWSTR)&strTemp, 6);
                WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&strTemp, -1, (LPSTR)&strParse, 6, NULL, NULL);
				signInEvent.guestId = atoi(strParse);

                signInEvent.guestLogin = VIDYO_TRUE;
                VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SIGN_IN, &signInEvent, sizeof(VidyoClientInEventSignIn));
                EndDialog(hDlg, LOWORD(wParam));
				
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;

}

// Message handler for Signin box.
INT_PTR CALLBACK Signin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	char serverAddress[URI_LEN]={0};
	char userName[USERID_SIZE]={0};
	char password[PASSWORD_SIZE]={0};

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_OK_CANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_OK_LOGIN)
		{
			// Do a WideChar to Char conversion here
			GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, (LPWSTR)&serverAddress, URI_LEN);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&serverAddress, -1, (LPSTR)&portalAddress, URI_LEN, NULL, NULL);
			GetDlgItemText(hDlg, IDC_EDIT_USERNAME, (LPWSTR)&userName, USERID_SIZE);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&userName, -1, (LPSTR)&userId, USERID_SIZE, NULL, NULL);
			GetDlgItemText(hDlg, IDC_EDIT_PASSWORD, (LPWSTR)&password, PASSWORD_SIZE);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&password, -1, (LPSTR)&passwd, PASSWORD_SIZE, NULL, NULL);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

/*
// Message handler for Join Conference by Name
INT_PTR CALLBACK JoinByName(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	char name[VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE]={0};

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
/*
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_OK_JOIN)
		{
			// Do a WideChar to Char conversion here
			GetDlgItemText(hDlg, IDC_EDIT_JOINCONF_NAME_TEXT, (LPWSTR)&name, VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&name, -1, (LPSTR)&roomName, VIDYO_CLIENT_PRIVATE_SOAP_USERNAME_SIZE, NULL, NULL);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
 
	}
	return (INT_PTR)FALSE;
}

// Meesage handler for Guest Join
INT_PTR CALLBACK GuestLink(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	char serverAddress[URI_LEN]={0};
	char userName[USERID_SIZE]={0};
	char guestLink[URI_LEN]={0};

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_OK_CANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_OK_LOGIN)
		{
			// Do a WideChar to Char conversion here
			GetDlgItemText(hDlg, IDC_EDIT_ADDRESS1, (LPWSTR)&serverAddress, URI_LEN);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&serverAddress, -1, (LPSTR)&portalAddress, URI_LEN, NULL, NULL);
			GetDlgItemText(hDlg, IDC_EDIT_USERNAME1, (LPWSTR)&userName, USERID_SIZE);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&userName, -1, (LPSTR)&userId, USERID_SIZE, NULL, NULL);
			GetDlgItemText(hDlg, IDC_EDIT_PASSWORD1, (LPWSTR)&guestLink, PASSWORD_SIZE);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&guestLink, -1, (LPSTR)&passwd, URI_LEN, NULL, NULL);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}*/

// Message handler for sending chat messages
INT_PTR CALLBACK sendChat(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	char msg[MAX_CHAT_MESSAGE_LEN]={0};

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_OK_OUTGOING_CHAT)
		{
			// Do a WideChar to Char conversion here
			GetDlgItemText(hDlg, IDC_EDIT_OUTGOING_TEXT, (LPWSTR)&msg, MAX_CHAT_MESSAGE_LEN);
			WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)&msg, -1, (LPSTR)&outgoingChatMessage, MAX_CHAT_MESSAGE_LEN, NULL, NULL);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL CALLBACK EnumerateWindows( HWND hwnd, LPARAM lParam )
{
	LONG_PTR ptr;
	static int j=0;

	if(IsWindowVisible(hwnd))
	{
		ptr = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
		if((ptr&WS_EX_TOOLWINDOW) == WS_EX_TOOLWINDOW)
			return TRUE;
		if (j == 0) {
			j++;
			return TRUE;
		}
		inEventShare.window = hwnd;
		VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SHARE, &inEventShare, sizeof(inEventShare));
		return FALSE;
	}
	return TRUE;
}
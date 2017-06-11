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
VidyoUint numOfParticipants = 0;								// Total number of participants
char participantUri[MAX_PARTICIPANTS][URI_LEN] = {0};			// URIs of the remote participants
char participantNames[MAX_PARTICIPANTS][USERID_SIZE] = {0};		// display names of the remote participants
VidyoUint appShareHandles[] = {0};								// Window handles of other applications
VidyoBool participantMode = VIDYO_FALSE;
VidyoBool willBackground = VIDYO_FALSE;
char remoteAppUri[MAX_REMOTE_SHARE_APP][MAX_URI_LEN] = {0};		// URIs of the remote shares available for viewing
char remoteAppname[MAX_REMOTE_SHARE_APP][MAX_URI_LEN] = {0};	// App names of the remote shares available for viewing
char eventUri[MAX_URI_LEN] = {0};
static VidyoClientRequestParticipantStatisticsList stats = {0};
static VidyoClientParticipantStatistics participantStats = {0};


static VidyoClientInEventPreview preview = {VIDYO_CLIENT_PREVIEW_MODE_NONE};
static VidyoClientInEventParticipantsLimit participantsLimit= {0};
static VidyoClientRequestParticipantsLimit reqParticipantLimit = {0};
static VidyoClientRequestParticipants reqParticipants = {0};
static VidyoClientRequestGetNumParticipants getNumParticipants = {0};
static VidyoClientInEventLogIn logInParams = {0};
static VidyoClientOutEventGroupChat *outEventGroupChat;
static VidyoClientInEventShare inEventShare;
static VidyoClientOutEventIncomingCall *outEventincomingCall;

static VidyoClientInEventLayout layout = {0};
//static VidyoClientInEventSetParticipantVideoMode participantVideoMode = {0};
static VidyoClientRequestConfiguration reqConfig = {0};
static VidyoClientRequestSetLabel setLabel = {VIDYO_CLIENT_LABEL_SELF_VIEW};
static VidyoClientVideoPreferences videoPreference = { VIDYO_CLIENT_VIDEO_PREFERENCES_BEST_QUALITY };

static VidyoClientRequestParticipantInfo getParticipantInfo = {0};
static VidyoClientParticipantStatistics statsAt = {0};
static VidyoClientRequestWindowShares windowShares = {LIST_SHARING_WINDOWS};
static VidyoClientInEventSignIn signInEvent = {0};
static VidyoClientInEventStartWatchVideoSource watchSource = {0};
//static VidyoClientOutEventVideoFrameReceived videoFrame = {0};
static char sPartURI[4][MAX_URI_LEN]={0};
static char sPartName[4][MAX_URI_LEN]={0};
static int nCount = 0;
#define MAX_STREAMS_RENDER	4

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
	const int cWidth = 640;
	const int cDepth = 360;

	if (pFrame == NULL || hWnd == NULL)
		return;
	if(nPos >= 4)
	{
		//hard to fit more currently based on our simple logic
		return;
	}

	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC dc = GetDC(hWnd);

	RECT dest = rect;
	int offsetLeft  = rect.left;
	if(!(nPos % 2))
		offsetLeft = cWidth + offsetLeft + 10;
	dest.left = offsetLeft;
	dest.right = dest.left + cWidth;
	int offsetTop  = rect.top;
	if(!(nPos >= 2))
		offsetTop = cDepth + offsetTop + 10;
	dest.top = offsetTop;
	dest.bottom = dest.top + cDepth;


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
			info.bmiHeader.biSizeImage = pFrame->width * pFrame->height * 3;
			info.bmiHeader.biCompression = BI_RGB;

			//VIDYO_CLIENT_LOG_INFO_FORMATTED("************ nPos = %d, nCount = %d, LEFT:[%d], BOTTOM:[%d]", nPos, nCount, dest.left, dest.bottom);
			StretchDIBits(dc, dest.left, dest.bottom, cWidth, -cDepth,
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
	static int nFrame[4] = {0};
	static UINT nFPS[4] = {0};
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
						strncpy_s(sPartURI[nCount], MAX_URI_LEN, videoFrame->participantURI, MAX_URI_LEN);
						VidyoClientRequestParticipants req;
						memset(&req, NULL, sizeof(req));
						VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &req, sizeof(req));
						for (unsigned i=0; i < req.numberParticipants; ++i)
						{
							if (strncmp(sPartURI[nCount], req.URI[i], MAX_URI_LEN) == 0)
								strncpy_s(sPartName[nCount], MAX_URI_LEN, req.name[i], MAX_URI_LEN);
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
							//VIDYO_CLIENT_LOG_INFO_FORMATTED("Participant:[%s], FPS:[%d], width:[%d], height:[%d]", sPartName[nPos], (nFPS[nPos]/2), pFrame->width, pFrame->height);
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
				strncpy_s(roomLink.displayName, USERID_SIZE, (const char*)"Sample Guest", strlen("Sample Guest"));
				strncpy_s(roomLink.portalUri,URI_LEN, "http://vvp5.vidyoqa.com", strlen("http://vvp5.vidyoqa.com"));
				strncpy_s(roomLink.roomKey,ROOMKEY_SIZE, "S2Elcic9k1PR", strlen("S2Elcic9k1PR"));
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

					for(unsigned index = 0; index < reqParticipants.numberParticipants; ++index)
					{

						VidyoClientInEventStopWatchVideoSource stopWatch = {0};
						strncpy_s(stopWatch.source.participantURI, MAX_URI_LEN, reqParticipants.URI[index], URI_LEN);
						stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;

						if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE, &stopWatch, sizeof(stopWatch)) != VIDYO_TRUE){
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Video) failed");
						}else{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_STOP_WATCH_VIDEO_SOURCE (Video) sent");
						}
					}

					int numOfParticipants = reqParticipants.numberParticipants;
					if(numOfParticipants > MAX_STREAMS_RENDER)
						numOfParticipants = MAX_STREAMS_RENDER;

					for(unsigned index = 0; index < numOfParticipants; ++index)
					{

						strncpy_s(watchSource.source.participantURI, MAX_URI_LEN, reqParticipants.URI[index], URI_LEN);
						watchSource.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
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

		case IDM_EXIT:
			{
				DestroyWindow(hWnd);
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


		case ID_COMMAND_LEAVECONFERENCE:
			{
				//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO, NULL, 0);

				/* Leave the conference */

				if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE, NULL, 0) != VIDYO_TRUE)
					SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_LEAVE failed");

				//VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_STOP_ACQUIRE_AUDIO, NULL, 0);

				Sleep(50);
				VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_DECLINE, NULL, NULL);
				VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_CANCEL, NULL, NULL);

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
							eventPreview.previewMode = VIDYO_CLIENT_PREVIEW_MODE_PIP;
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


					case VIDYO_CLIENT_OUT_EVENT_PREVIEW:
						{
							VidyoClientOutEventPreview *outEventPreview;
							outEventPreview = (VidyoClientOutEventPreview *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_PREVIEW received ");
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


					case VIDYO_CLIENT_OUT_EVENT_RESIZE:
						{
							VidyoClientOutEventResize *OutEventResize;
							OutEventResize = (VidyoClientOutEventResize *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_RESIZE received");
							break;
						}
					case VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT:
						{
							VidyoClientOutEventParticipantsLimit *outLimit;
							outLimit = (VidyoClientOutEventParticipantsLimit *)event_data->data;
							SetWindowText(hWnd, L"VidyoClient sample - Received VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT");
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
						{
							//CheckMenuItem(GetMenu(hWnd),ID_COMMAND_INCONFERENCE,MF_CHECKED);
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE received ");
							//Sleep(2000);
							VidyoClientInEventPreview eventPreview;	
							eventPreview.previewMode = VIDYO_CLIENT_PREVIEW_MODE_PIP;
							VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_PREVIEW, &eventPreview, sizeof(eventPreview));


							if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW, NULL, 0) != VIDYO_TRUE){
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW failed");
							}else{
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_IN_EVENT_START_WATCH_SELF_VIEW sent");
							}


							/* Get the participant URIs */
							memset(&participantStats, 0, sizeof(participantStats));
							memset(&stats, 0, sizeof(stats));
							if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST, &stats, sizeof(stats)) != VIDYO_FALSE) {
								SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_STATISTICS_LIST failed.");
							} else {
								if (stats.numParticipants != 0) {
									numOfParticipants = stats.numParticipants;
									for (unsigned i=0; i<numOfParticipants; i++) {
										participantStats = stats.statistics[i];
										strcpy_s(participantUri[i], URI_LEN, participantStats.uri);
										strcpy_s(participantNames[i], USERID_SIZE, participantStats.name);
										memset(&participantStats, 0, sizeof(participantStats));
									}
								} else {
									SetWindowText(hWnd, L"VidyoClient sample - Participants GET_PARTICIPANTS_STATISTICS_LIST=0 .");
								}
							}
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
							strncpy_s(startWatch.source.participantURI, MAX_URI_LEN, pEvent->participantURI, MAX_URI_LEN);
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
							strncpy_s(stopWatch.source.participantURI, MAX_URI_LEN, pEvent->participantURI, MAX_URI_LEN);
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
							strncpy_s(request.shareList.remoteAppUri[0], MAX_URI_LEN, pEvent->URI, MAX_URI_LEN);
							strncpy_s(request.shareList.remoteAppName[0], MAX_URI_LEN, "Share", MAX_URI_LEN);
							request.shareList.numApp = 1;
							request.shareList.currApp = 1;
							request.shareList.newApp = 1;

							VidyoUint result = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, &request, sizeof(request));
							if (result != VIDYO_CLIENT_ERROR_OK) {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES failed");
							} else {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES sent");
							}

							VidyoClientInEventStartWatchVideoSource startWatch={0};
							strncpy_s(startWatch.source.participantURI, MAX_URI_LEN, pEvent->URI, URI_LEN);
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
							strncpy_s(request.shareList.remoteAppUri[0], MAX_URI_LEN, pEvent->URI, MAX_URI_LEN);
							strncpy_s(request.shareList.remoteAppName[0], MAX_URI_LEN, "Share", MAX_URI_LEN);
							request.shareList.numApp = 0;
							request.shareList.currApp = 0;
							request.shareList.newApp = 0;

							VidyoUint result = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, &request, sizeof(request));
							if (result != VIDYO_CLIENT_ERROR_OK) {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES failed");
							} else {
								SetWindowText(hWnd, L"VidyoClient sample VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES sent");
							}

							VidyoClientInEventStopWatchVideoSource stopWatch = {0};
							strncpy_s(stopWatch.source.participantURI, MAX_URI_LEN, pEvent->URI, URI_LEN);
							stopWatch.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_APPLICATION;
							break;
						}

					case VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED:
						{
							SetWindowText(hWnd, L"VidyoClient sample - VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED received ");
							VidyoClientOutEventParticipantsChanged *OutEventParticipantsChanged = (VidyoClientOutEventParticipantsChanged *)event_data->data;

							VidyoClientRequestParticipantDetailsAt details= {0};
							details.index = (OutEventParticipantsChanged->participantCount - 1);
							VidyoUint error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANT_DETAILS_AT, &details, sizeof(VidyoClientRequestParticipantDetailsAt));




							if (OutEventParticipantsChanged->participantCount>1){

								if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_PARTICIPANTS, &reqParticipants, sizeof(reqParticipants)) == VIDYO_CLIENT_ERROR_OK){
									strncpy_s(watchSource.source.participantURI, MAX_URI_LEN, reqParticipants.URI[OutEventParticipantsChanged->participantCount-1], URI_LEN);
									watchSource.source.mediaType = VIDYO_CLIENT_MEDIA_CONTROL_TYPE_VIDEO;
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


					}
					free(event_data);
				}
			}
			break;
		}
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

	switch (message)
	{
	case WM_INITDIALOG:

		VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_EID, &eid, sizeof(VidyoClientRequestGetEid));
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
			signInEvent.proxyType = VIDYO_CLIENT_VIDYO_PROXY;
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
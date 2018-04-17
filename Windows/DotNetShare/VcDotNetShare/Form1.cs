using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices; // DllImport
using VGUClientLogic;
using System.Threading;
using UnifiedDotNetSample.UserServiceReference1;
using System.ServiceModel;


namespace VidyoClientCS
{

    public partial class Form1 : Form
    {
        public Vidyo32.VidyoClientOutEventCallback m_myDelegate;

        private int m_CurrentState = 0;
        public const int cVcStarted = 1;
        public const int cCallStarted = 2;
        public const int cApplicationClosing = 4;
        public const int cVideoMuted = 8;
        public const int cMicMuted = 16;
        int m_indexWindow = 0;

        public void  UpdateUi_()
        {
            buttonStart.Enabled = !IsFlagSet(cVcStarted);
            buttonStop.Enabled = IsFlagSet(cVcStarted);
            buttonJoin.Enabled = IsFlagSet(cVcStarted);
            buttonEnd.Enabled = IsFlagSet(cCallStarted);
            buttonMuteCamera.Enabled = IsFlagSet(cCallStarted);
            buttonMuteMic.Enabled = IsFlagSet(cCallStarted);

            if (IsFlagSet(cVideoMuted))
                buttonMuteCamera.Text = "UnmuteCamera";
            else
                buttonMuteCamera.Text = "MuteCamera";
            if (IsFlagSet(cMicMuted))
                buttonMuteMic.Text = "UnmuteMic";
            else
                buttonMuteMic.Text = "MuteMic";
        }
        
        private void UpdateUi()
        {
            if (InvokeRequired)
            {
                // after we've done all the processing, 
                this.Invoke(new MethodInvoker(delegate
                {
                    UpdateUi_();
                }));
            }
            else
                UpdateUi_();
            


        }

        private void SetFlag(int flag)
        {
            m_CurrentState = m_CurrentState | flag;
            UpdateUi();
        }

        private void ClearFlag(int flag)
        {
            m_CurrentState = m_CurrentState & ~flag;
            UpdateUi();
        }

        private Boolean IsFlagSet(int flag)
        {
            return ((flag & m_CurrentState) != 0);
        }


        public Form1()
        {
            InitializeComponent();

            m_myDelegate = MessageFromVidyoClient;
            try
            {
                //Specifying logging information
                Vidyo32.VidyoClientLogParams logParams = new Vidyo32.VidyoClientLogParams();

                logParams.logSize = 500000;            
                //log path must exist before running (this is done by Visual Studio build steps here)
                logParams.setpathToLogDir(".\\logs\\");
                logParams.setlogBaseFileName("VidyoSampleApplication");
                logParams.setLogLevelsAndCategories("+warning all@App all@AppEvents all@LmiApp");
                logParams.setPathToDumpDir(".\\logs\\");


                int szLog = Marshal.SizeOf(logParams);
                IntPtr ptrLog = Marshal.AllocCoTaskMem(szLog);
                Marshal.StructureToPtr(logParams, ptrLog, true);

                //Initializing the client
                byte initRes = Vidyo32.VidyoClientInitialize(m_myDelegate, // callback
                                                            IntPtr.Zero, // data ptr 
                                                           ptrLog);
            
            }

            catch (Exception ex)
            {
               
            }
        }
        unsafe  //unsafe for parsing messageCode Array

        void MessageFromVidyoClient(Vidyo32.VidyoClientOutEvent actionType, IntPtr param, uint paramSize, IntPtr ptr2)
        {
            string now = DateTime.Now.ToString("HH:mm:ss:fff") + "  + ";
            string message = now + "Out Event from Vidyoclient: " + actionType;
            switch (actionType)
            {
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_ROOM_LINK:
                    {
                        Vidyo32.VidyoClientOutEventRoomLink guestLink = (Vidyo32.VidyoClientOutEventRoomLink)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventRoomLink));

                        message += " Error = " + guestLink.error;
                        message += "state =" + guestLink.state;

                    } break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CLEARED:
                    {
                        if (IsFlagSet(cApplicationClosing))
                         {
                            //we were just waiting for application leave to come to restart closing process
                             ClearFlag(cCallStarted);
                             ClearFlag(cApplicationClosing);
                             StopLib();

                         }
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
                    {
                        SetFlag(cCallStarted);
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO:
                    {
                        Vidyo32.VidyoClientOutEventMuted muteInfo = (Vidyo32.VidyoClientOutEventMuted)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventMuted));
                        if (muteInfo.isMuted == Vidyo32.VidyoBool.VIDYO_TRUE)
                            SetFlag(cVideoMuted);
                        else
                            ClearFlag(cVideoMuted);
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN:
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN:                
                    {
                        Vidyo32.VidyoClientOutEventMuted muteInfo = (Vidyo32.VidyoClientOutEventMuted)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventMuted));
                        if (muteInfo.isMuted == Vidyo32.VidyoBool.VIDYO_TRUE)
                            SetFlag(cMicMuted);
                        else
                            ClearFlag(cMicMuted);
                    }
                    break;

              
                #region  VIDYO_CLIENT_OUT_EVENT(s) RINGING, CALLING AND RPOGRESS

               
                #endregion  VIDYO_CLIENT_OUT_EVENT(s) RINGING, CALLING AND RPOGRESS
                default:
                    {
                    }
                    break;
            }
        }   

    
        private void ThreadProcUnsafe(bool value)
        {
            
        }

        public void StopLib()
        {
            if (IsFlagSet(cCallStarted))
            {
                SetFlag(cApplicationClosing);
                Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_LEAVE, (IntPtr)0, 0);
                return;
            }

            if (IsFlagSet(cVcStarted))
            {
                ClearFlag(cVcStarted);
                Vidyo32.VidyoClientStop();
            }
            Vidyo32.VidyoClientUninitialize();
            Application.Exit();
        }

     
        public void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            StopLib();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            diffW = this.Width - pnlVideoArea.Width;
            diffH = this.Height - pnlVideoArea.Height;
        }


      

        /////////////////////////////////////////////////////////////
        #region  SIZING VIDEO WINDOW
        int diffW = 0;
        int diffH = 0;
        private bool inSizing = false;
        Vidyo32.VidyoClientResizingMethod sizingMethod;
        uint suggHeight = 0;
        uint suggWidth = 0;
        private delegate void UpdateSizeHandler(Size newSize);
        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            const int WM_SYSCOMMAND = 0x0112;
            const int SC_MAXIMIZE = 0xF030;
            const int SC_RESTORE = 0xF120;
            const int WM_SIZING = 0x214;
            const int WM_EXITSIZEMOVE = 0x232;

            const int WMSZ_LEFT = 1;
            const int WMSZ_RIGHT = 2;
            const int WMSZ_TOP = 3;
            //    const int WMSZ_TOPLEFT = 4;
            //    const int WMSZ_TOPRIGHT = 5;
            const int WMSZ_BOTTOM = 6;
            //    const int WMSZ_BOTTOMLEFT = 7;
            //    const int WMSZ_BOTTOMRIGHT = 8;

            switch (m.Msg)
            {
                case WM_SIZING:
                    inSizing = true;
                    if (m.WParam.ToInt32() == WMSZ_BOTTOM || m.WParam.ToInt32() == WMSZ_TOP)
                        sizingMethod = Vidyo32.VidyoClientResizingMethod.VIDYO_CLIENT_RESIZING_METHOD_VERTICAL;
                    else if (m.WParam.ToInt32() == WMSZ_RIGHT || m.WParam.ToInt32() == WMSZ_LEFT)
                        sizingMethod = Vidyo32.VidyoClientResizingMethod.VIDYO_CLIENT_RESIZING_METHOD_HORIZONTAL;
                    else //if (m.WParam.ToInt32() == WMSZ_TOPLEFT || m.WParam.ToInt32() == WMSZ_TOPRIGHT || m.WParam.ToInt32() == WMSZ_BOTTOMLEFT || m.WParam.ToInt32() == WMSZ_BOTTOMRIGHT)
                        sizingMethod = Vidyo32.VidyoClientResizingMethod.VIDYO_CLIENT_RESIZING_METHOD_DIAGONAL;
                    break;
                case WM_EXITSIZEMOVE:
                    if (inSizing)
                    {
                        OnFormResizeEnd();
                        inSizing = false;
                    }
                    break;
                case WM_SYSCOMMAND:
                    if ((int)m.WParam == SC_MAXIMIZE)
                    {
                        OnFormResizeEnd();
                        inSizing = false;
                    }
                    else if ((int)m.WParam == SC_RESTORE)
                    {
                        OnFormResizeEnd();
                        inSizing = false;
                    }
                    break;
            }
            base.WndProc(ref m);
        }

        private void UpdateFormSize(Size sz)
        {
            this.Width = sz.Width;
            this.Height = sz.Height;
        }

        private void OnFormResizeEnd()
        {
            //TODO: return if not in conf
            Size sz = new Size((int)(suggWidth + diffW), (int)(suggHeight + diffH));
            this.Invoke(new UpdateSizeHandler(UpdateFormSize), sz);
        }

        private void pnlVideoArea_SizeChanged(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientInEventResize EventResize = new Vidyo32.VidyoClientInEventResize();
            if (true)//(inSizing)            
            {

                EventResize.width = (uint)pnlVideoArea.Width;
                EventResize.height = (uint)pnlVideoArea.Height;
            }
            int szEventResize = Marshal.SizeOf(EventResize);
            IntPtr ptrEventResize = Marshal.AllocCoTaskMem(szEventResize);
            Marshal.StructureToPtr(EventResize, ptrEventResize, true);
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_RESIZE, ptrEventResize, szEventResize);
        }
        #endregion  SIZING VIDEO WINDOW
        /////////////////////////////////////////////////////////

       

        private void BringToForeground(IntPtr extHandle)
        {
          
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            try
            {
                //specifying the video handler location
                Rectangle rect = new Rectangle(0, 0, pnlVideoArea.Width, pnlVideoArea.Height);
                int szRect = Marshal.SizeOf(rect);
                IntPtr ptrRect = Marshal.AllocCoTaskMem(szRect);
                Marshal.StructureToPtr(rect, ptrRect, true);

                //Specifying logging information
                Vidyo32.VidyoClientLogParams logParams = new Vidyo32.VidyoClientLogParams();

                logParams.logSize = 500000;
                //log path must exist before running (this is done by Visual Studio build steps here)
                logParams.setpathToLogDir(".\\logs\\");
                logParams.setlogBaseFileName("VidyoSampleApplication");
                logParams.setLogLevelsAndCategories("warning all@App all@AppEvents all@LmiApp");
                logParams.setPathToDumpDir(".\\logs\\");


                int szLog = Marshal.SizeOf(logParams);
                IntPtr ptrLog = Marshal.AllocCoTaskMem(szLog);
                Marshal.StructureToPtr(logParams, ptrLog, true);

                Vidyo32.VidyoClientProfileParams profileParams = new Vidyo32.VidyoClientProfileParams();
                //this is where in the registry settings get stored betweeen runs. Empty value defaults to VidyoDesktop's location and settings (but also reuses VidyoDesktop EID)
                profileParams.setCONFIG_KEY_PATH("");
                profileParams.setMYDOCS_DIR("");
                profileParams.portNumber = 65000; //VidyoDesktop uses 63457
                profileParams.setPRODUCT_NAME("VidyoSampleApplication");
                profileParams.setPROGFILES_DIR("");
                profileParams.setVIDYO_DIR("");
                //this is where the CA base certificate is read from - here we're using Vidyo Desktop's version.
                profileParams.setCERT_FILE_DIR(".\\");
                profileParams.setINSTALLED_APP_DIR(".\\");


                int szProfile = Marshal.SizeOf(profileParams);
                IntPtr ptrProfile = Marshal.AllocCoTaskMem(szProfile);
                Marshal.StructureToPtr(profileParams, ptrProfile, true);

                //Starting the client
                Int32 startRes = Vidyo32.VidyoClientStart(m_myDelegate, // callback
                                                        IntPtr.Zero, // data ptr 
                                                        ptrLog,//logParams,
                                                        pnlVideoArea.Handle,
                                                        ptrRect, // Initial RECT
                                                        IntPtr.Zero, //reserved
                                                        ptrProfile,//profileParams,
                                                        false); //reserved
                SetFlag(cVcStarted);

                //Enable window share feature
                Vidyo32.VidyoClientRequestEnableAppShare enableShare = new Vidyo32.VidyoClientRequestEnableAppShare();
                enableShare.isEnable = Vidyo32.VidyoBool.VIDYO_TRUE;
                int nEnableSize = Marshal.SizeOf(enableShare);

                IntPtr ptrEnableShares = Marshal.AllocCoTaskMem(nEnableSize);
                Marshal.StructureToPtr(enableShare, ptrEnableShares, true);
                int szShares2 = Marshal.SizeOf(ptrEnableShares);

                uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_ENABLE_APP_SHARE,
                            ptrEnableShares, nEnableSize);
                if (error != 0)
                {
                    return;
                }

            }

            catch (Exception ex)
            {

            }
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            ClearFlag(cVcStarted);
            Vidyo32.VidyoClientStop();
        }

     
        private void buttonEnd_Click(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_LEAVE, (IntPtr)0, 0);
        }


        private void buttonJoin_Click(object sender, EventArgs e)
        {
            UnifiedDotNetSample.RoomLink roomLink = new UnifiedDotNetSample.RoomLink();
            roomLink.ShowDialog();
            if (!roomLink.m_bMakeCall)
                return;

            Vidyo32.VidyoClientInEventRoomLink guestJoin = new Vidyo32.VidyoClientInEventRoomLink();

            guestJoin.portalUri = roomLink.m_strPortal;
            guestJoin.roomKey = roomLink.m_strRoomKey;
            guestJoin.displayName = roomLink.m_strDisplayName;
            guestJoin.pin = roomLink.m_strPin;
            guestJoin.clientType = VGUClientLogic.Vidyo32.VidyoClientClientType.VIDYO_CLIENT_CLIENTTYPE_W;
            guestJoin.muteCamera = Vidyo32.VidyoBool.VIDYO_FALSE;
            guestJoin.muteMicrophone = Vidyo32.VidyoBool.VIDYO_FALSE;
            guestJoin.muteSpeaker = Vidyo32.VidyoBool.VIDYO_FALSE;

            int Gsize = Marshal.SizeOf(guestJoin);
            IntPtr Gptr = Marshal.AllocCoTaskMem(Gsize);
            Marshal.StructureToPtr(guestJoin, Gptr, false);

            Int32 Guest = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_ROOM_LINK, Gptr, Gsize);
        }

        private void buttonMuteCamera_Click(object sender, EventArgs e)
        {

            Vidyo32.VidyoClientInEventMute mute = new Vidyo32.VidyoClientInEventMute();
            mute.isMuted = (IsFlagSet(cVideoMuted)) ? Vidyo32.VidyoBool.VIDYO_TRUE : Vidyo32.VidyoBool.VIDYO_FALSE;
            int Gsize = Marshal.SizeOf(mute);
            IntPtr Gptr = Marshal.AllocCoTaskMem(Gsize);
            Marshal.StructureToPtr(mute, Gptr, false);

            Int32 Guest = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO, Gptr, Gsize);
        }

        private void buttonMuteMic_Click(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientInEventMute mute = new Vidyo32.VidyoClientInEventMute();
            mute.isMuted = (IsFlagSet(cMicMuted)) ? Vidyo32.VidyoBool.VIDYO_FALSE : Vidyo32.VidyoBool.VIDYO_TRUE;
            int Gsize = Marshal.SizeOf(mute);
            IntPtr Gptr = Marshal.AllocCoTaskMem(Gsize);
            Marshal.StructureToPtr(mute, Gptr, false);

            Int32 Guest = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN, Gptr, Gsize);

        }

        private void buttonShare_Click(object sender, EventArgs e)
        {
             Vidyo32.VidyoClientRequestGetWindowsAndDesktops shares = new Vidyo32.VidyoClientRequestGetWindowsAndDesktops();
             shares.Init();

             int szShares = Marshal.SizeOf(shares);
                       
                        IntPtr ptrShares = Marshal.AllocCoTaskMem(szShares);
                        Marshal.StructureToPtr(shares, ptrShares, true);
                        int szShares2 = Marshal.SizeOf(ptrShares);

			uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS, 
                        ptrShares, szShares);
            if (error != 0)
            {
                return;
            }

            Vidyo32.VidyoClientRequestGetWindowsAndDesktops currentShares = (Vidyo32.VidyoClientRequestGetWindowsAndDesktops)Marshal.PtrToStructure(ptrShares, typeof(Vidyo32.VidyoClientRequestGetWindowsAndDesktops));

          
            if (currentShares.numSystemDesktops > 0)
            {
                string firstDesktopId = currentShares.sysDesktopId[0];
                Vidyo32.VidyoClientInEventShare sharePara = new Vidyo32.VidyoClientInEventShare();
                sharePara.shareType = Vidyo32.VidyoClientContentsShareType.VIDYO_CLIENT_CONTENTS_SHARE_TYPE_DESKTOP_WINDOW;
                sharePara.window = (IntPtr)1;
                sharePara.desktopId = firstDesktopId;

                int sizeOfShareEvent = Marshal.SizeOf(sharePara);
                IntPtr sharePtr = Marshal.AllocCoTaskMem(sizeOfShareEvent);
                Marshal.StructureToPtr(sharePara, sharePtr, false);

                Int32 returnValue = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_SHARE, sharePtr, sizeOfShareEvent);

                return;

            }
        }

        private void buttonShareWnd_Click(object sender, EventArgs e)
        {

            Vidyo32.VidyoClientRequestGetWindowsAndDesktops shares = new Vidyo32.VidyoClientRequestGetWindowsAndDesktops();
            shares.Init();

            int szShares = Marshal.SizeOf(shares);

            IntPtr ptrShares = Marshal.AllocCoTaskMem(szShares);
            Marshal.StructureToPtr(shares, ptrShares, true);
            int szShares2 = Marshal.SizeOf(ptrShares);

            uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS,
                        ptrShares, szShares);
            if (error != 0)
            {
                return;
            }

            Vidyo32.VidyoClientRequestGetWindowsAndDesktops currentShares = (Vidyo32.VidyoClientRequestGetWindowsAndDesktops)Marshal.PtrToStructure(ptrShares, typeof(Vidyo32.VidyoClientRequestGetWindowsAndDesktops));
            if (currentShares.numApplicationWindows <= m_indexWindow)
                m_indexWindow = 0;

            if (currentShares.numApplicationWindows > m_indexWindow)
            {
                Vidyo32.VidyoClientInEventShare sharePara = new Vidyo32.VidyoClientInEventShare();
                sharePara.shareType = Vidyo32.VidyoClientContentsShareType.VIDYO_CLIENT_CONTENTS_SHARE_TYPE_APPLICATION_WINDOW;
                sharePara.window = (IntPtr)currentShares.appWindowId[m_indexWindow++];

                int sizeOfShareEvent = Marshal.SizeOf(sharePara);
                IntPtr sharePtr = Marshal.AllocCoTaskMem(sizeOfShareEvent);
                Marshal.StructureToPtr(sharePara, sharePtr, false);

                Int32 returnValue = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_SHARE, sharePtr, sizeOfShareEvent);

                return;

            }

        }

      

    }

}









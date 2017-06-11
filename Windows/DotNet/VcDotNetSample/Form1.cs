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
        private delegate void UpdateListBoxHandler(String addMessage);

        // invoking UI threads from one thread to another
        private delegate void SetButtonCallback(bool shdEnable);
        private delegate void ShareLocalWindow();
       

        private Vidyo32.VidyoClientPreviewMode PreviewMode = new Vidyo32.VidyoClientPreviewMode();
        public string directCallEntityID = null;

        public bool out_event_calling_received = false;
        private static BasicHttpBinding _httpBinding = new BasicHttpBinding("VidyoPortalUserServiceBindingHTTP");
        private static BasicHttpsBinding _httpsBinding = new BasicHttpsBinding("VidyoPortalUserServiceBindingHTTPS");

        //Binding the http/ https portal URLs
        public static HttpBindingBase GetBinding(string portal)
        {
            HttpBindingBase binding = null;

            // Use the appropriate binding, depending on whether portal is http or https
            if (portal.StartsWith("http://"))
                binding = _httpBinding;
            else if (portal.StartsWith("https://"))
                binding = _httpsBinding;

            return binding;
        }

        public Form1()
        {
            InitializeComponent();

            m_myDelegate = MessageFromVidyoClient;
            PreviewMode = Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_NONE;
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
                logParams.setLogLevelsAndCategories("warning all@App debug@AppEvents");
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

                //Initializing the client
                byte initRes = Vidyo32.VidyoClientInitialize(m_myDelegate, // callback
                                                            IntPtr.Zero, // data ptr 
                                                           ptrLog);

                //Starting the client
                Int32 startRes = Vidyo32.VidyoClientStart(m_myDelegate, // callback
                                                        IntPtr.Zero, // data ptr 
                                                        ptrLog,//logParams,
                                                        pnlVideoArea.Handle,
                                                        ptrRect, // Initial RECT
                                                        IntPtr.Zero, //reserved
                                                        ptrProfile,//profileParams,
                                                        false); //reserved


                string now = DateTime.Now.ToString("HH:mm:ss:fff") + "  = ";

                //Disabling auto enable option to prevent multiple signin's in the application
                Vidyo32.VidyoClientRequestConfiguration vidConfig = new Vidyo32.VidyoClientRequestConfiguration();
                int size = Marshal.SizeOf(vidConfig);
                IntPtr ptrConfig = Marshal.AllocCoTaskMem(size);
                Marshal.StructureToPtr(vidConfig, ptrConfig, false);
                uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, ptrConfig, size);
                vidConfig = (Vidyo32.VidyoClientRequestConfiguration)Marshal.PtrToStructure(ptrConfig, typeof(Vidyo32.VidyoClientRequestConfiguration));

                if (vidConfig.numberCameras != 0)
                {
                    String mic = vidConfig.GetMicrophones()[0];
                    if (mic.Length != 0)
                        MessageBox.Show(vidConfig.GetMicrophones()[0]);
                }
                listBox1.Items.Add(now + "Vidyo Client Autoenabled received as " + vidConfig.enableAutoLogIn);

                if (error == 0)
                {
                    vidConfig.enableAutoLogIn = 0;
                    error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, ptrConfig, size);
                    listBox1.Items.Add(now + "Vidyo Client Autoenabled set to " + vidConfig.enableAutoLogIn);
                }

                if (startRes == 1)
                {
                    listBox1.Items.Add(now + "Vidyo Client started");
                    listBox1.Items.Add(now + "Perform SignIn Process");

                    label1.Visible = true;
                    label2.Visible = true;
                    label3.Visible = true;
                    label4.Visible = true;
                    label5.Visible = true;
                    label6.Visible = true;
                    label7.Visible = true;
                    label8.Visible = true;
                    label8.Visible = true;
                    txtBxGuestNm.Visible = true;
                    txtBxGuestURI.Visible = true;
                    txtBxPwd.Visible = true;

                    txtBxRoomPin.Visible = true;
                    txtBxUserURI.Visible = true;
                    txtBxUsrNm.Visible = true;
                    btnSubmitGuest.Visible = true;
                    btnSubmitUser.Visible = true;

                }

                else
                {
                    listBox1.Items.Add(now + "Vidyo Client start up failed");

                }

            }

            catch (Exception ex)
            {
                string now = DateTime.Now.ToString("HH:mm:ss:fff") + "  - ";
                listBox1.Items.Add(now + "Exception starting vidyo client: " + ex.Message);
            }
        }
        uint numProgressSteps = 0;
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

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_SIGN_IN:
                    {
                        Vidyo32.VidyoClientOutEventSignIn EventSignIn = (Vidyo32.VidyoClientOutEventSignIn)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventSignIn));
                        int userEntityId = (int)EventSignIn.activeEid;
                        if (userEntityId == 0)
                            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_LICENSE, (IntPtr)0, 0);
                    } break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_LOGIN:
                    {
                        Vidyo32.VidyoClientOutEventLogIn login = (Vidyo32.VidyoClientOutEventLogIn)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventLogIn));
                        message += " Error = " + login.error;
                        message += " PortalURI =" + login.portalUri.ToString();
                        message += " Username  = " + login.userName.ToString();

                    }

                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE:
                    {
                        Vidyo32.VidyoClientOutEventPortalService OutPortalService = (Vidyo32.VidyoClientOutEventPortalService)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventPortalService));
                        Vidyo32.VidyoClientOutEventPortalServiceDirectCall OutServiceDirectCall = (Vidyo32.VidyoClientOutEventPortalServiceDirectCall)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventPortalServiceDirectCall));

                        message = now + "Out Event from Vidyoclient: " + actionType;
                        message += "  Type Request Direct Call = " + OutPortalService.directCall.typeRequest.ToString();
                        message += "   Vidyo Client Error = " + OutServiceDirectCall.error.ToString();
                        message += " httpStatusCode= " + OutServiceDirectCall.httpStatusCode.ToString();
                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_LICENSE:
                    {
                        Vidyo32.VidyoClientOutEventLicense lic = (Vidyo32.VidyoClientOutEventLicense)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventLicense));
                        message += " Error = " + lic.error;
                        message += "Connection Path  = " + lic.vmConnectionPath;
                        message += " Out of License? = " + lic.OutOfLicenses;
                    }


                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MOUSE_MOVE:
                    /*filtering any message we don't need to show*/
                    return;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE:
                    {
                        Vidyo32.VidyoClientOutEventUserMessage msg = (Vidyo32.VidyoClientOutEventUserMessage)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventUserMessage));
                        message += " Type = " + msg.messageType;
                        message += " Code = " + msg.messageCode[0];
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED:
                    {
                        Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_SIGNOFF, (IntPtr)0, 0); //added code newly
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL:
                    {
                        string strInviter = "Call from ";
                        Vidyo32.VidyoClientRequestInvitingUser InvUser = new Vidyo32.VidyoClientRequestInvitingUser();
                        int szInvUser = Marshal.SizeOf(InvUser);
                        IntPtr ptrInvUser = Marshal.AllocCoTaskMem(szInvUser);
                        Marshal.StructureToPtr(InvUser, ptrInvUser, true);
                        uint errInvUser = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_INVITING_USER, ptrInvUser, szInvUser);
                        if (errInvUser == 0)
                        {
                            InvUser = (Vidyo32.VidyoClientRequestInvitingUser)Marshal.PtrToStructure(ptrInvUser, typeof(Vidyo32.VidyoClientRequestInvitingUser));
                            strInviter += InvUser.GetInvitingUser();
                        }
                        DialogResult result = MessageBox.Show(strInviter, "Incoming Call ", MessageBoxButtons.OKCancel, MessageBoxIcon.Question, 0, 0);
                        switch (result)
                        {
                            case DialogResult.OK:
                                Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_ANSWER, (IntPtr)0, 0);
                                break;

                            case DialogResult.Cancel:
                                Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_DECLINE, (IntPtr)0, 0);
                                break;
                        }
                        break;
                    }
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_RESIZE:
                    {
                        Vidyo32.VidyoClientOutEventResize EventResize = (Vidyo32.VidyoClientOutEventResize)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventResize));
                        int width1 = (int)EventResize.width;
                        int height1 = (int)EventResize.height;
                        message += "  Width = " + EventResize.width.ToString() + "   Height = " + EventResize.height.ToString();
                        //Size sz = new Size(width1 + diffW, height1 + diffH);
                        //this.Invoke(new UpdateSizeHandler(UpdateFormSize), sz);
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_ADD_SHARE:
                    {
                        Vidyo32.VidyoClientOutEventAddShare EventShared = (Vidyo32.VidyoClientOutEventAddShare)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventAddShare));
                        message += "   " + EventShared.GetURI();
                        
                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO:
                    {
                        Vidyo32.VidyoClientOutEventMuted EvenMuted = (Vidyo32.VidyoClientOutEventMuted)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventMuted));
                        message += " Error = " + EvenMuted.errorCode;
                        message += EvenMuted.isMuted;
                    }
                    break;


                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE:
                    {
                        Vidyo32.VidyoClientOutEventRemoveShare EventShared = (Vidyo32.VidyoClientOutEventRemoveShare)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventRemoveShare));
                        message += "   " + EventShared.GetURI();
                        // listBoxNetShares.Invoke(new UpdateListBoxHandler(RemoveListBoxNetShares), EventShared.GetURI()); //change to removeListBoxNetShares
                    }

                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT:
                    {
                        Vidyo32.VidyoClientOutEventParticipantsLimit EventParticipantsLimit = (Vidyo32.VidyoClientOutEventParticipantsLimit)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventParticipantsLimit));
                        message += "  CPU limit = " + EventParticipantsLimit.CpuLimit.ToString();
                        message += "   Bandwidth Limit = " + EventParticipantsLimit.BandwidthLimit.ToString();


                    }
                    break;
                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT:
                    {

                        if (this.btnSubmitUser.InvokeRequired)
                        {
                            this.Invoke(new SetButtonCallback(ThreadProcUnsafe), true);

                        }
                        else
                        {
                            this.btnSubmitUser.Enabled = true;
                            this.btnSubmitUser.Visible = true;
                            this.txtBxUserURI.Enabled = true;
                            this.txtBxUsrNm.Enabled = true;
                            this.txtBxPwd.Enabled = true;
                        }

                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_SIGNED_IN:
                    {
                        Vidyo32.VidyoClientRequestConfiguration vidConfig = new Vidyo32.VidyoClientRequestConfiguration();
                        int size = Marshal.SizeOf(vidConfig);
                        IntPtr ptrConfig = Marshal.AllocCoTaskMem(size);
                        Marshal.StructureToPtr(vidConfig, ptrConfig, false);
                        uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, ptrConfig, size);
                        if (error == 0)
                        {
                            Vidyo32.VidyoClientRequestConfiguration strucConfig = (Vidyo32.VidyoClientRequestConfiguration)Marshal.PtrToStructure(ptrConfig, typeof(Vidyo32.VidyoClientRequestConfiguration));
                            strucConfig.enableHideCameraOnJoin = 1;
                            uint error2 = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, ptrConfig, size);
                        }
                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN:
                    {
                        Vidyo32.VidyoClientOutEventMuted EvenMuted = (Vidyo32.VidyoClientOutEventMuted)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventMuted));
                        message += " Error = " + EvenMuted.errorCode;
                        message += EvenMuted.isMuted;
                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO:
                    {
                        Vidyo32.VidyoClientOutEventMuted EvenMuted = (Vidyo32.VidyoClientOutEventMuted)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventMuted));
                        message += " Error = " + EvenMuted.errorCode;
                        message += EvenMuted.isMuted;
                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_SUBSCRIBING:
                    {
                        uint sInt = (uint)Marshal.PtrToStructure(param, typeof(uint));
                        //Subscribing(sInt);
                    }
                    return;
                #region  VIDYO_CLIENT_OUT_EVENT(s) RINGING, CALLING AND RPOGRESS

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_CALLING:
                    {
                        //after P2P sending request and collee is agree to talk, we can have progress bar with "entering Call" (not a conference)
                        Vidyo32.VidyoClientOutEventStartProgress StartProgress = (Vidyo32.VidyoClientOutEventStartProgress)Marshal.PtrToStructure(param, typeof(Vidyo32.VidyoClientOutEventStartProgress));
                        numProgressSteps = StartProgress.numProgressSteps;
                        string CallingTo = StartProgress.GetCaption();
                        message += "  Starting to .. " + CallingTo;

                        out_event_calling_received = true;

                        // code to enable cancel direct call button
                        if (this.btnCancelDirect.InvokeRequired)
                        {
                            this.Invoke(new SetButtonCallback(DisableDirectCall), true);

                        }
                        else
                        {
                            this.btnCancelDirect.Enabled = true;
                            this.btnCancelDirect.Visible = true;

                        }
                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_ALARMS_RAISED:
                    {
                        listBox1.Items.Add(now + "Vidyo Client Alarm Raised");
                        message = now + "Out Event from Vidyoclient: " + actionType;
                        Vidyo32.VidyoClientRequestGetAlarms Alarm = new Vidyo32.VidyoClientRequestGetAlarms();

                        int szAlarm = Marshal.SizeOf(Alarm);
                        IntPtr ptrAlarm = Marshal.AllocCoTaskMem(szAlarm);
                        Marshal.StructureToPtr(Alarm, ptrAlarm, true);
                        uint errAlarm = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_ALARMS, ptrAlarm, szAlarm);
                        if (errAlarm == 0)
                        {
                            Vidyo32.VidyoClientRequestGetAlarms CurrentAlarm = (Vidyo32.VidyoClientRequestGetAlarms)Marshal.PtrToStructure(ptrAlarm, typeof(Vidyo32.VidyoClientRequestGetAlarms));

                            string Alarmsg = " Alarm Info ";
                            Alarmsg += DateTime.Now + "***Alarm infromation***";
                            Alarmsg += " Treggered Alarm = " + CurrentAlarm.ToString();

                            listBox1.Invoke(new UpdateListBoxHandler(UpdateTextBox), Alarmsg);
                        }

                    }
                    break;

                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_ALARMS_CLEARED:
                    {
                        message = now + "Out Event from Vidyoclient: " + actionType;
                    }
                    break;


                case Vidyo32.VidyoClientOutEvent.VIDYO_CLIENT_OUT_EVENT_CALL_PROGRESS:
                    {
                        //we can send this value to progress bar
                        numProgressSteps--;
                        message += " Step " + numProgressSteps.ToString();
                    }
                    break;
                #endregion  VIDYO_CLIENT_OUT_EVENT(s) RINGING, CALLING AND RPOGRESS
                default:
                    {
                    }
                    break;
            }


            if (listBox1.InvokeRequired)
                listBox1.Invoke(new UpdateListBoxHandler(UpdateTextBox), message);
            else
                listBox1.Items.Add(message);
        }     

        private void DisableDirectCall(bool value)
        {
            this.btnCancelDirect.Enabled = value;
            this.btnCancelDirect.Visible = value;
        }

        private void ThreadProcUnsafe(bool value)
        {
            this.btnSubmitUser.Enabled = value;
            this.btnSubmitUser.Visible = value;
            this.txtBxUserURI.Enabled = value;
            this.txtBxUsrNm.Enabled = value;
            this.txtBxPwd.Enabled = value;
        }

        private void UpdateTextBox(String message)
        {
            int ind = listBox1.Items.Add(message);
            listBox1.SelectedIndex = ind;
        }

        private void cmdLeave_Click(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_LEAVE, (IntPtr)0, 0);

            if (comboBox1.SelectedItem.ToString() == "User Login")
            {
                panel1.Visible = true;
                panel3.Visible = true;

                panel1.Enabled = true;
                panel3.Enabled = false;
            }
            else
            {
                panel2.Visible = true;
                panel2.Enabled = false;
            }

            label1.Visible = true;
            label2.Visible = true;
            label3.Visible = true;
            label4.Visible = true;
            label5.Visible = true;
            label6.Visible = true;
            label7.Visible = true;
            label8.Visible = true;
            label8.Visible = true;
            txtBxGuestNm.Visible = true;
            txtBxGuestURI.Visible = true;
            txtBxPwd.Visible = true;

            txtBxRoomPin.Visible = true;
            txtBxUserURI.Visible = true;
            txtBxUsrNm.Visible = true;
            btnSubmitGuest.Visible = true;
            btnSubmitUser.Visible = true;

            txtBxGuestNm.Enabled = true;
            txtBxGuestURI.Enabled = true;
            txtBxPwd.Enabled = true;

            txtBxRoomPin.Enabled = true;
            txtBxUserURI.Enabled = true;
            txtBxUsrNm.Enabled = true;

            btnDirect.Visible = false;
            btnCancelDirect.Visible = false;
            btnJoin.Visible = false;
            cmdLeave.Visible = false;
            btnJoinPublicRoom.Visible = false;

            cmbBxLocalShares.Items.Clear();
            cmbBxRemoteShares.Items.Clear();

        }

        public void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Vidyo32.VidyoClientStop();
            System.Threading.Thread.Sleep(18);
            Vidyo32.VidyoClientUninitialize();
            Application.Exit();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            diffW = this.Width - pnlVideoArea.Width;
            diffH = this.Height - pnlVideoArea.Height;
        }


        private void chkMuteSpeaker_CheckedChanged(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientRequestVolume vlmParam = new Vidyo32.VidyoClientRequestVolume();
            if (chkMuteSpeaker.Checked)
            {
                //nn vlmParam.isMuted = Vidyo32.VidyoBool.VIDYO_TRUE  ;
            }
            else
            {
                //nn vlmParam.isMuted = Vidyo32.VidyoBool.VIDYO_FALSE ;
                vlmParam.volume = 32000;
            }
            int size = Marshal.SizeOf(vlmParam);
            IntPtr ptr = Marshal.AllocCoTaskMem(size);
            Marshal.StructureToPtr(vlmParam, ptr, false);
            uint errVolSet = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_VOLUME_AUDIO_OUT, ptr, size);
            if (errVolSet == 0)
            {
                Vidyo32.VidyoClientRequestVolume strucVolParNw = (Vidyo32.VidyoClientRequestVolume)Marshal.PtrToStructure(ptr, typeof(Vidyo32.VidyoClientRequestVolume));
            }
        }

        private void chkPreview_CheckedChanged(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientInEventPreview EventPreview = new Vidyo32.VidyoClientInEventPreview();
            switch (PreviewMode)
            {
                case Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_NONE:
                    {
                        PreviewMode = Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_PIP;
                    } break;

                case Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_PIP:
                    {
                        PreviewMode = Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_DOCK;
                    } break;

                case Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_DOCK:
                    {
                        PreviewMode = Vidyo32.VidyoClientPreviewMode.VIDYO_CLIENT_PREVIEW_MODE_NONE;
                    } break;
            }
            EventPreview.PreviewMode = PreviewMode;
            int szEventPreview = Marshal.SizeOf(EventPreview);
            IntPtr ptrEventPreview = Marshal.AllocCoTaskMem(szEventPreview);
            Marshal.StructureToPtr(EventPreview, ptrEventPreview, true);
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_PREVIEW, ptrEventPreview, szEventPreview);
            EventPreview = (Vidyo32.VidyoClientInEventPreview)Marshal.PtrToStructure(ptrEventPreview, typeof(Vidyo32.VidyoClientInEventPreview));

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

        private void chkLayout_CheckedChanged(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientInEventLayout layoutParam = new Vidyo32.VidyoClientInEventLayout();
            if (chkLayout.Checked)
            {
                layoutParam.layout_num = 1;
            }
            else
            {
                layoutParam.layout_num = 0;
            }
            int size = Marshal.SizeOf(layoutParam);
            IntPtr ptr = Marshal.AllocCoTaskMem(size);
            Marshal.StructureToPtr(layoutParam, ptr, false);
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_LAYOUT, ptr, size);

        }

        private void MuteMic_CheckedChanged_1(object sender, EventArgs e)
        {
            string message;
            Vidyo32.VidyoClientInEventMute muteAudio = new Vidyo32.VidyoClientInEventMute();

            if (MuteMic.Checked)
            {
                muteAudio.isMuted = Vidyo32.VidyoBool.VIDYO_TRUE;
            }
            else
            {
                muteAudio.isMuted = Vidyo32.VidyoBool.VIDYO_FALSE;
            }

            int size1 = Marshal.SizeOf(muteAudio);
            IntPtr muteAudioptr = Marshal.AllocCoTaskMem(size1);
            Marshal.StructureToPtr(muteAudio, muteAudioptr, true);
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_MUTE_AUDIO_IN, muteAudioptr, size1);

            Vidyo32.VidyoClientRequestGetMuted ReqGetMuted = new Vidyo32.VidyoClientRequestGetMuted();
            int size2 = Marshal.SizeOf(ReqGetMuted);
            IntPtr MuteMicrophoneptr = Marshal.AllocCoTaskMem(size2);
            Marshal.StructureToPtr(muteAudio, MuteMicrophoneptr, true);
            // Marshal.StructureToPtr(ReqGetMuted, MuteMicrophoneptr, true);
            uint errMute = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_MUTED_AUDIO_IN, MuteMicrophoneptr, size2);
            if (errMute == 2)
            {
                Vidyo32.VidyoClientRequestGetMuted OutVideoVul = (Vidyo32.VidyoClientRequestGetMuted)Marshal.PtrToStructure(MuteMicrophoneptr, typeof(Vidyo32.VidyoClientRequestGetMuted));
            }

            if (ReqGetMuted.isMuted == Vidyo32.VidyoBool.VIDYO_TRUE)
            {
                message = "Vidyo Is Muted" + ReqGetMuted.isMuted;
            }

            else
            {
                message = "Vidyo Is not Muted" + ReqGetMuted.isMuted;
            }

        }

        private void chkMuteVideo_CheckedChanged_1(object sender, EventArgs e)
        {
            string message;
            Vidyo32.VidyoClientInEventMute muteVideo = new Vidyo32.VidyoClientInEventMute();
            if (chkMuteVideo.Checked)
            {
                muteVideo.isMuted = Vidyo32.VidyoBool.VIDYO_TRUE;
            }
            else
            {
                muteVideo.isMuted = Vidyo32.VidyoBool.VIDYO_FALSE;
            }

            int size1 = Marshal.SizeOf(muteVideo);
            IntPtr ptr1 = Marshal.AllocCoTaskMem(size1);
            Marshal.StructureToPtr(muteVideo, ptr1, true);
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_MUTE_VIDEO, ptr1, size1);

            //Inquire privacy state of video camera device.
            Vidyo32.VidyoClientRequestGetMuted ReqGetMuted = new Vidyo32.VidyoClientRequestGetMuted();
            int size2 = Marshal.SizeOf(ReqGetMuted);
            IntPtr MuteVideoptr = Marshal.AllocCoTaskMem(size2);
            Marshal.StructureToPtr(ReqGetMuted, MuteVideoptr, true);
            uint errMute = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_MUTED_VIDEO, MuteVideoptr, size2);
            if (errMute == 2)
            {
                Vidyo32.VidyoClientRequestGetMuted OutVideoVul = (Vidyo32.VidyoClientRequestGetMuted)Marshal.PtrToStructure(MuteVideoptr, typeof(Vidyo32.VidyoClientRequestGetMuted));
            }

            if (ReqGetMuted.isMuted == Vidyo32.VidyoBool.VIDYO_TRUE)
            {
                message = "Vidyo Is Muted" + ReqGetMuted.isMuted;
            }

            else
            {
                message = "Vidyo Is not Muted" + ReqGetMuted.isMuted;
            }
        }

        private void btnSubmitUser_Click(object sender, EventArgs e)
        {
            panel1.Visible = true;
            panel2.Visible = false;
            panel3.Visible = true;
            txtBxGuestNm.Enabled = false;
            txtBxGuestURI.Enabled = false;
            txtBxPwd.Enabled = false;
            txtBxRoomPin.Enabled = false;
            txtBxUserURI.Enabled = false;
            txtBxUsrNm.Enabled = false;
            btnSubmitUser.Visible = false;

            btnJoin.Visible = true;
            btnDirect.Visible = true;
            cmdLeave.Visible = true;
            btnCreateRoom.Visible = true;
            btnJoinPublicRoom.Visible = true;

            btnJoin.Enabled = true;
            btnDirect.Enabled = true;
            btnDirect.Enabled = true;
            btnDirect.Enabled = true;
            btnLogout.Enabled = true;

            Vidyo32.VidyoClientInEventLogin Login = new Vidyo32.VidyoClientInEventLogin();
            Login.portalUri = txtBxUserURI.Text;
            Login.userName = txtBxUsrNm.Text;
            Login.userPass = txtBxPwd.Text;

            int size = Marshal.SizeOf(Login);
            IntPtr ptr = Marshal.AllocCoTaskMem(size);
            Marshal.StructureToPtr(Login, ptr, false);

            Int32 test = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_LOGIN, ptr, size);
            Login = (Vidyo32.VidyoClientInEventLogin)Marshal.PtrToStructure(ptr, typeof(Vidyo32.VidyoClientInEventLogin));
        }

        private void btnSubmitGuest_Click(object sender, EventArgs e)
        {
            panel1.Visible = false;
            panel2.Visible = false;
            label1.Visible = false;
            label2.Visible = false;
            label3.Visible = false;
            label4.Visible = false;
            label5.Visible = false;
            label6.Visible = false;
            label7.Visible = false;
            label8.Visible = false;
            label8.Visible = false;
            txtBxGuestNm.Visible = false;
            txtBxGuestURI.Visible = false;
            txtBxPwd.Visible = false;

            txtBxRoomPin.Visible = false;
            txtBxUserURI.Visible = false;
            txtBxUsrNm.Visible = false;

            btnJoin.Visible = true;
            btnDirect.Visible = true;
            cmdLeave.Visible = true;

            btnDirect.Enabled = false;
            btnJoin.Enabled = false;
            cmdLeave.Enabled = true;

            string[] separator = new string[] { "//", "/", "key=" };
            string[] guestUrlSplit = txtBxGuestURI.Text.Split(separator, StringSplitOptions.None);

            Vidyo32.VidyoClientInEventRoomLink GuestLogin = new Vidyo32.VidyoClientInEventRoomLink();

            GuestLogin.portalUri = guestUrlSplit[0] + "//" + guestUrlSplit[1];
            GuestLogin.roomKey = guestUrlSplit[3];
            GuestLogin.displayName = txtBxGuestNm.Text;
            GuestLogin.pin = txtBxRoomPin.Text;
            GuestLogin.clientType = VGUClientLogic.Vidyo32.VidyoClientClientType.VIDYO_CLIENT_CLIENTTYPE_W;
            GuestLogin.muteCamera = Vidyo32.VidyoBool.VIDYO_FALSE;
            GuestLogin.muteMicrophone = Vidyo32.VidyoBool.VIDYO_FALSE;
            GuestLogin.muteSpeaker = Vidyo32.VidyoBool.VIDYO_FALSE;

            int Gsize = Marshal.SizeOf(GuestLogin);
            IntPtr Gptr = Marshal.AllocCoTaskMem(Gsize);
            Marshal.StructureToPtr(GuestLogin, Gptr, false);

            Int32 Guest = Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_ROOM_LINK, Gptr, Gsize);

            GuestLogin = (Vidyo32.VidyoClientInEventRoomLink)Marshal.PtrToStructure(Gptr, typeof(Vidyo32.VidyoClientInEventRoomLink));

        }

        private void btnJoin_Click(object sender, EventArgs e)
        {
            btnDirect.Enabled = false;
            cmdLeave.Visible = true;
            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            try
            {
                client.Open();

                MyAccountRequest accnt = new MyAccountRequest();

                MyAccountResponse response = client.myAccount(accnt);

                JoinConferenceRequest joinRequest = new JoinConferenceRequest();
                joinRequest.Item = response.Entity.entityID;

                JoinConferenceResponse joinResponse = client.joinConference(joinRequest);

                client.Close();
            }
            catch (Exception ex)
            {
                string errorMessage = ex.ToString();

            }
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            btnJoin.Visible = true;
            btnDirect.Visible = true;
            cmdLeave.Visible = true;
            btnDirect.Enabled = true;
            btnJoin.Enabled = false;
            cmdLeave.Enabled = true;

            int count = 0;
            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            comboBoxRemoteUsers.Items.Clear();
            try
            {
                client.Open();

                // First get my entity ID to send back to caller
                MyAccountRequest accnt = new MyAccountRequest();
                MyAccountResponse response = client.myAccount(accnt);
                string myEntityID = response.Entity.entityID;

                // Next do the search request
                SearchRequest searchReq = new SearchRequest();
                searchReq.Filter = new Filter();
                searchReq.Filter.start = 0;
                searchReq.Filter.limit = 20;
                searchReq.Filter.sortBy = "displayName";
                searchReq.Filter.query = txtRemoteUser.Text;

                SearchResponse searchRes = client.search(searchReq);

                // Check if any users were found
                if (searchRes.total > 0)
                {
                    for (int i = 0; i < searchRes.total; i++)
                    {
                        if (searchRes.Entity[i].MemberStatus == MemberStatus.Online)
                        {
                            comboBoxRemoteUsers.Items.Add(searchRes.Entity[i].displayName);
                            count++;
                        }
                        if (count == 0)
                        {
                            comboBoxRemoteUsers.Items.Add(searchRes.Entity[count].MemberStatus);
                            count = -1;
                        }
                    }
                }

                client.Close();
            }
            catch (Exception ex)
            {
                string error = ex.Message;
            }
        }

        private void comboBoxRemoteUsers_SelectedIndexChanged(object sender, EventArgs e)
        {
            Object selectedItem = comboBoxRemoteUsers.SelectedItem;

            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            try
            {
                client.Open();

                // First get my entity ID to send back to caller
                MyAccountRequest accnt = new MyAccountRequest();
                MyAccountResponse response = client.myAccount(accnt);
                string myEntityID = response.Entity.entityID;

                // Next do the search request
                SearchRequest searchReq = new SearchRequest();
                searchReq.Filter = new Filter();
                searchReq.Filter.query = selectedItem.ToString();
                SearchResponse searchRes = client.search(searchReq);

                // Check if any users were found
                if (searchRes.total > 0)
                {
                    directCallEntityID = searchRes.Entity[0].entityID;
                }
                client.Close();
            }
            catch (Exception ex)
            {
                string error = ex.Message;

            }
        }

        private void btnDirect_Click(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientInEventPortalService PortalService = new Vidyo32.VidyoClientInEventPortalService();
            PortalService.directCall.entityType = Vidyo32.VidyoClientPortalServiceEntityType.VIDYO_CLIENT_ENTITY_TYPE_MEMBER;
            PortalService.directCall.typeRequest = 0;
            byte[] entityMemberArr = System.Text.Encoding.UTF8.GetBytes(directCallEntityID);
            unsafe
            {

                Marshal.Copy(entityMemberArr, 0, (IntPtr)PortalService.directCall.entityID, entityMemberArr.Length);
            }

            int size1 = Marshal.SizeOf(PortalService);
            IntPtr ptr1 = Marshal.AllocCoTaskMem(size1);
            Marshal.StructureToPtr(PortalService, ptr1, false);
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_PORTAL_SERVICE, ptr1, size1);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            panel1.Enabled = true;
            panel2.Enabled = true;
            panel3.Enabled = true;

            txtPublicRoomUrl.Text = "";

            if (comboBox1.SelectedItem.ToString() == "User Login")
            {
                panel1.Visible = true;
                panel2.Visible = false;
                panel3.Visible = true;

                panel1.Location = new Point(897, 188);
                panel1.Size = new System.Drawing.Size(337, 250);

                panel3.Location = new Point(898, 472);
                panel3.Size = new System.Drawing.Size(337, 173);
            }
            else if (comboBox1.SelectedItem.ToString() == "Guest Login")
            {

                panel1.Visible = false;
                panel2.Visible = true;
                panel3.Visible = false;

                panel2.Location = new Point(897, 188);
                panel2.Size = new System.Drawing.Size(337, 175);
            }

        }

        private void btnLogout_Click(object sender, EventArgs e)
        {
            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            try
            {
                client.Open();
                LogOutRequest logout = new LogOutRequest();
                LogOutResponse resLogOut = client.logOut(logout);

                client.Close();

            }
            catch (Exception ex)
            {
                string error = ex.Message;

            }
        }

        private void btnRequest_Click(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientRequestConfiguration strucConfig = new Vidyo32.VidyoClientRequestConfiguration();
            int size = Marshal.SizeOf(strucConfig);
            IntPtr ptrConfig = Marshal.AllocCoTaskMem(size);
            Marshal.StructureToPtr(strucConfig, ptrConfig, false);
            uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, ptrConfig, size);
            if (error == 0)
            {
                string pass = strucConfig.GetPassword();
                string[] mics = strucConfig.GetMicrophones();
                string userID = strucConfig.GetUserID();
                string[] camera = strucConfig.GetCameras();
                string[] speakers = strucConfig.GetSpeakers();
                strucConfig.enableEntryTone = 0;
                strucConfig.enableFeccController = 1;
                strucConfig.enableFeccEndpoint = 1;
                strucConfig.enableAutoAnswer = 0;
                strucConfig.enableAutoLogIn = 0;
                uint error2 = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, ptrConfig, size);
            }
        }

        private void btnCancelDirect_Click(object sender, EventArgs e)
        {
            Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_CANCEL, (IntPtr)0, 0);
            label1.Visible = true;
            label2.Visible = true;
            label3.Visible = true;
            label4.Visible = true;
            label5.Visible = true;
            label6.Visible = true;
            label7.Visible = true;
            label8.Visible = true;
            label8.Visible = true;
            txtBxGuestNm.Visible = true;
            txtBxGuestURI.Visible = true;
            txtBxPwd.Visible = true;

            txtBxRoomPin.Visible = true;
            txtBxUserURI.Visible = true;
            txtBxUsrNm.Visible = true;
            btnSubmitGuest.Visible = true;
            btnSubmitUser.Visible = true;

            txtBxGuestNm.Enabled = true;
            txtBxGuestURI.Enabled = true;
            txtBxPwd.Enabled = true;

            txtBxRoomPin.Enabled = true;
            txtBxUserURI.Enabled = true;
            txtBxUsrNm.Enabled = true;

            btnDirect.Visible = true;
            btnCancelDirect.Visible = false;
            btnJoin.Visible = true;
            btnJoin.Enabled = true;
            cmdLeave.Visible = false;
        }

        public struct WindowAndDesktopData
        {
            // Window specific app parameters
            public uint numApplicationWindows;
            public string[] appWindowName;
            public string[] appWindowAppName;
            public IntPtr[] appWindowId;
            public Vidyo32.VidyoRect[] appWindowRect;

            // Desktop specific parameters
            public uint numSystemDesktops;
            public string[] sysDesktopName;
            public IntPtr[] sysDesktopId;
            public Vidyo32.VidyoRect[] sysDesktopRect;
        };

        public WindowAndDesktopData aWinShareData;
        public IntPtr[] appID;
        Vidyo32.VidyoClientRequestGetWindowsAndDesktops lholdWinDesktopsStruct = new Vidyo32.VidyoClientRequestGetWindowsAndDesktops();

        

        Vidyo32.VidyoClientRequestWindowShares RtShareInfo;
        
        public const int SW_RESTORE = 9;

        private void BringToForeground(IntPtr extHandle)
        {
            if (Vidyo32.IsIconic(extHandle))
            {
                Vidyo32.ShowWindow(extHandle, SW_RESTORE);
            }
            Vidyo32.SetForegroundWindow(extHandle);
        }

        private void cmbBxLocalShares_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbBxLocalShares.SelectedItem.ToString() == "Stop Local Share")
            {
                Vidyo32.VidyoClientInEventUnShare EventUnShare = new Vidyo32.VidyoClientInEventUnShare();
                int szEventUnShare = Marshal.SizeOf(EventUnShare);
                IntPtr ptrEventUnShare = Marshal.AllocCoTaskMem(szEventUnShare);
                Marshal.StructureToPtr(EventUnShare, ptrEventUnShare, true);
                Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_UNSHARE, ptrEventUnShare, szEventUnShare);
                cmbBxLocalShares.Items.Clear();
            }

            else
            {
                int index = cmbBxLocalShares.SelectedIndex;
                IntPtr HWnd = IntPtr.Zero;
                lholdWinDesktopsStruct.Init();

                try
                {
                    HWnd = appID[index];
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Exception in sharing window");

                }
                if (HWnd != IntPtr.Zero)
                {
                    // IntPtr ptrHWND = new IntPtr(HWnd);
                    BringToForeground(HWnd);
                    Vidyo32.VidyoClientInEventShare EventShare = new Vidyo32.VidyoClientInEventShare();
                    EventShare.window = HWnd;
                    if (cmbBxLocalShares.SelectedItem.ToString() != "DISPLAY1")
                        EventShare.shareType = Vidyo32.VidyoClientContentsShareType.VIDYO_CLIENT_CONTENTS_SHARE_TYPE_APPLICATION_WINDOW;
                    else
                        EventShare.shareType = Vidyo32.VidyoClientContentsShareType.VIDYO_CLIENT_CONTENTS_SHARE_TYPE_DESKTOP_WINDOW;
                    int szEventShare = Marshal.SizeOf(EventShare);
                    IntPtr ptrEventShare = Marshal.AllocCoTaskMem(szEventShare);
                    Marshal.StructureToPtr(EventShare, ptrEventShare, true);
                    Vidyo32.VidyoClientSendEvent(Vidyo32.VidyoClientInEvent.VIDYO_CLIENT_IN_EVENT_SHARE, ptrEventShare, szEventShare);
                    EventShare = (Vidyo32.VidyoClientInEventShare)Marshal.PtrToStructure(ptrEventShare, typeof(Vidyo32.VidyoClientInEventShare));

                    RtShareInfo = new Vidyo32.VidyoClientRequestWindowShares();
                    int szShareInfo = Marshal.SizeOf(RtShareInfo);
                    IntPtr ptrShareInfo = Marshal.AllocCoTaskMem(szShareInfo);
                    Marshal.StructureToPtr(RtShareInfo, ptrShareInfo, true);
                    uint errShareInfo = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, ptrShareInfo, szShareInfo);
                    if (errShareInfo == 0)
                    {
                        RtShareInfo = (Vidyo32.VidyoClientRequestWindowShares)Marshal.PtrToStructure(ptrShareInfo, typeof(Vidyo32.VidyoClientRequestWindowShares));

                        RtShareInfo.shareList.newApp = index + 1;
                        RtShareInfo.shareReqType = Vidyo32.VidyoClientWindowShareRequestType.CHANGE_SHARING_WINDOW;
                        IntPtr ptrShareInfo2 = Marshal.AllocCoTaskMem(szShareInfo);
                        Marshal.StructureToPtr(RtShareInfo, ptrShareInfo2, true);
                        uint errShareInfo2 = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, ptrShareInfo2, szShareInfo);
                    }


                }
            }

        }

        private void cmbBxRemoteShares_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbBxRemoteShares.SelectedItem.ToString() == "Stop Remote Share")
            {
                cmbBxRemoteShares.Items.Clear();
                RtShareInfo = new Vidyo32.VidyoClientRequestWindowShares();
                int szShareInfo = Marshal.SizeOf(RtShareInfo);
                IntPtr ptrShareInfo = Marshal.AllocCoTaskMem(szShareInfo);
                Marshal.StructureToPtr(RtShareInfo, ptrShareInfo, true);
                uint errShareInfo = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, ptrShareInfo, szShareInfo);
                if (errShareInfo == 0)
                {
                    RtShareInfo = (Vidyo32.VidyoClientRequestWindowShares)Marshal.PtrToStructure(ptrShareInfo, typeof(Vidyo32.VidyoClientRequestWindowShares));
                    RtShareInfo.shareReqType = Vidyo32.VidyoClientWindowShareRequestType.CHANGE_SHARING_WINDOW;
                    RtShareInfo.shareList.numApp = 1;
                    RtShareInfo.shareList.newApp = 0;
                    RtShareInfo.shareList.currApp = 0;
                    IntPtr ptrShareInfo2 = Marshal.AllocCoTaskMem(szShareInfo);
                    Marshal.StructureToPtr(RtShareInfo, ptrShareInfo2, true);

                    uint errShareInfo2 = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, ptrShareInfo2, szShareInfo);

                      if (errShareInfo2 == 0)
                      {
                           errShareInfo = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, ptrShareInfo2, szShareInfo);
                      }

                }
            }
            else
            {
                int indx = cmbBxRemoteShares.SelectedIndex;

                RtShareInfo = new Vidyo32.VidyoClientRequestWindowShares();
                int szShareInfo = Marshal.SizeOf(RtShareInfo);
                IntPtr ptrShareInfo = Marshal.AllocCoTaskMem(szShareInfo);
                Marshal.StructureToPtr(RtShareInfo, ptrShareInfo, true);
                uint errShareInfo = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, ptrShareInfo, szShareInfo);
                if (errShareInfo == 0)
                {
                    RtShareInfo = (Vidyo32.VidyoClientRequestWindowShares)Marshal.PtrToStructure(ptrShareInfo, typeof(Vidyo32.VidyoClientRequestWindowShares));

                    RtShareInfo.shareList.newApp = indx + 1;
                    RtShareInfo.shareReqType = Vidyo32.VidyoClientWindowShareRequestType.CHANGE_SHARING_WINDOW;
                    IntPtr ptrShareInfo2 = Marshal.AllocCoTaskMem(szShareInfo);
                    Marshal.StructureToPtr(RtShareInfo, ptrShareInfo2, true);
                    uint errShareInfo2 = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, ptrShareInfo2, szShareInfo);
                }
            }
        }


       
        private void cmbBxLocalShares_DropDown(object sender, System.EventArgs e)
        {
            cmbBxLocalShares.Items.Clear();
            

            IntPtr innerPtr = IntPtr.Zero;


            lholdWinDesktopsStruct.Init();

            lholdWinDesktopsStruct.numApplicationWindows = 0;
            appID = new IntPtr[Vidyo32.MAX_REMOTE_SHARE_APP];

            // Initialize window specific data
            for (int i = 0; i < Vidyo32.MAX_REMOTE_SHARE_APP; i++)
            {
                lholdWinDesktopsStruct.appWindowName[i] = "";
                lholdWinDesktopsStruct.appWindowAppName[i] = "";
                lholdWinDesktopsStruct.appWindowRect[i].height = 0;
                lholdWinDesktopsStruct.appWindowRect[i].width = 0;
                lholdWinDesktopsStruct.appWindowRect[i].xPos = 0;
                lholdWinDesktopsStruct.appWindowRect[i].yPos = 0;
            }

            // Initialize window specific data
            for (int i = 0; i < Vidyo32.MAX_SHARE_DISPLAY_DEVICE; i++)
            {
                lholdWinDesktopsStruct.sysDesktopName[i] = "";
                lholdWinDesktopsStruct.sysDesktopRect[i].height = 0;
                lholdWinDesktopsStruct.sysDesktopRect[i].width = 0;
                lholdWinDesktopsStruct.sysDesktopRect[i].xPos = 0;
                lholdWinDesktopsStruct.sysDesktopRect[i].yPos = 0;

            }


            int innerSize = Marshal.SizeOf(lholdWinDesktopsStruct);
            innerPtr = Marshal.AllocCoTaskMem(innerSize);
            Marshal.StructureToPtr(lholdWinDesktopsStruct, innerPtr, false);

            uint error = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOWS_AND_DESKTOPS, innerPtr, innerSize);

            lholdWinDesktopsStruct = (Vidyo32.VidyoClientRequestGetWindowsAndDesktops)Marshal.PtrToStructure(innerPtr, typeof(Vidyo32.VidyoClientRequestGetWindowsAndDesktops));


            uint lNumAppWins = lholdWinDesktopsStruct.numApplicationWindows;
            aWinShareData.numApplicationWindows = lholdWinDesktopsStruct.numApplicationWindows;
            aWinShareData.appWindowAppName = new string[lNumAppWins];
            aWinShareData.appWindowId = new IntPtr[lNumAppWins];
            aWinShareData.appWindowName = new string[lNumAppWins];
            aWinShareData.appWindowRect = new Vidyo32.VidyoRect[lNumAppWins];

            for (int i = 0; i < lNumAppWins; i++)
            {
                aWinShareData.appWindowAppName[i] = lholdWinDesktopsStruct.appWindowAppName[i];
                aWinShareData.appWindowId[i] = lholdWinDesktopsStruct.appWindowId[i];
                aWinShareData.appWindowName[i] = lholdWinDesktopsStruct.appWindowName[i];
                aWinShareData.appWindowRect[i].height = lholdWinDesktopsStruct.appWindowRect[i].height;
                aWinShareData.appWindowRect[i].width = lholdWinDesktopsStruct.appWindowRect[i].width;
                aWinShareData.appWindowRect[i].xPos = lholdWinDesktopsStruct.appWindowRect[i].xPos;
                aWinShareData.appWindowRect[i].yPos = lholdWinDesktopsStruct.appWindowRect[i].yPos;

                cmbBxLocalShares.Items.Add(aWinShareData.appWindowAppName[i].ToString());
                appID[i] = lholdWinDesktopsStruct.appWindowId[i];
            }

            uint lNumDesktops = lholdWinDesktopsStruct.numSystemDesktops;
            aWinShareData.numSystemDesktops = lholdWinDesktopsStruct.numSystemDesktops;
            aWinShareData.sysDesktopId = new IntPtr[lNumDesktops];
            aWinShareData.sysDesktopName = new string[lNumDesktops];
            aWinShareData.sysDesktopRect = new Vidyo32.VidyoRect[lNumDesktops];

            for (int j = 0; j < lNumDesktops; j++)
            {
                aWinShareData.sysDesktopId[j] = lholdWinDesktopsStruct.sysDesktopId[j];
                aWinShareData.sysDesktopName[j] = lholdWinDesktopsStruct.sysDesktopName[j];
                aWinShareData.sysDesktopRect[j].height = lholdWinDesktopsStruct.sysDesktopRect[j].height;
                aWinShareData.sysDesktopRect[j].width = lholdWinDesktopsStruct.sysDesktopRect[j].width;
                aWinShareData.sysDesktopRect[j].xPos = lholdWinDesktopsStruct.sysDesktopRect[j].xPos;
                aWinShareData.sysDesktopRect[j].yPos = lholdWinDesktopsStruct.sysDesktopRect[j].yPos;

                cmbBxLocalShares.Items.Add(aWinShareData.sysDesktopName[j].ToString());
            }

            cmbBxLocalShares.Items.Add("Stop Local Share");
        }


        private void cmbBxRemoteShares_DropDown(object sender, System.EventArgs e)
        {
            cmbBxRemoteShares.Items.Clear();
            RtShareInfo = new Vidyo32.VidyoClientRequestWindowShares();
            int szRtShareInfo = Marshal.SizeOf(RtShareInfo);
            IntPtr ptrRtShareInfo = Marshal.AllocCoTaskMem(szRtShareInfo);
            Marshal.StructureToPtr(RtShareInfo, ptrRtShareInfo, true);
            uint errRtShareInfo = Vidyo32.VidyoClientSendRequest(Vidyo32.VidyoClientRequest.VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, ptrRtShareInfo, szRtShareInfo);
            if (errRtShareInfo == 0)
            {
                RtShareInfo = (Vidyo32.VidyoClientRequestWindowShares)Marshal.PtrToStructure(ptrRtShareInfo, typeof(Vidyo32.VidyoClientRequestWindowShares));
                uint numApp = RtShareInfo.shareList.numApp;
                string[] ListApp = RtShareInfo.shareList.GetShareUriList();


                for (int i = 0; i < numApp; i++)
                {
                    cmbBxRemoteShares.Items.Add(ListApp[i]);
                }
            }

            cmbBxRemoteShares.Items.Add("Stop Remote Share");
        }

        private void btnCreateRoom_Click(object sender, EventArgs e)
        {
            btnDirect.Enabled = false;
            cmdLeave.Visible = true;
            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            try
            {
                client.Open();

                Random rnd = new Random();
                int extension = rnd.Next(10000, 99999);
                //make sure tenant prefix is a number
                txtRoomExtension.Text = txtTenantPrefix.Text + extension;
                CreateRoomRequest roomRequest = new CreateRoomRequest();
                roomRequest.name = "Room " + txtRoomExtension.Text;
                roomRequest.extension = txtRoomExtension.Text;
                CreateRoomResponse roomResponse = client.createRoom(roomRequest);

                String roomId = roomResponse.Entity.entityID;

                txtRoomId.Text = roomId;
                txtPublicRoomUrl.Text = roomResponse.Entity.RoomMode.roomURL;

                btnJoinPublicRoom.Enabled = true;

                client.Close();
            }
            catch (Exception ex)
            {
                //string errorMessage = ex.ToString();
                txtPublicRoomUrl.Text = ex.Message.ToString();

            }
        }

        private void btnDelRoom_Click(object sender, EventArgs e)
        {
            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            try
            {
                client.Open();

                String roomId = txtRoomId.Text;

                DeleteRoomRequest delRequest = new DeleteRoomRequest();
                delRequest.roomID = roomId;

                DeleteRoomResponse delResponse = client.deleteRoom(delRequest);

                client.Close();

                btnJoinPublicRoom.Enabled = false;

                txtRoomExtension.Text = "";
                txtRoomId.Text = "";
                txtPublicRoomUrl.Text = "Successful!!";
                
               
            }
            catch (Exception ex)
            {
                txtPublicRoomUrl.Text = ex.Message.ToString();

            }
        }

        private void btnJoinPublicRoom_Click(object sender, EventArgs e)
        {
            string portal = txtBxUserURI.Text;
            EndpointAddress endpoint = new EndpointAddress(new Uri(portal + "/services/v1_1/VidyoPortalUserService/"));
            HttpBindingBase binding = GetBinding(portal);
            var client = new VidyoPortalUserServicePortTypeClient(binding, endpoint);

            client.ClientCredentials.UserName.UserName = txtBxUsrNm.Text;
            client.ClientCredentials.UserName.Password = txtBxPwd.Text;

            try
            {
                client.Open();

                JoinConferenceRequest joinRequest = new JoinConferenceRequest();
                joinRequest.Item = txtRoomId.Text;

                JoinConferenceResponse joinResponse = client.joinConference(joinRequest);

                client.Close();
            }
            catch (Exception ex)
            {
                string errorMessage = ex.ToString();
            }
        }

    }

}









namespace VidyoClientCS
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.pnlVideoArea = new System.Windows.Forms.Panel();
            this.chkMuteSpeaker = new System.Windows.Forms.CheckBox();
            this.cmdLeave = new System.Windows.Forms.Button();
            this.MuteMic = new System.Windows.Forms.CheckBox();
            this.chkPreview = new System.Windows.Forms.CheckBox();
            this.chkLayout = new System.Windows.Forms.CheckBox();
            this.tmrSubscribe = new System.Windows.Forms.Timer(this.components);
            this.chkMuteVideo = new System.Windows.Forms.CheckBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.txtTenantPrefix = new System.Windows.Forms.TextBox();
            this.btnDelRoom = new System.Windows.Forms.Button();
            this.txtPublicRoomUrl = new System.Windows.Forms.TextBox();
            this.btnLogout = new System.Windows.Forms.Button();
            this.btnSubmitUser = new System.Windows.Forms.Button();
            this.btnCreateRoom = new System.Windows.Forms.Button();
            this.txtBxPwd = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtBxUsrNm = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtBxUserURI = new System.Windows.Forms.TextBox();
            this.comboBoxRemoteUsers = new System.Windows.Forms.ComboBox();
            this.txtRemoteUser = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.btnSearch = new System.Windows.Forms.Button();
            this.btnDirect = new System.Windows.Forms.Button();
            this.btnJoin = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.btnSubmitGuest = new System.Windows.Forms.Button();
            this.txtBxRoomPin = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txtBxGuestNm = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtBxGuestURI = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.btnCancelDirect = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.cmbBxRemoteShares = new System.Windows.Forms.ComboBox();
            this.cmbBxLocalShares = new System.Windows.Forms.ComboBox();
            this.btnRequest = new System.Windows.Forms.Button();
            this.RoomInfo = new System.Windows.Forms.Panel();
            this.txtRoomId = new System.Windows.Forms.TextBox();
            this.txtRoomExtension = new System.Windows.Forms.TextBox();
            this.labelRoomExtension = new System.Windows.Forms.Label();
            this.btnJoinPublicRoom = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            this.RoomInfo.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.Location = new System.Drawing.Point(12, 2);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(1156, 134);
            this.listBox1.TabIndex = 3;
            // 
            // pnlVideoArea
            // 
            this.pnlVideoArea.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlVideoArea.Location = new System.Drawing.Point(13, 142);
            this.pnlVideoArea.Name = "pnlVideoArea";
            this.pnlVideoArea.Size = new System.Drawing.Size(803, 425);
            this.pnlVideoArea.TabIndex = 4;
            this.pnlVideoArea.SizeChanged += new System.EventHandler(this.pnlVideoArea_SizeChanged);
            // 
            // chkMuteSpeaker
            // 
            this.chkMuteSpeaker.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.chkMuteSpeaker.AutoSize = true;
            this.chkMuteSpeaker.Location = new System.Drawing.Point(751, 38);
            this.chkMuteSpeaker.Name = "chkMuteSpeaker";
            this.chkMuteSpeaker.Size = new System.Drawing.Size(90, 17);
            this.chkMuteSpeaker.TabIndex = 9;
            this.chkMuteSpeaker.Text = "MuteSpeaker";
            this.chkMuteSpeaker.UseVisualStyleBackColor = true;
            this.chkMuteSpeaker.CheckedChanged += new System.EventHandler(this.chkMuteSpeaker_CheckedChanged);
            // 
            // cmdLeave
            // 
            this.cmdLeave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdLeave.BackColor = System.Drawing.Color.WhiteSmoke;
            this.cmdLeave.Location = new System.Drawing.Point(352, 601);
            this.cmdLeave.Name = "cmdLeave";
            this.cmdLeave.Size = new System.Drawing.Size(104, 66);
            this.cmdLeave.TabIndex = 5;
            this.cmdLeave.Text = "Leave ";
            this.cmdLeave.UseVisualStyleBackColor = false;
            this.cmdLeave.Visible = false;
            this.cmdLeave.Click += new System.EventHandler(this.cmdLeave_Click);
            // 
            // MuteMic
            // 
            this.MuteMic.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.MuteMic.AutoSize = true;
            this.MuteMic.Location = new System.Drawing.Point(753, 62);
            this.MuteMic.Name = "MuteMic";
            this.MuteMic.Size = new System.Drawing.Size(67, 17);
            this.MuteMic.TabIndex = 10;
            this.MuteMic.Text = "MuteMic";
            this.MuteMic.UseVisualStyleBackColor = true;
            this.MuteMic.CheckedChanged += new System.EventHandler(this.MuteMic_CheckedChanged_1);
            // 
            // chkPreview
            // 
            this.chkPreview.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.chkPreview.Appearance = System.Windows.Forms.Appearance.Button;
            this.chkPreview.Location = new System.Drawing.Point(616, 46);
            this.chkPreview.Name = "chkPreview";
            this.chkPreview.Size = new System.Drawing.Size(112, 23);
            this.chkPreview.TabIndex = 13;
            this.chkPreview.Text = "Toggle Preview";
            this.chkPreview.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.chkPreview.UseVisualStyleBackColor = true;
            this.chkPreview.CheckedChanged += new System.EventHandler(this.chkPreview_CheckedChanged);
            // 
            // chkLayout
            // 
            this.chkLayout.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.chkLayout.Appearance = System.Windows.Forms.Appearance.Button;
            this.chkLayout.AutoSize = true;
            this.chkLayout.Location = new System.Drawing.Point(510, 46);
            this.chkLayout.Name = "chkLayout";
            this.chkLayout.Size = new System.Drawing.Size(85, 23);
            this.chkLayout.TabIndex = 15;
            this.chkLayout.Text = "Toggle Layout";
            this.chkLayout.UseVisualStyleBackColor = true;
            this.chkLayout.CheckedChanged += new System.EventHandler(this.chkLayout_CheckedChanged);
            // 
            // chkMuteVideo
            // 
            this.chkMuteVideo.AutoSize = true;
            this.chkMuteVideo.Location = new System.Drawing.Point(751, 18);
            this.chkMuteVideo.Name = "chkMuteVideo";
            this.chkMuteVideo.Size = new System.Drawing.Size(77, 17);
            this.chkMuteVideo.TabIndex = 19;
            this.chkMuteVideo.Text = "MuteVideo";
            this.chkMuteVideo.UseVisualStyleBackColor = true;
            this.chkMuteVideo.CheckedChanged += new System.EventHandler(this.chkMuteVideo_CheckedChanged_1);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label15);
            this.panel1.Controls.Add(this.label14);
            this.panel1.Controls.Add(this.txtTenantPrefix);
            this.panel1.Controls.Add(this.btnDelRoom);
            this.panel1.Controls.Add(this.txtPublicRoomUrl);
            this.panel1.Controls.Add(this.btnLogout);
            this.panel1.Controls.Add(this.btnSubmitUser);
            this.panel1.Controls.Add(this.btnCreateRoom);
            this.panel1.Controls.Add(this.txtBxPwd);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.txtBxUsrNm);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.txtBxUserURI);
            this.panel1.Location = new System.Drawing.Point(897, 188);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(337, 267);
            this.panel1.TabIndex = 23;
            this.panel1.Visible = false;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(3, 195);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(144, 13);
            this.label15.TabIndex = 55;
            this.label15.Text = "Tenant Prefix to CreateRoom";
            // 
            // label14
            // 
            this.label14.Location = new System.Drawing.Point(0, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(100, 23);
            this.label14.TabIndex = 0;
            // 
            // txtTenantPrefix
            // 
            this.txtTenantPrefix.Location = new System.Drawing.Point(153, 192);
            this.txtTenantPrefix.Name = "txtTenantPrefix";
            this.txtTenantPrefix.Size = new System.Drawing.Size(48, 20);
            this.txtTenantPrefix.TabIndex = 53;
            // 
            // btnDelRoom
            // 
            this.btnDelRoom.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnDelRoom.Location = new System.Drawing.Point(4, 217);
            this.btnDelRoom.Name = "btnDelRoom";
            this.btnDelRoom.Size = new System.Drawing.Size(113, 26);
            this.btnDelRoom.TabIndex = 51;
            this.btnDelRoom.Text = "Delete Room";
            this.btnDelRoom.UseVisualStyleBackColor = false;
            this.btnDelRoom.Click += new System.EventHandler(this.btnDelRoom_Click);
            // 
            // txtPublicRoomUrl
            // 
            this.txtPublicRoomUrl.Location = new System.Drawing.Point(133, 221);
            this.txtPublicRoomUrl.Name = "txtPublicRoomUrl";
            this.txtPublicRoomUrl.Size = new System.Drawing.Size(174, 20);
            this.txtPublicRoomUrl.TabIndex = 51;
            // 
            // btnLogout
            // 
            this.btnLogout.Location = new System.Drawing.Point(190, 143);
            this.btnLogout.Name = "btnLogout";
            this.btnLogout.Size = new System.Drawing.Size(75, 23);
            this.btnLogout.TabIndex = 38;
            this.btnLogout.Text = "Logout";
            this.btnLogout.UseVisualStyleBackColor = true;
            this.btnLogout.Click += new System.EventHandler(this.btnLogout_Click);
            // 
            // btnSubmitUser
            // 
            this.btnSubmitUser.Location = new System.Drawing.Point(99, 143);
            this.btnSubmitUser.Name = "btnSubmitUser";
            this.btnSubmitUser.Size = new System.Drawing.Size(75, 23);
            this.btnSubmitUser.TabIndex = 37;
            this.btnSubmitUser.Text = "User Login";
            this.btnSubmitUser.UseVisualStyleBackColor = true;
            this.btnSubmitUser.Visible = false;
            this.btnSubmitUser.Click += new System.EventHandler(this.btnSubmitUser_Click);
            // 
            // btnCreateRoom
            // 
            this.btnCreateRoom.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnCreateRoom.Location = new System.Drawing.Point(213, 187);
            this.btnCreateRoom.Name = "btnCreateRoom";
            this.btnCreateRoom.Size = new System.Drawing.Size(113, 28);
            this.btnCreateRoom.TabIndex = 49;
            this.btnCreateRoom.Text = "Create Public Room";
            this.btnCreateRoom.UseVisualStyleBackColor = false;
            this.btnCreateRoom.Click += new System.EventHandler(this.btnCreateRoom_Click);
            // 
            // txtBxPwd
            // 
            this.txtBxPwd.Location = new System.Drawing.Point(86, 117);
            this.txtBxPwd.MaxLength = 20;
            this.txtBxPwd.Name = "txtBxPwd";
            this.txtBxPwd.PasswordChar = '*';
            this.txtBxPwd.Size = new System.Drawing.Size(210, 20);
            this.txtBxPwd.TabIndex = 36;
            this.txtBxPwd.Text = "Password";
            this.txtBxPwd.Visible = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 120);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 35;
            this.label4.Text = "Password";
            this.label4.Visible = false;
            // 
            // txtBxUsrNm
            // 
            this.txtBxUsrNm.Location = new System.Drawing.Point(86, 76);
            this.txtBxUsrNm.Name = "txtBxUsrNm";
            this.txtBxUsrNm.Size = new System.Drawing.Size(210, 20);
            this.txtBxUsrNm.TabIndex = 34;
            this.txtBxUsrNm.Text = "UserName";
            this.txtBxUsrNm.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 33;
            this.label3.Text = "Username";
            this.label3.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 13);
            this.label2.TabIndex = 32;
            this.label2.Text = "Portal URL";
            this.label2.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(126, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 13);
            this.label1.TabIndex = 31;
            this.label1.Text = "User Login ";
            this.label1.Visible = false;
            // 
            // txtBxUserURI
            // 
            this.txtBxUserURI.Location = new System.Drawing.Point(85, 33);
            this.txtBxUserURI.Name = "txtBxUserURI";
            this.txtBxUserURI.Size = new System.Drawing.Size(210, 20);
            this.txtBxUserURI.TabIndex = 30;
            this.txtBxUserURI.Text = "http://<TenantName>.sandboxga.vidyo.com";
            this.txtBxUserURI.Visible = false;
            this.txtBxUserURI.WordWrap = false;
            // 
            // comboBoxRemoteUsers
            // 
            this.comboBoxRemoteUsers.FormattingEnabled = true;
            this.comboBoxRemoteUsers.Location = new System.Drawing.Point(83, 68);
            this.comboBoxRemoteUsers.Name = "comboBoxRemoteUsers";
            this.comboBoxRemoteUsers.Size = new System.Drawing.Size(213, 21);
            this.comboBoxRemoteUsers.TabIndex = 43;
            this.comboBoxRemoteUsers.SelectedIndexChanged += new System.EventHandler(this.comboBoxRemoteUsers_SelectedIndexChanged);
            // 
            // txtRemoteUser
            // 
            this.txtRemoteUser.Location = new System.Drawing.Point(26, 35);
            this.txtRemoteUser.Name = "txtRemoteUser";
            this.txtRemoteUser.Size = new System.Drawing.Size(129, 20);
            this.txtRemoteUser.TabIndex = 42;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(10, 77);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(62, 13);
            this.label10.TabIndex = 41;
            this.label10.Text = "Select User";
            // 
            // btnSearch
            // 
            this.btnSearch.Location = new System.Drawing.Point(161, 33);
            this.btnSearch.Name = "btnSearch";
            this.btnSearch.Size = new System.Drawing.Size(117, 23);
            this.btnSearch.TabIndex = 40;
            this.btnSearch.Text = "Search Remote User";
            this.btnSearch.UseVisualStyleBackColor = true;
            this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click);
            // 
            // btnDirect
            // 
            this.btnDirect.AccessibleRole = System.Windows.Forms.AccessibleRole.OutlineButton;
            this.btnDirect.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnDirect.Location = new System.Drawing.Point(26, 101);
            this.btnDirect.Name = "btnDirect";
            this.btnDirect.Size = new System.Drawing.Size(84, 40);
            this.btnDirect.TabIndex = 39;
            this.btnDirect.Text = "DirectCall";
            this.btnDirect.UseVisualStyleBackColor = false;
            this.btnDirect.Visible = false;
            this.btnDirect.Click += new System.EventHandler(this.btnDirect_Click);
            // 
            // btnJoin
            // 
            this.btnJoin.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnJoin.Location = new System.Drawing.Point(107, 601);
            this.btnJoin.Name = "btnJoin";
            this.btnJoin.Size = new System.Drawing.Size(119, 67);
            this.btnJoin.TabIndex = 38;
            this.btnJoin.Text = "Join Personal Room";
            this.btnJoin.UseVisualStyleBackColor = false;
            this.btnJoin.Visible = false;
            this.btnJoin.Click += new System.EventHandler(this.btnJoin_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.btnSubmitGuest);
            this.panel2.Controls.Add(this.txtBxRoomPin);
            this.panel2.Controls.Add(this.label9);
            this.panel2.Controls.Add(this.txtBxGuestNm);
            this.panel2.Controls.Add(this.label7);
            this.panel2.Controls.Add(this.txtBxGuestURI);
            this.panel2.Controls.Add(this.label6);
            this.panel2.Controls.Add(this.label5);
            this.panel2.Location = new System.Drawing.Point(896, 490);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(337, 173);
            this.panel2.TabIndex = 24;
            this.panel2.Visible = false;
            // 
            // btnSubmitGuest
            // 
            this.btnSubmitGuest.Location = new System.Drawing.Point(98, 137);
            this.btnSubmitGuest.Name = "btnSubmitGuest";
            this.btnSubmitGuest.Size = new System.Drawing.Size(117, 23);
            this.btnSubmitGuest.TabIndex = 44;
            this.btnSubmitGuest.Text = "Guest Login and Join";
            this.btnSubmitGuest.UseVisualStyleBackColor = true;
            this.btnSubmitGuest.Visible = false;
            this.btnSubmitGuest.Click += new System.EventHandler(this.btnSubmitGuest_Click);
            // 
            // txtBxRoomPin
            // 
            this.txtBxRoomPin.Location = new System.Drawing.Point(86, 111);
            this.txtBxRoomPin.Name = "txtBxRoomPin";
            this.txtBxRoomPin.Size = new System.Drawing.Size(210, 20);
            this.txtBxRoomPin.TabIndex = 43;
            this.txtBxRoomPin.Visible = false;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(11, 118);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(50, 13);
            this.label9.TabIndex = 42;
            this.label9.Text = "RoomPin";
            // 
            // txtBxGuestNm
            // 
            this.txtBxGuestNm.Location = new System.Drawing.Point(90, 73);
            this.txtBxGuestNm.Name = "txtBxGuestNm";
            this.txtBxGuestNm.Size = new System.Drawing.Size(205, 20);
            this.txtBxGuestNm.TabIndex = 41;
            this.txtBxGuestNm.Text = "Guest User";
            this.txtBxGuestNm.Visible = false;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 76);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(63, 13);
            this.label7.TabIndex = 40;
            this.label7.Text = "GuestName";
            this.label7.Visible = false;
            // 
            // txtBxGuestURI
            // 
            this.txtBxGuestURI.Location = new System.Drawing.Point(86, 36);
            this.txtBxGuestURI.Name = "txtBxGuestURI";
            this.txtBxGuestURI.Size = new System.Drawing.Size(209, 20);
            this.txtBxGuestURI.TabIndex = 37;
            this.txtBxGuestURI.Text = "http://<tenantname>.sandboxga.vidyo.com/flex.html?roomdirect.html&key=XXXXXXX";
            this.txtBxGuestURI.Visible = false;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(2, 36);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(82, 13);
            this.label6.TabIndex = 1;
            this.label6.Text = "Portal roomURL";
            this.label6.Visible = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(122, 11);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(64, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "Guest Login";
            this.label5.Visible = false;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "User Login",
            "Guest Login"});
            this.comboBox1.Location = new System.Drawing.Point(1002, 161);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(170, 21);
            this.comboBox1.TabIndex = 47;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(929, 169);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(66, 13);
            this.label11.TabIndex = 46;
            this.label11.Text = " Login Mode";
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.panel3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.panel3.Controls.Add(this.btnCancelDirect);
            this.panel3.Controls.Add(this.label8);
            this.panel3.Controls.Add(this.label10);
            this.panel3.Controls.Add(this.comboBoxRemoteUsers);
            this.panel3.Controls.Add(this.txtRemoteUser);
            this.panel3.Controls.Add(this.btnSearch);
            this.panel3.Controls.Add(this.btnDirect);
            this.panel3.Location = new System.Drawing.Point(908, 672);
            this.panel3.Margin = new System.Windows.Forms.Padding(4);
            this.panel3.Name = "panel3";
            this.panel3.Padding = new System.Windows.Forms.Padding(1);
            this.panel3.Size = new System.Drawing.Size(306, 158);
            this.panel3.TabIndex = 0;
            this.panel3.Visible = false;
            // 
            // btnCancelDirect
            // 
            this.btnCancelDirect.AccessibleRole = System.Windows.Forms.AccessibleRole.OutlineButton;
            this.btnCancelDirect.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnCancelDirect.Location = new System.Drawing.Point(161, 101);
            this.btnCancelDirect.Name = "btnCancelDirect";
            this.btnCancelDirect.Size = new System.Drawing.Size(84, 40);
            this.btnCancelDirect.TabIndex = 45;
            this.btnCancelDirect.Text = "Cancel DirectCall";
            this.btnCancelDirect.UseVisualStyleBackColor = false;
            this.btnCancelDirect.Visible = false;
            this.btnCancelDirect.Click += new System.EventHandler(this.btnCancelDirect_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(108, 18);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(61, 13);
            this.label8.TabIndex = 44;
            this.label8.Text = "Direct Call  ";
            this.label8.Visible = false;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panel4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.panel4.Controls.Add(this.label13);
            this.panel4.Controls.Add(this.label12);
            this.panel4.Controls.Add(this.cmbBxRemoteShares);
            this.panel4.Controls.Add(this.cmbBxLocalShares);
            this.panel4.Controls.Add(this.btnRequest);
            this.panel4.Controls.Add(this.chkLayout);
            this.panel4.Controls.Add(this.chkPreview);
            this.panel4.Controls.Add(this.chkMuteVideo);
            this.panel4.Controls.Add(this.chkMuteSpeaker);
            this.panel4.Controls.Add(this.MuteMic);
            this.panel4.Location = new System.Drawing.Point(13, 721);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(859, 109);
            this.panel4.TabIndex = 48;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(322, 29);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(75, 13);
            this.label13.TabIndex = 28;
            this.label13.Text = "Remote Share";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(91, 29);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(64, 13);
            this.label12.TabIndex = 27;
            this.label12.Text = "Local Share";
            // 
            // cmbBxRemoteShares
            // 
            this.cmbBxRemoteShares.FormattingEnabled = true;
            this.cmbBxRemoteShares.Location = new System.Drawing.Point(252, 48);
            this.cmbBxRemoteShares.Name = "cmbBxRemoteShares";
            this.cmbBxRemoteShares.Size = new System.Drawing.Size(230, 21);
            this.cmbBxRemoteShares.TabIndex = 22;
            this.cmbBxRemoteShares.DropDown += new System.EventHandler(this.cmbBxRemoteShares_DropDown);
            this.cmbBxRemoteShares.SelectedIndexChanged += new System.EventHandler(this.cmbBxRemoteShares_SelectedIndexChanged);
            // 
            // cmbBxLocalShares
            // 
            this.cmbBxLocalShares.FormattingEnabled = true;
            this.cmbBxLocalShares.Location = new System.Drawing.Point(13, 48);
            this.cmbBxLocalShares.Name = "cmbBxLocalShares";
            this.cmbBxLocalShares.Size = new System.Drawing.Size(218, 21);
            this.cmbBxLocalShares.TabIndex = 21;
            this.cmbBxLocalShares.DropDown += new System.EventHandler(this.cmbBxLocalShares_DropDown);
            this.cmbBxLocalShares.SelectedIndexChanged += new System.EventHandler(this.cmbBxLocalShares_SelectedIndexChanged);
            // 
            // btnRequest
            // 
            this.btnRequest.Location = new System.Drawing.Point(3, 3);
            this.btnRequest.Name = "btnRequest";
            this.btnRequest.Size = new System.Drawing.Size(75, 23);
            this.btnRequest.TabIndex = 20;
            this.btnRequest.Text = "Request";
            this.btnRequest.UseVisualStyleBackColor = true;
            this.btnRequest.Visible = false;
            this.btnRequest.Click += new System.EventHandler(this.btnRequest_Click);
            // 
            // RoomInfo
            // 
            this.RoomInfo.Controls.Add(this.txtRoomId);
            this.RoomInfo.Controls.Add(this.txtRoomExtension);
            this.RoomInfo.Controls.Add(this.labelRoomExtension);
            this.RoomInfo.Location = new System.Drawing.Point(493, 609);
            this.RoomInfo.Name = "RoomInfo";
            this.RoomInfo.Size = new System.Drawing.Size(248, 41);
            this.RoomInfo.TabIndex = 50;
            this.RoomInfo.Visible = false;
            // 
            // txtRoomId
            // 
            this.txtRoomId.Enabled = false;
            this.txtRoomId.Location = new System.Drawing.Point(182, 12);
            this.txtRoomId.Name = "txtRoomId";
            this.txtRoomId.Size = new System.Drawing.Size(63, 20);
            this.txtRoomId.TabIndex = 52;
            this.txtRoomId.Visible = false;
            // 
            // txtRoomExtension
            // 
            this.txtRoomExtension.Enabled = false;
            this.txtRoomExtension.Location = new System.Drawing.Point(105, 12);
            this.txtRoomExtension.Name = "txtRoomExtension";
            this.txtRoomExtension.Size = new System.Drawing.Size(71, 20);
            this.txtRoomExtension.TabIndex = 1;
            this.txtRoomExtension.Visible = false;
            // 
            // labelRoomExtension
            // 
            this.labelRoomExtension.AutoSize = true;
            this.labelRoomExtension.Location = new System.Drawing.Point(13, 15);
            this.labelRoomExtension.Name = "labelRoomExtension";
            this.labelRoomExtension.Size = new System.Drawing.Size(84, 13);
            this.labelRoomExtension.TabIndex = 0;
            this.labelRoomExtension.Text = "Room Extension";
            this.labelRoomExtension.Visible = false;
            // 
            // btnJoinPublicRoom
            // 
            this.btnJoinPublicRoom.BackColor = System.Drawing.Color.WhiteSmoke;
            this.btnJoinPublicRoom.Enabled = false;
            this.btnJoinPublicRoom.Location = new System.Drawing.Point(236, 601);
            this.btnJoinPublicRoom.Name = "btnJoinPublicRoom";
            this.btnJoinPublicRoom.Size = new System.Drawing.Size(105, 67);
            this.btnJoinPublicRoom.TabIndex = 52;
            this.btnJoinPublicRoom.Text = "Join Public Room";
            this.btnJoinPublicRoom.UseVisualStyleBackColor = false;
            this.btnJoinPublicRoom.Visible = false;
            this.btnJoinPublicRoom.Click += new System.EventHandler(this.btnJoinPublicRoom_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1235, 842);
            this.Controls.Add(this.btnJoinPublicRoom);
            this.Controls.Add(this.panel4);
            this.Controls.Add(this.RoomInfo);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btnJoin);
            this.Controls.Add(this.cmdLeave);
            this.Controls.Add(this.pnlVideoArea);
            this.Controls.Add(this.listBox1);
            this.Name = "Form1";
            this.Text = "VidyoSample";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            this.RoomInfo.ResumeLayout(false);
            this.RoomInfo.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Panel pnlVideoArea;
        private System.Windows.Forms.Button cmdLeave;
        private System.Windows.Forms.CheckBox chkMuteSpeaker;
        private System.Windows.Forms.CheckBox MuteMic;
        private System.Windows.Forms.CheckBox chkPreview;
        private System.Windows.Forms.CheckBox chkLayout;
        private System.Windows.Forms.Timer tmrSubscribe;
        private System.Windows.Forms.CheckBox chkMuteVideo;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox txtBxPwd;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtBxUsrNm;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtBxUserURI;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox txtBxGuestNm;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtBxGuestURI;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtBxRoomPin;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnSubmitUser;
        private System.Windows.Forms.Button btnSubmitGuest;
        private System.Windows.Forms.Button btnSearch;
        private System.Windows.Forms.Button btnDirect;
        private System.Windows.Forms.Button btnJoin;
        private System.Windows.Forms.ComboBox comboBoxRemoteUsers;
        private System.Windows.Forms.TextBox txtRemoteUser;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Button btnCancelDirect;
        private System.Windows.Forms.Button btnLogout;
        private System.Windows.Forms.Button btnRequest;
        private System.Windows.Forms.ComboBox cmbBxRemoteShares;
        private System.Windows.Forms.ComboBox cmbBxLocalShares;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button btnCreateRoom;
        private System.Windows.Forms.Panel RoomInfo;
        private System.Windows.Forms.TextBox txtRoomExtension;
        private System.Windows.Forms.Label labelRoomExtension;
        private System.Windows.Forms.Button btnDelRoom;
        private System.Windows.Forms.TextBox txtRoomId;
        private System.Windows.Forms.TextBox txtPublicRoomUrl;
        private System.Windows.Forms.Button btnJoinPublicRoom;
        private System.Windows.Forms.TextBox txtTenantPrefix;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
    }
}

